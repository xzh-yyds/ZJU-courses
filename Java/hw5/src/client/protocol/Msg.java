package client.protocol;

import java.io.DataInputStream;
import java.net.DatagramSocket;

public interface Msg {
    int BAOS_SIZE = 128;
    int TANK_CREATE = 1;
    int TANK_MOVE = 2;
    int BULLET_CREATE = 3;
    int TANK_DEAD = 4;
    int BULLET_DEAD = 5;
    int TANK_EXIST = 6;
    int TANK_INJURED = 7;

    void send(DatagramSocket ds, String IP, int UDP_Port);
    void parse(DataInputStream dis);
}


