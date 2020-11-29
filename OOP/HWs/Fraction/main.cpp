#include <iostream>
#include "Fraction.h"
using namespace std;

int main(){
	// testing

    Fraction f1;
    cout<<"Fraction f1      f1 = : "<<f1<<endl;
    Fraction f2(2,3);
    cout<<"Fraction f2(2,3) f2 = : "<<f2<<endl;
    Fraction f3(f2);
    cout<<"Fraction f3(f2)  f3 = : "<<f3<<endl;
    cout<<endl;

    Fraction fa(2,3);
    Fraction fb(4,5);
    cout<<"fa = "<<fa<<", fb = "<<fb<<endl;
    cout<<"fa + fb = "<<fa+fb<<endl;
    cout<<"fa - fb = "<<fa-fb<<endl;
    cout<<"fa * fb = "<<fa*fb<<endl;
    cout<<"fa / fb = "<<fa/fb<<endl;
	cout<<endl;

	cout<<"fa + 2   = "<<fa+2<<endl;
    cout<<"fa - 1   = "<<fa-1<<endl;
    cout<<"2 * fb   = "<<2*fb<<endl;
    cout<<"1.2 / fb = "<<1.2/fb<<endl;
	cout<<endl;

    cout<<"fa > fb  : "<<(fa>fb?"True":"False")<<endl;
    cout<<"fa < fb  : "<<(fa<fb?"True":"False")<<endl;
    cout<<"fa == fb : "<<(fa==fb?"True":"False")<<endl;
    cout<<"fa != fb : "<<(fa!=fb?"True":"False")<<endl;
    cout<<"fa >= fb : "<<(fa>=fb?"True":"False")<<endl;
    cout<<"fa <= fb : "<<(fa<=fb?"True":"False")<<endl;
	cout<<endl;

    cout<<"fa > 0.5  : "<<(fa>0.5?"True":"False")<<endl;
    cout<<"fa < 1    : "<<(fa<1?"True":"False")<<endl;
    cout<<"0.8 == fb : "<<(0.8==fb?"True":"False")<<endl;
    cout<<"1.2 != fb : "<<(1.2!=fb?"True":"False")<<endl;
	cout<<endl;

	cout<<"fa to string : "<<fa.frac2string()<<endl;
	cout<<"fa to double : "<<fa.frac2double()<<endl;

	cout<<"cout<<fa : "<<fa<<endl;
	cout<<"Fraction(\"1.414\") : "<<Fraction("1.414")<<endl;

    return 0;
}