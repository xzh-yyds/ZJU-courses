package mua;
import java.lang.reflect.Array;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.*;
import java.io.*;
import java.util.regex.Pattern;

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

        },
        LIST{

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
        public String val_ls;

        public Value(){

        }
        public Value(BasicType type){
            this.type = type;
        }
        public Value(String expr){
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
            }else if(expr.startsWith("[") && expr.endsWith("]")){
                this.type = BasicType.LIST;
                this.val_ls = expr.substring(1,expr.length()-1);
            }
            else{
                error(String.format("unrecognized value: <%s>\n", expr));
            }
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
        @Override
        public String toString(){
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
            else if(this.type==BasicType.LIST){
                t = "list";
                v = "[" + val_ls + "]";
            }
            // return t+","+v;
            return v;
        }

    }

    static void error(String msg){
        err.printf("Error:%s\n", msg);
        exit(1);
    }

    static String[] a_op3 = {"if"};
    static String[] a_op2 = {"make", "add", "sub", "mul", "div", "mod", "eq", "gt", "lt", "and", "or"};
    static String[] a_op1 = {"print", "thing", "not", "erase", "run", "isname", "isnumber", "isword", "islist", "isbool", "isempty"};

    static boolean isDigit(char c){
        if(c>='0' && c<='9') return true;
        return false;
    }
    static boolean isArithmeticOp(String s){
        if(s.equals("add") || s.equals("sub") || s.equals("mul") || s.equals("div") || s.equals("mod")) return true;
        return false;
    }
    static Value arithmetic(String op, Value a, Value b){
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
    static boolean isLogicOp(String op){
        return op.equals("eq") || op.equals("gt") || op.equals("lt") || op.equals("not") || op.equals("and") || op.equals("or");
    }
    static boolean isJudgeOp(String op){
        return op.equals("isname") || op.equals("isnumber") || op.equals("isword") || op.equals("islist") || op.equals("isbool") || op.equals("isempty");
    }
    static Value judge(String op, Value a){
        Value res = new Value(BasicType.BOOL);
        if(op.equals("isname")){
            if(a.type!=BasicType.WORD) error("non-word type for arg_1 in \"make\".");
            res.val_bool = varTable.containsKey(a.val_word);
            return res;
        }else if(op.equals("isnumber")){
            res.val_bool = a.type==BasicType.NUMBER;
            if(a.type==BasicType.WORD){
                if(is_num(a.val_word)){
                    res.val_bool = true;
                }
            }
            return res;
        }else if(op.equals("isword")){
            res.val_bool = a.type==BasicType.WORD;
            return res;
        }else if(op.equals("islist")){
            res.val_bool = a.type==BasicType.LIST;
            return res;
        }else if(op.equals("isbool")){
            res.val_bool = a.type==BasicType.BOOL;
            return res;
        }else if(op.equals("isempty")){
            if(a.type==BasicType.WORD)
                res.val_bool = a.val_word.equals("");
            else if(a.type==BasicType.LIST)
                res.val_bool = a.val_ls.equals("");
            if(a.type!=BasicType.WORD && a.type!=BasicType.LIST)
                error("non-word/list type for arg_1 in \"isempty\".");
            return res;
        }
        return null;
    }

    static Value logic(String op, Value a, Value b){
        Value res = new Value(BasicType.BOOL);
        if(op.equals("eq")){
            if(a.type!=b.type) res.val_bool = false;
            if(a.type==BasicType.WORD) res.val_bool = a.val_word.compareTo(b.val_word)==0;
            else if(a.type==BasicType.NUMBER) res.val_bool = a.val_num.compareTo(b.val_num)==0;
            else error("illegal arg type in \"eq\".");
        }
        else if(op.equals("gt")){
            if(a.type!=b.type) res.val_bool = false;
            if(a.type==BasicType.WORD) res.val_bool = a.val_word.compareTo(b.val_word)<0;
            else if(a.type==BasicType.NUMBER) res.val_bool = a.val_num.compareTo(b.val_num)<0;
            else error("illegal arg type in \"eq\".");
        }
        else if(op.equals("lt")){
            if(a.type!=b.type) res.val_bool = false;
            if(a.type==BasicType.WORD) res.val_bool = a.val_word.compareTo(b.val_word)>0;
            else if(a.type==BasicType.NUMBER) res.val_bool = a.val_num.compareTo(b.val_num)>0;
            else error("illegal arg type in \"eq\".");
        }
        else if(op.equals("and")){
            if(a.type!=BasicType.BOOL || b.type!=BasicType.BOOL)
                error("Two args of \"and\" must be both BOOL.");
            res.val_bool = a.val_bool && b.val_bool;
        }
        else if(op.equals("or")){
            if(a.type!=BasicType.BOOL || b.type!=BasicType.BOOL)
                error("Two args of \"or\" must be both BOOL.");
            res.val_bool = a.val_bool || b.val_bool;
        }
        return res;
    }
    static Value logic(String op, Value a){
        if(!op.equals("not") || a.type!=BasicType.BOOL)
            error("illegal args in \"not\".");
        Value res = new Value(BasicType.BOOL);
        res.val_bool = !a.val_bool;
        return res;
    }

    static String[] instr_split(String instrs){
        String[] op = instrs.split(" ");
        Stack<Integer> arg_cnt = new Stack<>();

        List<String> op2 = Arrays.asList(a_op2);
        List<String> op1 = Arrays.asList(a_op1);
        String instr = "";
        List<String> res = new ArrayList<>();
        for(String s : op){
            instr += " " + s;
            if(op2.contains(s)){
                arg_cnt.push(2);
            }else if(op1.contains(s)){
                arg_cnt.push(1);
            }else{
                int cnt = arg_cnt.pop() - 1;
                arg_cnt.push(cnt);
            }
            if(arg_cnt.peek().equals(0)){
                arg_cnt.pop();
                res.add(instr);
                instr = "";
            }
        }
        String[] ss = new String[res.size()];
        for(int i=0; i<res.size(); i++)
            ss[i] = res.get(i);
        return ss;
    }
    static int[] find_args(String[] ss){
        if(ss.length==1){
            return new int[]{0};
        }

        List<String> op3 = Arrays.asList(a_op3);
        List<String> op2 = Arrays.asList(a_op2);
        List<String> op1 = Arrays.asList(a_op1);
        Stack<Integer> arg_cnt = new Stack<>();
        List<Integer> res = new ArrayList<>();
        for(int i=0; i<ss.length; i++){
            String s = ss[i];
            if(op3.contains(s)){
                arg_cnt.push(3+(i==0?1:0));
            }else if(op2.contains(s)){
                arg_cnt.push(2+(i==0?1:0));
            }else if(op1.contains(s)){
                arg_cnt.push(1+(i==0?1:0));
            }else{
                if(i==0) break;
                int cnt = arg_cnt.pop() - 1;
                arg_cnt.push(cnt);
            }
            while(arg_cnt.peek().equals(0)){
                arg_cnt.pop();
                int cnt = arg_cnt.pop() - 1;
                arg_cnt.push(cnt);
            }
            if(arg_cnt.size()==1)
                res.add(i);
        }
        if(arg_cnt.size()>1 || arg_cnt.empty())
            error("unmatched args");
        if(arg_cnt.get(0)!=1)
            error("unmatched args");
        return res.stream().mapToInt(i->i).toArray();
    }

    static boolean is_op_char(char c){
        if(c=='+' || c=='-' || c=='*' || c=='/' || c=='%') return true;
        return false;
    }
    static boolean is_num(String s){
        for(int i=0; i<s.length(); i++){
            if(s.charAt(i)=='+' || s.charAt(i)=='-' || s.charAt(i)=='*' || s.charAt(i)=='/' || s.charAt(i)=='%')
                return false;
            if(s.charAt(i)=='(' || s.charAt(i)==')')
                return false;
            if(s.charAt(i)>='0' && s.charAt(i)<='9') continue;
            if(s.charAt(i)=='.') continue;
            return false;
        }
        return true;
    }
    static boolean is_name(String s){
        for(int i=0; i<s.length(); i++){
            if(s.charAt(i)>='0' && s.charAt(i)<='9') continue;
            if(s.charAt(i)>='a' && s.charAt(i)<='z') continue;
            if(s.charAt(i)>='A' && s.charAt(i)<='Z') continue;
            if(s.charAt(i)=='_') continue;
            return false;
        }
        return true;
    }

    static Value parse(String instr){
        instr = instr.trim();
        List<String> op_list = new LinkedList<>(Arrays.asList(instr.split(" ")));
        op_list.remove("");

        int brackets = 0;
        for(int i=0; i<op_list.size(); i++){
            int org = brackets;
            for(int j=0; j<op_list.get(i).length(); j++){
                if(op_list.get(i).charAt(j)=='('){
                    brackets++;
                }
                if(op_list.get(i).charAt(j)==')'){
                    brackets--;
                }
            }
            if(org>0) {
                op_list.set(i-1, op_list.get(i-1) + " " + op_list.get(i));
                op_list.remove(i);
                i--;
            }
        }

        for(int i=0; i<op_list.size(); i++){
            if(op_list.get(i).charAt(0)=='[' && !op_list.get(i).endsWith("]")){
                for(int j=i+1; j<op_list.size(); j++){
                    op_list.set(i, op_list.get(i)+" "+op_list.get(j));
                    op_list.remove(j);
                    j--;
                    if(op_list.get(i).endsWith("]")) break;
                }
            }
        }
        String[] op_arr = new String[op_list.size()];
        op_arr = op_list.toArray(op_arr);
        int[] arg_indices = find_args(op_arr);
        String[] args = new String[arg_indices.length];
        for(int i=0; i<arg_indices.length; i++){
            args[i] = "";
            for(int j=i>0?arg_indices[i-1]+1:0; j<=arg_indices[i]; j++){
                args[i] += (j==(i>0?arg_indices[i-1]+1:0)?"":" ") + op_arr[j];
            }
        }

        if(args[0].equals("make")){
            if(args.length<3) error("Too less args for \"make\".");
            if(args.length>3) error("Too many args for \"make\".");
            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.WORD) error("non-word type for arg_1 in \"make\".");
            Value v2 = parse(args[2]);
            varTable.put(v1.val_word, v2);
            return v2;
        }
        else if(args[0].equals("thing")){
            if(args.length<2) error("Too less args for \"print\".");
            if(args.length>2) error("Too many args for \"print\".");
            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.WORD) error("non-word type for arg_1 in \"thing\".");
            if(!varTable.containsKey(v1.val_word)) {
                error(String.format("no such word binded: %s", v1.val_word));
            }
            return varTable.get(v1.val_word);
        }
        else if(args[0].equals("print")){
            if(args.length<2) error("Too less args for \"print\".");
            if(args.length>2) error("Too many args for \"print\".");
            Value v1 = parse(args[1]);
            out.println(v1);
            return v1;
        }
        else if(args[0].equals("read")){
            if(args.length>1) error("Too many args for \"read\".");
            String line = "";
            if(!sc.hasNextLine()){
                error("no input in buffer: read");
            }
            line = sc.nextLine();
            if(line.equals("")) error("empty input: read");
            return new Value(line);
        }
        else if(args[0].equals("erase")){
            if(args.length<2) error("Too less args for \"erase\".");
            if(args.length>2) error("Too many args for \"erase\".");
            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.WORD) error("non-word type for arg_1 in \"erase\".");
            if(!varTable.containsKey(v1.val_word)){
                return null;
            }
            Value res = varTable.get(v1.val_word);
            varTable.remove(v1.val_word);
            return res;
        }
        else if(args[0].equals("run")){
            if(args.length<2) error("Too less args for \"run\".");
            if(args.length>2) error("Too many args for \"run\".");
            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.LIST) error("non-list type for arg_1 in \"run\".");
            String[] lines = instr_split(v1.val_ls);
            Value res = new Value();
            for(String line : lines){
                res = parse(line);
            }
            return res;
        }
        else if(isArithmeticOp(args[0])){
            if(args.length<3) error(String.format("Too less args for \"%s\".", args[0]));
            if(args.length>3) error(String.format("Too many args for \"%s\".", args[0]));
            Value v1 = parse(args[1]);
            assert v1!=null;
            Value v2 = parse(args[2]);
            assert v2!=null;
            return arithmetic(args[0], v2, v1);
        }
        else if(isLogicOp(args[0])){
            if(args[0].equals("not")){
                if(args.length<2) error("Too less args for \"not\".");
                if(args.length>2) error("Too many args for \"not\".");
                Value v1 = parse(args[1]);
                assert v1!=null;
                return logic(args[0], v1);
            }
            if(args.length<3) error(String.format("Too less args for \"%s\".", args[0]));
            if(args.length>3) error(String.format("Too many args for \"%s\".", args[0]));
            Value v1 = parse(args[1]);
            assert v1!=null;
            Value v2 = parse(args[2]);
            assert v2!=null;
            return logic(args[0], v2, v1);
        }
        else if(isJudgeOp(args[0])){
            if(args.length<2) error(String.format("Too less args for \"%s\".", args[0]));
            if(args.length>3) error(String.format("Too many args for \"%s\".", args[0]));
            Value v1 = parse(args[1]);
            assert v1!=null;
            return judge(args[0], v1);
        }
        else if(args[0].equals("if")){
            if(args.length<4) error("Too less args for \"if\".");
            if(args.length>4) error("Too many args for \"if\".");
            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!= BasicType.BOOL) error("non-bool type for arg_1 in \"if\".");
            if(v1.val_bool) {
                Value l1 =  parse(args[2]);
                assert l1 != null;
                if(l1.type!=BasicType.LIST) error("non-list type for arg_2 in \"if\"");
                return parse(l1.val_ls);
            }
            Value l2 =  parse(args[3]);
            assert l2 != null;
            if(l2.type!=BasicType.LIST) error("non-list type for arg_3 in \"if\"");
            return parse(l2.val_ls);
        }
        else if(args.length==1){
            String arg = args[0];
            if(arg.length()<=0) error("empty arg!");
            if(arg.charAt(0)==':' && is_name(arg.substring(1))){
                String var_name = arg.substring(1);
                if(!varTable.containsKey(var_name)){
                    error(String.format("no such word binded: %s", var_name));
                }
                return varTable.get(var_name);
            }
            if(arg.startsWith("(") && arg.endsWith(")")){
                for(int i=0; i<arg.length(); i++){
                    if(is_op_char(arg.charAt(i))){
                        while(arg.charAt(i-1)==' '){
                            arg = arg.substring(0,i-1) + arg.substring(i);
                            i--;
                        }
                        while(arg.charAt(i+1)==' '){
                            arg = arg.substring(0,i+1) + arg.substring(i+2);
                        }
                    }
                }
                return parse(arg.substring(1, arg.length()-1));
            }
            if(arg.startsWith("\"") || arg.startsWith("[")&&arg.endsWith("]"))
                return new Value(arg);

            List<Value> nums = new LinkedList<>();
            List<Character> plus_minus = new LinkedList<>();
            brackets = 0;
            for(int i=0; i<arg.length(); i++){
                if(arg.charAt(i)=='(') brackets++;
                if(arg.charAt(i)==')') {
                    brackets--;
                }
                if(brackets>0) continue;
                if(arg.charAt(i)=='+' || arg.charAt(i)=='-'){
                    if(i==0) {
                        arg = "0" + arg;
                        i++;
                    }
                    if(is_num(arg.substring(i))) nums.add(new Value(arg.substring(0, i).trim()));
                    else nums.add(parse(arg.substring(0, i).trim()));
                    plus_minus.add(arg.charAt(i));
                    arg = arg.substring(i+1);
                    i=-1;
                }
            }

            if(nums.size()==0){
                List<Character> mul_div_mod = new LinkedList<>();
                brackets = 0;
                for(int i=0; i<arg.length(); i++){
                    if(arg.charAt(i)=='(') brackets++;
                    if(arg.charAt(i)==')') {
                        brackets--;
                    }
                    if(brackets>0) continue;
                    if(arg.charAt(i)=='*' || arg.charAt(i)=='/' || arg.charAt(i)=='%'){
                        if(is_num(arg.substring(i))) nums.add(new Value(arg.substring(0, i).trim()));
                        else nums.add(parse(arg.substring(0, i).trim()));
                        mul_div_mod.add(arg.charAt(i));
                        arg = arg.substring(i+1);
                        i=-1;
                    }
                }
                if(is_num(arg)) nums.add(new Value(arg.trim()));
                else nums.add(parse(arg.trim()));

                for(int i=0; i<mul_div_mod.size(); i++){
                    if(mul_div_mod.get(i)=='*') nums.set(0, nums.get(0).mul(nums.get(1)));
                    else if(mul_div_mod.get(i)=='/') nums.set(0, nums.get(0).div(nums.get(1)));
                    else if(mul_div_mod.get(i)=='%') nums.set(0, nums.get(0).mod(nums.get(1)));
                    nums.remove(1);
                }
                return nums.get(0);
            }

            nums.add(parse(arg.trim()));

            for(int i=0; i<plus_minus.size(); i++){
                if(plus_minus.get(i)=='+') nums.set(0, nums.get(0).add(nums.get(1)));
                else if(plus_minus.get(i)=='-') nums.set(0, nums.get(0).sub(nums.get(1)));
                nums.remove(1);
            }
            return nums.get(0);

        }
        error(String.format("unknown line: %s", instr));
        return null;
    }

    public static String getPrompt(){
        String line="";
        // Scanner sc = new Scanner(in);
        // out.print("-> ");
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
        line = getPrompt();
        while(line!=null && !line.equals("exit") && !line.equals("quit")){
            while(line.equals("")) line = getPrompt();
            parse(line);
            line = getPrompt();
        }
        sc.close();
        // out.println("Bye, mua~");
    }
}
