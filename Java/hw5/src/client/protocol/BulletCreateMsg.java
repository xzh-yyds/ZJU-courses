package client.protocol;

import client.Bullet;
import client.Client;
import client.Direction;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;

public class BulletCreateMsg implements Msg {
    private Client player;
    private Bullet bullet;

    public BulletCreateMsg(Client p){
        this.player = p;
    }

    public BulletCreateMsg(Bullet b){
        this.bullet = b;
    }

    @Override
    public void send(DatagramSocket ds, String IP, int UDP_Port) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try {
            dos.writeInt(Msg.BULLET_CREATE);
            dos.writeInt(bullet.getTankID());
            dos.writeInt(bullet.getID());
            dos.writeInt(bullet.get_x());
            dos.writeInt(bullet.get_y());
            dos.writeInt(bullet.getDirc().ordinal());
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
            if(tankId == player.getMyTank().getID()){
                return;
            }
            int id = dis.readInt();
            int x = dis.readInt();
            int y = dis.readInt();
            Direction d = Direction.values()[dis.readInt()];

            Bullet b = new Bullet(tankId, x, y, d, player);
            b.setID(id);
            player.getBullets().add(b);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
