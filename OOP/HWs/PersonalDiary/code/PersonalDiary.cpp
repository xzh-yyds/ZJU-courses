#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

// the path of the diary file
char diary_path[]="diary.txt";

// the structure of date, data cannot be accessed directly
class date{
private:
	int year;
	int month;
	int day;
public:
	date(int y, int m, int d){
		year=y;
		month=m;
		day=d;
	}
	date(){
		year=0;
		month=0;
		day=0;
	}
	~date(){

	}
	// check the legality of the date
	bool isLegal(){
		if(month<1 || month>12) return false;
		if(day<1 || day>31) return false;
		if((month==4||month==6||month==9||month==11) && day >30) return false;
		if((year%100 && year%4==0) || (year%100==0 && year%400==0)){
			if(month==2 && day>29) return false;
		}else{
			if(month==2 && day>28) return false;
		}
		return true;
	}
	bool operator < (const date& d){
		if(this->year<d.year) return true;
		if(this->year==d.year && this->month<d.month) return true;
		if(this->year==d.year && this->month==d.month && this->day<d.day) return true;
		return false;
	}
	bool operator > (const date& d){
		if(this->year>d.year) return true;
		if(this->year==d.year && this->month>d.month) return true;
		if(this->year==d.year && this->month==d.month && this->day>d.day) return true;
		return false;
	}
	bool operator == (const date& d){
		if(this->year==d.year && this->month==d.month && this->day==d.day) return true;
		return false;
	}
	bool operator != (const date& d){
		if(this->year!=d.year || this->month!=d.month || this->day!=d.day) return true;
		return false;
	}
	bool operator <= (const date& d){
		if(this->year<d.year) return true;
		if(this->year==d.year && this->month<d.month) return true;
		if(this->year==d.year && this->month==d.month && this->day<=d.day) return true;
		return false;
	}
	bool operator >= (const date& d){
		if(this->year>d.year) return true;
		if(this->year==d.year && this->month>d.month) return true;
		if(this->year==d.year && this->month==d.month && this->day>=d.day) return true;
		return false;
	}
	friend ostream& operator << (ostream &out, const date &d);
	friend istream& operator >> (istream &in, date &d);
};
ostream& operator << (ostream &out, const date &d){
	out<<d.year<<'-'<<setw(2)<<setfill('0')<<d.month<<'-'<<setw(2)<<setfill('0')<<d.day;
	return out;
};// overload << for output
istream& operator >> (istream &in, date &d){
	in>>d.year>>d.month>>d.day;
	return in;
};// overload << for input
const date MAXDATE(9999,13,32); // a large date value
const date MINDATE(0,0,0);		// a small date value
const date ERRDATE(-1,-1,-1);	// an error flag

// the structure of single diary entity
class entity{
private:
	string content;
	date Date;
public:
	entity(string cont, date dat){
		content=cont;
		Date=dat;
	}
	entity(){}
	~entity(){}
	date getdate(){
		return Date;
	}
	string getcontent(){
		return content;
	}
};

// the structure of personal diary
class PersonalDiary{
private:
	vector<entity> entities;
public:
	PersonalDiary(){};
	~PersonalDiary(){};

	// this method seems to be useless, or unnecessary
	void pdpush(entity e){
		entities.push_back(e);
	}
	// add a entity
	void pdadd(string cont, date Date){
		entity new_ent(cont, Date);
		int index;
		// find the insertion possition, to keep the order
		for(index=0;index<entities.size();index++){
			if(entities[index].getdate()>=Date){
				break;
			}
		}
		if(index<entities.size()){
			// if there is already a entity with the same date, replace it by the new one
			if(entities[index].getdate()==Date){
				entities[index]=new_ent;
			}else {
				entities.insert(entities.begin()+index,new_ent);
			}
		}else{
			entities.push_back(new_ent);
		}
	}
	// list/return all selected entities
	vector<entity> pdlist(date start, date end){
		vector<entity> res;
		for(int i=0;i<entities.size();i++){
			date d=entities[i].getdate();
			if(!(start<=d && d<=end)){
				continue;
			}
			res.push_back(entities[i]);
		}
		return res;
	}
	// show the entity with a specific date
	void pdshow(date d){
		if(d==ERRDATE){
			cout<<"ERROR!"<<endl<<endl;
			return;
		}
		for(int i=0;i<entities.size();i++){
			if(d==entities[i].getdate()){
				cout<<entities[i].getcontent()<<endl;
				return;
			}
		}
		// if no entity with such date
		cout<<"Nothing found, check the date inputed."<<endl<<endl;
	}
	// remove the entity with a specific date
	void pdremove(date d){
		if(d==ERRDATE){
			cout<<"ERROR!"<<endl<<endl;
			return;
		}
		for(int i=0;i<entities.size();i++){
			if(d==entities[i].getdate()){
				entities.erase(entities.begin()+i);
				return;
			}
		}
		// if no entity with such date
		cout<<"There is no entity with this date."<<endl<<endl;
	}
};

// an auxiliary function, split a string using a delimiter
vector<string> strSplit(string s,char c){
	vector<string> res;
	int begin=0;
	for(int i=0;i<s.length();i++){
		if(s[i]==c){
			res.push_back(s.substr(begin,i-begin));
			begin=i+1;
		}
	}
	res.push_back(s.substr(begin,s.length()-begin));
	return res;
}
// transform a string to the date format
date str2date(string s){
	int y=0,m=0,d=0;
	for(int i=0;i<s.length();i++){
		if(s[i]==' '){
			s.erase(s.begin()+i);
			i--;
		}
	}
	vector<string> ymd=strSplit(s,'-');
	if(ymd.size()==3){
		y=atoi(ymd[0].c_str());
		m=atoi(ymd[1].c_str());
		d=atoi(ymd[2].c_str());
	}
	date res(y,m,d);
	return res;
}
// read the diary from file
void diaryRead(PersonalDiary& pd){
	ifstream diary;
	diary.open(diary_path);
	
	string cont,line;
	date Date;
	while(1){
		cont.clear();
		getline(diary,line,'\n');
		Date=str2date(line);
		if(!Date.isLegal()){
			break;
		}
		getline(diary,line,'\n');
		while(line!="."){// end reading by '.'
			cont.append(line);
			cont.append("\n");
			getline(diary,line,'\n');
		}
		pd.pdadd(cont,Date);
	}
	
	diary.close();
}
// write/store the diary into the file
void diaryWrite(PersonalDiary& pd){
	ofstream diary;
	diary.open(diary_path);
	
	vector<entity> res=pd.pdlist(MINDATE,MAXDATE);// fetch all entities
	for(int i=0;i<res.size();i++){
		diary<<res[i].getdate()<<endl;
		diary<<res[i].getcontent();
		diary<<"."<<endl;
	}

	diary.close();
}

// hints, for convenience
void commandHint(){
	cout<<"command: ";
}
void dateHint(){
	cout<<"Date:"<<endl;
}
void contentHint(){
	cout<<"Content:"<<endl;
}
void errorHint(){
	cout<<"Illegal command!"<<endl;
}

int main(){
	PersonalDiary pd;
	// read diary date file
	diaryRead(pd);

	string cmd;
	vector<string> para;

	// supported command:
	// pdadd, pdlist, pdshow, pdremove, help, exit
	while(cmd!="exit"){
		commandHint();
		getline(cin,cmd,'\n');
		// eliminate all whitespace in the head
		while(cmd.length()&&cmd[0]==' '){
			cmd.erase(cmd.begin());
		}
		// separate parameters from the command line input
		para=strSplit(cmd,' ');
		// eliminate all white parameters
		for(int i=0;i<para.size();i++){
			if(para[i].length()<=0){
				para.erase(para.begin()+i);
				i--;
			}
		}

		if(para.size() && para[0]=="pdadd"){
			// format 1: pdadd
			// format 2: yyyy-mm-dd
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
				continue;
			}
			if(!Date.isLegal()){
				// warning if the input date is illegal
				cout<<"Illegal date!"<<endl<<endl;	
				continue;
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
		}else if(para.size() && para[0]=="pdlist"){
			// format 1: pdlist
			// format 2: pdlist yyyy-mm-dd yyyy-mm-dd
			date start=MINDATE,end=MAXDATE;
			if(para.size()==3){
				start=str2date(para[1]);
				end=str2date(para[2]);
			}else if(para.size()>3){
				cout<<"Too many parameters!"<<endl<<endl;
				continue;
			}
			vector<entity> res=pd.pdlist(start,end);
			for(int i=0;i<res.size();i++){
				cout<<res[i].getdate()<<endl;
				cout<<res[i].getcontent()<<endl;
			}
		}else if(para.size() && para[0]=="pdshow"){
			// format 1: pdshow
			// format 2: pdshow yyyy-mm-dd
			date Date=ERRDATE;
			string line;
			if(para.size()==2){
				Date=str2date(para[1]);
			}else if(para.size()==1){
				dateHint();
				getline(cin,line,'\n');
				Date=str2date(line);
			}else if(para.size()>2){
				cout<<"Too many parameters!"<<endl<<endl;
				continue;
			}
			if(!Date.isLegal()){
				// warning if the input date is illegal
				cout<<"Illegal date!"<<endl<<endl;
				continue;
			}
			pd.pdshow(Date);
		}else if(para.size() && para[0]=="pdremove"){
			// format 1: pdremove
			// format 2: pdremove yyyy-mm-dd
			date Date=ERRDATE;
			string line;
			if(para.size()==2){
				Date=str2date(para[1]);
			}else if(para.size()==1){
				dateHint();
				getline(cin,line,'\n');
				Date=str2date(line);
			}else if(para.size()>2){
				cout<<"Too many parameters!"<<endl<<endl;
				continue;
			}
			if(!Date.isLegal()){
				// warning if the input date is illegal
				cout<<"Illegal date!"<<endl<<endl;
				continue;
			}
			pd.pdremove(Date);
		}else if(para.size() && para[0]=="help"){
			//format: help
			// give a help list about supported commands
			cout<<"Supported commands:"<<endl;
			cout<<"exit:     exit and save modification"<<endl;
			cout<<"pdadd:    add a new entity"<<endl;
			cout<<"pdlist:   list entities in a specific period (all default)"<<endl;
			cout<<"pdshow:   show the entity with a specific date"<<endl;
			cout<<"pdremove: remove the entity with a specific date"<<endl;
		}else if(para.size()>0){
			// if an unsupported command is typed in
			errorHint();
		}
	}
	
	//save all modification
	diaryWrite(pd);

	system("pause");
	return 0;
}