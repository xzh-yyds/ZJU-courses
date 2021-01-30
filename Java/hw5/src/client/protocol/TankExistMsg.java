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


public class TankExistMsg implements Msg {
    private Tank tank;
    private Client player;

    public TankExistMsg(Tank tank){
        this.tank = tank;
    }

    public TankExistMsg(Client p){
        this.player = p;
    }

    @Override
    public void send(DatagramSocket ds, String IP, int UDP_Port) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream(BAOS_SIZE);
        DataOutputStream dos = new DataOutputStream(baos);
        try{
            dos.writeInt(Msg.TANK_EXIST);
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

    @Override
    public void parse(DataInputStream dis) {
        try{
            int id = dis.readInt();
            if(id == player.getMyTank().getID()){
                return;
            }
            boolean existed = false;
            for(Tank t : player.getTanks()){
                if(id == t.getID()){
                    existed = true;
                    break;
                }
            }
            if(!existed){
                int x = dis.readInt();
                int y = dis.readInt();
                Direction dir = Direction.values()[dis.readInt()];
                String name = dis.readUTF();
                Tank existed_tk = new Tank(name, x, y, dir, player);
                existed_tk.setID(id);
                player.getTanks().add(existed_tk);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
