// #include<stdio.h>
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
    println("%d",f);
    println("%d",k);
    return 0;
}