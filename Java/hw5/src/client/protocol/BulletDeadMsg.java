package client.protocol;

import client.Bullet;
import client.Client;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;


public class BulletDeadMsg implements Msg {
    private Client player;
    private int tank_id;
    private int id;

    public BulletDeadMsg(int tankId, int id){
        this.tank_id = tankId;
        this.id = id;
    }

    public BulletDeadMsg(Client p){
        this.player = p;
    }

    @Override
    public void send(DatagramSocket ds, String IP, int UDP_Port) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try {
            dos.writeInt(Msg.BULLET_DEAD);
            dos.writeInt(tank_id);
            dos.writeInt(id);
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
        try{
            int tankId = dis.readInt();
            int id = dis.readInt();
            for(Bullet b : player.getBullets()){
                if(tankId == player.getMyTank().getID() && id == b.getID()){
                    b.setLive(false);
                    break;
                }
            }
        }catch (IOException e) {
            e.printStackTrace();
        }
    }
}
