// pdadd
#include"pd.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

extern const date MAXDATE;	// a large date value
extern const date MINDATE;	// a small date value
extern const date ERRDATE;	// an error flag

// format 1: pdadd
// format 2: yyyy-mm-dd
int main(int argc, char *argv[]){
	PersonalDiary pd;
    diaryRead(pd);

    vector<string> para;
    for(int i=0;i<argc;i++){
        para.push_back(argv[i]);
    }
    
    string cont,line;
    date Date;
    if(para.size()==1){
        dateHint();
        getline(cin,line,'\n');
        Date=str2date(line);
    }else if(para.size()==2){
        Date=str2date(para[1]);
    }else if(para.size()>2){
        cout<<"Too many parameters!"<<endl<<endl;
        exit(2);
    }
    if(!Date.isLegal()){
        // warning if the input date is illegal
        cout<<"Illegal date!"<<endl<<endl;	
        exit(4);
    }
    // get the conteny of a diary entity
    cont.clear();
    line.clear();
    contentHint();
    int first=1;
    while(line!="."){
        cont.append(line);
        if(first){
            first=0;
        }else{
            cont.append("\n");
        }
        getline(cin,line,'\n');
    }
    pd.pdadd(cont,Date);

    diaryWrite(pd);

    return 0;
}