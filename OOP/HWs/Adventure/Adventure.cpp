#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;
char inputPath[]="input.txt";

class Room{
    //the definition of a room
public:
    string Name;
    int East;
    int South;
    int West;
    int North;
    //four possible exits: east, south, west, north
    //the value of exits: -1-exit of castle, -2-wall, other-room number

    Room(string nm, int e, int s, int w, int n){
        Name=nm;
        East=e;
        South=s;
        West=w;
        North=n;
    }//the constructor

    //print the room info in format
    void showRoomInfo(){
        int exitcnt=0;
        int exits=0;
        if(East!=-2) {
            exitcnt++;
            exits+=1;
        }//if the east exit is available
        if(South!=-2) {
            exitcnt++;
            exits+=2;
        }//if the south exit is available
        if(West!=-2) {
            exitcnt++;
            exits+=4;
        }//if the west exit is available
        if(North!=-2) {
            exitcnt++;
            exits+=8;
        }//if the north exit is available
        cout<<"Welcome to the "<<Name<<". ";
        cout<<"There "<<(exitcnt==1?"is ":"are ")<<exitcnt<<(exitcnt==1?" exit: ":" exits: ");
        if(exits==0) cout<<".";
        int cnt=0;
        //keep the output format
        if(exits&1) {
            cnt++;
            cout<<"east";
            if(cnt==exitcnt) cout<<".";
            else if(cnt==exitcnt-1) cout<<" and ";
            else cout<<", ";
        }
        if(exits&2) {
            cnt++;
            cout<<"south";
            if(cnt==exitcnt) cout<<".";
            else if(cnt==exitcnt-1) cout<<" and ";
            else cout<<", ";
        }
        if(exits&4) {
            cnt++;
            cout<<"west";
            if(cnt==exitcnt) cout<<".";
            else if(cnt==exitcnt-1) cout<<" and ";
            else cout<<", ";
        }
        if(exits&8) {
            cnt++;
            cout<<"north";
            if(cnt==exitcnt) cout<<".";
            else if(cnt==exitcnt-1) cout<<" and ";
            else cout<<", ";
        }
        cout<<endl;
    }
};

class Castle{
    //the structure of castle
public:
    int RoomNum;
    int MonsterRoom;
    int PrincessRoom;
    int Lobby;
    vector<Room> Rooms;

    Castle(int room_num,int lobby,int monster,int princess){
        RoomNum=room_num;
        Lobby=lobby;
        MonsterRoom=monster;
        PrincessRoom=princess;
        //rooms.resize(room_num*sizeof(Room));
    }//the constructor
};

//a function that can generate an legal castle
Castle CastleGenerate(int n){
    srand((unsigned)time(NULL));
    int lobby=0;
    int mr=rand()%(n*n);
    while(mr==lobby){
        mr=rand()%(n*n);
    }
    int pr=rand()%(n*n);
    while(pr==mr || pr==lobby){
        pr=rand()%(n*n);
    }

    Castle c(n*n,lobby,mr,pr);
    //c.Rooms.resize(n*n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            string name="room"+to_string(i*n+j);
            int east = j+1<n ? i*n+j+1 : -2;
            int south = i+1<n ? (i+1)*n+j : -2;
            int west = j-1>=0 ? i*n+j-1 : -2;
            int north = i-1>=0 ? (i-1)*n+j : -2;
            Room r(name,east,south,west,north);
            c.Rooms.push_back(r);
        }
    }
    c.Rooms[lobby].North=-1;

    return c;
}

void showHint(){
    cout<<"Enter your command:"<<endl;
}//just a hint for command

int main(){
    //freopen(inputPath,"r",stdin);

    //read input data from an input file
    ifstream input;
    input.open(inputPath);
    int n;
    int lobby,monster,princess;
    input>>n;
    input>>lobby>>monster>>princess;
    Castle castle(n,lobby,monster,princess);

    string name;
    int east,south,west,north;
    for(int i=0;i<n;i++){
        input>>name>>east>>south>>west>>north;
        Room r(name,east,south,west,north);
        castle.Rooms.push_back(r);
    }
    input.close();

    //castle=CastleGenerate(n);

    //adventure starts
    string cmd;
    int room=castle.Lobby;
    int findPrincess=0;
    int win=0;
    cout<<"Welcome to CASTLE ADVENTURE! Enjoy it!"<<endl;
    while(room!=-1){
        cout<<endl;
        castle.Rooms[room].showRoomInfo();
        showHint();
        char str[9];
        cin.getline(str,9);
        cmd=str;
        int next=room;
        if(cmd=="go east") next=castle.Rooms[room].East;
        else if(cmd=="go south") next=castle.Rooms[room].South;
        else if(cmd=="go west") next=castle.Rooms[room].West;
        else if(cmd=="go north") next=castle.Rooms[room].North;
        else{
            cout<<"Illegal command!"<<endl;
        }

        if(next==castle.PrincessRoom){
            cout<<"Wow, what a beautiful princess!"<<endl;
            findPrincess=1;
        }//meet the princess and pick up her
        if(next==castle.MonsterRoom){
            win=-1;
            break;
        }//meet the monster and over
        if(next==-2){
            next==room;
            cout<<"Bang! You hit the wall. Be careful!"<<endl;
            continue;
        }//the chosen exit is unavailable
        if(next==-1){
            if(findPrincess==1){
                win=1;
                break;
            }//get out of the castle together with the princess
            cout<<"You forget the princess, you stupid!"<<endl;
            next=room;
        }//find the export of the castle
        room=next;//go to the next room
    }

    if(win==1){
        cout<<"Congratulations!"<<endl;
        cout<<"You have rescued the beautiful princess!"<<endl;
        cout<<"Then you live a happy life with her."<<endl;
    }else if(win==-1){
        if(findPrincess){//the princess died with you
            cout<<"You and the princess died together."<<endl;
            cout<<"What a sad story!"<<endl;
        }else{//you died alone
            cout<<"You came across a monster and died."<<endl;
            cout<<"But it's good news that the princess is still alive."<<endl;
        }
    }
    
    system("pause");
    return 0;
}