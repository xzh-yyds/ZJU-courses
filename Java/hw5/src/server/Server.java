package server;

import javax.swing.*;
import java.awt.*;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
import java.text.SimpleDateFormat;
import java.time.ZoneId;
import java.util.*;
import java.util.Date;
import java.util.List;
import java.sql.*;

public class Server{
    public static int ID = 100;
    public static final int TCP_PORT = 20086;
    public static final int UDP_PORT = 20087;
    public static final int TANK_DEAD_UDP_PORT = 20088;
    static List<Player> players = new ArrayList<>();
    static final int BUF_LEN = 1024;

    static class Player{
        String ip;
        int udp_port;
        int id;

        public Player(String _ip, int _port, int _id){
            this.ip = _ip;
            this.udp_port = _port;
            this.id = _id;
        }
    }

    static class UDPThread implements Runnable{
        byte[] buf = new byte[BUF_LEN];

        @Override
        public void run(){
            DatagramSocket ds = null;
            try{
                ds = new DatagramSocket(UDP_PORT);
            }catch (SocketException e){
                e.printStackTrace();
            }

            while(ds != null){
                DatagramPacket dp = new DatagramPacket(buf, buf.length);
                try{
                    ds.receive(dp);
                    for(Player p: players){
                        dp.setSocketAddress(new InetSocketAddress(p.ip, p.udp_port));
                        ds.send(dp);
                    }
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        }
    }

    static class TankDeadUDPThread implements Runnable{
        byte[] buf = new byte[BUF_LEN];

        @Override
        public void run(){
            DatagramSocket ds = null;
            try {
                ds = new DatagramSocket(TANK_DEAD_UDP_PORT);
            }catch (SocketException e){
                e.printStackTrace();
            }

            while(ds != null){
                DatagramPacket dp = new DatagramPacket(buf, buf.length);
                ByteArrayInputStream bis = null;
                DataInputStream dis = null;
                try {
                    ds.receive(dp);
                    bis = new ByteArrayInputStream(buf, 0, dp.getLength());
                    dis = new DataInputStream(bis);
                    int dead_tank_udp_port = dis.readInt();
                    for(int i=0; i<players.size(); i++){
                        Player p = players.get(i);
                        if(p.udp_port == dead_tank_udp_port){
                            players.remove(p);
                        }
                    }
                }catch (IOException e){
                    e.printStackTrace();
                }finally {
                    if(dis != null){
                        try {
                            dis.close();
                        }catch (IOException e){
                            e.printStackTrace();
                        }
                    }
                    if(bis != null){
                        try {
                            bis.close();
                        }catch (IOException e){
                            e.printStackTrace();
                        }
                    }
                }
            }
        }
    }

    static class GUI extends JFrame{

        static final int HEIGHT= 500;
        static final int WIDTH = 500;

        class UpdateThread implements Runnable{
            public void run(){
                while (true){
                    repaint();
                    try {
                        Thread.sleep(1000);
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }
                }
            }
        }

        void launch(){
            this.setTitle("Tanks Server");
            this.setSize(WIDTH, HEIGHT);
            this.setLocation(200, 100);
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setResizable(true);
            this.getContentPane().setBackground(Color.orange);

            this.setVisible(true);
            new Thread(new UpdateThread()).start();
        }

        public void paint(Graphics g){
            g.clearRect(0, 0, this.getWidth(), this.getHeight());
            Color text_color = Color.BLACK;
            g.setColor(Color.orange);
            g.fillRect(0, 0, WIDTH, HEIGHT);
            SimpleDateFormat sdf = new SimpleDateFormat();
            sdf.applyPattern("yyyy-MM-dd HH:mm:ss");
            String time = sdf.format(new Date());
            g.setColor(text_color);
            g.drawString(time, 30, 50);

            g.drawString("Tank Client :", 30, 80);
            int y = 100;
            for (Player c : players) {
                // list all clients
                g.drawString("id: " + c.id + " - IP: " + c.ip, 30, y);
                y += 20;
            }

            y += 30;
            g.drawString("Historical Connections :", 30, y-20);
            String[] cons = Database.select();
            for (String con : cons) {
                // list all connections
                g.drawString(con, 30, y);
                y += 20;
            }
        }
    }

    static void start(){
        new Thread(new UDPThread()).start();
        new Thread(new TankDeadUDPThread()).start();

        ServerSocket ss = null;
        try {
            ss = new ServerSocket(TCP_PORT);
            System.out.println("Server started");
        }catch (IOException e){
            e.printStackTrace();
        }

        while(true){
            Socket s = null;
            try {
                assert ss != null;
                s = ss.accept();
                System.out.println("A client has connected");

                DataInputStream dis = new DataInputStream(s.getInputStream());
                String client_ip = s.getInetAddress().getHostAddress();
                int udpp = dis.readInt();
                Player p = new Player(client_ip, udpp, ID);
                players.add(p);

                String row = Database.format(ID, client_ip, udpp);
                Database.insert(row);

                DataOutputStream dos = new DataOutputStream(s.getOutputStream());
                dos.writeInt(ID++);
                dos.writeInt(Server.UDP_PORT);
                dos.writeInt(Server.TANK_DEAD_UDP_PORT);
            }catch (IOException e){
                e.printStackTrace();
            }finally {
                try {
                    if(s != null)
                        s.close();
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        }
    }

    static class Database{
        static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
        static final String url = "jdbc:mysql://182.92.71.45/java_hw5";
        static final String user = "admin";
        static final String pswd = "123456";

        static void insert(String row){
            Connection conn = null;
            Statement stmt = null;
            try{
                Class.forName(JDBC_DRIVER);
                conn = DriverManager.getConnection(url, user, pswd);
                stmt = conn.createStatement();
                String sql = "INSERT INTO connections VALUES(" + row + ");";
                stmt.executeUpdate(sql);
            }catch (SQLException | ClassNotFoundException e){
                e.printStackTrace();
            }
        }

        static String format(int id, String ip, int port){
            SimpleDateFormat sdf = new SimpleDateFormat();
            sdf.applyPattern("yyyy-MM-dd HH:mm:ss");
            String time = sdf.format(new Date());
            return id + ", '" + ip + "', " + port + ", '" + time + "'";
        }

        static String[] select(){
            Connection conn;
            Statement stmt;
            List<String> res = new ArrayList<>();

            try{
                Class.forName(JDBC_DRIVER);
                conn = DriverManager.getConnection(url, user, pswd);
                stmt = conn.createStatement();
                String sql = "SELECT * FROM connections;";
                ResultSet rs = stmt.executeQuery(sql);

                while(rs.next()){
                    String time = rs.getTimestamp("dt").toInstant().atZone(ZoneId.of("UTC-6")).toLocalDateTime().toString();
                    String row = rs.getString("ip") + ":" + rs.getInt("port") + " " + time;
                    res.add(row);
                }
            }catch (SQLException | ClassNotFoundException e){
                System.out.println("exception in sql!");
                e.printStackTrace();
            }
            return res.toArray(new String[0]);
        }
    }

    public static void main(String[] args){
        GUI gui = new GUI();
        gui.launch();
        start();
    }
}