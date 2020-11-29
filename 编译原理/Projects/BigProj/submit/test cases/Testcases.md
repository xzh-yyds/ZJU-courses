### T1.c
```c++
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
```

### T4.c
```C++
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
```

### T2.c
```C++
int f,k;
int go(int b,int a){
    int fk;
    double t;
    if(a>0){
        return a*go(b,a-1);
    }else{
        return 1;
    }
}

int main(){
    k = 0;
    f = go(k,5);
    println("%d\n",f);
    println("%d\n",k);
    return 0;
}
```