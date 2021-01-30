package mua;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.*;
import java.io.*;

import static java.lang.System.*;

public class Main {
    enum BasicType{
        WORD {
            public boolean compare(String a, String b) {
                return a.trim().equals(b.trim());
            }
        },
        NUMBER {
            public boolean compare(String a, String b) {
                boolean ret = false;
                try {
                    BigDecimal d1 = BigDecimal.valueOf(Double.parseDouble(a));
                    BigDecimal d2 = BigDecimal.valueOf(Double.parseDouble(b));
                    ret = d1.equals(d2);
                } catch (Exception e) {
                    out.println(e.getMessage());
                }
                return ret;
            }
        },
        BOOL{

        };
        public boolean compare(String a, String b) {
            return false;
        }
    }
    static Map<String,Value> varTable = new HashMap<>();
    static Scanner sc = new Scanner(System.in);
    static class Value {
        private BasicType type;
        private String value;
        public boolean val_bool;
        public String val_word;
        public BigDecimal val_num;
        private int mark;
        private String comment;

        public Value(){

        }
        public Value(String expr){
//            Value val = new Value();
            if(expr.equals("True") || expr.equals("true")){
                this.type = BasicType.BOOL;
                this.val_bool = true;
            }else if(expr.equals("False") || expr.equals("false")){
                this.type = BasicType.BOOL;
                this.val_bool = false;
            }else if(expr.charAt(0)=='"'){
                this.type = BasicType.WORD;
                this.val_word = expr.substring(1);
            }else if(expr.charAt(0)=='-' || (expr.charAt(0)>='0' && expr.charAt(0)<='9')){
                this.type = BasicType.NUMBER;
                try {
                    this.val_num = new BigDecimal(expr);
                }catch(NumberFormatException e){
                    this.type = BasicType.WORD;
                    this.val_word = expr;
                }catch(Exception e){
                    out.println(e.getMessage());
                }
            }else{
                error(String.format("unrecognized value: <%s>\n", expr));
            }
        }

        public boolean judge(String line) {
            return type.compare(line, value);
        }
        public int getMark() {
            return mark;
        }
        public String getComment() {
            return comment;
        }
        public Value add(Value a){
            if(this.type!=BasicType.NUMBER || a.type!=BasicType.NUMBER)
                error("only numbers can be calculated!");
            Value res = new Value();
            res.type = BasicType.NUMBER;
            res.val_num = this.val_num.add(a.val_num);
            return res;
        }
        public Value sub(Value a){
            if(this.type!=BasicType.NUMBER || a.type!=BasicType.NUMBER)
                error("only numbers can be calculated!");
            Value res = new Value();
            res.type = BasicType.NUMBER;
            res.val_num = this.val_num.subtract(a.val_num);
            return res;
        }
        public Value mul(Value a){
            if(this.type!=BasicType.NUMBER || a.type!=BasicType.NUMBER)
                error("only numbers can be calculated!");
            Value res = new Value();
            res.type = BasicType.NUMBER;
            res.val_num = this.val_num.multiply(a.val_num);
            return res;
        }
        public Value div(Value a){
            if(this.type!=BasicType.NUMBER || a.type!=BasicType.NUMBER)
                error("only numbers can be calculated!");
            Value res = new Value();
            res.type = BasicType.NUMBER;
            res.val_num = this.val_num.divide(a.val_num, 1, RoundingMode.HALF_UP);
            return res;
        }
        public Value div(Value a, int scale){
            if(this.type!=BasicType.NUMBER || a.type!=BasicType.NUMBER)
                error("only numbers can be calculated!");
            Value res = new Value();
            res.type = BasicType.NUMBER;
            res.val_num = this.val_num.divide(a.val_num, scale, RoundingMode.HALF_UP);
            return res;
        }
        public Value mod(Value a){
            if(this.type!=BasicType.NUMBER || a.type!=BasicType.NUMBER)
                error("only numbers can be calculated!");
            Value res = new Value();
            res.type = BasicType.NUMBER;
            res.val_num = this.val_num.divideAndRemainder(a.val_num)[1];
            return res;
        }
        public String toStr(){
            String t = "";
            String v = "";
            if(this.type==BasicType.BOOL){
                t = "bool";
                v = Boolean.toString(val_bool);
            }
            else if(this.type==BasicType.WORD){
                t = "word";
                v = val_word;
            }
            else if(this.type==BasicType.NUMBER){
                t = "number";
                v = val_num.toString();
            }
            // return t+","+v;
            return v;
        }

    }
    static void error(String msg){
        out.printf("Error:%s\n", msg);
        exit(0);
    }
    static boolean isNumber(String s){
        if(s.charAt(0)=='-' || (s.charAt(0)>='0' && s.charAt(0)<='9')) return true;
        return false;
    }
    static boolean isDigit(char c){
        if(c>='0' && c<='9') return true;
        return false;
    }
    static boolean isOperation(String s){
        if(s.equals("add") || s.equals("sub") || s.equals("mul") || s.equals("div") || s.equals("mod")) return true;
        return false;
    }

    static Value calculate(String op, Value a, Value b){
        if(a.type!=BasicType.NUMBER){
            Value aa = new Value();
            aa.type = BasicType.NUMBER;
            try{
                aa.val_num = new BigDecimal(a.val_word);
            }catch (Exception e){
                int i=0;
                while(i<a.val_word.length() && ((i==0 && a.val_word.charAt(i)=='-') || isDigit(a.val_word.charAt(i)))) i++;
                aa.val_num = new BigDecimal(a.val_word.substring(0,i));
            }
            a = aa;
        }
        if(b.type!=BasicType.NUMBER){
            Value bb = new Value();
            bb.type = BasicType.NUMBER;
            try{
                bb.val_num = new BigDecimal(b.val_word);
            }catch (Exception e){
                int i=0;
                while(i<b.val_word.length() && ((i==0 && b.val_word.charAt(i)=='-') || isDigit(b.val_word.charAt(i)))) i++;
                bb.val_num = new BigDecimal(b.val_word.substring(0,i));
            }
            b = bb;
        }
        if(op.equals("add")) return a.add(b);
        else if(op.equals("sub")) return b.sub(a);
        else if(op.equals("mul")) return a.mul(b);
        else if(op.equals("div")) return b.div(a);
        else if(op.equals("mod")) return b.mod(a);
        else return null;
    }

    static Value parse(String expr){
        String[] opp = expr.split(" ");
        List<String> op = new ArrayList<String>(Arrays.asList(opp));
//        for(int i=0; i<op.size(); i++){
//            if(op.get(i).isEmpty()) {
//                op.remove(i);
//                i--;
//            }
//        }
        if(op.isEmpty()) return null;
        if(op.get(0).equals("make")){
            if(op.size()<3)
                error(String.format("%d args required, but %d given.", 3, op.size()));
            while(op.size()>3){
                op.set(2, op.get(2)+" "+op.get(3));
                op.remove(3);
            }
            String name = op.get(1);
            if(name.charAt(0)=='"'){
                name = name.substring(1);
            }
            Value val = parse(op.get(2));
            varTable.put(name, val);
            return val;
        }
        else if(op.get(0).equals("thing")){
            if(op.size()<2)
                error(String.format("%d args required, but %d given.", 2, op.size()));
            String name = Objects.requireNonNull(parse(op.get(1))).val_word;
            Value val = varTable.get(name);
            if(val==null)
                error(String.format("Variable %s is undefined.", name));
            assert val != null : "val is null";
//            out.printf("%s:%s", name, val.value);
            return val;
        }
        else if(op.get(0).charAt(0)==':'){
            String var_name = op.get(0).substring(1);
            return varTable.get(var_name);
        }
        else if(op.get(0).equals("print")){
            if(op.size()<2)
                error(String.format("%d args required, but %d given.", 2, op.size()));
            int op_size = op.size();
            while(op_size>2){
                op.set(1, op.get(1)+" "+op.get(2));
                op.remove(2);
                op_size--;
            }
            Value val = parse(op.get(1));
            assert val != null;
            out.println(val.toStr());
            return val;
        }
        else if(op.get(0).equals("read")){
            if(op.size()!=1)
                error(String.format("%d args required, but %d given.", 1, op.size()));
            // Scanner sc = new Scanner(System.in);
            // out.print("read:");
            String line = "";
            if(sc.hasNextLine()){
                line = sc.nextLine();
                // sc.close();
                // out.println("Has nextline");
            }
            if(line.equals("")) error("line is empty\n");
            return new Value(line);
        }
        else if(isOperation(op.get(0))){
            if(op.size()<3)
                error(String.format("%d args required, but %d given.", 3, op.size()));
            Stack<String> op_stk = new Stack<>();
            Stack<Value> val_stk = new Stack<>();
            for(String s : op) {
                if (isOperation(s)) {
                    op_stk.push(s);
                } else {
                    val_stk.push(parse(s));
                }
                if (val_stk.size() == 2) {
                    String opc = op_stk.pop();
                    Value v = calculate(opc, val_stk.pop(), val_stk.pop());
                    if (val_stk.empty()) val_stk.push(v);
                    else error("value stk is still nonempty!");
                }
            }
            if(!op_stk.empty()) error("Syntax error for too less args");
            if(val_stk.size()!=1) error("Syntax error for too many args");
            return val_stk.pop();
        }
        else{
            if(op.size()==1) return new Value(op.get(0));
        }

        return null;
    }
    public static String getPrompt(){
        String line="";
        // Scanner sc = new Scanner(in);
        out.print("-> ");
        if(!sc.hasNext()) return null;
        line = sc.nextLine();
        // sc.close();
        return line;
    }

    public static void main(String[] args) throws IOException{
        // out.println("Hello, mua~");
        // FileInputStream cin = new FileInputStream("in");
        // System.setIn(cin);
        String line = "";
        // line = getPrompt(System.in);
        // Scanner sc = new Scanner(System.in);
        // sc = new Scanner(System.in);
        line = sc.nextLine();
        while(line!=null && !line.equals("exit") && !line.equals("quit")){
            parse(line);
            // line = getPrompt(System.in);
            if(!sc.hasNextLine()) break;
            line = sc.nextLine();
        }
        // sc.close();
        // out.println("Bye, mua~");
    }
}
