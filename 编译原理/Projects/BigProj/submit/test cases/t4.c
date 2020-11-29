int main(){
    int a = 13%5;

    a += 3+2*2-12/4;

    println("a = %d",a);

    int b = a==4 ? 1 : 2;

    a+= a,b,1,2,3,4;

    println("a = %d",a);

    while(a<100){
        b+=a;
        a+=1;
    }

    println("a = %d",a);
    println("b = %d",b);
    return 0;
}