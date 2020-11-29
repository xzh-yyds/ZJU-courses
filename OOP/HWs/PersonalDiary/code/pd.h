#ifndef PD_H
#define PD_H

#include<string>
#include<iostream>
#include<vector>
using namespace std;

// the path of the diary file
// char diary_path[]="diary.txt";

// the structure of date, data cannot be accessed directly
class date{
private:
	int year;
	int month;
	int day;
public:
	date(int y, int m, int d);
	date();
	~date();
	// check the legality of the date
	bool isLegal();
	bool operator < (const date& d);
	bool operator > (const date& d);
	bool operator == (const date& d);
	bool operator != (const date& d);
	bool operator <= (const date& d);
	bool operator >= (const date& d);
	friend ostream& operator << (ostream &out, const date &d);
	friend istream& operator >> (istream &in, date &d);
};

// const date MAXDATE(9999,13,32); // a large date value
// const date MINDATE(0,0,0);		// a small date value
// const date ERRDATE(-1,-1,-1);	// an error flag
extern const date MAXDATE;	// a large date value
extern const date MINDATE;	// a small date value
extern const date ERRDATE;	// an error flag

// the structure of single diary entity
class entity{
private:
	string content;
	date Date;
public:
	entity(string cont, date dat);
	entity();
	~entity();
	date getdate();
	string getcontent();
};

// the structure of personal diary
class PersonalDiary{
private:
	vector<entity> entities;
public:
	PersonalDiary();
	~PersonalDiary();

	// this method seems to be useless, or unnecessary
	void pdpush(entity e);
	// add a entity
	void pdadd(string cont, date Date);
	// list/return all selected entities
	vector<entity> pdlist(date start, date end);
	// show the entity with a specific date
	void pdshow(date d);
	// remove the entity with a specific date
	void pdremove(date d);
};

// an auxiliary function, split a string using a delimiter
vector<string> strSplit(string s,char c);

// transform a string to the date format
date str2date(string s);
// read the diary from file
void diaryRead(PersonalDiary& pd);
// write/store the diary into the file
void diaryWrite(PersonalDiary& pd);

// hints, for convenience
void commandHint();
void dateHint();
void contentHint();
void errorHint();

#endif