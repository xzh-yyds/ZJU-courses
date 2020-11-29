#include "Fraction.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

void errorHint(){
    cout<<"The denominator cannot be zero!"<<endl;
}

Fraction::Fraction(){
    numerator=0;
    denominator=1;
}
Fraction::Fraction(int a,int b){
    if(b==0){
        errorHint();
        numerator=0;
        denominator=1;
        return;
    }
    numerator=a;
    denominator=b;
    simplify();
}
Fraction::Fraction(const Fraction& f){
    numerator=f.numerator;
    denominator=f.denominator;
    simplify();
}
Fraction::Fraction(double f){
    string fs=to_string(f);
    *this=Fraction(fs);
}
Fraction::Fraction(string df){
    int index=0;
    while(index<df.length() && df[index]!='.'){
        index++;
    }
    int power=pow(10,df.length()-1-index);
    df.erase(df.begin()+index);
    int num=stoi(df);
    numerator=num;
    denominator=power;
    simplify();
}
Fraction::~Fraction(){

}
void Fraction::simplify(){
    int a=this->numerator;
    int b=this->denominator;
    int flag=a*b>=0?1:-1;
    a=abs(a);
    b=abs(b);
    this->numerator=a;
    this->denominator=b;
    while(b!=0){
        int r=a%b;
        a=b;
        b=r;
    }
    this->numerator/=a;
    this->denominator/=a;
    this->numerator*=flag;
}
Fraction Fraction::operator+(const Fraction& f){
    int num=this->numerator*f.denominator+this->denominator*f.numerator;
    int den=this->denominator*f.denominator;
    return Fraction(num,den);
}
Fraction Fraction::operator-(const Fraction& f){
    int num=this->numerator*f.denominator-this->denominator*f.numerator;
    int den=this->denominator*f.denominator;
    return Fraction(num,den);
}
Fraction Fraction::operator*(const Fraction& f){
    int num=this->numerator*f.numerator;
    int den=this->denominator*f.denominator;
    return Fraction(num,den);
}
Fraction Fraction::operator/(const Fraction& f){
    int num=this->numerator*f.denominator;
    int den=this->denominator*f.numerator;
    return Fraction(num,den);
}

Fraction operator+(const Fraction f, const int x){
    return (Fraction)f+Fraction(x,1);
}
Fraction operator-(const Fraction f, const int x){
    return (Fraction)f-Fraction(x,1);
}
Fraction operator*(const Fraction f, const int x){
    return (Fraction)f*Fraction(x,1);
}
Fraction operator/(const Fraction f, const int x){
    return (Fraction)f/Fraction(x,1);
}

Fraction operator+(const int x, const Fraction& f){
    return Fraction(x,1)+(Fraction)f;
}
Fraction operator-(const int x, const Fraction& f){
    return Fraction(x,1)-(Fraction)f;
}
Fraction operator*(const int x, const Fraction& f){
    return Fraction(x,1)*(Fraction)f;
}
Fraction operator/(const int x, const Fraction& f){
    return Fraction(x,1)/(Fraction)f;
}

Fraction operator+(const Fraction& f, const double x){
    return (Fraction)f+Fraction(x);
}
Fraction operator-(const Fraction& f, const double x){
    return (Fraction)f-Fraction(x);
}
Fraction operator*(const Fraction& f, const double x){
    return (Fraction)f*Fraction(x);
}
Fraction operator/(const Fraction& f, const double x){
    return (Fraction)f/Fraction(x);
}

Fraction operator+(const double x, const Fraction& f){
    return Fraction(x)+(Fraction)f;
}
Fraction operator-(const double x, const Fraction& f){
    return Fraction(x)-(Fraction)f;
}
Fraction operator*(const double x, const Fraction& f){
    return Fraction(x)*(Fraction)f;
}
Fraction operator/(const double x, const Fraction& f){
    return Fraction(x)/(Fraction)f;
}

bool operator<(const Fraction f, const int x){
    return (Fraction)f<Fraction(x,1);
}
bool operator>(const Fraction f, const int x){
    return (Fraction)f>Fraction(x,1);
}
bool operator==(const Fraction f, const int x){
    return (Fraction)f==Fraction(x,1);
}
bool operator!=(const Fraction f, const int x){
    return (Fraction)f!=Fraction(x,1);
}
bool operator<=(const Fraction f, const int x){
    return (Fraction)f<=Fraction(x,1);
}
bool operator>=(const Fraction f, const int x){
    return (Fraction)f>=Fraction(x,1);
}

bool operator>=(const int x, const Fraction f){
    return Fraction(x,1)>=f;
}
bool operator<=(const int x, const Fraction f){
    return Fraction(x,1)<=f;
}
bool operator==(const int x, const Fraction f){
    return Fraction(x,1)==f;
}
bool operator!=(const int x, const Fraction f){
    return Fraction(x,1)!=f;
}
bool operator<(const int x, const Fraction f){
    return Fraction(x,1)<f;
}
bool operator>(const int x, const Fraction f){
    return Fraction(x,1)>f;
}

bool operator<=(const double x, const Fraction f){
    return Fraction(x)<=f;
}
bool operator>=(const double x, const Fraction f){
    return Fraction(x)>=f;
}
bool operator==(const double x, const Fraction f){
    return Fraction(x)==f;
}
bool operator!=(const double x, const Fraction f){
    return Fraction(x)!=f;
}
bool operator<(const double x, const Fraction f){
    return Fraction(x)<f;
}
bool operator>(const double x, const Fraction f){
    return Fraction(x)>f;
}

bool operator<=(const Fraction f, const double x){
    return (Fraction)f<=Fraction(x);
}
bool operator>=(const Fraction f, const double x){
    return (Fraction)f>=Fraction(x);
}
bool operator==(const Fraction f, const double x){
    return (Fraction)f==Fraction(x);
}
bool operator!=(const Fraction f, const double x){
    return (Fraction)f!=Fraction(x);
}
bool operator<(const Fraction f, const double x){
    return (Fraction)f<Fraction(x);
}
bool operator>(const Fraction f, const double x){
    return (Fraction)f>Fraction(x);
}

bool Fraction::operator<(const Fraction f){
    Fraction diff=*this-f;
    if(diff.numerator<0){
        return true;
    }
    return false;
}
bool Fraction::operator>(const Fraction f){
    Fraction diff=*this-f;
    if(diff.numerator>0){
        return true;
    }
    return false;
}
bool Fraction::operator==(const Fraction f){
    Fraction diff=*this-f;
    if(diff.numerator==0){
        return true;
    }
    return false;
}
bool Fraction::operator!=(const Fraction f){
    Fraction diff=*this-f;
    if(diff.numerator!=0){
        return true;
    }
    return false;
}
bool Fraction::operator>=(const Fraction f){
    Fraction diff=*this-f;
    if(diff.numerator>=0){
        return true;
    }
    return false;
}
bool Fraction::operator<=(const Fraction f){
    Fraction diff=*this-f;
    if(diff.numerator<=0){
        return true;
    }
    return false;
}

string Fraction::frac2string(){
    string num=to_string(this->numerator);
    string den=to_string(this->denominator);
    return num+"/"+den;
}
double Fraction::frac2double(){
    double a=numerator;
    double b=denominator;
    return a/b;
}

istream& operator>>(istream& in, Fraction& f){
    // string fstr;
    // in>>fstr;
    // int dsign_ind=fstr.find('/');
    // int num=stoi(fstr.substr(0,dsign_ind));
    // int den=stoi(fstr.substr(dsign_ind+1,fstr.length()-1-dsign_ind));
    // f=Fraction(num,den);

    in>>f.numerator>>f.denominator;
    return in;
}
ostream& operator<<(ostream& out, const Fraction& f){
    Fraction tmp=f;
    out<<tmp.frac2string();
    return out;
}
ifstream& operator>>(ifstream& in, Fraction& f){
    // string fstr;
    // in>>fstr;
    // int dsign_ind=fstr.find('/');
    // int num=stoi(fstr.substr(0,dsign_ind));
    // int den=stoi(fstr.substr(dsign_ind+1,fstr.length()-1-dsign_ind));
    // f=Fraction(num,den);

    in>>f.numerator>>f.denominator;
    return in;
}
ofstream& operator<<(ofstream& out, const Fraction& f){
    Fraction tmp=f;
    string sf=tmp.frac2string();
    char* s=new char[sf.length()+1];
    strcpy(s,sf.c_str());
    out<<s;
    return out;
}