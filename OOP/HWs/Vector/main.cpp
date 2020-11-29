#include"Vector.h"
#include<iostream>
using namespace std;

int main(){
    Vector<int> V_int;
    cout<<"After construct V_int with no parameter,"<<endl;
    cout<<"Is V_int empty? "<<(V_int.empty()?"True":"Flase")<<endl;
    V_int.push_back(1);
    V_int.push_back(2);
    V_int.push_back(3);
    cout<<"After 3 push_back operations,"<<endl;
    cout<<"Is V_int empty? "<<(V_int.empty()?"True":"Flase")<<endl;
    cout<<"V_int.size(): "<<V_int.size()<<endl;
    cout<<"V_int[0]: "<<V_int[0]<<endl;
    cout<<"V_int.at(1): "<<V_int.at(1)<<endl;
    cout<<"V_int.at(3): "<<V_int.at(3)<<endl;
    cout<<endl;
    
    Vector<int> V_int_copy(V_int);
    cout<<"After construct V_int_copy by copying V_int,"<<endl;
    cout<<"Is V_int_copy empty? "<<(V_int_copy.empty()?"True":"Flase")<<endl;
    cout<<"V_int_copy.size(): "<<V_int_copy.size()<<endl;
    cout<<"V_int_copy[0]: "<<V_int_copy[0]<<endl;
    cout<<"V_int_copy[1]: "<<V_int_copy[1]<<endl;
    cout<<"V_int_copy[2]: "<<V_int_copy[2]<<endl;
    cout<<endl;

    V_int.clear();
    cout<<"After clear operation,"<<endl;
    cout<<"Is V_int empty? "<<(V_int.empty()?"True":"Flase")<<endl;
    cout<<endl;

    Vector<char> V_char(20);
    V_char.push_back('H');
    V_char.push_back('e');
    V_char.push_back('l');
    V_char.push_back('l');
    V_char.push_back('o');

    for(int i=0;i<V_char.size();i++){
        cout<<V_char[i];
    }
    cout<<endl;

    return 0;
}