package mua;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.*;

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

        },
        FUNC{

        },
    }

    static Vector<Map<String, Integer>> funcDecls = new Vector<>();
    static Vector<Map<String, Func>> funcTables = new Vector<>();
    static Vector<Map<String, Value>> varTables = new Vector<>();
    static Vector<Func> invocations = new Vector<>();
    static Scanner sc = new Scanner(System.in);

    static class Value {
        BasicType type;
        //private String value;
        boolean val_bool;
        String val_word;
        BigDecimal val_num;
        String val_ls;
        Func val_func;

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
                String ctt = expr.substring(1, expr.length()-1).trim();
                int lstcnt = 0;
                int open = 0;
                for(int i=0; i<ctt.length(); i++){
                    if(ctt.charAt(i) == '[') open++;
                    if(ctt.charAt(i) == ']'){
                        open--;
                        if(open == 0) lstcnt++;
                    }
                }
                if(lstcnt == 2 ){
                    this.type = BasicType.FUNC;
                    int l1 = ctt.indexOf('[');
                    int r1 = ctt.indexOf(']');
                    int l2 = ctt.indexOf('[', r1);
                    int r2 = ctt.indexOf(']', l2);
                    if(l1==0 && r2==ctt.length()-1 && ctt.substring(r1+1, l2).trim().equals("")){
                        String[] params = ctt.substring(l1+1, r1).trim().split(" ");
                        String body = ctt.substring(l2+1, r2).trim();
                        Func f = new Func(params, body);
                        val_func = f;
                        return;
                    }
                }
                this.type = BasicType.LIST;
                this.val_ls = ctt;
            }
            else{
                error(String.format("unrecognized value: <%s>\n", expr));
            }
        }
        public Value(Func f){
            this.type = BasicType.FUNC;
            this.val_func = f;
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
        @Override public String toString(){
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

    static class Func{
        String name;
        String[] params;
        String body;
        String[] instrs;
        Value ret = null;

        Func(String _name, Value _params, Value _body){
            if(_params.type != BasicType.LIST)
                error("non-list params!");
            if(_body.type != BasicType.LIST)
                error("non-list func body!");
            name = _name;
            List<String> param_lst = new ArrayList(Arrays.asList(_params.val_ls.split(" ")));
            for(int i=0; i<param_lst.size(); i++){
                if(param_lst.get(i).equals("")){
                    param_lst.remove(i);
                    i--;
                }
            }
            params = param_lst.toArray(new String[param_lst.size()]);
            body = _body.val_ls.trim();
        }

        Func(String[] _params, String _body){
            List<String> param_lst = new ArrayList(Arrays.asList(_params));
            for(int i=0; i<param_lst.size(); i++){
                if(param_lst.get(i).equals(""))
                    param_lst.remove(i--);
            }
            params = param_lst.toArray(new String[param_lst.size()]);
            body = _body;
            name = arr2str(_params) + "{" + _body + "}";
        }

        void init(){
            instrs = instrs_split(body);
        }
    }

    static void error(String msg){
        err.printf("Error:%s\n", msg);
        exit(1);
    }

    static List op1 = new ArrayList(Arrays.asList("export", "return", "print", "thing", "not", "erase", "run", "isname", "isnumber", "isword", "islist", "isbool", "isempty"));
    static List op2 = new ArrayList(Arrays.asList("make", "add", "sub", "mul", "div", "mod", "eq", "gt", "lt", "and", "or"));
    static List op3 = new ArrayList(Arrays.asList("if"));

    static String arr2str(String[] ss){
        String res = "";
        for(int i=0; i<ss.length; i++){
            res += " " + ss[i];
        }
        res = "[" + res.trim() + "]";
        return res;
    }

    static boolean isDigit(char c){
        if(c>='0' && c<='9') return true;
        return false;
    }
    static boolean isArithmeticOp(String s){
        if(s.equals("add") || s.equals("sub") || s.equals("mul") || s.equals("div") || s.equals("mod")) return true;
        return false;
    }
    static Value arithmetic(String op, Value a, Value b){
        if(a.type != BasicType.NUMBER){
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
        if(b.type != BasicType.NUMBER){
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
    static boolean inFuncTabel(String name){
        for(int i=0; i<funcTables.size(); i++){
            Map<String, Func> ft = funcTables.get(i);
            if(ft.containsKey(name)) return true;
        }
        return false;
    }

    static Func lookup_func(String name){
        for(int i=funcTables.size()-1; i>=0; i--){
            Map<String, Func> ft = funcTables.get(i);
            if(ft.containsKey(name))
                return ft.get(name);
        }
        return null;
    }
    static Value lookup_var(String name){
        if(varTables.size() > 1){
            Map<String, Value> vt = varTables.lastElement();
            if(vt.containsKey(name))
                return vt.get(name);
        }
        Map<String, Value> vt = varTables.elementAt(0);
        if(vt.containsKey(name))
            return vt.get(name);
        return null;
    }
    static void rm_var(String name){
        for(int i=varTables.size()-1; i>=0; --i){
            if(varTables.elementAt(i).containsKey(name))
                varTables.elementAt(i).remove(name);
        }
    }

    static Value judge(String op, Value a){
        Value res = new Value(BasicType.BOOL);
        if(op.equals("isname")){
            if(a.type!=BasicType.WORD) error("non-word type for arg_1 in \"make\"");
            res.val_bool = varTables.lastElement().containsKey(a.val_word);
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

    static String[] instrs_split(String instrs){
        String[] elems = instrs.trim().split(" ");
        elems = brac_close(elems, '[');
        elems = brac_close(elems, '(');

        Map<Integer, List<String>> opn = new HashMap<>();
        opn.put(1, op1);
        opn.put(2, op2);
        opn.put(3, op3);

        for(Map<String, Integer> decls: funcDecls){
            for(String name: decls.keySet()){
                int n = decls.get(name);
                if(!opn.containsKey(n)){
                    List<String> funcs = new ArrayList<>();
                    opn.put(n, funcs);
                }
                List<String> l = opn.get(n);
                l.add(name);
                opn.put(n, l);
            }
        }

        List<Integer> indices = new ArrayList<>();
        Stack<Integer> arg_cnt = new Stack<>();
        for(int i=0; i<elems.length; i++){
            String s = elems[i];
            int cnt = 0;
            for(int n: opn.keySet()){
                if(opn.get(n).contains(s)){
                    cnt = n;
                    break;
                }
            }
            arg_cnt.push(cnt);
            while(arg_cnt.peek().equals(0)){
                arg_cnt.pop();
                if(arg_cnt.empty()){
                    indices.add(i);
                    break;
                }
                int t = arg_cnt.pop() - 1;
                arg_cnt.push(t);
            }
        }
        List<String> res = new ArrayList<>();
        res.add("");
        for(int i=0, j=0; i<elems.length; i++){
            res.set(j, res.get(j) + " " + elems[i]);
            if(i == indices.get(j)){
                res.set(j, res.get(j).trim());
                j++;
                res.add("");
            }
        }
        if(res.get(res.size() - 1).equals("")){
            res.remove(res.size() - 1);
        }
        return res.toArray(new String[res.size()]);
    }

    static String[] brac_close(String[] ops, char left){
        List<String> opl = new ArrayList(Arrays.asList(ops));
        int open = 0;
        for(int i=0; i<opl.size(); i++){
            String t = opl.get(i);
            if(i > 0 && open > 0) {
                opl.set(i-1, opl.get(i-1) + " " + t);
                opl.remove(i--);
            }
            open += get_open(t, left);
        }
        return opl.toArray(new String[opl.size()]);
    }

    static Map<Integer, List<String>> get_oplen(){
        Map<Integer, List<String>> oplen = new HashMap<>();
        oplen.put(1, op1);
        oplen.put(2, op2);
        oplen.put(3, op3);

        for(Map<String, Func> ft: funcTables){
            for(String name: ft.keySet()){
                Func f = ft.get(name);
                if(!oplen.containsKey(f.params.length)){
                    List<String> funcs = new ArrayList<>();
                    funcs.add(name);
                    oplen.put(f.params.length, funcs);
                }
                List<String> l = oplen.get(f.params.length);
                l.add(name);
                oplen.put(f.params.length, l);
            }
        }
        return oplen;
    }

    static int[] find_args(String[] ss){
        if(ss.length==1){
            return new int[]{0};
        }

        Map<Integer, List<String>> oplen = get_oplen();

        Stack<Integer> arg_cnt = new Stack<>();
        List<Integer> res = new ArrayList<>();
        for(int i=0; i<ss.length; i++){
            String s = ss[i];
            int n_args = i==0?1:0;
            for(int n: oplen.keySet()){
                if(oplen.get(n).contains(s)){
                    n_args = n + (i==0?1:0);
                    break;
                }
            }
            arg_cnt.push(n_args);

            while(arg_cnt.peek().equals(0)){
                arg_cnt.pop();
                int cnt = arg_cnt.pop() - 1;
                arg_cnt.push(cnt);
            }
            if(arg_cnt.size() == 1)
                res.add(i);
        }

        if(arg_cnt.size()>1 || arg_cnt.empty())
            error("unmatched args: too many");
        if(arg_cnt.get(0)!=1)
            error("unmatched args: too less: " + arg_cnt.get(0));
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
    static boolean is_func(String s){
        if(!s.startsWith("[")) return false;
        if(!s.endsWith("]")) return false;

        int open = 0;
        int list_cnt = 0;
        for(int i=0; i<s.length(); i++){
            if(s.charAt(i) == '['){
                open++;
                if(open == 2) list_cnt++;
            }
            if(s.charAt(i) == ']') open--;
        }
        if(list_cnt == 2) return true;
        return false;
    }

    static Value invoke_func(String name, Value[] args){
        Func f = lookup_func(name);
        if(f == null){
            error(String.format("undefined function: %s", name));
        }
        varTables.add(new HashMap<>());
        funcDecls.add(new HashMap<>());
        funcTables.add(new HashMap<>());
        invocations.add(f);

        for(int i=0; i<args.length; i++){
            varTables.lastElement().put(f.params[i], args[i]);
        }

        for(int i=0; i<args.length; i++){
            if(args[i].type == BasicType.FUNC){
                funcDecls.lastElement().put(f.params[i], args[i].val_func.params.length);
                funcTables.lastElement().put(f.params[i], args[i].val_func);
            }
        }

        f.init();

        for(String s: f.instrs){
            parse(s);
        }
        varTables.remove(varTables.size() - 1);
        funcDecls.remove(funcDecls.size() - 1);
        funcTables.remove(funcTables.size() - 1);
        invocations.remove(invocations.size() - 1);
        return f.ret;
    }

    static void bracket_close(List<String> lst, char left){
        int open = 0;
        for(int i=0; i<lst.size(); i++){
            String t = lst.get(i);
            if(i > 0 && open > 0) {
                lst.set(i-1, lst.get(i-1) + " " + t);
                lst.remove(i--);
            }
            open += get_open(t, left);
        }
    }
    static String expr_in_brackets(String s){
        if(!s.startsWith("(") || !s.endsWith(")")){
            error("not in bracket?");
        }
        s = s.substring(1, s.length()-1);
        int open = 0;
        for(int i=0; i<s.length(); i++){
            if(s.charAt(i)=='(') open++;
            if(s.charAt(i)==')') open--;
            if(open > 0) continue;
            if(is_op_char(s.charAt(i))){
                int l = i-1, r = i+1;
                while(s.charAt(l)==' ') l--;
                while(s.charAt(r)==' ') r++;
                s = s.substring(0, i+1) + "$" + s.substring(r);
                s = s.substring(0, l+1) + "$" + s.substring(i);
                i = l + 2;
            }
        }
        return s;
    }
    static boolean is_pm(String s){
        return s.equals("+") || s.equals("-");
    }
    static boolean is_mdm(String s){
        return s.equals("*") || s.equals("/") || s.equals("%");
    }

    static boolean is_complete(String[] elems){
        Map<Integer, List<String>> oplen = get_oplen();
        Stack<Integer> argcnt = new Stack<>();
        for(int i=0; i<elems.length; i++){
            String s = elems[i];
            int n_args = i==0?1:0;
            for(int n: oplen.keySet()){
                if(oplen.get(n).contains(s)){
                    n_args = n + (i==0?1:0);
                    break;
                }
            }
            argcnt.push(n_args);

            while(argcnt.peek().equals(0)){
                argcnt.pop();
                int cnt = argcnt.pop() - 1;
                argcnt.push(cnt);
            }
        }
        if(argcnt.size()>1 || argcnt.empty())
            return false;
        if(argcnt.get(0)!=1)
            return false;
        return true;
    }

    static void argc_chk(String name, int need, int given){
        if(given < need)
            error(String.format("Too less args for `%s`", name));
        if(given > need)
            error(String.format("Too many args for `%s`", name));
    }

    static Value parse(String instr){
        instr = instr.trim();
        if(instr.equals("")) return null;

        List<String> op_list = new ArrayList<>(Arrays.asList(instr.split(" ")));
        op_list.remove("");

        if(instr.indexOf('$') != -1){
            while(op_list.size() > 1){
                op_list.set(0, op_list.get(0) + " " + op_list.get(1));
                op_list.remove(1);
            }
        }

        for(int i=0; i<op_list.size(); i++){
            if(is_pm(op_list.get(i)) || is_mdm(op_list.get(i))){
                int j=i+1;
                while(!is_complete(op_list.subList(i+1, j+1).toArray(new String[j-i]))){
                    j++;
                }
                for(int k=i; k<j+1; k++){
                    op_list.set(i-1, op_list.get(i-1) + " " + op_list.get(k));
                }
                op_list.subList(i, j+1).clear();
                i--;
            }
        }

        bracket_close(op_list, '(');
        bracket_close(op_list, '[');

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
            argc_chk("make", 3, args.length);

            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.WORD) error("non-word type for arg_1 in \"make\"");

            if(is_func(args[2])){
                String fd = args[2].substring(1, args[2].length()-1);
                int end1 = fd.indexOf(']');
                int begin2 = fd.indexOf('[', end1);
                Value params = parse(fd.substring(0, end1+1));
                Value body = parse(fd.substring(begin2, fd.length()));
                assert params != null;
                int n_params = params.val_ls.split(" ").length;
                if(params.val_ls.trim().equals("")){
                    n_params = 0;
                }
                funcDecls.lastElement().put(v1.val_word, n_params);
                Func f = new Func(v1.val_word, params, body);
                funcTables.lastElement().put(v1.val_word, f);
                Value v2 = new Value(f);
                varTables.lastElement().put(v1.val_word, v2);
                return null;
            }

            Value v2 = parse(args[2]);
            varTables.lastElement().put(v1.val_word, v2);
            return v2;
        }
        else if(args[0].equals("thing")){
            argc_chk("thing", 2, args.length);

            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.WORD) error("non-word type for arg_1 in \"thing\".");

            if(lookup_var(v1.val_word) == null) {
                error(String.format("no such word binded: %s", v1.val_word));
            }
            return lookup_var(v1.val_word);
        }
        else if(args[0].equals("print")){
            argc_chk("print", 2, args.length);
            Value v1 = parse(args[1]);
            out.println(v1);
            return v1;
        }
        else if(args[0].equals("read")){
            argc_chk("read", 1, args.length);
            String line = "";
            if(!sc.hasNextLine()){
                error("no input in buffer: read");
            }
            line = sc.nextLine();
            if(line.equals("")) error("empty input: read");
            return new Value(line);
        }
        else if(args[0].equals("erase")){
            argc_chk("erase", 2, args.length);

            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.WORD) error("non-word type for arg_1 in \"erase\".");

            Value res = lookup_var(v1.val_word);
            if(res == null){
                return null;
            }
            rm_var(v1.val_word);
            return res;
        }
        else if(args[0].equals("run")){
            argc_chk("run", 2, args.length);

            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!=BasicType.LIST) error("non-list type for arg_1 in \"run\".");
            String[] lines = instrs_split(v1.val_ls);
            Value res = new Value();
            for(String line : lines){
                res = parse(line);
            }
            return res;
        }
        else if(isArithmeticOp(args[0])){
            argc_chk(args[0], 3, args.length);
            Value v1 = parse(args[1]);
            assert v1!=null;
            Value v2 = parse(args[2]);
            assert v2!=null;
            return arithmetic(args[0], v2, v1);
        }
        else if(isLogicOp(args[0])){
            if(args[0].equals("not")){
                argc_chk("not", 2, args.length);
                Value v1 = parse(args[1]);
                assert v1!=null;
                return logic(args[0], v1);
            }
            argc_chk(args[0], 3, args.length);
            Value v1 = parse(args[1]);
            assert v1!=null;
            Value v2 = parse(args[2]);
            assert v2!=null;
            return logic(args[0], v2, v1);
        }
        else if(isJudgeOp(args[0])){
            argc_chk(args[0], 3, args.length);
            Value v1 = parse(args[1]);
            assert v1!=null;
            return judge(args[0], v1);
        }
        else if(args[0].equals("if")){
            argc_chk(args[0], 4, args.length);
            Value v1 = parse(args[1]);
            assert v1 != null;
            if(v1.type!= BasicType.BOOL) error("non-bool type for arg_1 in \"if\".");
            if(v1.val_bool) {
                Value l1 =  parse(args[2]);
                assert l1 != null;
                if(l1.type!=BasicType.LIST) error("non-list type for arg_2 in \"if\"");
                String[] instrs = instrs_split(l1.val_ls);
                Value res = null;
                for(String ins: instrs){
                    res = parse(ins);
                }
                return res;
            }
            Value l2 =  parse(args[3]);
            assert l2 != null;
            if(l2.type!=BasicType.LIST) error("non-list type for arg_3 in \"if\"");
            String[] instrs = instrs_split(l2.val_ls);
            Value res = null;
            for(String ins: instrs){
                res = parse(ins);
            }
            return res;
        }
        else if(inFuncTabel(args[0])){
            Value[] arg_list = new Value[args.length - 1];
            for(int i=0; i<arg_list.length; i++){
                arg_list[i] = parse(args[i+1]);
            }
            Value res = invoke_func(args[0], arg_list);
            return res;
        }
        else if(args[0].equals("return")){
            argc_chk("return", 2, args.length);
            Value v1 = parse(args[1]);
            if(invocations.isEmpty()) return v1;
            invocations.lastElement().ret = v1;
            return v1;
        }
        else if(args[0].equals("export")){
            argc_chk("export", 2, args.length);
            Value v1 = parse(args[1]);
            Value v = lookup_var(v1.val_word);
            varTables.get(0).put(v1.val_word, v);
            return v;
        }
        else if(args.length==1){
            String arg = args[0];
            if(arg.length() <= 0)
                error("empty arg!");
            if(arg.charAt(0)==':' && is_name(arg.substring(1))){
                String var_name = arg.substring(1);
                Value v = lookup_var(var_name);
                if(v == null)
                    error(String.format("no such word bound: %s", var_name));
                return v;
            }
            if(arg.startsWith("\"") || arg.startsWith("[")&&arg.endsWith("]"))
                return new Value(arg);

            if(arg.startsWith("(") && arg.endsWith(")")){
                String expr = expr_in_brackets(arg);
                return parse(expr);
            }

            if(is_num(arg)){
                return new Value(arg);
            }

            List<String> elems = new ArrayList(Arrays.asList(arg.split("\\$")));
            for(int i=0; i<elems.size(); i++){
                if(is_pm(elems.get(i))){
                    if(i==0 || is_pm(elems.get(i-1))){
                        elems.add(i, "0");
                    }
                }
            }

            List<Value> nums = new ArrayList<>();
            List<Character> pms = new ArrayList<>();
            for(int i=1; i<elems.size(); i+=2){
                if(is_pm(elems.get(i))){
                    pms.add(elems.get(i).charAt(0));
                    if(i==1){
                        nums.add(parse(elems.get(0)));
                        elems.subList(0, 2).clear();
                    }else{
                        String subexpr = "";
                        for(int j=0; j<i; j++){
                            subexpr += " " + elems.get(j);
                        }
                        subexpr = expr_in_brackets("(" + subexpr.trim() + ")");
                        Value a = parse(subexpr);
                        nums.add(a);
                        elems.subList(0, i+1).clear();
                    }
                    i = -1;
                }
            }

            if(nums.size() == 0){
                List<Character> mdms = new ArrayList<>();
                for(int i=0; i<elems.size(); i++){
                    if(is_mdm(elems.get(i))){
                        mdms.add(elems.get(i).charAt(0));
                        if(i==1){
                            nums.add(parse(elems.get(0)));
                            elems.subList(0, 2).clear();
                        }else{
                            error(arg);
                        }
                        i = -1;
                    }
                }
                while(elems.size() > 1){
                    elems.set(0, elems.get(0) + " " + elems.get(1));
                    elems.remove(1);
                }
                nums.add(parse(expr_in_brackets("(" + elems.get(0) + ")")));
                for(int i=0; i<mdms.size(); i++){
                    if(mdms.get(i)=='*')
                        nums.set(0, nums.get(0).mul(nums.get(1)));
                    else if(mdms.get(i)=='/')
                        nums.set(0, nums.get(0).div(nums.get(1)));
                    else if(mdms.get(i)=='%')
                        nums.set(0, nums.get(0).mod(nums.get(1)));
                    nums.remove(1);
                }
                return nums.get(0);
            }

            while(elems.size() > 1){
                elems.set(0, elems.get(0) + " " + elems.get(1));
                elems.remove(1);
            }
            nums.add(parse(expr_in_brackets("(" + elems.get(0) + ")")));

            for(int i=0; i<pms.size(); i++){
                if(pms.get(i)=='+')
                    nums.set(0, nums.get(0).add(nums.get(1)));
                else if(pms.get(i)=='-')
                    nums.set(0, nums.get(0).sub(nums.get(1)));
                nums.remove(1);
            }

            return nums.get(0);
        }
        error(String.format("unknown line: %s", instr));
        return null;
    }

    static int get_open(String s, char left){
        int open = 0;
        char right = ')';
        if(left == '(')
            right = ')';
        else if(left == '[')
            right = ']';
        else if(left == '{')
            right = '}';

        for(int i=0; i<s.length(); i++){
            if(s.charAt(i) == left)
                open++;
            else if(s.charAt(i) == right)
                open--;
        }
        return open;
    }

    static boolean is_complete_line(String line){
        line = line.trim();
        List<String> words = new ArrayList(Arrays.asList(line.split(" ")));

        bracket_close(words, '(');
        bracket_close(words, '[');

        Map<Integer, List<String>> oplen = get_oplen();
        Stack<Integer> argcnt = new Stack<>();
        for(int i=0; i<words.size(); i++){
            String s = words.get(i);
            int n_args = i==0?1:0;
            for(int n: oplen.keySet()){
                if(oplen.get(n).contains(s)){
                    n_args = n + (i==0?1:0);
                    break;
                }
            }
            argcnt.push(n_args);

            while(argcnt.peek().equals(0)){
                argcnt.pop();
                int cnt = argcnt.pop() - 1;
                argcnt.push(cnt);
            }
        }
        if(argcnt.size()>1 || argcnt.empty())
            return false;
        if(argcnt.get(0)!=1)
            return false;
        return true;
    }

    public static String getPrompt(){
        String line = "";
        //out.print("-> ");
        if(!sc.hasNext()) return null;
        line = sc.nextLine();
        int open = 0;
        for(int i=0; i<line.length(); i++){
            if(line.charAt(i) == '[') open++;
            else if(line.charAt(i) == ']') open--;
        }
        while(open > 0 || !is_complete_line(line)){
            //out.print("-> ");
            String t = sc.nextLine();
            open += get_open(t, '[');
            line += " " + t.trim();
        }
        return line;
    }

    public static void main(String[] args){
        //out.println("Hello, mua~");
        varTables.add(new HashMap<>());
        funcDecls.add(new HashMap<>());
        funcTables.add(new HashMap<>());
        String line = "";
        line = getPrompt();
        while(line!=null && !line.equals("exit") && !line.equals("quit")){
            while(line.equals("")) line = getPrompt();
            parse(line);
            line = getPrompt();
        }
        sc.close();
        //out.println("Bye, mua~");
    }
}
