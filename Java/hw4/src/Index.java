import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;
import org.wltea.analyzer.lucene.IKAnalyzer;

public class Index {
    public static void main(String[] args) {
        String prom = "Please input your choice:\n"
                + "0. exit\n"
                + "1. create index\n"
                + "2. search\n-> ";
        System.out.print(prom);
        Scanner sc = new Scanner(System.in);
        int chc = sc.nextInt();
        if(chc == 0){
            System.out.println("pass");
        }
        else if(chc == 1){
            create_index("./index", "books");
        }
        else if(chc == 2){
            String fieldchcs = "Choose index field:\n"
                    + "1. title\n"
                    + "2. synopsis\n"
                    + "3. author\n"
                    + "4. publisher\n"
                    + "5. price\n-> ";

            System.out.println(fieldchcs);
            int fc = sc.nextInt();
            String[] fields = new String[]{"title", "synopsis", "author", "publisher", "price"};
            String field = fields[(fc-1)%5];

            System.out.print("Key word:\n-> ");
            String key = sc.next();

            System.out.print("count:\n-> ");
            int cnt = sc.nextInt();

            search("./index", field, key, cnt);
        }else{
            System.out.println("Illegal input!");
        }
    }

    public static void del_dir(File d){
        if(!d.isDirectory())
            return;

        File[] children = d.listFiles();
        for(File child: children){
            if(child.isDirectory())
                del_dir(child);
            else{
                if(!child.delete()){
                    System.out.println("failed to delete directory:" + child.getName());
                }
            }
        }
        if(!d.delete())
            System.out.println("failed to delete directory: " + d.getName());
    }

    public static void create_index(String path, String src){
        File d = new File(path);
        File[] files = d.listFiles();
        assert files != null;
        for(File f: files){
            if(f.isDirectory())
                del_dir(f);
            else{
                if(!f.delete()){
                    System.out.println("failed to delete directory:" + f.getName());
                }
            }
        }

        IndexWriter iw = null;
        try {
            Directory dir=FSDirectory.open(d);
            Analyzer analyzer = new IKAnalyzer();

            IndexWriterConfig conf = new IndexWriterConfig(Version.LUCENE_4_10_0, analyzer);
            iw = new IndexWriter(dir,conf); //建立IndexWriter。固定套路
            Document[] docs = get_docs(src);
            for(Document doc: docs){
                iw.addDocument(doc);
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            iw.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    static String get_file_content(String path){
        File f = new File(path);
        byte[] content = new byte[(int)f.length()];

        try {
            FileInputStream in = new FileInputStream(f);
            in.read(content);
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        String encoding = "utf-8";
        try {
            return new String(content, encoding);
        } catch (UnsupportedEncodingException e) {
            System.err.println("The OS does not support " + encoding);
            e.printStackTrace();
            return null;
        }
    }

    static String in_tag(String content, String tag){
        String left = "<" + tag + ">";
        String right = "</" + tag + ">";
        int l = content.indexOf(left) + left.length();
        int r = content.indexOf(right);
        if(l>r){
            System.out.println("no such tag?: " + tag);
            return "";
        }
        return content.substring(l, r);
    }

    static Document get_doc(String path){
        Document doc = new Document();
        String content = get_file_content(path);
        assert content != null;
        Field title = new TextField("title", in_tag(content, "title"), Field.Store.YES);
        Field synopsis = new TextField("synopsis", in_tag(content, "synopsis"), Field.Store.YES);
        Field catalog = new TextField("catalog", in_tag(content, "catalog"), Field.Store.YES);
        Field price = new TextField("price", in_tag(content, "price"), Field.Store.YES);
        Field cover = new TextField("cover", in_tag(content, "cover"), Field.Store.YES);
        Field publisher = new TextField("publisher", in_tag(content, "publisher"), Field.Store.YES);
        Field author = new TextField("author", in_tag(content, "author"), Field.Store.YES);

        doc.add(title);
        doc.add(synopsis);
        doc.add(catalog);
        doc.add(price);
        doc.add(cover);
        doc.add(publisher);
        doc.add(author);

        return doc;
    }

    static Document[] get_docs(String path){
        File dir = new File(path);
        List<Document> doc_lst = new ArrayList<>();
        File[] fs = dir.listFiles();
        for(File f: fs){
            doc_lst.add(get_doc(f.getAbsolutePath()));
        }
        return doc_lst.toArray(new Document[doc_lst.size()]);
    }

    public static void search(String filePath, String field, String key, int cnt){
        File f = new File(filePath);
        try {
            IndexSearcher searcher = new IndexSearcher(DirectoryReader.open(FSDirectory.open(f)));
            String queryStr = key;
            Analyzer analyzer = new IKAnalyzer();
            //指定field为“name”，Lucene会按照关键词搜索每个doc中的name。
            QueryParser parser = new QueryParser(field, analyzer);

            Query query = parser.parse(queryStr);
            TopDocs hits = searcher.search(query, cnt);//前面几行代码也是固定套路，使用时直接改field和关键词即可
            for(ScoreDoc doc: hits.scoreDocs){
                Document d = searcher.doc(doc.doc);
                System.out.println(d.get("title"));
            }
        } catch (IOException | ParseException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
