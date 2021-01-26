import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static class Request{
        String url;
        String method;
        String version;
        Map<String,String> headers = new HashMap<>();
        String data;
        Request(){
            url = "";
            method = "";
            version = "";
            data = "";
        }
    }
    public static class Response{
        String version;
        int code;
        String status;
        Map<String,String> headers = new HashMap<>();
        ByteBuffer data;
        Response(){
            version = "";
            code = -1;
            status = "";
            data = ByteBuffer.allocate(1<<20);
        }
        byte[] headBytes(){
            String s = version + " " + code + " " + status + "\r\n";
            for(String key: headers.keySet()){
                String val = headers.get(key);
                s += key + ": " + val + "\r\n";
            }
            s += "\r\n";
            // s += data;
            return s.getBytes();
        }
    }

    public static class HttpServer extends Thread{
        private InputStream input;
        private OutputStream output;
        private String root;

        HttpServer(Socket socket, String path){
            try{
                input = socket.getInputStream();
                output = socket.getOutputStream();
                root = path;
            }catch(IOException e){
                e.printStackTrace();
            }
        }

        Request getRequest(){
            BufferedReader br = new BufferedReader(new InputStreamReader(input));
            Request request = new Request();
            try{
                String line = br.readLine();
                // System.out.println(line);
                String[] args = line.split(" ");
                assert args.length==3;
                request.method = args[0];
                request.url = args[1];
                request.version = args[2];

                line = br.readLine();
                while(!line.equals("")){
                    // System.out.println(line);
                    String[] kv = line.split(":");
                    assert kv.length>=2;
                    for(int i=kv.length-1; i>1; i--){
                        kv[i-1] += kv[i];
                    }
                    request.headers.put(kv[0].strip(), kv[1].strip());
                    line = br.readLine();
                }
                if(request.headers.containsKey("Content-Length")){
                    int l = Integer.parseInt(request.headers.get("Content-Length"));
                    while(l>0){
                        request.data += (char)br.read();
                        l--;
                    }
                }
            }catch (IOException e){
                e.printStackTrace();
            }
            return request;
        }

        void responseGET(Request req) throws IOException {
            String path = req.url;
            File f = new File(root, path);
            System.out.println("A GET request for: " + f.getName());
            Response res = new Response();
            if(path.equals("/") || !f.exists()){
                res.code = 404;
                res.version = "HTTP/1.1";
                res.status = "file not found";
                res.headers.put("Content-Type", "text/html; charset=UTF-8");
                res.headers.put("Content-Length", "22");
                res.data.put("<h1>404 not found</h1>".getBytes());
                output.write(res.headBytes());
                output.write(res.data.array());
                output.flush();
                output.close();
                return;
            }
            String ext = path.substring(path.lastIndexOf('.') + 1);
            InputStream fb = new FileInputStream(f);
            res.version = "HTTP/1.1";
            res.code = 200;
            res.status = "OK";
            if(ext.equals("jpg")){
                res.headers.put("Content-Type", "image/jpeg");
            }else if(ext.equals("html")){
                res.headers.put("Content-Type", "text/html; charset=UTF-8");
            }else{
                res.headers.put("Content-Type", "text/plain; charset=UTF-8");
            }

            for(int b=fb.read(); b!=-1; b=fb.read()){
                res.data.put((byte)b);
            }
            fb.close();
            output.write(res.headBytes());
            output.write(res.data.array());
            output.flush();
            output.close();
            return;
        }

        String login = "3180105099";
        String pass = "5099";

        void responsePOST(Request req) throws IOException {
            Response res = new Response();
            System.out.printf("A POST request for: %s\n", req.url);
            if(!req.url.equals("/dopost")){
                res.version = "HTTP/1.1";
                res.code = 404;
                res.status = "file not found";
                res.headers.put("Content-Type", "text/html; charset=UTF-8");
                res.headers.put("Content-Length", "22");
                res.data.put("<h1>404 not found</h1>".getBytes());
                this.output.write(res.headBytes());
                this.output.write(res.data.array());
                this.output.flush();
                this.output.close();
                return;
            }
            String[] post = req.data.split("&");
            Map<String, String> paras = new HashMap<>();
            for(int i=0; i<post.length; i++){
                String para = post[i].substring(0, post[i].indexOf('='));
                String val = post[i].substring(post[i].indexOf('=') + 1);
                paras.put(para, val);
            }
            res.version = "HTTP/1.1";
            res.code = 200;
            res.status = "OK";
            res.headers.put("Content-Type", "text/html; charset=UTF-8");
            String msg = "<html>" +
                    "<head></head>" +
                    "<body>login success :)<body>" +
                    "</html>";
            if(!paras.containsKey("login") || !paras.containsKey("pass")
            || !paras.get("login").equals(login) || !paras.get("pass").equals(pass)){
                msg = "<html>" +
                        "<head></head>" +
                        "<body>login failed :(<body>" +
                        "</html>";
                
            }
            res.headers.put("Content-Length", ""+msg.length());
            res.data.put(msg.getBytes());

            output.write(res.headBytes());
            output.write(res.data.array());
            output.flush();
            output.close();
            return;
        }

        @Override
        public void run(){
            // System.out.println("<Start>");
            Request request = getRequest();
            if(request.method.equals("GET")){
                try {
                    responseGET(request);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }else if(request.method.equals("POST")){
                try {
                    responsePOST(request);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            // System.out.println("<End>");
        }
    }

    public static void main(String[] args){
        int port = 5099;
        String root = "..\\root";
        System.out.printf("port: %s\n", ""+port);
        System.out.printf("root: %s\n", root);
        try{
            ServerSocket server_socket = new ServerSocket(port);
            while(true){
                Socket socket = server_socket.accept();
                new HttpServer(socket, root).start();
            }
        }catch(IOException e){
            e.printStackTrace();
        }
    }
}

