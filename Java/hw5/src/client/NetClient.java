package client;

import client.protocol.*;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.Socket;

public class NetClient {
    private static final int BAOS_SIZE = 128;
    private final Client player;
    private int UDP_PORT;
    private String SERVER_IP;
    private int SERVER_UDP_PORT;
    private int TANK_DEAD_UDP_PORT;
    private DatagramSocket ds = null;

    private final int BUF_LEN = 1024;

    public NetClient(Client p){
        this.player = p;
        try{
            this.UDP_PORT = getRandomUDPPort();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public void connect(String ip, int port){
        SERVER_IP = ip;
        Socket s = null;
        try {
            ds = new DatagramSocket(UDP_PORT);
            //create UDP socket
            try{
                s = new Socket(ip, port);
                //create TCP socket
            }catch (Exception e1){
                player.getServerUnstartedDlg().setVisible(true);
            }
            assert s != null;
            DataOutputStream dos = new DataOutputStream(s.getOutputStream());
            dos.writeInt(UDP_PORT);
            //send UDP port to server
            DataInputStream dis = new DataInputStream(s.getInputStream());
            int id = dis.readInt();
            this.SERVER_UDP_PORT = dis.readInt();
            this.TANK_DEAD_UDP_PORT = dis.readInt();
            player.getMyTank().setID(id);
            System.out.println("Connect to server successfully");
        }catch (IOException e) {
            e.printStackTrace();
        }finally {
            try{
                if(s != null) s.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        new Thread(new UDPThread()).start();
        TankCreateMsg msg = new TankCreateMsg(player.getMyTank());
        send(msg);
    }

    private int getRandomUDPPort(){
        return 55558 + (int)(Math.random() * 9000);
    }

    public void send(Msg msg){
        msg.send(ds, SERVER_IP, SERVER_UDP_PORT);
    }

    public void sendDisconnectMsg(){
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try {
            dos.writeInt(UDP_PORT);
        }catch (IOException e) {
            e.printStackTrace();
        }finally {
            try {
                dos.close();
                baos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        byte[] buf = baos.toByteArray();
        try{
            DatagramPacket dp = new DatagramPacket(buf, buf.length, new InetSocketAddress(SERVER_IP, TANK_DEAD_UDP_PORT));
            ds.send(dp);
        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    public class UDPThread implements Runnable{
        byte[] buf = new byte[BUF_LEN];

        @Override
        public void run() {
            while(null != ds){
                DatagramPacket dp = new DatagramPacket(buf, buf.length);
                try{
                    ds.receive(dp);
                    parse(dp);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private void parse(DatagramPacket dp) {
            ByteArrayInputStream bais = new ByteArrayInputStream(buf, 0, dp.getLength());
            DataInputStream dis = new DataInputStream(bais);
            int msg_type = 0;
            try {
                msg_type = dis.readInt();
            } catch (IOException e) {
                e.printStackTrace();
            }
            Msg msg;
            switch (msg_type){
                case Msg.TANK_CREATE :
                    msg = new TankCreateMsg(player);
                    msg.parse(dis);
                    break;
                case  Msg.TANK_MOVE :
                    msg = new TankMoveMsg(player);
                    msg.parse(dis);
                    break;
                case Msg.BULLET_CREATE:
                    msg = new BulletCreateMsg(player);
                    msg.parse(dis);
                    break;
                case Msg.TANK_DEAD:
                    msg = new TankDeadMsg(player);
                    msg.parse(dis);
                    break;
                case Msg.BULLET_DEAD:
                    msg = new BulletDeadMsg(player);
                    msg.parse(dis);
                    break;
                case Msg.TANK_EXIST:
                    msg = new TankExistMsg(player);
                    msg.parse(dis);
                    break;
                case Msg.TANK_INJURED:
                    msg = new TankInjuredMsg(player);
                    msg.parse(dis);
                    break;
            }
        }
    }
}
