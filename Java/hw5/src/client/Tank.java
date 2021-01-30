package client;

import client.protocol.BulletCreateMsg;
import client.protocol.TankDeadMsg;
import client.protocol.TankMoveMsg;
import client.protocol.TankInjuredMsg;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.HashMap;
import java.util.Map;

public class Tank {
    private int id;
    private static final int vx = 5;
    private static final int vy = 5;

    private final String name;
    private int x, y;
    private boolean live = true;
    private Direction mv_drc = Direction.STOP;
    private Direction drc = Direction.D;
    private int HP = 100;

    private final HealthBar health_bar = new HealthBar();

    private boolean btnL, btnU, btnR, btnD;

    Client player;

    private static final Image[] images;
    private static final Map<Direction, Image> map = new HashMap<>();

    static{
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        images = new Image[]{
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/D.png")),
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/L.png")),
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/LD.png")),
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/LU.png")),
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/R.png")),
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/RD.png")),
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/RU.png")),
                toolkit.getImage(Tank.class.getClassLoader().getResource("client/images/tank/U.png"))
        };
        map.put(Direction.D,  images[0]);
        map.put(Direction.L,  images[1]);
        map.put(Direction.LD, images[2]);
        map.put(Direction.LU, images[3]);
        map.put(Direction.R,  images[4]);
        map.put(Direction.RD, images[5]);
        map.put(Direction.RU, images[6]);
        map.put(Direction.U,  images[7]);
    }

    private static int WIDTH = images[0].getWidth(null);
    private static int HEIGHT = images[0].getHeight(null);

    class HealthBar{
        int bar_w = 40;
        int bar_h = 8;
        public void draw(Graphics g) {
            Color c = g.getColor();
            g.setColor(Color.BLACK);
            g.drawRect(x, y - 15, bar_w, bar_h);
            int w = bar_w * HP / 100 ;
            g.setColor(Color.RED);
            g.fillRect(x, y - 15, w, bar_h);
            g.setColor(c);
        }
    }

    public Tank(int _x, int _y, String _name) {
        this.x = _x;
        this.y = _y;
        this.name = _name;
    }

    public Tank(String _name, int _x, int _y, Direction mv_d, Client p) {
        this(_x, _y, _name);
        this.mv_drc = mv_d;
        this.player = p;
    }

    public void draw(Graphics g){
        if(!live){
            player.getTanks().remove(this);
            return;
        }
        g.drawImage(map.get(this.drc), x, y, null);
        g.drawString(name, x, y - 20);
        health_bar.draw(g);
        move();
    }

    public void move(){
        switch(this.mv_drc) {
            case L:
                this.x -= vx;
                break;
            case LU:
                this.x -= vx;
                this.y -= vy;
                break;
            case U:
                y -= vy;
                break;
            case RU:
                x += vx;
                y -= vy;
                break;
            case R:
                x += vx;
                break;
            case RD:
                x += vx;
                y += vy;
                break;
            case D:
                y += vy;
                break;
            case LD:
                x -= vx;
                y += vy;
                break;
            case STOP:
                break;
        }
        if(this.mv_drc != Direction.STOP){
            this.drc = this.mv_drc;
        }
        if(x < 0) x = 0;
        if(y < 0) y = 0;
        if(x + WIDTH  > player.GAME_W) x = player.GAME_W - WIDTH;
        if(y + HEIGHT > player.GAME_H) y = player.GAME_H - HEIGHT;
    }

    public void keyPressed(KeyEvent ke){
        int key_code = ke.getKeyCode();
        switch (key_code){
            case KeyEvent.VK_A:
                btnL = true;
                break;
            case KeyEvent.VK_W:
                btnU = true;
                break;
            case KeyEvent.VK_D:
                btnR = true;
                break;
            case KeyEvent.VK_S:
                btnD = true;
                break;
        }
        orient();
    }

    private void orient() {
        Direction old_drc = this.mv_drc;
        int index = (btnU?8:0) + (btnL?4:0) + (btnD?2:0) + (btnR?1:0);
        Direction[] drcs = new Direction[]{
                Direction.STOP,
                Direction.R,
                Direction.D,
                Direction.RD,
                Direction.L,
                Direction.STOP,
                Direction.LD,
                Direction.STOP,
                Direction.U,
                Direction.RU,
                Direction.STOP,
                Direction.STOP,
                Direction.LU,
                Direction.STOP,
                Direction.STOP,
                Direction.STOP,
        };

        mv_drc = drcs[index];

        if(mv_drc != old_drc){
            TankMoveMsg msg = new TankMoveMsg(id, x, y, mv_drc, drc);
            player.get_nc().send(msg);
        }
    }

    public void keyReleased(KeyEvent ke){
        int key_code = ke.getKeyCode();
        switch (key_code){
            case KeyEvent.VK_J:
                fire();
                break;
            case KeyEvent.VK_A:
                btnL = false;
                break;
            case KeyEvent.VK_W:
                btnU = false;
                break;
            case KeyEvent.VK_D:
                btnR = false;
                break;
            case KeyEvent.VK_S:
                btnD = false;
                break;
        }
        orient();
    }

    public void fire(){
        if(!live) return;

        int bx = this.x + get_width()/2 - Bullet.get_width()/2;
        int by = this.y + get_height()/2 - Bullet.get_height()/2;

        Bullet b = new Bullet(this.id, bx, by, drc, player);
        this.player.getBullets().add(b);
        BulletCreateMsg msg = new BulletCreateMsg(b);
        this.player.get_nc().send(msg);
    }

    public void got_hit(HitEvent hit){
        // System.out.println("got hit");
        if(this.HP <= Bullet.DMG){
            this.live = false;
            TankDeadMsg msg = new TankDeadMsg(this.id);
            this.player.get_nc().send(msg);
            this.player.get_nc().sendDisconnectMsg();
            this.player.gameOver();
            return;
        }
        this.HP -= Bullet.DMG;
        TankInjuredMsg msg = new TankInjuredMsg(this.id, hit.getSrc());
        this.player.get_nc().send(msg);
    }

    public boolean isLive(){
        return this.live;
    }

    public void setLive(boolean l){
        this.live = l;
    }

    public int getID(){
        return this.id;
    }

    public void setID(int _id){
        this.id = _id;
    }

    public int getHealth(){
        return this.HP;
    }

    public void setHealth(int hth){
        this.HP = hth;
    }

    public Rectangle getArea(){
        return new Rectangle(x, y, images[0].getWidth(null), images[0].getWidth(null));
    }

    public static int get_width(){
        while(WIDTH == -1){
            WIDTH = images[0].getWidth(null);
        }
        return WIDTH;
    }

    public static int get_height(){
        while(HEIGHT == -1){
            HEIGHT = images[0].getHeight(null);
        }
        return HEIGHT;
    }

    public int get_x(){
        return this.x;
    }

    public int get_y(){
        return this.y;
    }

    public void set_xy(int new_x, int new_y){
        this.x = new_x;
        this.y = new_y;
    }

    public String get_name(){
        return this.name;
    }

    public Direction get_drc(){
        return this.drc;
    }

    public void set_drc(Direction new_drc){
        this.drc = new_drc;
    }

    public Direction get_mvdrc(){
        return this.mv_drc;
    }

    public void set_mvdrc(Direction new_drc){
        this.mv_drc = new_drc;
    }
}
