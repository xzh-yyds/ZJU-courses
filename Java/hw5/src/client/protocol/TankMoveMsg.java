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

public class TankMoveMsg implements Msg {
    private int id;
    private int x, y;
    private Direction mvdrc;
    private Direction drc;
    private Client player;

    public TankMoveMsg(int _id, int _x, int _y, Direction _mvdrc, Direction _drc){
        this.id = _id;
        this.x = _x;
        this.y = _y;
        this.mvdrc = _mvdrc;
        this.drc = _drc;
    }

    public TankMoveMsg(Client p){
        this.player = p;
    }

    @Override
    public void send(DatagramSocket ds, String IP, int UDP_Port) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try {
            dos.writeInt(Msg.TANK_MOVE);
            dos.writeInt(id);
            dos.writeInt(mvdrc.ordinal());
            dos.writeInt(drc.ordinal());
            dos.writeInt(x);
            dos.writeInt(y);
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
            int id = dis.readInt();
            if(id == this.player.getMyTank().getID()){
                return;
            }
            Direction mvdrc = Direction.values()[dis.readInt()];
            Direction drc = Direction.values()[dis.readInt()];
            int x = dis.readInt();
            int y = dis.readInt();
            for(Tank t : player.getTanks()){
                if(t.getID() == id){
                    t.set_drc(drc);
                    t.set_mvdrc(mvdrc);
                    t.set_xy(x, y);
                    break;
                }
            }
        }catch (IOException e) {
            e.printStackTrace();
        }
    }
}
