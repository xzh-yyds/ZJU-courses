#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef unsigned word;

word atom(char* s){
    word w=0;
    int n=strlen(s);
    for(int i=0;i<n;i++){
        w=w<<1+s[i]-'0';
    }
    return w;
}
char* mtoa(word w){
    char *s;
    s=(char*)malloc(33*sizeof(char));
    s[32]='\0';
    for(int i=31;i>=0;i--){
        s[i]=w%2+'0';
        w=w>>1;
    }   
    return s;
}
word madd(word a, word b){
    word fa=a & 0x80000000;
    word fb=b & 0x80000000;
    word res=a+b;
    word f=res & 0x80000000;
    if(fa==fb && fa!=f){
        printf("Addition overflow!\n");
        exit(1);
    }
    return res;
}
word msub(word a, word b){
    b^=0xFFFFFFFF;
    b++;
    return madd(a,b);
}
word mmul(word a, word b){
    word fa=a & 0x80000000;
    word fb=b & 0x80000000;
    word flag=fa!=fb;
    word res=0;
    for(int i=0;i<32;i++){
        // res += b%2?a<<i:0;
        if(b%2) res=madd(res,a<<i);
        b>>=1;
    }
    return res;
}
word mdiv(word a, word b){
    word flag=0;
    if(a & 0x80000000){
        a^=0xFFFFFFFF;
        a=a+1;
        flag=!flag;
    }
    if(b & 0x80000000){
        b^=0xFFFFFFFF;
        b=b+1;
        flag=!flag;
    }
    word res=0;
    while((a&0x80000000)==0 && a>=b) {
        res++;
        a=msub(a,b);
    }
    if(flag){
        res^=0xFFFFFFFF;
        res=res+1;
    }
    return res;
}
word mdiv2(word a, word b){
    word flag=0;
    if(a & 0x80000000){
        a^=0xFFFFFFFF;
        a=a+1;
        flag=!flag;
    }
    if(b & 0x80000000){
        b^=0xFFFFFFFF;
        b=b+1;
        flag=!flag;
    }
    
    word res=0;
    word wa=31;
    word wb=31;
    while((a>>wa)%2==0){
        wa--;
    }
    while((b>>wb)%2==0){
        wb--;
    }
    if(wa<wb){
        return 0;
    }
    for(int i=wa-wb;i>=0;i--){
        res<<=1;
        if((b<<i)<=a){
            res++;
            a-=b<<i;
        }
    }
    if(flag){
        res^=0xFFFFFFFF;
        res=res+1;
    }
    return res;
}
word mmod(word a, word b){
    word fa=a & 0x80000000;
    word fb=b & 0x80000000;
    if(a & 0x80000000){
        a^=0xFFFFFFFF;
        a=a+1;
    }
    if(b & 0x80000000){
        b^=0xFFFFFFFF;
        b=b+1;
    }
    word res=a%b;
    if(fa||fb){
        res^=0xFFFFFFFF;
        res++;
    }
    return res;
}
word ushort2word(unsigned short a){
    word res=a;
    if(a&0x8000){
        res|=0xFFFF0000;
    }else{
        res&=0x0000FFFF;
    }
    return res;
}
unsigned short uchar2ushort(unsigned char a){
    unsigned short res=a;
    if(a&0x80){
        res|=0xFF00;
    }else{
        res&=0x00FF;
    }
    return res;
}

int main(){
    word a=0x00000010;
    word b=0xFFFFFFFD;

    char sa[33],sb[32];
    sa[33]='\0';
    sb[32]='\0';

    // gets(sa);
    // gets(sb);

    // a=atom(sa);
    // b=atom(sb);

    word sum=madd(a,b);
    word dif=msub(a,b);
    word prd=mmul(a,b);
    word quo=mdiv(a,b);
    word quo2=mdiv2(a,b);
    word rem=mmod(a,b);

    printf("a=   %08xH\n",a);
    printf("b=   %08xH\n",b);
    printf("sum: %08xH\n",sum);
    printf("dif: %08xH\n",dif);
    printf("prd: %08xH\n",prd);
    printf("quo: %08xH\n",quo);
    printf("qup2:%08xH\n",quo2);
    printf("rem: %08xH\n",rem);
    printf("\n");

    printf("a=   %sB\n",mtoa(a));
    printf("b=   %sB\n",mtoa(b));
    printf("sum: %sB\n",mtoa(sum));
    printf("dif: %sB\n",mtoa(dif));
    printf("prd: %sB\n",mtoa(prd));
    printf("quo: %sB\n",mtoa(quo));
    printf("qup2:%sB\n",mtoa(quo2));
    printf("rem: %sB\n",mtoa(rem));
    printf("\n");

    unsigned char c=0xFFF0;
    unsigned char d=0x0010;
    unsigned short cc=uchar2ushort(c);
    unsigned short dd=uchar2ushort(d);
    word ccc=ushort2word(cc);
    word ddd=ushort2word(dd);

    printf("c:   %02xH\n",c);
    printf("d:   %02xH\n",d);
    printf("cc:  %04xH\n",cc);
    printf("dd:  %04xH\n",dd);
    printf("ccc: %08xH\n",ccc);
    printf("ddd: %08xH\n",ddd);
    printf("\n");

    printf("c:   %d\n",(char)c);
    printf("d:   %d\n",d);
    printf("cc:  %d\n",(short)cc);
    printf("dd:  %d\n",dd);
    printf("ccc: %d\n",ccc);
    printf("ddd: %d\n",ddd);

    system("pause");
    return 0;
}