package client;

import client.protocol.BulletDeadMsg;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;

public class Client{
    public final int GAME_W = 800;
    public final int GAME_H = 600;

    private Tank mytank;
    private final List<Tank> tanks = new ArrayList<>();
    private final List<Bullet> bullets = new ArrayList<>();

    private final NetClient nc = new NetClient(this);
    private final ConnectDlg connectDlg = new ConnectDlg();
    private final GameOverDlg gameOverDlg = new GameOverDlg();
    private final ServerUnstartedDlg serverUnstartDlg = new ServerUnstartedDlg();

    public List<Bullet> getBullets(){
        return bullets;
    }

    class ConnectDlg extends JDialog{
        JButton btn = new JButton("connect");
        JTextField tf_ip = new JTextField("127.0.0.1", 15);
        //JTextField tf_port = new JTextField("20086", 6);
        JTextField tf_tkname = new JTextField("myTank", 8);

        public ConnectDlg() {
            this.setLayout(new FlowLayout());
            this.add(new JLabel("Server IP:"));
            this.add(tf_ip);
            //this.add(new JLabel("port"));
            //this.add(tf_port);
            this.add(new JLabel("Your tank's name:"));
            this.add(tf_tkname);
            this.add(btn);
            this.setLocation(500, 400);
            this.pack();
            this.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    System.exit(0);
                }
            });
            btn.addActionListener(e -> {
                String ip = tf_ip.getText().trim();
                String tkname = tf_tkname.getText().trim();
                //int port = Integer.parseInt(tf_port.getText().trim());
                int port = 20086;
                mytank = new Tank(tkname, 50 + (int)(Math.random() * (GAME_W - 100)), 50 + (int)(Math.random() * (GAME_H - 100)), Direction.STOP, Client.this);
                nc.connect(ip, port);
                setVisible(false);
            });
        }
    }

    class GameOverDlg extends JDialog {
        JButton b = new JButton("exit");
        public GameOverDlg() {
            this.setLayout(new FlowLayout());
            this.add(new Label("Game Over~"));
            this.add(b);
            this.setLocation(500, 400);
            this.pack();
            this.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    System.exit(0);
                }
            });
            b.addActionListener(e -> System.exit(0));
        }
    }

    class ServerUnstartedDlg extends JDialog{
        Button btn = new Button("ok");
        public ServerUnstartedDlg() {
            this.setLayout(new FlowLayout());
            this.add(new Label("The server has not been opened yet..."));
            this.add(btn);
            this.setLocation(500, 400);
            this.pack();
            this.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    System.exit(0);
                }
            });
            btn.addActionListener(e -> System.exit(0));
        }
    }

    class GUI extends JFrame{
        class PaintThread implements Runnable{
            public void run(){
                while(true){
                    repaint();
                    try{
                        Thread.sleep(50);
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }
                }
            }
        }

        void launch(){
            this.setLocation(400, 300);
            this.setSize(GAME_W, GAME_H);
            this.setTitle("Tank Client");
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setResizable(false);
            this.setBackground(Color.yellow);
            this.addKeyListener(new KeyMonitor());
            this.setVisible(true);
            new Thread(new PaintThread()).start();
            connectDlg.setVisible(true);
        }

        public void paint(Graphics g){
            g.clearRect(0, 0, this.getWidth(), this.getHeight());
            g.drawString("tanks count:" + tanks.size(), 10, 90);
            for(Bullet b: bullets){
                if(b.hit(mytank)){
                    BulletDeadMsg msg = new BulletDeadMsg(b.getTankID(), b.getID());
                    nc.send(msg);
                }
                b.draw(g);
            }
            for(Tank t: tanks){
                t.draw(g);
            }
            if(null != mytank){
                mytank.draw(g);
            }
        }
    }

    class KeyMonitor extends KeyAdapter{
        @Override
        public void keyReleased(KeyEvent e) {
            mytank.keyReleased(e);
        }

        @Override
        public void keyPressed(KeyEvent e) {
            mytank.keyPressed(e);
        }
    }

    public void gameOver(){
        this.gameOverDlg.setVisible(true);
    }

    public ServerUnstartedDlg getServerUnstartedDlg() {
        return serverUnstartDlg;
    }

    public List<Tank> getTanks(){
        return tanks;
    }
    public Tank getMyTank(){
        return mytank;
    }
    public NetClient get_nc() {
        return nc;
    }

    public static void main(String[] args){
        Client player = new Client();
        GUI gui = player.new GUI();
        gui.launch();
    }
}
