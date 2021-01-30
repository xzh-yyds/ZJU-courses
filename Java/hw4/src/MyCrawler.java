import edu.uci.ics.crawler4j.crawler.Page;
import edu.uci.ics.crawler4j.crawler.WebCrawler;
import edu.uci.ics.crawler4j.parser.HtmlParseData;
import edu.uci.ics.crawler4j.url.WebURL;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

public class MyCrawler extends WebCrawler {

    private final static Pattern FILTERS = Pattern.compile(".*(\\.(css|js|gif|jpg"
            + "|png|mp3|mp4|zip|gz))$");

    @Override
    public boolean shouldVisit(Page referringPage, WebURL url) {
        String href = url.getURL().toLowerCase();
        return !FILTERS.matcher(href).matches()
                && href.startsWith("http://e.dangdang.com/products/")
                && href.endsWith(".html");
    }

    @Override
    public void visit(Page page) {
        String url = page.getWebURL().getURL();
        System.out.println("URL: " + url);

        if (page.getParseData() instanceof HtmlParseData) {
            HtmlParseData htmlParseData = (HtmlParseData) page.getParseData();
            String html = htmlParseData.getHtml();

            try {
                html_parse(html);
            } catch (IOException e) {
                e.printStackTrace();
            }

            // System.out.println("Html length: " + html.length());
        }
    }

    int page_cnt = 0;

    public void html_parse(String html) throws IOException {
        page_cnt++;
        Document doc = Jsoup.parse(html);
        Elements titles = doc.getElementsByClass("title_words");
        String title = titles.first().text();
        String synopsis = doc.getElementById("newEditModule").text();
        Element catalog = doc.getElementById("catalog_title");
        String price = "";

        price = doc.getElementsByClass("normal_price").first().getElementsByTag("i").first().text();

        String cover_img = doc.getElementsByClass("bookCover_area").first().getElementsByTag("img").first().attr("src");
        String author = doc.getElementById("author").getElementsByTag("span").first().getElementsByTag("a").text();
        String publisher = doc.getElementById("publisher").getElementsByTag("span").first().getElementsByTag("a").first().text();

        List<String> cata_ents = new ArrayList();
        for(Element e: catalog.getElementsByTag("p")){
            cata_ents.add(e.text());
        }
        String[] cata = cata_ents.toArray(new String[cata_ents.size()]);

        Book book = new Book(page_cnt, title, synopsis, cata, price, cover_img, author, publisher);
        //System.out.println(book.toString());
        book.save_as("./books");
        System.out.println("page count: " + page_cnt);
    }
}