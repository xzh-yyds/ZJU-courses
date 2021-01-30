package client;

public class HitEvent {
    private Bullet src;

    public HitEvent(Bullet b){
        this.src = b;
    }

    public Bullet getSrc(){
        return src;
    }

    public void setSrc(Bullet b){
        this.src = b;
    }
}
