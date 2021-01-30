package client;

import java.awt.*;

public class Bullet {
    private static final int vx = 10;
    private static final int vy = 10;
    public static final int DMG = 20;
    private static int ID = 10;

    private int id;
    private int x, y;
    private final int tank_id;
    private Client player;
    private final Direction drc;
    private boolean live = true;

    private static final String img_path = "client/images/bullet.png";
    private static final Image image = Toolkit.getDefaultToolkit()
            .getImage(Bullet.class.getClassLoader().getResource(img_path));;
    private static int WIDTH = -1;
    private static int HEIGHT = -1;

    public Bullet(int tank_id, int _x, int _y, Direction d){
        this.tank_id = tank_id;
        this.x = _x;
        this.y = _y;
        this.drc = d;
        this.id = ID++;
    }

    public Bullet(int _id, int _x, int _y, Direction d, Client p){
        this(_id, _x, _y, d);
        this.player = p;
    }

    public void draw(Graphics g){
        if(!live) {
            player.getBullets().remove(this);
            return;
        }
        g.drawImage(image, x, y, null);
        move();
    }

    public void move(){
        switch (drc){
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

        if(x<0 || y<0 || x>player.GAME_W || y>player.GAME_H){
            live = false;
        }
    }

    public Rectangle getArea(){
        return new Rectangle(x, y, image.getWidth(null), image.getHeight(null));
    }

    public boolean hit(Tank t){
        if(this.tank_id == t.getID())
            return false;
        if(this.live && t.isLive() && getArea().intersects(t.getArea())){
            this.live = false;
            t.got_hit(new HitEvent(this));
            return true;
        }
        return false;
    }

    public int getID(){
        return id;
    }

    public void setID(int _id){
        this.id = _id;
    }

    public int get_x(){
        return this.x;
    }
    public int get_y(){
        return this.y;
    }

    public void setLive(boolean _live){
        this.live = _live;
    }

    public Direction getDirc(){
        return this.drc;
    }

    public int getTankID(){
        return this.tank_id;
    }

    public static int get_width(){
        while(WIDTH == -1){
            WIDTH = image.getWidth(null);
        }
        return WIDTH;
    }

    public static int get_height(){
        while(HEIGHT == -1){
            HEIGHT = image.getWidth(null);
        }
        return HEIGHT;
    }
}
