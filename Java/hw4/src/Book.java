import java.io.*;
import java.nio.file.Paths;

public class Book {
    String title;
    String synopsis;
    String[] catalog;
    String price;
    String cover;
    String publisher;
    String author;
    int no;

    Book(int _no, String _title, String _synopsis, String[] _catalog,
         String _price, String _cover, String _author, String _publisher){
        title = _title;
        synopsis = _synopsis;
        catalog = _catalog;
        price = _price;
        cover = _cover;
        publisher = _publisher;
        no = _no;
    }

    @Override
    public String toString(){
        String cata = "";
        for(String ent: catalog){
            cata += ent + "\n";
        }
        if(cata.endsWith("\n")){
            cata = cata.substring(0, cata.length()-1);
        }
        return "<title>" + title + "</title>" + "\n"
                + String.format("<author>%s</author>\n", author)
                + "<price>" + price + "</price>" + "\n"
                + "<cover>" + cover + "</cover>" + "\n"
                + "<synopsis>" + synopsis + "</synopsis>" + "\n"
                + "<publisher>" + publisher + "</publisher>" + "\n"
                + "<catalog>" + cata + "</catalog>";
    }

    public void save_as(String path) throws IOException {
        String p = Paths.get(path, String.format("%03d", no)).toString();
        System.out.println(p);
        File f = new File(p);
        if(!f.exists())
            f.createNewFile();
        FileOutputStream of = new FileOutputStream(f);
        of.write(toString().getBytes());
        of.flush();
        of.close();
    }
}
