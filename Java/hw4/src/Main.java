import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        String prom =
                "Please input your choice:\n"
                + "\t0. exit\n"
                + "\t1. Crawl\n"
                + "\t2. Search\n-> ";
        System.out.print(prom);
        Scanner sc = new Scanner(System.in);
        int chc = sc.nextInt();
        while(chc != 0){
            if(chc == 1){
                Controller.main(new String[0]);
            }
            else if(chc == 2){
                Index.main(new String[0]);
            }
            else{
                System.out.println("Illegal input!");
            }
            System.out.print(prom);
            chc = sc.nextInt();
        }
        System.out.println("Bye~");
    }
}
