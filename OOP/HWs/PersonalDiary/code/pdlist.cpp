// pdlist
#include"pd.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

extern const date MAXDATE;	// a large date value
extern const date MINDATE;	// a small date value
extern const date ERRDATE;	// an error flag

// format 1: pdlist
// format 2: pdlist yyyy-mm-dd yyyy-mm-dd
int main(int argc, char *argv[]){
	PersonalDiary pd;
    diaryRead(pd);
    
    vector<string> para;
    for(int i=0;i<argc;i++){
        para.push_back(argv[i]);
    }

	date start=MINDATE,end=MAXDATE;
	if(para.size()==3){
		start=str2date(para[1]);
		end=str2date(para[2]);
	}else if(para.size()>3){
		cout<<"Too many parameters!"<<endl<<endl;
		exit(2);
	}else if(para.size()>1 && para.size()<3){
		cout<<"Too few parameters!"<<endl<<endl;
		exit(3);
	}
	vector<entity> res=pd.pdlist(start,end);
	for(int i=0;i<res.size();i++){
		cout<<res[i].getdate()<<endl;
		cout<<res[i].getcontent()<<endl;
	}

	diaryWrite(pd);

    return 0;
}