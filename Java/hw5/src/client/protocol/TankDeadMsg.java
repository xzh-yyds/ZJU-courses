package client.protocol;

import client.Client;
import client.Tank;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;

public class TankDeadMsg implements Msg {
    private int msg_type = Msg.TANK_DEAD;
    private int tank_id;
    private Client player;

    public TankDeadMsg(int id){
        this.tank_id = id;
    }

    public TankDeadMsg(Client p){
        this.player = p;
    }

    @Override
    public void send(DatagramSocket ds, String IP, int UDP_Port) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try {
            dos.writeInt(msg_type);
            dos.writeInt(tank_id);
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
            if(tankId == this.player.getMyTank().getID()){
                return;
            }
            for(Tank t : player.getTanks()){
                if(t.getID() == tankId){
                    t.setLive(false);
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
