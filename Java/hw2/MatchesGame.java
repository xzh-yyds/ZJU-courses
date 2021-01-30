import java.util.Random;
import java.util.Scanner;
import java.util.Vector;

public class MatchesGame {
    public static String rmSpaces(String s){
        for(int i=0; i<s.length(); i++){
            if(s.charAt(i)==' '){
                s = s.substring(0,i) + s.substring(i+1);
                i--;
            }
        }
        return s;
    }
    public static class Pair<T1,T2>{
        public T1 first;
        public T2 second;
        public Pair(T1 x, T2 y){
            this.first=x;
            this.second=y;
        }
    }
    public static class MatchDigit{
        byte[] seg = new byte[7];

        public MatchDigit(){
            seg = new byte[7];
        }
        public MatchDigit(int n){
            if(n==0){
                seg[0] = 0;
                seg[1] = 1;
                seg[2] = 1;
                seg[3] = 1;
                seg[4] = 1;
                seg[5] = 1;
                seg[6] = 1;
            }
            else if(n==1){
                seg[0] = 0;
                seg[1] = 1;
                seg[2] = 1;
                seg[3] = 0;
                seg[4] = 0;
                seg[5] = 0;
                seg[6] = 0;
            }
            else if(n==2){
                seg[0] = 1;
                seg[1] = 1;
                seg[2] = 0;
                seg[3] = 1;
                seg[4] = 1;
                seg[5] = 0;
                seg[6] = 1;
            }
            else if(n==3){
                seg[0] = 1;
                seg[1] = 1;
                seg[2] = 1;
                seg[3] = 1;
                seg[4] = 0;
                seg[5] = 0;
                seg[6] = 1;
            }
            else if(n==4){
                seg[0] = 1;
                seg[1] = 1;
                seg[2] = 1;
                seg[3] = 0;
                seg[4] = 0;
                seg[5] = 1;
                seg[6] = 0;
            }
            else if(n==5){
                seg[0] = 1;
                seg[1] = 0;
                seg[2] = 1;
                seg[3] = 1;
                seg[4] = 0;
                seg[5] = 1;
                seg[6] = 1;
            }
            else if(n==6){
                seg[0] = 1;
                seg[1] = 0;
                seg[2] = 1;
                seg[3] = 1;
                seg[4] = 1;
                seg[5] = 1;
                seg[6] = 1;
            }
            else if(n==7){
                seg[0] = 0;
                seg[1] = 1;
                seg[2] = 1;
                seg[3] = 0;
                seg[4] = 0;
                seg[5] = 0;
                seg[6] = 1;
            }
            else if(n==8){
                seg[0] = 1;
                seg[1] = 1;
                seg[2] = 1;
                seg[3] = 1;
                seg[4] = 1;
                seg[5] = 1;
                seg[6] = 1;
            }
            else if(n==9){
                seg[0] = 1;
                seg[1] = 1;
                seg[2] = 1;
                seg[3] = 1;
                seg[4] = 0;
                seg[5] = 1;
                seg[6] = 1;
            }
        }
        public int value(){
            if(seg[0]==0 && seg[1]==1 && seg[2]==1 && seg[3]==1 && seg[4]==1 && seg[5]==1 && seg[6]==1){
                return 0;
            }
            if(seg[0]==0 && seg[1]==1 && seg[2]==1 && seg[3]==0 && seg[4]==0 && seg[5]==0 && seg[6]==0){
                return 1;
            }
            if(seg[0]==1 && seg[1]==1 && seg[2]==0 && seg[3]==1 && seg[4]==1 && seg[5]==0 && seg[6]==1){
                return 2;
            }
            if(seg[0]==1 && seg[1]==1 && seg[2]==1 && seg[3]==1 && seg[4]==0 && seg[5]==0 && seg[6]==1){
               return 3;
            }
            if(seg[0]==1 && seg[1]==1 && seg[2]==1 && seg[3]==0 && seg[4]==0 && seg[5]==1 && seg[6]==0){
                return 4;
            }
            if(seg[0]==1 && seg[1]==0 && seg[2]==1 && seg[3]==1 && seg[4]==0 && seg[5]==1 && seg[6]==1){
                return 5;
            }
            if(seg[0]==1 && seg[1]==0 && seg[2]==1 && seg[3]==1 && seg[4]==1 && seg[5]==1 && seg[6]==1){
                return 6;
            }
            if(seg[0]==0 && seg[1]==1 && seg[2]==1 && seg[3]==0 && seg[4]==0 && seg[5]==0 && seg[6]==1){
                return 7;
            }
            if(seg[0]==1 && seg[1]==1 && seg[2]==1 && seg[3]==1 && seg[4]==1 && seg[5]==1 && seg[6]==1){
                return 8;
            }
            if(seg[0]==1 && seg[1]==1 && seg[2]==1 && seg[3]==1 && seg[4]==0 && seg[5]==1 && seg[6]==1){
                return 9;
            }
            return -1;
        }
        public void print(){
            if(seg[6]==1){
                System.out.print(" _");
            }
            System.out.println();
            if(seg[5]==1){
                System.out.print("|");
            }else{
                System.out.print(" ");
            }
            if(seg[0]==1){
                System.out.print("_");
            }else{
                System.out.print(" ");
            }
            if(seg[1]==1){
                System.out.print("|");
            }
            System.out.println();
            if(seg[4]==1){
                System.out.print("|");
            }else{
                System.out.print(" ");
            }
            if(seg[3]==1){
                System.out.print("_");
            }else{
                System.out.print(" ");
            }
            if(seg[2]==1){
                System.out.print("|");
            }
            System.out.println();
        }
        public int matchesCnt(){
            int cnt=0;
            for(int i=0; i<seg.length; i++){
                if(seg[i]==1) cnt++;
            }
            return cnt;
        }
        public int reMatchesCnt(){
            int cnt=0;
            for(int i=0; i<seg.length; i++){
                if(seg[i]==0) cnt++;
            }
            return cnt;
        }

        public int addMatches(int cnt) {
            if(cnt==1) {
                if (this.value() == 0) seg[0] = 1;
                else if (this.value() == 1) seg[6] = 1;
                else if (this.value() == 2) return 1;
                else if (this.value() == 3) seg[4] = 1;
                else if (this.value() == 4) return 1;
                else if (this.value() == 5) seg[4] = 1;
                else if (this.value() == 6) seg[1] = 1;
                else if (this.value() == 7) return 1;
                else if (this.value() == 8) return 1;
                else if (this.value() == 9) seg[4] = 1;
                else return 1;
            }
            else if(cnt==2){
                if (this.value() == 0) {seg[0]=1; return 1;}
                else if (this.value() == 1) {seg[0]=1; seg[5]=1;}
                else if (this.value() == 2) {seg[2]=1; seg[5]=1;}
                else if (this.value() == 3) {seg[4]=1; seg[5]=1;}
                else if (this.value() == 4) {seg[3]=1; seg[6]=1;}
                else if (this.value() == 5) {seg[4]=1; seg[1]=1;}
                else if (this.value() == 6) {seg[1]=1; return 1;}
                else if (this.value() == 7) {seg[0]=1; seg[3]=1;}
                else if (this.value() == 8) {return 2;}
                else if (this.value() == 9) {seg[4]=1; return 1;}
                else return 2;
            }
            else if(cnt==3){
                if (this.value() == 0) {seg[0]=1; return 2;}
                else if (this.value() == 1) {seg[0]=1; seg[3]=1; seg[6]=1;}
                else if (this.value() == 2) {seg[2]=1; seg[5]=1; return 1;}
                else if (this.value() == 3) {seg[4]=1; seg[5]=1; return 1;}
                else if (this.value() == 4) {seg[3]=1; seg[6]=1; seg[4]=1;}
                else if (this.value() == 5) {seg[4]=1; seg[1]=1; return 1;}
                else if (this.value() == 6) {seg[1]=1; return 2;}
                else if (this.value() == 7) {seg[0]=1; seg[3]=1; seg[5]=1;}
                else if (this.value() == 8) {return 3;}
                else if (this.value() == 9) {seg[4]=1; return 2;}
                else return 3;
            }
            return 0;
        }
        public int rmvMatches(int cnt){
            if(cnt==1){
                if (this.value() == 0) return 1;
                else if (this.value() == 1) return 1;
                else if (this.value() == 2) return 1;
                else if (this.value() == 3) return 1;
                else if (this.value() == 4) return 1;
                else if (this.value() == 5) return 1;
                else if (this.value() == 6) seg[4]=0;
                else if (this.value() == 7) seg[6]=0;
                else if (this.value() == 8) seg[0]=0;
                else if (this.value() == 9) seg[5]=0;
                else return 1;
            }
            else if(cnt==2){
                if (this.value() == 0) return 2;
                else if (this.value() == 1) return 2;
                else if (this.value() == 2) return 2;
                else if (this.value() == 3) {seg[0]=seg[3]=0;}//7
                else if (this.value() == 4) {seg[0]=seg[5]=0;}//1
                else if (this.value() == 5) return 2;
                else if (this.value() == 6) {seg[4]=0; return 1;}//5
                else if (this.value() == 7) {seg[6]=0; return 1;}//1
                else if (this.value() == 8) {seg[4]=seg[5]=0;}//3
                else if (this.value() == 9) {seg[1]=0; return 1;}//5
                else return 2;
            }
            else if(cnt==3){
                if (this.value() == 0) {seg[3]=seg[4]=seg[5]=0;}//7
                else if (this.value() == 1) return 3;
                else if (this.value() == 2) return 3;
                else if (this.value() == 3) {seg[0]=seg[3]=seg[6]=0;}//1
                else if (this.value() == 4) {seg[0]=seg[5]=0; return 1;}//1
                else if (this.value() == 5) return 3;
                else if (this.value() == 6) {seg[4]=0; return 2;}//5
                else if (this.value() == 7) {seg[6]=0; return 2;}//1
                else if (this.value() == 8) {seg[4]=seg[5]=0; return 1;}//3
                else if (this.value() == 9) {seg[0]=seg[3]=seg[5]=0;}//7
                else return 3;
            }
            return 0;
        }
    }
    public static class MatchNumber{
        public MatchDigit[] digits;

        public MatchNumber(){}
        public MatchNumber(int num){
            if(num==0){
                digits = new MatchDigit[1];
                digits[0] = new MatchDigit(0);
                return;
            }
            int cnt = 0;
            while(Math.pow(10,cnt) <= num){
                cnt++;
            }
            digits = new MatchDigit[cnt];
            for(int i=0; i<cnt; i++){
                digits[i] = new MatchDigit(num%10);
                num /= 10;
            }
        }
        public int value(){
            int val = 0;
            for(int i=0; i<digits.length; i++){
                val += digits[i].value() * (int)Math.pow(10,i);
            }
            return val;
        }
        public void print(){
            int len = 3*digits.length;
            char[] line1 = new char[len];
            char[] line2 = new char[len];
            char[] line3 = new char[len];
            for(int i=0; i<len; i++){
                line1[i] = ' ';
                line2[i] = ' ';
                line3[i] = ' ';
            }
            for(int i=digits.length-1; i>=0; i--){
                if(digits[i].seg[6]==1){
                    line1[1+3*(digits.length-i-1)] = '_';
                }
                if(digits[i].seg[5]==1){
                    line2[0+3*(digits.length-i-1)] = '|';
                }
                if(digits[i].seg[4]==1){
                    line3[0+3*(digits.length-i-1)] = '|';
                }
                if(digits[i].seg[3]==1){
                    line3[1+3*(digits.length-i-1)] = '_';
                }
                if(digits[i].seg[2]==1){
                    line3[2+3*(digits.length-i-1)] = '|';
                }
                if(digits[i].seg[1]==1){
                    line2[2+3*(digits.length-i-1)] = '|';
                }
                if(digits[i].seg[0]==1){
                    line2[1+3*(digits.length-i-1)] = '_';
                }
            }
            System.out.println(String.valueOf(line1));
            System.out.println(String.valueOf(line2));
            System.out.println(String.valueOf(line3));
        }
        public int matchesCnt(){
            int cnt=0;
            for(int i=0; i<digits.length; i++){
                cnt += digits[i].matchesCnt();
            }
            return cnt;
        }
        public int reMatchesCnt(){
            int cnt=0;
            for(int i=0; i<digits.length; i++){
                cnt+=digits[i].reMatchesCnt();
            }
            return cnt;
        }

        public int addMatches(int cnt){
            for(int i=0; i<digits.length; i++){
                cnt = digits[i].addMatches(cnt);
                if(cnt==0) return 0;
            }
            return cnt;
        }
        public int rmvMatches(int cnt){
            for(int i=0; i<digits.length; i++){
                cnt = digits[i].rmvMatches(cnt);
                if(cnt==0) return 0;
            }
            return cnt;
        }
        public Pair<Integer,Integer> movMatches(int rmv, int add){
            int i=0;
            while(i<digits.length){
                rmv = digits[i].rmvMatches(rmv);
                i++;
                if(rmv==0) break;
            }
            if(rmv>0){return new Pair<Integer,Integer>(rmv,add);}
            while(i<digits.length){
                add = digits[i].addMatches(add);
                i++;
                if(add==0){return new Pair<Integer,Integer>(0,0);}
            }
            return new Pair<Integer, Integer>(rmv, add);
        }
    }
    public static class MatchExp{
        MatchNumber[] nums;
        char[] ops;

        public MatchExp(){

        }
        public MatchExp(int[] numss, char[] opss){
            if(numss.length - opss.length != 1){
                return;
            }
            this.nums = new MatchNumber[numss.length];
            this.ops = new char[opss.length];
            for(int i=0; i<this.nums.length; i++){
                this.nums[i] = new MatchNumber(numss[i]);
            }
            for(int i=0; i<this.ops.length; i++){
                this.ops[i] = opss[i];
            }
        }
        public MatchExp(String exp){
            exp = rmSpaces(exp);
            Vector<String> nums = new Vector<String>();
            Vector<Character> ops = new Vector<Character>();
            for(int i=0; i<exp.length(); i++){
                if(exp.charAt(i)=='+' || exp.charAt(i)=='-'){
                    nums.add(exp.substring(0,i));
                    ops.add(exp.charAt(i));
                    exp = exp.substring(i+1);
                    i = 0;
                }
            }
            if(!exp.isEmpty()){
                nums.add(exp);
            }
            int[] numss = new int[nums.size()];
            char[] opss = new char[ops.size()];
            for(int i=0; i<numss.length; i++){
                numss[i] = Integer.parseInt(nums.elementAt(i));
            }
            for(int i=0; i<opss.length; i++){
                opss[i] = ops.elementAt(i);
            }
            if(numss.length - opss.length != 1){
                return;
            }
            this.nums = new MatchNumber[numss.length];
            this.ops = new char[opss.length];
            for(int i=0; i<this.nums.length; i++){
                this.nums[i] = new MatchNumber(numss[i]);
            }
            for(int i=0; i<this.ops.length; i++){
                this.ops[i] = opss[i];
            }
        }
        public int value(){
            int a = this.nums[0].value();
            for(int i=0; i<this.ops.length; i++){
                int b = this.nums[1+i].value();
                if(this.ops[i]=='+'){
                    a = a + b;
                }else if(this.ops[i]=='-'){
                    a = a - b;
                }
            }
            return a;
        }
        public void print(){
            String l1 = "";
            String l2 = "";
            String l3 = "";
            for(int i=0; i<ops.length; i++){
                MatchNumber num = this.nums[i];
                int len = 3*num.digits.length;
                char[] line1 = new char[len];
                char[] line2 = new char[len];
                char[] line3 = new char[len];
                for(int j=0; j<len; j++){
                    line1[j] = ' ';
                    line2[j] = ' ';
                    line3[j] = ' ';
                }
                for(int j=num.digits.length-1; j>=0; j--){
                    if(num.digits[j].seg[6]==1){
                        line1[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[5]==1){
                        line2[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[4]==1){
                        line3[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[3]==1){
                        line3[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[2]==1){
                        line3[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[1]==1){
                        line2[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[0]==1){
                        line2[1+3*(num.digits.length-j-1)] = '_';
                    }
                }
                l1 += String.valueOf(line1) + "   ";
                //l2 += String.valueOf(line2) + " " + this.ops[i] + " ";
                if(this.ops[i]=='+'){
                    l2 += String.valueOf(line2) + " + ";
                }else if(this.ops[i]=='-'){
                    l2 += String.valueOf(line2) + " _ ";
                }
                l3 += String.valueOf(line3) + "   ";
            }
            for(int i=this.nums.length-1; i<this.nums.length; i++){
                MatchNumber num = this.nums[i];
                int len = 3*num.digits.length;
                char[] line1 = new char[len];
                char[] line2 = new char[len];
                char[] line3 = new char[len];
                for(int j=0; j<len; j++){
                    line1[j] = ' ';
                    line2[j] = ' ';
                    line3[j] = ' ';
                }
                for(int j=num.digits.length-1; j>=0; j--){
                    if(num.digits[j].seg[6]==1){
                        line1[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[5]==1){
                        line2[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[4]==1){
                        line3[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[3]==1){
                        line3[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[2]==1){
                        line3[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[1]==1){
                        line2[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[0]==1){
                        line2[1+3*(num.digits.length-j-1)] = '_';
                    }
                }
                l1 += String.valueOf(line1);
                l2 += String.valueOf(line2);
                l3 += String.valueOf(line3);
            }
            System.out.println(l1);
            System.out.println(l2);
            System.out.println(l3);
        }
        public int matchesCnt(){
            int cnt=0;
            for(int i=0; i<this.nums.length; i++){
                cnt += nums[i].matchesCnt();
            }
            for(int i=0; i<this.ops.length; i++){
                if(ops[i]=='+'){
                    cnt += 2;
                }else if(ops[i]=='-'){
                    cnt += 1;
                }
            }
            return cnt;
        }
        public int reMatchesCnt(){
            int cnt=0;
            for(int i=0; i<ops.length; i++){
                if(ops[i]=='-') cnt+=1;
            }
            for(int i=0; i<nums.length; i++){
                cnt+=nums[i].reMatchesCnt();
            }
            return cnt;
        }

        public int addMatches(int cnt){
            for(int i=0; i<nums.length; i++){
                cnt = nums[i].addMatches(cnt);
                if(cnt==0) return 0;
            }
            return cnt;
        }
        public int rmvMatches(int cnt){
            for(int i=0; i<ops.length; i++){
                cnt = nums[i].rmvMatches(cnt);
                if(cnt==0) return 0;
                if(ops[i]=='+') {ops[i]='-'; cnt--;}
                if(cnt==0) return 0;
            }
            for(int i=nums.length-1; i<nums.length; i++){
                cnt = nums[i].rmvMatches(cnt);
                if(cnt==0) return 0;
            }
            return cnt;
        }
        public Pair<Integer,Integer> movMatches(int rmv, int add){
            int i=0;
            Pair<Integer,Integer> mov = new Pair<Integer, Integer>(rmv,add);
            while(i<ops.length){
                mov = nums[i].movMatches(mov.first, mov.second);
                if(mov.first>0 && ops[i]=='+'){
                    ops[i]='-';
                    mov.first--;
                }
                i++;
                if(mov.first==0 && mov.second==0) return mov;
            }
            while(i<nums.length){
                mov = nums[i].movMatches(mov.first, mov.second);
                i++;
                if(mov.first==0 && mov.second==0) return mov;
            }
            return mov;
        }
    }
    public static class MatchEqu{
        MatchExp left;
        MatchExp right;

        public MatchEqu(){

        }
        public MatchEqu(MatchExp l, MatchExp r){
            this.left = l;
            this.right = r;
        }
        public MatchEqu(String equ){
            equ = rmSpaces(equ);
            int eq_pos=-1;
            for(int i=0; i<equ.length(); i++){
                if(equ.charAt(i)=='='){
                    if(eq_pos < 0){
                        eq_pos = i;
                    }
                }
            }
            String left = equ.substring(0, eq_pos);
            String right = equ.substring(eq_pos+1);
            this.left = new MatchExp(left);
            this.right = new MatchExp(right);
        }
        public boolean isEstablished(){
            if(this.left.value()==this.right.value()){
                return true;
            }else{
                return false;
            }
        }
        public void print(){
            String l1 = "";
            String l2 = "";
            String l3 = "";
            for(int i=0; i<this.left.ops.length; i++){
                MatchNumber num = this.left.nums[i];
                int len = 3*num.digits.length;
                char[] line1 = new char[len];
                char[] line2 = new char[len];
                char[] line3 = new char[len];
                for(int j=0; j<len; j++){
                    line1[j] = ' ';
                    line2[j] = ' ';
                    line3[j] = ' ';
                }
                for(int j=num.digits.length-1; j>=0; j--){
                    if(num.digits[j].seg[6]==1){
                        line1[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[5]==1){
                        line2[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[4]==1){
                        line3[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[3]==1){
                        line3[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[2]==1){
                        line3[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[1]==1){
                        line2[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[0]==1){
                        line2[1+3*(num.digits.length-j-1)] = '_';
                    }
                }
                l1 += String.valueOf(line1) + "   ";
                //l2 += String.valueOf(line2) + " " + this.ops[i] + " ";
                if(this.left.ops[i]=='+'){
                    l2 += String.valueOf(line2) + " + ";
                }else if(this.left.ops[i]=='-'){
                    l2 += String.valueOf(line2) + " _ ";
                }
                l3 += String.valueOf(line3) + "   ";
            }
            for(int i=this.left.nums.length-1; i<this.left.nums.length; i++){
                MatchNumber num = this.left.nums[i];
                int len = 3*num.digits.length;
                char[] line1 = new char[len];
                char[] line2 = new char[len];
                char[] line3 = new char[len];
                for(int j=0; j<len; j++){
                    line1[j] = ' ';
                    line2[j] = ' ';
                    line3[j] = ' ';
                }
                for(int j=num.digits.length-1; j>=0; j--){
                    if(num.digits[j].seg[6]==1){
                        line1[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[5]==1){
                        line2[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[4]==1){
                        line3[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[3]==1){
                        line3[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[2]==1){
                        line3[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[1]==1){
                        line2[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[0]==1){
                        line2[1+3*(num.digits.length-j-1)] = '_';
                    }
                }
                l1 += String.valueOf(line1);
                l2 += String.valueOf(line2);
                l3 += String.valueOf(line3);
            }
            l1 += "   ";
            l2 += " = ";
            l3 += "   ";
            for(int i=0; i<this.right.ops.length; i++){
                MatchNumber num = this.left.nums[i];
                int len = 3*num.digits.length;
                char[] line1 = new char[len];
                char[] line2 = new char[len];
                char[] line3 = new char[len];
                for(int j=0; j<len; j++){
                    line1[j] = ' ';
                    line2[j] = ' ';
                    line3[j] = ' ';
                }
                for(int j=num.digits.length-1; j>=0; j--){
                    if(num.digits[j].seg[6]==1){
                        line1[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[5]==1){
                        line2[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[4]==1){
                        line3[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[3]==1){
                        line3[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[2]==1){
                        line3[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[1]==1){
                        line2[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[0]==1){
                        line2[1+3*(num.digits.length-j-1)] = '_';
                    }
                }
                l1 += String.valueOf(line1) + "   ";
                //l2 += String.valueOf(line2) + " " + this.ops[i] + " ";
                if(this.right.ops[i]=='+'){
                    l2 += String.valueOf(line2) + " + ";
                }else if(this.right.ops[i]=='-'){
                    l2 += String.valueOf(line2) + " _ ";
                }
                l3 += String.valueOf(line3) + "   ";
            }
            for(int i=this.right.nums.length-1; i<this.right.nums.length; i++){
                MatchNumber num = this.right.nums[i];
                int len = 3*num.digits.length;
                char[] line1 = new char[len];
                char[] line2 = new char[len];
                char[] line3 = new char[len];
                for(int j=0; j<len; j++){
                    line1[j] = ' ';
                    line2[j] = ' ';
                    line3[j] = ' ';
                }
                for(int j=num.digits.length-1; j>=0; j--){
                    if(num.digits[j].seg[6]==1){
                        line1[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[5]==1){
                        line2[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[4]==1){
                        line3[0+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[3]==1){
                        line3[1+3*(num.digits.length-j-1)] = '_';
                    }
                    if(num.digits[j].seg[2]==1){
                        line3[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[1]==1){
                        line2[2+3*(num.digits.length-j-1)] = '|';
                    }
                    if(num.digits[j].seg[0]==1){
                        line2[1+3*(num.digits.length-j-1)] = '_';
                    }
                }
                l1 += String.valueOf(line1);
                l2 += String.valueOf(line2);
                l3 += String.valueOf(line3);
            }
            System.out.println(l1);
            System.out.println(l2);
            System.out.println(l3);
        }
        public int matchesCnt(){
            int cnt=0;
            cnt = this.left.matchesCnt() + 2 + this.right.matchesCnt();
            return cnt;
        }
        public int reMatchesCnt(){
            int cnt=0;
            cnt =left.reMatchesCnt() + right.reMatchesCnt();
            return cnt;
        }

        public int addMatches(int cnt){
            cnt = left.addMatches(cnt);
            if(cnt==0) return 0;
            cnt = right.addMatches(cnt);
            return cnt;
        }
        public int rmvMatches(int cnt){
            cnt = left.rmvMatches(cnt);
            if(cnt==0) return 0;
            cnt = right.rmvMatches(cnt);
            return cnt;
        }
        public int movMatches(int cnt){
            Pair<Integer,Integer> mov = new Pair<Integer, Integer>(cnt,cnt);
            mov=left.movMatches(mov.first, mov.second);
            if(mov.first==0 && mov.second==0) return 0;
            mov=right.movMatches(mov.first, mov.second);
            if(mov.first>0) return -1*mov.first;
            return mov.second;
        }

        public String toStr(){
            String res="";
            for(int i=0; i<left.ops.length; i++){
                res += String.valueOf(left.nums[i].value());
                res += String.valueOf(left.ops[i]);
            }
            for(int i=left.ops.length; i<left.nums.length; i++){
                res += String.valueOf(left.nums[i].value());
            }
            res += "=";
            for(int i=0; i<right.ops.length; i++){
                res += String.valueOf(right.nums[i].value());
                res += String.valueOf(right.ops[i]);
            }
            for(int i=right.ops.length; i<right.nums.length; i++){
                res += String.valueOf(right.nums[i].value());
            }
            return res;
        }
    }
    public static String genEquation(int num_len, int num_cnt){
        String equ_str;
        Random r = new Random();
        //generate an equation string
        if(num_cnt==2){
            int a = r.nextInt(10000)%(int)Math.pow(10,num_len);
            int b = r.nextInt(10000)%(int)Math.pow(10,num_len);
            int op = r.nextInt(2); op = 0;
            int c = op==0?(a+b):a-b;
            equ_str = String.valueOf(a) + (op==0?"+":"-") + String.valueOf(b) + "=" + String.valueOf(c);
        }else {
            int a = r.nextInt(10000)%(int)Math.pow(10,num_len);
            int b = r.nextInt(10000)%(int)Math.pow(10,num_len);
            int op = r.nextInt(2); op = 0;
            int c = op==0?(a+b):a-b;
            equ_str = String.valueOf(a) + (op==0?"+":"-") + String.valueOf(b);
            op = r.nextInt(2); op = 0;
            b = r.nextInt(10000)%(int)Math.pow(10,num_len);
            c = op==0?(c+b):c-b;
            equ_str += (op==0?"+":"-") + String.valueOf(b) + "=" + String.valueOf(c);
        }
        return equ_str;
    }
    public static void main(String[] args) {
        //input
        int num_len = 0;
        int num_cnt = 0;
        int mod = 0;
        int change = 0;
        Scanner s = new Scanner(System.in);

        System.out.print("number length in the left of '=':");
        num_len = s.nextInt();
        if(num_len>3) num_len=3;

        System.out.print("num of numbers in the left of '=':");
        num_cnt = s.nextInt();
        if(num_cnt>3) num_cnt=3;

        System.out.print("game mod(0:add, 1:rmv, 2:mov):");
        mod = s.nextInt();
        mod %= 3;

        System.out.print("num of matches to operate:");
        change = s.nextInt();
        if(change>3) change=3;

        //generate an equation string
        String equ_str = genEquation(num_len, num_cnt);
        MatchEqu euqation = new MatchEqu(equ_str);
        //euqation.print();

        if(mod==0){//need to add
            while(euqation.rmvMatches(change)!=0){
                equ_str = genEquation(num_len, num_cnt);
                euqation = new MatchEqu(equ_str);
            }
            System.out.println("Ok to add");
        }else if(mod==1){//need to rm
            while(euqation.addMatches(change)!=0){
                equ_str = genEquation(num_len, num_cnt);
                euqation = new MatchEqu(equ_str);
            }
            System.out.println("OK to rmv");
        }else if(mod==2){//need to mov
            while(euqation.movMatches(change)!=0){
                equ_str = genEquation(num_len, num_cnt);
                euqation = new MatchEqu(equ_str);
            }
            System.out.println("OK to mov");
        }
        System.out.printf("original equation(for test):%s\n", equ_str);
        euqation.print();
        System.out.println(euqation.toStr());

        String ans;
        System.out.println("answer:");
        ans = s.nextLine();
        ans = s.nextLine();
        while(!ans.equals(equ_str)){
            if(ans.equals("")){
                System.out.printf("Answer: %s\n", equ_str);
                return;
            }
            if(ans.equals("quit")){
                System.out.println("You failed, but this is not the end. Good luck.");
                return;
            }
            System.out.printf("Wrong answer(%s). Try again:\n",ans);
            ans = s.nextLine();
        }
        System.out.println("Right answer. Congratulations!");
    }
}
