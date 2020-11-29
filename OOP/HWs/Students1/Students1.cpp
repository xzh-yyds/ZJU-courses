#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
using namespace std;

struct student{
    string name;
    int score1;
    int score2;
    int score3;
    float average;
}students[10];
//the defination of the student record type

int main(){
    int n=10;
    //set the number of students to be 10
    for(int i=0;i<n;i++){
        cin>>students[i].name;
        cin>>students[i].score1;
        cin>>students[i].score2;
        cin>>students[i].score3;
        students[i].average=students[i].score1+students[i].score2+students[i].score3;
        students[i].average/=3;
    }
    //get 10 records from stdin and calculate average score of each student
    float ave_score1,ave_score2,ave_score3;
    int min_score1,min_score2,min_score3;
    min_score1=min_score2=min_score3=6;
    int max_score1,max_score2,max_score3;
    max_score1=max_score2=max_score3=0;
    for(int i=0;i<n;i++){
        ave_score1+=students[i].score1;
        ave_score2+=students[i].score2;
        ave_score3+=students[i].score3;
        min_score1=min_score1<students[i].score1?min_score1:students[i].score1;
        min_score2=min_score2<students[i].score2?min_score2:students[i].score2;
        min_score3=min_score3<students[i].score3?min_score3:students[i].score3;
        max_score1=max_score1>students[i].score1?max_score1:students[i].score1;
        max_score2=max_score2>students[i].score2?max_score2:students[i].score2;
        max_score3=max_score3>students[i].score3?max_score3:students[i].score3;
    }
    ave_score1/=n;
    ave_score2/=n;
    ave_score3/=n;
    //calculate the average, the minimum and the maximum of each score
    cout<<"no    name    score1  score1  score3  average"<<endl;
    for(int i=0;i<n;i++){
        cout<<setw(6)<<left<<setfill(' ')<<i+1;
        cout<<setw(7)<<left<<setfill(' ')<<students[i].name<<" ";
        cout<<setw(8)<<left<<setfill(' ')<<students[i].score1;
        cout<<setw(8)<<left<<setfill(' ')<<students[i].score2;
        cout<<setw(8)<<left<<setfill(' ')<<students[i].score3;
        cout<<setw(7)<<left<<setfill(' ')<<students[i].average;
        cout<<endl;
    }
    cout<<"      "<<"average "<<setw(8)<<ave_score1<<setw(8)<<ave_score2<<ave_score3<<endl;
    cout<<"      "<<"min     "<<setw(8)<<min_score1<<setw(8)<<min_score2<<min_score3<<endl;
    cout<<"      "<<"max     "<<setw(8)<<max_score1<<setw(8)<<max_score2<<max_score3<<endl;
    //output the result in form

    //system("pause");
    return 0;
}