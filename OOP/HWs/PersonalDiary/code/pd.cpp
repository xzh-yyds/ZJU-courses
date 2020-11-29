#include"pd.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

// the path of the diary file
char diary_path[]="diary.txt";

date::date(int y, int m, int d){
	year=y;
	month=m;
	day=d;
}
date::date(){
	year=0;
	month=0;
	day=0;
}
date::~date(){

}
	// check the legality of the date
bool date::isLegal(){
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
bool date::operator < (const date& d){
	if(this->year<d.year) return true;
	if(this->year==d.year && this->month<d.month) return true;
	if(this->year==d.year && this->month==d.month && this->day<d.day) return true;
	return false;
}
bool date::operator > (const date& d){
	if(this->year>d.year) return true;
	if(this->year==d.year && this->month>d.month) return true;
	if(this->year==d.year && this->month==d.month && this->day>d.day) return true;
	return false;
}
bool date::operator == (const date& d){
	if(this->year==d.year && this->month==d.month && this->day==d.day) return true;
	return false;
}
bool date::operator != (const date& d){
	if(this->year!=d.year || this->month!=d.month || this->day!=d.day) return true;
	return false;
}
bool date::operator <= (const date& d){
	if(this->year<d.year) return true;
	if(this->year==d.year && this->month<d.month) return true;
	if(this->year==d.year && this->month==d.month && this->day<=d.day) return true;
	return false;
}
bool date::operator >= (const date& d){
	if(this->year>d.year) return true;
	if(this->year==d.year && this->month>d.month) return true;
	if(this->year==d.year && this->month==d.month && this->day>=d.day) return true;
	return false;
}

ostream& operator << (ostream &out, const date &d){
	out<<d.year<<'-'<<setw(2)<<setfill('0')<<d.month<<'-'<<setw(2)<<setfill('0')<<d.day;
	return out;
}// overload << for output
istream& operator >> (istream &in, date &d){
	in>>d.year>>d.month>>d.day;
	return in;
}// overload << for input

const date MAXDATE(9999,13,32); // a large date value
const date MINDATE(0,0,0);		// a small date value
const date ERRDATE(-1,-1,-1);	// an error flag

// the structure of single diary entity

entity::entity(string cont, date dat){
	content=cont;
	Date=dat;
}
entity::entity(){

}
entity::~entity(){

}
date entity::getdate(){
	return Date;
}
string entity::getcontent(){
	return content;
}

PersonalDiary::PersonalDiary(){

}
PersonalDiary::~PersonalDiary(){

}
// this method seems to be useless, or unnecessary
void PersonalDiary::pdpush(entity e){
	entities.push_back(e);
}
// add a entity
void PersonalDiary::pdadd(string cont, date Date){
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
vector<entity> PersonalDiary::pdlist(date start, date end){
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
void PersonalDiary::pdshow(date d){
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
void PersonalDiary::pdremove(date d){
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