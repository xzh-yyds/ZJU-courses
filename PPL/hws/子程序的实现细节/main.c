#include <stdio.h>

struct tuple5{
    int a0;
    int a1;
    int a2;
    int a3;
    int a4;
};

int func1(int a, int b){
    if(a > b){
        int c;
        c = a - b;
        return c;
    }else{
        int d;
        int c = 1;
        d = b - a;
        return d;
    }
    return 0;
}

struct tuple5 func2(int a, int b){
    struct tuple5 t;
    if(a > b){
        t.a0 = t.a1 = t.a2 = t.a3 = t.a4 = a;
    }else{
        t.a0 = t.a1 = t.a2 = t.a3 = t.a4 = b;
    }
    return t;
}

struct tuple5 func3(int a, int b){
    struct tuple5 t;
    if(a < b){
        t.a0 = t.a1 = t.a2 = t.a3 = t.a4 = a;
    }else{
        t.a0 = t.a1 = t.a2 = t.a3 = t.a4 = b;
    }
    return t;
}

int main(){
    int a = 0;
    a = func1(1, 2);
    struct tuple5 t1;
    t1 = func2(2, 3);
    struct tuple5 t2;
    t2 = func3(2, 3);
    printf("%d\n", a);
    printf("%d\n", t1.a0+t2.a0);
    return 0;
}