// pdadd
// #include"pd.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// extern const date MAXDATE;	// a large date value
// extern const date MINDATE;	// a small date value
// extern const date ERRDATE;	// an error flag

// format: help
// give a help list about supported commands
int main(int argc, char *argv[]){
	// PersonalDiary pd;
    // diaryRead(pd);

    vector<string> para;
    for(int i=0;i<argc;i++){
        para.push_back(argv[i]);
    }
    
    cout<<"Supported commands:"<<endl;
    cout<<"exit:     exit and save modification"<<endl;
    cout<<"pdadd:    add a new entity"<<endl;
    cout<<"pdlist:   list entities in a specific period (all default)"<<endl;
    cout<<"pdshow:   show the entity with a specific date"<<endl;
    cout<<"pdremove: remove the entity with a specific date"<<endl;

    // diaryWrite(pd);

    return 0;
}