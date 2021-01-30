package client.protocol;

import client.Bullet;
import client.Client;
import client.Tank;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;

public class TankInjuredMsg implements Msg {
    private int tank_id;
    private Bullet bullet;
    private Client player;

    public TankInjuredMsg(int tankId, Bullet b){
        this.tank_id = tankId;
        this.bullet = b;
    }

    public TankInjuredMsg(Client p){
        this.player = p;
    }

    @Override
    public void send(DatagramSocket ds, String IP, int UDP_Port) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try{
            dos.writeInt(Msg.TANK_INJURED);
            dos.writeInt(tank_id); //id of injured tank
            dos.writeInt(bullet.get_x() - 20);
            dos.writeInt(bullet.get_y() - 20);
        } catch (IOException e) {
            e.printStackTrace();
        }
        byte[] buf = baos.toByteArray();
        try{
            DatagramPacket dp = new DatagramPacket(buf, buf.length, new InetSocketAddress(IP, UDP_Port));
            ds.send(dp);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void parse(DataInputStream dis) {
        try {
            int id = dis.readInt();
            if(id == player.getMyTank().getID()){
                return;
            }

            for(Tank t : player.getTanks()){
                if(t.getID() == id){
                    t.setHealth(t.getHealth() - Bullet.DMG);//找到扣血的坦克, 减少20滴血
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
