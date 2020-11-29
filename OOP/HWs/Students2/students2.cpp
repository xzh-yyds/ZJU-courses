#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;

class student{
private:
    string name;
public:
    //a student's scores, the score of a unselected course is set to be -1
    vector<int> score;
    student(){}

    void init(string stud_name){
        name=stud_name;
        score.clear();
    }
    //compute the average score of all selected courses
    float score_avrg(){
        int cnt=0;
        float avrg=0;
        for(int i=0;i<score.size();i++){
            if(score[i]<=0){
                continue;
            }
            avrg+=score[i];
            cnt++;
        }
        avrg/=cnt;
        return avrg;
    }
    //print all grades of a student in fromat
    void scorePrint(){
        cout<<setw(7)<<left<<setfill(' ')<<name<<" ";
        for(int i=0;i<score.size();i++){
            if(score[i]<=0){
                cout<<setw(9)<<left<<setfill(' ')<<' ';
                continue;
            }
            cout<<setw(8)<<left<<setfill(' ')<<score[i]<<' ';
        }
        cout<<setw(7)<<left<<score_avrg();
    }
};

//count grades by course
class course{
private:
public:
    vector<int> score;
    course(){}
    
    float average(){
        float avrg=0;
        int cnt=0;
        for(int i=0;i<score.size();i++){
            if(score[i]<=0){
                continue;
            }
            cnt++;
            avrg+=score[i];
        }
        avrg/=cnt;
        return avrg;
    }
    int min_score(){
        int min=6;
        for(int i=0;i<score.size();i++){
            if(score[i]<=0) continue;
            min=score[i]<min?score[i]:min;
        }
        return min;
    }
    int max_score(){
        int max=-2;
        for(int i=0;i<score.size();i++){
            if(score[i]<=0) continue;
            max=score[i]>max?score[i]:max;
        }
        return max;
    }
};


int main(){
    //read input from file
    freopen("inputfile.txt","r",stdin);
    string stud_name;
    student stud;
    int course_cnt=10;
    int stud_cnt=0;
    cin>>course_cnt>>stud_cnt;
    vector<student> studs;
    vector<course> courses;
    for(int i=0;i<stud_cnt;i++){
        cin>>stud_name;
        stud.init(stud_name);
        for(int j=0;j<course_cnt;j++){
            int scr;
            cin>>scr;
            stud.score.push_back(scr);
        }
        studs.push_back(stud);
    }
    //count the average, min, and max score of each course
    course crs;
    for(int i=0;i<course_cnt;i++){
        crs.score.clear();
        for(int j=0;j<stud_cnt;j++){
            crs.score.push_back(studs[j].score[i]);
        }
        courses.push_back(crs);
    }
    //print result in a sheet
    cout<<"No.   "<<"name    ";
    for(int i=0;i<course_cnt;i++){
        cout<<"course"<<i+1<<"  ";
    }
    cout<<"average";
    cout<<endl;
    for(int i=0;i<studs.size();i++){
        cout<<setw(6)<<left<<setfill(' ')<<i+1;
        studs[i].scorePrint();
        cout<<endl;
    }
    cout<<"      average ";
    for(int i=0;i<courses.size();i++){
        cout<<setw(8)<<left<<setfill(' ')<<courses[i].average()<<' ';
    }
    cout<<endl;
    cout<<"      min     ";
    for(int i=0;i<courses.size();i++){
        cout<<setw(8)<<left<<setfill(' ')<<courses[i].min_score()<<' ';
    }
    cout<<endl;
    cout<<"      max     ";
    for(int i=0;i<courses.size();i++){
        cout<<setw(8)<<left<<setfill(' ')<<courses[i].max_score()<<' ';
    }
    cout<<endl;

    system("pause");
    return 0;
}