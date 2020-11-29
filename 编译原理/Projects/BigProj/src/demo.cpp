int ans;

int gcd(int a,int b){
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
}

int main(){
    ans = gcd(9,36)*gcd(3,6);
    println("ans = %d",ans);
    return 0;
}