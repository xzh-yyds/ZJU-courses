package client.protocol;

import client.Client;
import client.Direction;
import client.Tank;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;


public class TankCreateMsg implements Msg{
    private Tank tank;
    private Client player;

    public TankCreateMsg(Tank tank){
        this.tank = tank;
    }

    public TankCreateMsg(Client p){
        this.player = p;
    }

    public void send(DatagramSocket ds, String IP, int UDP_Port){
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try {
            dos.writeInt(Msg.TANK_CREATE);
            dos.writeInt(tank.getID());
            dos.writeInt(tank.get_x());
            dos.writeInt(tank.get_y());
            dos.writeInt(tank.get_mvdrc().ordinal());
            dos.writeUTF(tank.get_name());
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

    public void parse(DataInputStream dis){
        try{
            int id = dis.readInt();
            if(id == this.player.getMyTank().getID()){
                return;
            }
            int x = dis.readInt();
            int y = dis.readInt();
            Direction mv_drc = Direction.values()[dis.readInt()];
            String tankName = dis.readUTF();
            Tank newTank = new Tank(tankName, x, y, mv_drc, this.player);
            newTank.setID(id);
            this.player.getTanks().add(newTank);

            TankExistMsg msg = new TankExistMsg(this.player.getMyTank());
            this.player.get_nc().send(msg);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
