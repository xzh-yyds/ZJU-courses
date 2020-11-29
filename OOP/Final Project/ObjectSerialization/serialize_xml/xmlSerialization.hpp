#pragma once

#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <list>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstring>

using namespace std;

#define LB_BEGIN 0
#define LB_END 1
#define LB_SINGLE 2

// an auxiliary function for error reporting
void errHint(string msg){
    cout << "Error: " << msg << endl;
}

// namespace
namespace xmlSerialization{

// the class of a xml label
class xmlLabel{
public:
    int type;
    string name;
    int level;
public:
    xmlLabel(){

    }
    xmlLabel(string s, int l, int t){
        this->name = s;
        this->level = l;
        this->type = t;
    }
    // ctor a xml label from a line in text
    xmlLabel(string line){
        int lv;
        int i=0;
        while(i<line.length()){
            if(line[i] != ' '){
                lv = i/4;
                break;
            }
            i++;
        }
        string lbstr = line.substr(i, line.length()-i);
        if(lbstr.length()<=2){
            errHint("invalid label: " + lbstr + " of lv " + to_string(lv));
            exit(0);
        }
        if(lbstr.front()!='<' || lbstr.back()!='>'){
            errHint("illegal label: " + lbstr);
            exit(0);
        }
        int lbtype = LB_BEGIN;
        // cout << lbstr << endl;
        if(lbstr[1] == '/'){
            lbtype == LB_END;
        }
        if(lbstr[lbstr.length()-2] == '/'){
            lbtype == LB_SINGLE;
        }
        this->name = lbstr;
        this->level = lv;
        this->type = lbtype;
    }
};

class xmlText{
public:
    string head;
    vector<xmlLabel> labels;

    xmlText(){

    }
};

// overload << and >> for stringifying variables
template<class T>
ostream& operator<<(ostream &out, vector<T> x){
    out << "vector";
    return out;
}
template<class T>
ostream& operator<<(ostream &out, queue<T> x){
    out << "queue";
    return out;
}
template<class T>
ostream& operator<<(ostream &out, deque<T> x){
    out << "deque";
    return out;
}
template<class T>
ostream& operator<<(ostream &out, stack<T> x){
    out << "stack";
    return out;
}
template<class T1, class T2>
ostream& operator<<(ostream &out, pair<T1,T2> x){
    out << "pair";
    return out;
}
template<class T1, class T2>
ostream& operator<<(ostream &out, map<T1,T2> x){
    out << "map";
    return out;
}
template<class T>
ostream& operator<<(ostream &out, list<T> x){
    out << "list";
    return out;
}
template<class T>
ostream& operator<<(ostream &out, set<T> x){
    out << "set";
    return out;
}

template<class T>
istream& operator>>(istream &in, list<T> x){
    // out << "list";
    return in;
}
template<class T>
istream& operator>>(istream &in, vector<T> x){
    // out << "vector";
    return in;
}
template<class T>
istream& operator>>(istream &in, queue<T> x){
    // out << "queue";
    return in;
}
template<class T>
istream& operator>>(istream &in, deque<T> x){
    // out << "deque";
    return in;
}
template<class T>
istream& operator>>(istream &in, stack<T> x){
    // out << "stack";
    return in;
}
template<class T>
istream& operator>>(istream &in, set<T> x){
    // out << "set";
    return in;
}
template<class T1, class T2>
istream& operator>>(istream &in, pair<T1,T2> x){
    // out << "list";
    return in;
}
template<class T1, class T2>
istream& operator>>(istream &in, map<T1,T2> x){
    // out << "list";
    return in;
}

// for <T1,T2>, get T1 and T2
vector<string> getSubTypes(string s){
    char c = ',';
    vector<string> res;
    int begin = 0;
    int layer = 0;
    for(int i=0;i<s.length();i++){
        if(s[i] == '<'){
            layer++;
            continue;
        }
        if(s[i] == '>'){
            layer--;
            continue;
        }
        if(s[i]==c && layer==0){
            res.push_back(s.substr(begin,i-begin));
            begin=i+1;
        }
    }
    res.push_back(s.substr(begin,s.length()-begin));
    return res;
}

// remove blanks from a string
void str_rm_blanks(string& s){
    for(int i=0; i<s.length(); i++){
        if(s[i]==' ' || s[i]=='\t'){
            s.erase(s.begin() + i);
            i--;
        }
    }
}

// split a string with some char
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

// check if a type is basic type
// that is, has no sub type
bool isBasicType(string type){
    if(type == "int"){
        return true;
    }
    else if(type == "short"){
        return true;
    }
    else if(type == "long_long"){
        return true;
    }
    else if(type == "unsigned_int"){
        return true;
    }
    else if(type == "unsigned_short"){
        return true;
    }
    else if(type == "unsigned_long_long"){
        return true;
    }

    else if(type == "float"){
        return true;
    }
    else if(type == "double"){
        return true;
    }

    else if(type == "char"){
        return true;
    }
    else if(type == "unsigned_char"){
        return true;
    }
    else if(type == "std_string"){
        return true;
    }    

    return false;
}

// for <...>, get the content between < and >
string strInBrackets(string s){
    int status = 0;
    string res;
    int l = 0;
    int r = s.length()-1;
    while(l <= r){
        if(s[l] == '<'){
            status |= 1;
            break;
        }
        l++;
    }
    while(l<=r){
        if(s[r] == '>'){
            status |= 2;
            break;
        }
        r--;
    }
    if(l < r){
        res = s.substr(l+1, r-l-1);
    }
    if(status&1 != (status&2)>>1){
        errHint("mismatch < > for " + s);
        exit(0);
    }
    return res;
}

// true->"true", false->"false"
string toStr(bool x){
    string s = x ? "true" : "false";
    return s;
}

// in fact, this is an overload to remain blanks when use the function
string toStr(string x){
    string s = x;
    return s;
}

// get a string from a variable
template<class T>
string toStr(T x){
    stringstream ss;
    ss << x;
    string s;
    ss >> s;
    return s;
}

// the reverse of toStr(string s)
void strTo(string s, string &x){
    x = s;
    // cout << s << " " << x << endl;
}

// the reverse of toStr(T x)
template<class T>
void strTo(string s, T &x){
    stringstream ss;
    ss << s;
    ss >> x;
    // cout << s << " " << x << endl;
}


template<class T>
vector<xmlLabel> xml_serialize(T x, int lv, string type);

// write xml labels to a xml file
void write_xml(vector<xmlLabel> lbs, string outfile){
    fstream out;
    out.open(outfile, fstream::out);
    for(int i=0; i<lbs.size(); i++){
        for(int j=0; j<lbs[i].level; j++){
            out << "    ";
        }
        out << lbs[i].name << endl;
    }
    out.close();
}

// read xml labels from a xml file
void read_xml(vector<xmlLabel>& lbs, string infile){
    fstream xml_in;
    xml_in.open(infile, fstream::in);
    string line;
    getline(xml_in, line);
    while(line != ""){
        xmlLabel lb(line);
        lbs.push_back(lb);
        getline(xml_in, line);
    }
    xml_in.close();
}

// serialize a bool
vector<xmlLabel> xml_serialize_bool(bool x, int lv){
    vector<xmlLabel> res;
    xmlLabel begin;
    string boolstr = x ? "true" : "false";
    string name = "<bool val=\"" + boolstr + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a short
vector<xmlLabel> xml_serialize_short(short x, int lv){
    vector<xmlLabel> res;
    xmlLabel begin;
    string name = "<short val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a int
vector<xmlLabel> xml_serialize_int(int x, int lv){
    vector<xmlLabel> res;
    xmlLabel begin;
    string name = "<int val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a long long int
vector<xmlLabel> xml_serialize_llint(long long x, int lv){
    vector<xmlLabel> res;
    xmlLabel begin;
    string name = "<long_long val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a unsigned short
vector<xmlLabel> xml_serialize_ushort(unsigned short x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<unsigned_short val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a unsigned int
vector<xmlLabel> xml_serialize_uint(unsigned int x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<unsigned_int val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a unsigned long long int
vector<xmlLabel> xml_serialize_ullint(unsigned long long x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<unsigned_long_long val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a float
vector<xmlLabel> xml_serialize_flt(float x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<float val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a double
vector<xmlLabel> xml_serialize_dbl(double x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<double val=\"" + to_string(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a char
vector<xmlLabel> xml_serialize_char(char x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<char val=\"" +toStr(x)+ "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a unsigned char
vector<xmlLabel> xml_serialize_uchar(unsigned char x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<unsigned_char val=\"" + toStr(x) + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}
// serialize a string
vector<xmlLabel> xml_serialize_str(string x, int lv){
    vector<xmlLabel> res;
    xmlText xmldoc;
    xmlLabel begin;
    string name = "<std_string val=\"" + x + "\"/>";
    xmlLabel lb(name, lv, LB_SINGLE);
    res.push_back(lb);
    return res;
}

template<class T> //vector
vector<xmlLabel> xml_serialize(vector<T> x, int lv, string type){
    if(type.find("std_vector")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_vector: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    string begin = "<std_vector>";
    string end = "</std_vector>";
    xmlLabel lb1(begin, lv, LB_BEGIN);
    xmlLabel lb2(end, lv, LB_END);
    res.push_back(lb1);
    for(int i=0; i<x.size(); i++){
        // cout << x[i] << type << endl;
        vector<xmlLabel> ele = xml_serialize(x[i], lv+1, type);
        for(int j=0; j<ele.size(); j++){
            res.push_back(ele[j]);
        }
    }
    res.push_back(lb2);
    return res;
}

template<class T> //queue
vector<xmlLabel> xml_serialize(queue<T> x, int lv, string type){
    if(type.find("std_queue")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_queue: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    string begin = "<std_queue>";
    string end = "</std_queue>";
    xmlLabel lb1(begin, lv, LB_BEGIN);
    xmlLabel lb2(end, lv, LB_END);
    res.push_back(lb1);

    while(!x.empty()){
        vector<xmlLabel> ele = xml_serialize(x.front(), lv+1, type);
        for(int j=0; j<ele.size(); j++){
            res.push_back(ele[j]);
        }
        x.pop();
    }
    res.push_back(lb2);
    return res;
}

template<class T> //deque
vector<xmlLabel> xml_serialize(deque<T> x, int lv, string type){
    if(type.find("std_deque")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_deque: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    string begin = "<std_deque>";
    string end = "</std_deque>";
    xmlLabel lb1(begin, lv, LB_BEGIN);
    xmlLabel lb2(end, lv, LB_END);
    res.push_back(lb1);

    for(int i=0; i<x.size(); i++){
        // cout << x[i] << type << endl;
        vector<xmlLabel> ele = xml_serialize(x[i], lv+1, type);
        for(int j=0; j<ele.size(); j++){
            res.push_back(ele[j]);
        }
    }
    res.push_back(lb2);
    return res;
}

template<class T> //stack
vector<xmlLabel> xml_serialize(stack<T> x, int lv, string type){
    if(type.find("std_stack")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_stack: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    string begin = "<std_stack>";
    string end = "</std_stack>";
    xmlLabel lb1(begin, lv, LB_BEGIN);
    xmlLabel lb2(end, lv, LB_END);
    res.push_back(lb1);

    while(!x.empty()){
        vector<xmlLabel> ele = xml_serialize(x.top(), lv+1, type);
        for(int j=0; j<ele.size(); j++){
            res.push_back(ele[j]);
        }
        x.pop();
    }
    res.push_back(lb2);
    return res;
}

template<class T1, class T2> //pair
vector<xmlLabel> xml_serialize(pair<T1,T2> x, int lv, string type){
    if(type.find("std_pair")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_pair!");
        exit(0);
    }

    // cout << "pair: " << type << endl;
    vector<string> types = getSubTypes(type);
    if(types.size() < 2){
        errHint("less than 2 subtypes for std_pair");
        exit(0);
    }
    if(types.size() > 2){
        errHint("more than 2 subtypes for std_pair");
        exit(0);
    }
    string t1 = types[0];
    string t2 = types[1];
    // cout << "pair:" << t1 << " " << t2 << endl;

    vector<xmlLabel> res;

    string beg = "<std_pair>";
    string end = "</std_pair>";
    xmlLabel pair_beg(beg, lv, LB_BEGIN);
    xmlLabel pair_end(end, lv, LB_END);
    res.push_back(pair_beg);

    if(isBasicType(t1)){
        string first = "<first val=\"" + toStr(x.first) + "\"/>";
        xmlLabel lb_first(first, lv+1, LB_SINGLE);
        res.push_back(lb_first);
    }else{
        xmlLabel first_beg("<first>", lv+1, LB_BEGIN);
        xmlLabel first_end("</first>", lv+1, LB_END);
        res.push_back(first_beg);
        vector<xmlLabel> firsts = xml_serialize(x.first, lv+2, t1);
        for(int i=0; i<firsts.size(); i++){
            res.push_back(firsts[i]);
        }
        res.push_back(first_end);
    }

    if(isBasicType(t2)){
        string scd = "<second val=\"" + toStr(x.second) + "\"/>";
        xmlLabel lb_scd(scd, lv+1, LB_SINGLE);
        res.push_back(lb_scd);
    }else{
        xmlLabel scd_beg("<second>", lv+1, LB_BEGIN);
        xmlLabel scd_end("</second>", lv+1, LB_END);
        res.push_back(scd_beg);
        vector<xmlLabel> scds = xml_serialize(x.second, lv+2, t2);
        for(int i=0; i<scds.size(); i++){
            res.push_back(scds[i]);
        }
        res.push_back(scd_end);
    }
    
    res.push_back(pair_end);
    
    return res;
}

template<class T1, class T2> //map
vector<xmlLabel> xml_serialize(map<T1,T2> x, int lv, string type){
    if(type.find("std_map")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_map!");
        exit(0);
    }

    vector<string> types = getSubTypes(type);
    if(types.size() < 2){
        errHint("less than 2 subtypes for std_map");
        exit(0);
    }
    if(types.size() > 2){
        errHint("more than 2 subtypes for std_map");
        exit(0);
    }
    string t1 = types[0];
    string t2 = types[1];

    vector<xmlLabel> res;

    xmlLabel map_begin("<std_map>", lv, LB_BEGIN);
    xmlLabel map_end("</std_map>", lv, LB_END);
    res.push_back(map_begin);

    xmlLabel item_begin("<std_map_item>", lv+1, LB_BEGIN);
    xmlLabel item_end("</std_map_item>", lv+1, LB_END);

    for(auto it=x.begin(); it!=x.end(); it++){
        res.push_back(item_begin);
        if(isBasicType(t1)){
            string key = "<key val=\"" + toStr(it->first) + "\"/>";
            xmlLabel lb_key(key, lv+2, LB_SINGLE);
            res.push_back(lb_key);
        }else{
            xmlLabel key_begin("<key>", lv+2, LB_BEGIN);
            xmlLabel key_end("</key>", lv+2, LB_END);
            res.push_back(key_begin);

            vector<xmlLabel> keys = xml_serialize(it->first, lv+3, t1);
            for(int i=0; i<keys.size(); i++){
                res.push_back(keys[i]);
            }
            res.push_back(key_end);
        }

        if(isBasicType(t2)){
            string value = "<value val=\"" + toStr(it->second) + "\"/>";
            xmlLabel lb_value(value, lv+2, LB_SINGLE);
            res.push_back(lb_value);
        }else{
            xmlLabel value_begin("<value>", lv+2, LB_BEGIN);
            xmlLabel value_end("</value>", lv+2, LB_END);
            res.push_back(value_begin);

            vector<xmlLabel> values = xml_serialize(it->second, lv+3, t2);
            for(int i=0; i<values.size(); i++){
                res.push_back(values[i]);
            }
            res.push_back(value_end);
        }
        res.push_back(item_end);
    }

    res.push_back(map_end);
    return res;
}

template<class T> //list
vector<xmlLabel> xml_serialize(list<T> x, int lv, string type){
    if(type.find("std_list")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_list!");
        exit(0);
    }

    vector<xmlLabel> res;
    string begin = "<std_list>";
    string end = "</std_list>";
    xmlLabel lb1(begin, lv, LB_BEGIN);
    xmlLabel lb2(end, lv, LB_END);
    res.push_back(lb1);

    for(auto it=x.begin(); it!=x.end(); it++){
        // cout << x[i] << type << endl;
        vector<xmlLabel> ele = xml_serialize(*it, lv+1, type);
        for(int j=0; j<ele.size(); j++){
            res.push_back(ele[j]);
        }
    }
    res.push_back(lb2);
    return res;
}

template<class T> //set
vector<xmlLabel> xml_serialize(set<T> x, int lv, string type){
    string elem_type;
    if(type.find("std_set")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_set: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    string begin = "<std_set>";
    string end = "</std_set>";
    xmlLabel lb1(begin, lv, LB_BEGIN);
    xmlLabel lb2(end, lv, LB_END);
    res.push_back(lb1);

    for(auto it=x.begin(); it!=x.end(); it++){
        // cout << x[i] << type << endl;
        vector<xmlLabel> ele = xml_serialize(*it, lv+1, elem_type);
        for(int j=0; j<ele.size(); j++){
            res.push_back(ele[j]);
        }
    }
    res.push_back(lb2);
    return res;
}

template<class T> //basic types
vector<xmlLabel> xml_serialize(T x, int lv, string type){
    string prim;
    int i=0;
    while(i < type.length()){
        if(type[i]=='<'){
            break;
        }
        i++;
    }
    prim = type.substr(0, i);
    
    // cout << prim << endl;
    string s = toStr(x);
    vector<xmlLabel> res;

    if(prim == "int"){
        return xml_serialize_int(stoi(s), lv);
    }
    else if(prim == "short"){
        return xml_serialize_short((short)stoi(s), lv);
    }
    else if(prim == "long_long"){
        return xml_serialize_llint(stoll(s), lv);
    }
    else if(prim == "unsigned_int"){
        return xml_serialize_uint(stoul(s), lv);
    }
    else if(prim == "unsigned_short"){
        return xml_serialize_ushort((unsigned short)stoul(s), lv);
    }
    else if(prim == "unsigned_long_long"){
        return xml_serialize_ullint(stoull(s), lv);
    }
    
    else if(prim == "bool"){
        bool tmp = false;
        if(s == "true"){
            tmp = true;
        }else if(s == "false"){
            tmp = false;
        }else{
            errHint("invalid bool var: " + s);
            exit(0);
        }
        return xml_serialize_bool(tmp, lv);
    }
    else if(prim == "char"){
        return xml_serialize_char(s[0], lv);
    }
    else if(prim == "unsigned_char"){
        return xml_serialize_uchar(s[0], lv);
    }
    else if(prim == "float"){
        return xml_serialize_flt(stof(s), lv);
    }
    else if(prim == "double"){
        return xml_serialize_dbl(stod(s), lv);
    }
    else if(prim == "std_string"){
        return xml_serialize_str(s, lv);
    }
    else if(prim == "std_vector"){
        return xml_serialize(x, lv, type);
    }
    else if(prim == "std_pair"){
        return xml_serialize(x, lv, type);
    }
    else if(prim == "std_map"){
        return xml_serialize(x, lv, type);
    }
    else if(prim == "std_list"){
        return xml_serialize(x, lv, type);
    }
    
    return xml_serialize(x, lv, type);
}

template<class T> //unique_ptr
vector<xmlLabel> xml_serialize(unique_ptr<T> &p, int lv, string type){
    string elem_type;
    if(type.find("std_unique_ptr")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid type for std_unique_ptr: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    xmlLabel lb_begin("<std_unique_ptr>", lv, LB_BEGIN);
    xmlLabel lb_end("</std_unique_ptr>", lv, LB_END);
    res.push_back(lb_begin);

    if(p == NULL){
        xmlLabel lb_null("<nullptr/>", lv+1, LB_SINGLE);
        res.push_back(lb_null);
        res.push_back(lb_end);
        return res;
    }

    T tmp = *p;
    vector<xmlLabel> elemlbs = xml_serialize(tmp, lv+1, elem_type);
    while(!elemlbs.empty()){
        res.push_back(elemlbs.front());
        elemlbs.erase(elemlbs.begin());
    }    
    res.push_back(lb_end);
    return res;
}

template<class T> //shared_ptr
vector<xmlLabel> xml_serialize(shared_ptr<T> p, int lv, string type){
    string elem_type;
    if(type.find("std_shared_ptr")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid type for std_shared_ptr: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    xmlLabel lb_begin("<std_shared_ptr>", lv, LB_BEGIN);
    xmlLabel lb_end("</std_shared_ptr>", lv, LB_END);
    res.push_back(lb_begin);

    if(p == NULL){
        xmlLabel lb_null("<nullptr/>", lv+1, LB_SINGLE);
        res.push_back(lb_null);
        res.push_back(lb_end);
        return res;
    }

    T tmp = *p;
    vector<xmlLabel> elemlbs = xml_serialize(tmp, lv+1, elem_type);
    while(!elemlbs.empty()){
        res.push_back(elemlbs.front());
        elemlbs.erase(elemlbs.begin());
    }    
    res.push_back(lb_end);
    return res;
}

template<class T> //weak_ptr
vector<xmlLabel> xml_serialize(weak_ptr<T> p, int lv, string type){
    string elem_type;
    if(type.find("std_weak_ptr")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid type for std_weak_ptr: " + type);
        exit(0);
    }

    vector<xmlLabel> res;
    xmlLabel lb_begin("<std_weak_ptr>", lv, LB_BEGIN);
    xmlLabel lb_end("</std_weak_ptr>", lv, LB_END);
    res.push_back(lb_begin);

    if(p.lock() == NULL){
        xmlLabel lb_null("<nullptr/>", lv+1, LB_SINGLE);
        res.push_back(lb_null);
        res.push_back(lb_end);
        return res;
    }

    T tmp = *(p.lock());
    vector<xmlLabel> elemlbs = xml_serialize(tmp, lv+1, elem_type);
    while(!elemlbs.empty()){
        res.push_back(elemlbs.front());
        elemlbs.erase(elemlbs.begin());
    }    
    res.push_back(lb_end);
    return res;
}

template<class T> // add a layer of packaging
void xmlSerialize(T x, string type, string outfile){
    int lv=0;
    xmlLabel begin("<serialization>", lv, LB_BEGIN);
    xmlLabel end("</serialization>", lv, LB_END);

    vector<xmlLabel> lbs;
    lbs.push_back(begin);

    vector<xmlLabel> res = xml_serialize(x, lv+1, type);
    for(int i=0; i<res.size(); i++){
        lbs.push_back(res[i]);
    }

    lbs.push_back(end);
    write_xml(lbs, outfile);
}

template<class T> //the unique_ptr version of adding a layer of packaging
void xmlSerialize(unique_ptr<T> &p, string type, string outfile){
    int lv=0;
    xmlLabel begin("<serialization>", lv, LB_BEGIN);
    xmlLabel end("</serialization>", lv, LB_END);

    vector<xmlLabel> lbs;
    lbs.push_back(begin);

    vector<xmlLabel> res = xml_serialize(p, lv+1, type);
    for(int i=0; i<res.size(); i++){
        lbs.push_back(res[i]);
    }

    lbs.push_back(end);
    write_xml(lbs, outfile);
}

// for <xxx>, get xxx
string getLabelName(xmlLabel lb){
    string lbstr = lb.name;
    int begin = 1;
    if(lbstr[1] == '/'){
        begin = 2;
    }
    int end = begin;
    while(end<lbstr.length() && lbstr[end] != ' '){
        end++;
    }
    string res = lbstr.substr(begin, end-begin);
    return res;
}
// for <xxx val="yyy">, get yyy
string getLabelValue(xmlLabel lb){
    string lbstr = lb.name;
    int begin = lbstr.find("val=");
    if(begin == lbstr.npos){
        errHint("val doesnt exist for label " + lbstr);
        exit(0);
    }
    begin += 4;
    bool quoted = false;
    if(lbstr[begin] == '\"'){
        begin++;
        quoted = true;
    }
    int end = begin;

    if(quoted){
        while(end<lbstr.length() && lbstr[end] != '\"'){
            end++;
        }
    }else{
        while(end<lbstr.length() && lbstr[end] != '>'){
            end++;
        }
    }
    
    string res = lbstr.substr(begin, end-begin);
    return res;
}

template<class T>
void xml_deserialize(T &x, vector<xmlLabel> lbs, string type);
// deserialize a bool
void xml_deserialize_bool(bool &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for a bool");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "bool"){
        errHint("unmatched type for bool: " + lbname);
        exit(0);
    }
    string lbval = getLabelValue(lb);
    if(lbval == "true"){
        x = true;
    }else if(lbval == "false"){
        x = false;
    }else{
        errHint("invalid bool valstr: " + lbval);
        exit(0);
    }
}
// deserialize a short
void xml_deserialize_short(short &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for an short");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "short"){
        errHint("unmatched type for short: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    x = stoll(valstr);
}
// deserialize a int
void xml_deserialize_int(int &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for an int");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "int"){
        errHint("unmatched type for int: " + lbname);
        exit(0);
    }
    string lbval = getLabelValue(lb);
    x = stoi(lbval);
}
// deserialize a long long int
void xml_deserialize_llint(long long &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for a long_long");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "long_long"){
        errHint("unmatched type for long_long: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    x = stoll(valstr);
}
// deserialize a unsigned short
void xml_deserialize_ushort(unsigned short &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for an unsigned_short");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "unsigned_short"){
        errHint("unmatched type for unsigned_short: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    x = stoul(valstr);
}
// deserialize a unsigned int
void xml_deserialize_uint(unsigned int &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for an unsigned_int");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "unsigned_int"){
        errHint("unmatched type for unsigned_int: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    x = stoul(valstr);
}
// deserialize a unsigned long long int
void xml_deserialize_ullint(unsigned long long &x, vector<xmlLabel> lbs){
    if(lbs.size() > 1){
        errHint("too many info for an unsigned_long_long:" + to_string(lbs.size()));
        for(int i=0; i<lbs.size(); i++){
            cout << lbs[i].name << endl;
        }
        exit(0);
    }
    if(lbs.size() < 1){
        errHint("too less info for an unsigned_long_long:" + to_string(lbs.size()));
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "unsigned_long_long"){
        errHint("unmatched type for unsigned_long_long: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    x = stoul(valstr);
}
// deserialize a float
void xml_deserialize_flt(float &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for a float");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "float"){
        errHint("unmatched type for float: " + lbname);
        exit(0);
    }
    string lbval = getLabelValue(lb);
    x = stof(lbval);
}
// deserialize a double
void xml_deserialize_dbl(double &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for a double");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "double"){
        errHint("unmatched type for double: " + lbname);
        exit(0);
    }
    string lbval = getLabelValue(lb);
    x = stod(lbval);
}
// deserialize a char
void xml_deserialize_char(char &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for a char");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "char"){
        errHint("unmatched type for char: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    if(valstr.length() != 1){
        errHint("too long for a char: " + valstr);
        exit(0);
    }
    x = valstr.front();
}
// deserialize a string
void xml_deserialize(string &x, vector<xmlLabel> lbs, string type){
    // cout<<"string"<<endl;
    if(lbs.size() != 1){
        errHint("too many info for a string");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "std_string"){
        errHint("unmatched type for string: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    x = valstr;
}
// deserialize a unsigned char
void xml_deserialize_uchar(unsigned char &x, vector<xmlLabel> lbs){
    if(lbs.size() != 1){
        errHint("too many info for an uchar");
        exit(0);
    }
    xmlLabel lb = lbs.front();
    string lbname = getLabelName(lb);
    if(lbname != "unsigned_char"){
        errHint("unmatched type for uchar: " + lbname);
        exit(0);
    }
    string valstr = getLabelValue(lb);
    if(valstr.length() != 1){
        errHint("too long for an uchar: " + valstr);
        exit(0);
    }
    x = valstr.front();
}

template<class T> //vector
void xml_deserialize(vector<T> &x, vector<xmlLabel> lbs, string type){
    // cout<<"vector"<<endl;
    string elem_type;
    if(type.find("std_vector")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_vector!"  + type);
        exit(0);
    }

    if(lbs.size() < 2){
        errHint("too less labels for a vector: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_vector>"){
        errHint("unmatched begin for a vector: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_vector>"){
        errHint("unmatched end for a vector: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    int lv = lbs.front().level;
    vector<T> tmp;
    if(isBasicType(elem_type)){
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push_back(elem);
        }
    }
    else{
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            int lv = lbs.front().level;
            lbs.erase(lbs.begin());
            while(!lbs.empty() && lbs.front().level != lv){
                elems_lbs.push_back(lbs.front());
                lbs.erase(lbs.begin());
                if(lbs.empty()){
                    errHint("incomplete element in vector");
                    exit(0);
                }
            }
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push_back(elem);
        }
    }
    x = tmp;
}

template<class T> //queue
void xml_deserialize(queue<T> &x, vector<xmlLabel> lbs, string type){
    // cout<<"vector"<<endl;
    string elem_type;
    if(type.find("std_queue")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_queue!"  + type);
        exit(0);
    }

    if(lbs.size() < 2){
        errHint("too less labels for a queue: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_queue>"){
        errHint("unmatched begin for a queue: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_queue>"){
        errHint("unmatched end for a queue: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    int lv = lbs.front().level;
    queue<T> tmp;
    if(isBasicType(elem_type)){
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push(elem);
        }
    }
    else{
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            int lv = lbs.front().level;
            lbs.erase(lbs.begin());
            while(!lbs.empty() && lbs.front().level != lv){
                elems_lbs.push_back(lbs.front());
                lbs.erase(lbs.begin());
                if(lbs.empty()){
                    errHint("incomplete element in queue");
                    exit(0);
                }
            }
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push(elem);
        }
    }
    x = tmp;
}

template<class T> //deque
void xml_deserialize(deque<T> &x, vector<xmlLabel> lbs, string type){
    // cout<<"vector"<<endl;
    string elem_type;
    if(type.find("std_deque")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_deque!"  + type);
        exit(0);
    }

    if(lbs.size() < 2){
        errHint("too less labels for a deque: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_deque>"){
        errHint("unmatched begin for a deque: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_deque>"){
        errHint("unmatched end for a deque: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    int lv = lbs.front().level;
    deque<T> tmp;
    if(isBasicType(elem_type)){
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push_back(elem);
        }
    }
    else{
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            int lv = lbs.front().level;
            lbs.erase(lbs.begin());
            while(!lbs.empty() && lbs.front().level != lv){
                elems_lbs.push_back(lbs.front());
                lbs.erase(lbs.begin());
                if(lbs.empty()){
                    errHint("incomplete element in deque");
                    exit(0);
                }
            }
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push_back(elem);
        }
    }
    x = tmp;
}

template<class T> //stack
void xml_deserialize(stack<T> &x, vector<xmlLabel> lbs, string type){
    // cout<<"vector"<<endl;
    string elem_type;
    if(type.find("std_stack")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_stack!"  + type);
        exit(0);
    }

    if(lbs.size() < 2){
        errHint("too less labels for a stack: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_stack>"){
        errHint("unmatched begin for a stack: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_stack>"){
        errHint("unmatched end for a stack: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    int lv = lbs.front().level;
    stack<T> tmp;
    if(isBasicType(elem_type)){
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push(elem);
        }
    }
    else{
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            int lv = lbs.front().level;
            lbs.erase(lbs.begin());
            while(!lbs.empty() && lbs.front().level != lv){
                elems_lbs.push_back(lbs.front());
                lbs.erase(lbs.begin());
                if(lbs.empty()){
                    errHint("incomplete element in stack");
                    exit(0);
                }
            }
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push(elem);
        }
    }
    while(!tmp.empty()){
        x.push(tmp.top());
        tmp.pop();
    }
}

template<class T> //list
void xml_deserialize(list<T> &x, vector<xmlLabel> lbs, string type){
    // cout<<"list"<<endl;
    string elem_type;
    if(type.find("std_list")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_list!" + type);
        exit(0);
    }

    if(lbs.size() < 2){
        errHint("too less labels for a list: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_list>"){
        errHint("unmatched begin for a list: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_list>"){
        errHint("unmatched end for a list: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    int lv = lbs.front().level;
    list<T> tmp;
    if(isBasicType(elem_type)){
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push_back(elem);
        }
    }
    else{
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            int lv = lbs.front().level;
            lbs.erase(lbs.begin());
            while(!lbs.empty() && lbs.front().level != lv){
                elems_lbs.push_back(lbs.front());
                lbs.erase(lbs.begin());
                if(lbs.empty()){
                    errHint("incomplete element in list");
                    exit(0);
                }
            }
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.push_back(elem);
        }
    }
    x = tmp;
}

template<class T> //set
void xml_deserialize(set<T> &x, vector<xmlLabel> lbs, string type){
    // cout<<"set"<<endl;
    string elem_type;
    if(type.find("std_set")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_set: " + type);
        exit(0);
    }

    if(lbs.size() < 2){
        errHint("too less labels for a set: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_set>"){
        errHint("unmatched begin for a set: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_set>"){
        errHint("unmatched end for a set: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    int lv = lbs.front().level;
    set<T> tmp;
    if(isBasicType(elem_type)){
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.insert(elem);
        }
    }
    else{
        while(!lbs.empty()){
            vector<xmlLabel> elems_lbs;
            elems_lbs.push_back(lbs.front());
            int lv = lbs.front().level;
            lbs.erase(lbs.begin());
            while(!lbs.empty() && lbs.front().level != lv){
                elems_lbs.push_back(lbs.front());
                lbs.erase(lbs.begin());
                if(lbs.empty()){
                    errHint("incomplete element in set");
                    exit(0);
                }
            }
            elems_lbs.push_back(lbs.front());
            lbs.erase(lbs.begin());
            T elem;
            xml_deserialize(elem, elems_lbs, elem_type);
            tmp.insert(elem);
        }
    }
    x = tmp;
}

template<class T1, class T2> //pair
void xml_deserialize(pair<T1,T2> &x, vector<xmlLabel> lbs, string type){
    if(type.find("std_pair")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_pair!");
        exit(0);
    }

    if(lbs.size() < 4){
        errHint("too less labels for a pair: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_pair>"){
        errHint("unmatched begin for a pair: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_pair>"){
        errHint("unmatched end for a list: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    // cout << "pair: " << type << endl;
    vector<string> types = getSubTypes(type);
    if(types.size() < 2){
        errHint("less than 2 subtypes for std_pair");
        exit(0);
    }
    if(types.size() > 2){
        errHint("more than 2 subtypes for std_pair");
        exit(0);
    }
    string t1 = types[0];
    string t2 = types[1];
    // cout << "pair:" << t1 << " " << t2 << endl;

    pair<T1,T2> tmp;

    if(isBasicType(t1)){
        string name = getLabelName(lbs.front());
        if(name != "first"){
            errHint("unmatched label for pair_first: " + name);
            exit(0);
        }
        string valstr = getLabelValue(lbs.front());
        T1 val1;
        strTo(valstr, val1);
        tmp.first = val1;
        lbs.erase(lbs.begin());
    }
    else{
        xmlLabel begin = lbs.front();
        int lv = begin.level;
        lbs.erase(lbs.begin());
        if(begin.name != "<first>"){
            errHint("unmatched begin of pair_first for: " + begin.name);
            exit(0);
        }
        auto it = lbs.begin();
        vector<xmlLabel> sublbs;
        while(it!=lbs.end() && it->level!=lv){
            sublbs.push_back(*it);
            it++;
            if(it == lbs.end()){
                errHint("incomplete pair_first");
                exit(0);
            }
        }
        lbs.erase(lbs.begin(), it);
        if(lbs.front().name != "</first>"){
            errHint("unmatched end of pair_first for: " + lbs.front().name);
            exit(0);
        }
        lbs.erase(lbs.begin());
        T1 val1;
        xml_deserialize(val1, sublbs, t1);
        tmp.first = val1;
    }

    if(isBasicType(t2)){
        string name = getLabelName(lbs.front());
        if(name != "second"){
            errHint("unmatched label for pair_second: " + name);
            exit(0);
        }
        string valstr = getLabelValue(lbs.front());
        T2 val2;
        strTo(valstr, val2);
        tmp.second = val2;
        lbs.erase(lbs.begin());
    }
    else{
        xmlLabel begin = lbs.front();
        int lv = begin.level;
        lbs.erase(lbs.begin());
        if(begin.name != "<second>"){
            errHint("unmatched begin of pair_second for: " + begin.name);
            exit(0);
        }
        auto it = lbs.begin();
        vector<xmlLabel> sublbs;
        while(it!=lbs.end() && it->level!=lv){
            sublbs.push_back(*it);
            it++;
            if(it == lbs.end()){
                errHint("incomplete pair_second");
                exit(0);
            }
        }
        lbs.erase(lbs.begin(), it);
        if(lbs.front().name != "</second>"){
            errHint("unmatched end of pair_second for: " + lbs.front().name);
            exit(0);
        }
        lbs.erase(lbs.begin());
        if(!lbs.empty()){
            errHint("additional info for pair");
            exit(0);
        }
        T2 val2;
        xml_deserialize(val2, sublbs, t2);
        tmp.second = val2;
    }
    x = tmp;
}

template<class T1, class T2> //map
void xml_deserialize(map<T1,T2> &x, vector<xmlLabel> lbs, string type){
    if(type.find("std_map")==0){
        type = strInBrackets(type);
    }else{
        errHint("invalid std_map!");
        exit(0);
    }

    // cout << "map: " << type << endl;
    vector<string> types = getSubTypes(type);
    if(types.size() < 2){
        errHint("less than 2 subtypes for std_map");
        exit(0);
    }
    if(types.size() > 2){
        errHint("more than 2 subtypes for std_map");
        exit(0);
    }
    string t1 = types[0];
    string t2 = types[1];
    // cout << "map:" << t1 << " " << t2 << endl;

    map<T1,T2> tmp;

    if(lbs.size() < 4){
        errHint("too less labels for a map: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_map>"){
        errHint("unmatched begin for a map: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_map>"){
        errHint("unmatched end for a map: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    while(!lbs.empty()){
        if(lbs.front().name != "<std_map_item>"){
            errHint("unmatched begin for map_item: " + lbs.front().name);
            exit(0);
        }
        int item_lv = lbs.front().level;
        lbs.erase(lbs.begin());

        T1 key;
        T2 value;

        if(isBasicType(t1)){
            string name = getLabelName(lbs.front());
            if(name != "key"){
                errHint("unmatched label for map_key: " + name);
                exit(0);
            }
            string valstr = getLabelValue(lbs.front());
            strTo(valstr, key);
            lbs.erase(lbs.begin());
        }
        else{
            if(lbs.front().name != "<key>"){
                errHint("unmatched begin for map_key: " + lbs.front().name);
                exit(0);
            }
            int key_lv = lbs.front().level;
            lbs.erase(lbs.begin());
            
            auto it = lbs.begin();
            vector<xmlLabel> sublbs;
            while(it!=lbs.end() && it->level!=key_lv){
                sublbs.push_back(*it);
                it++;
                if(it==lbs.end()){
                    errHint("incomplete map_key");
                    exit(0);
                }
            }
            lbs.erase(lbs.begin(), it);
            if(lbs.front().name != "</key>"){
                errHint("unmatched end of map_key for: " + lbs.front().name);
                exit(0);
            }
            lbs.erase(lbs.begin());
            xml_deserialize(key, sublbs, t1);
        }

        if(isBasicType(t2)){
            string name = getLabelName(lbs.front());
            if(name != "value"){
                errHint("unmatched label for map_value: " + name);
                exit(0);
            }
            string valstr = getLabelValue(lbs.front());
            strTo(valstr, value);
            lbs.erase(lbs.begin());
        }
        else{
            if(lbs.front().name != "<value>"){
                errHint("unmatched begin for map_value: " + lbs.front().name);
                exit(0);
            }
            int value_lv = lbs.front().level;
            lbs.erase(lbs.begin());
            
            auto it = lbs.begin();
            vector<xmlLabel> sublbs;
            while(it!=lbs.end() && it->level!=value_lv){
                sublbs.push_back(*it);
                it++;
                if(it==lbs.end()){
                    errHint("incomplete map_value");
                    exit(0);
                }
            }
            lbs.erase(lbs.begin(), it);
            if(lbs.front().name != "</value>"){
                errHint("unmatched end of map_value for: " + lbs.front().name);
                exit(0);
            }
            lbs.erase(lbs.begin());
            xml_deserialize(value, sublbs, t2);
        }

        if(lbs.front().name != "</std_map_item>"){
            errHint("unmatched end for map_item: " + lbs.front().name);
            exit(0);
        }
        lbs.erase(lbs.begin());

        tmp[key] = value;
    }
    x = tmp;
}

template<class T> //unique_ptr
void xml_deserialize(unique_ptr<T> &p, vector<xmlLabel> lbs, string type){
    // cout<<"unique_ptr"<<endl;
    string elem_type;
    if(type.find("std_unique_ptr")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_unique_ptr!"  + type);
        exit(0);
    }

    if(lbs.size() <= 2){
        errHint("too less labels for a unique_ptr: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_unique_ptr>"){
        errHint("unmatched begin for a unique_ptr: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_unique_ptr>"){
        errHint("unmatched end for a unique_ptr: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    if(lbs.size()==1 && lbs.front().name=="<nullptr/>"){
        unique_ptr<T> tmp;
        p = move(tmp);
        return;
    }

    T elem;
    xml_deserialize(elem, lbs, elem_type);

    auto tmp = make_unique<T>(elem);
    p = move(tmp);
}

template<class T> //shared_ptr
void xml_deserialize(shared_ptr<T> &p, vector<xmlLabel> lbs, string type){
    // cout<<"shared_ptr"<<endl;
    string elem_type;
    if(type.find("std_shared_ptr")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_shared_ptr!"  + type);
        exit(0);
    }

    if(lbs.size() <= 2){
        errHint("too less labels for a shared_ptr: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_shared_ptr>"){
        errHint("unmatched begin for a shared_ptr: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_shared_ptr>"){
        errHint("unmatched end for a shared_ptr: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    if(lbs.size()==1 && lbs.front().name=="<nullptr/>"){
        p = NULL;
        return;
    }

    T elem;
    xml_deserialize(elem, lbs, elem_type);

    auto tmp = make_shared<T>(elem);
    p = tmp;
}

template<class T> //weak_ptr
void xml_deserialize(weak_ptr<T> &p, vector<xmlLabel> lbs, string type){
    // cout<<"weak_ptr"<<endl;
    string elem_type;
    if(type.find("std_weak_ptr")==0){
        elem_type = strInBrackets(type);
    }else{
        errHint("invalid std_weak_ptr!"  + type);
        exit(0);
    }

    if(lbs.size() <= 2){
        errHint("too less labels for a weak_ptr: " + to_string(lbs.size()));
        exit(0);
    }
    if(lbs.front().name != "<std_weak_ptr>"){
        errHint("unmatched begin for a weak_ptr: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</std_weak_ptr>"){
        errHint("unmatched end for a weak_ptr: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();

    if(lbs.size()==1 && lbs.front().name=="<nullptr/>"){
        // p = NULL;
        return;
    }

    T elem;
    xml_deserialize(elem, lbs, elem_type);

    auto tmp = make_shared<T>(elem);
    p = tmp;
}

template<class T> //basic types
void xml_deserialize(T &x, vector<xmlLabel> lbs, string type){
    string prim;
    int i=0;
    while(i < type.length()){
        if(type[i]=='<'){
            break;
        }
        i++;
    }
    prim = type.substr(0, i);

    if(prim == "int"){
        int tmp;
        xml_deserialize_int(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "short"){
        short tmp;
        xml_deserialize_short(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "long_long"){
        long long tmp;
        xml_deserialize_llint(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "unsigned_int"){
        unsigned tmp;
        xml_deserialize_uint(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "unsigned_short"){
        unsigned short tmp;
        xml_deserialize_ushort(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "unsigned_long_long"){
        unsigned long long tmp;
        xml_deserialize_ullint(tmp, lbs);
        x = tmp;
        return;
    }
    
    else if(prim == "bool"){
        bool tmp;
        xml_deserialize_bool(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "float"){
        float tmp;
        xml_deserialize_flt(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "double"){
        double tmp;
        xml_deserialize_dbl(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "char"){
        char tmp;
        xml_deserialize_char(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "unsigned_char"){
        unsigned char tmp;
        xml_deserialize_uchar(tmp, lbs);
        x = tmp;
        return;
    }
    else if(prim == "std_string"){
        // string tmp;
        // xml_deserialize_str(tmp, lbs);
        // strTo(tmp, x);
        // cout << "tmp: " << tmp << endl;
        // cout << "x: " << x << endl;
        // return;
    }
    else{

    }
}

template<class T> // unpackage
void xmlDeserialize(T &x, string type, string infile){
    vector<xmlLabel> lbs;
    read_xml(lbs, infile);

    if(lbs.size() <= 2){
        errHint("too less labels for deserialization: " + lbs.size());
        exit(0);
    }
    if(lbs.front().name != "<serialization>"){
        errHint("illegal begin for deserialization: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</serialization>"){
        errHint("illegal end for deserialization: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();
    T tmp;
    xml_deserialize(x, lbs, type);
    // x = tmp;
}

// the map from a 6-bit bin to a char, for base64
// the reverse of base64ToChar
map<int,char> charToBase64 = {
    {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'},
    {4, 'E'}, {5, 'F'}, {6, 'G'}, {7, 'H'},
    {8, 'I'}, {9, 'J'}, {10, 'K'}, {11, 'L'},
    {12, 'M'}, {13, 'N'}, {14, 'O'}, {15, 'P'},
    {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'},
    {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'},
    {24, 'Y'}, {25, 'Z'}, {26, 'a'}, {27, 'b'},
    {28, 'c'}, {29, 'd'}, {30, 'e'}, {31, 'f'},
    {32, 'g'}, {33, 'h'}, {34, 'i'}, {35, 'j'},
    {36, 'k'}, {37, 'l'}, {38, 'm'}, {39, 'n'},
    {40, 'o'}, {41, 'p'}, {42, 'q'}, {43, 'r'},
    {44, 's'}, {45, 't'}, {46, 'u'}, {47, 'v'},
    {48, 'w'}, {49, 'x'}, {50, 'y'}, {51, 'z'},
    {52, '0'}, {53, '1'}, {54, '2'}, {55, '3'},
    {56, '4'}, {57, '5'}, {58, '6'}, {59, '7'},
    {60, '8'}, {61, '9'}, {62, '+'}, {63, '/'}
};
// the map from a base64 char to a 6-bit bin
// the reverse of charToBase64
map<char,int> base64ToChar = {
    {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, 
    {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, 
    {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11},
    {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15},
    {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19},
    {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23},
    {'Y', 24}, {'Z', 25}, {'a', 26}, {'b', 27},
    {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31},
    {'g', 32}, {'h', 33}, {'i', 34}, {'j', 35},
    {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39},
    {'o', 40}, {'p', 41}, {'q', 42}, {'r', 43},
    {'s', 44}, {'t', 45}, {'u', 46}, {'v', 47},
    {'w', 48}, {'x', 49}, {'y', 50}, {'z', 51},
    {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55},
    {'4', 56}, {'5', 57}, {'6', 58}, {'7', 59},
    {'8', 60}, {'9', 61}, {'+', 62}, {'/', 63},
    {'=', 61}
};

// get the base 64 form of a string
string str2Base64(string s){
    unsigned char three[3];
    string res;
    int i;
    for(i=0; i<s.length()-3; i+=3){
        three[0] = s[i];
        three[1] = s[i+1];
        three[2] = s[i+2];
        char four[5] = {0};
        four[0] = (three[0]&0xFC)>>2;
        four[1] = (three[0]&0x03)<<4 | (three[1]&0xF0)>>4;
        four[2] = (three[1]&0x0F)<<2 | (three[2]&0xC0)>>6;
        four[3] = (three[2]&0x3F);

        four[0] = charToBase64[four[0]];
        four[1] = charToBase64[four[1]];
        four[2] = charToBase64[four[2]];
        four[3] = charToBase64[four[3]];
        res.append(four);
    }
    if(s.length() - i == 3){
        three[0] = s[i];
        three[1] = s[i+1];
        three[2] = s[i+2];
        char four[5] = {0};
        four[0] = (three[0]&0xFC)>>2;
        four[1] = (three[0]&0x03)<<4 | (three[1]&0xF0)>>4;
        four[2] = (three[1]&0x0F)<<2 | (three[2]&0xC0)>>6;
        four[3] = (three[2]&0x3F);

        four[0] = charToBase64[four[0]];
        four[1] = charToBase64[four[1]];
        four[2] = charToBase64[four[2]];
        four[3] = charToBase64[four[3]];
        res.append(four);
    }
    else if(s.length() - i == 2){
        three[0] = s[i];
        three[1] = s[i+1];
        // three[2] = s[i+2];
        char four[5] = {0};
        four[0] = (three[0]&0xFC)>>2;
        four[1] = (three[0]&0x03)<<4 | (three[1]&0xF0)>>4;
        four[2] = (three[1]&0x0F)<<2;
        four[3] = '=';

        four[0] = charToBase64[four[0]];
        four[1] = charToBase64[four[1]];
        four[2] = charToBase64[four[2]];
        // four[3] = base64code[four[3]];
        res.append(four);
    }
    else if(s.length() - i == 1){
        three[0] = s[i];
        // three[1] = s[i+1];
        // three[2] = s[i+2];
        char four[5] = {0};
        four[0] = (three[0]&0xFC)>>2;
        four[1] = (three[0]&0x03)<<4;
        four[2] = '=';
        four[3] = '=';

        four[0] = charToBase64[four[0]];
        four[1] = charToBase64[four[1]];
        // four[2] = base64code[four[2]];
        // four[3] = base64code[four[3]];
        res.append(four);
    }
    else{
        
    }
    return res;
}
// get the original form of a base64 string
string aStr2Base64(string s){
    string res;
    unsigned char four[4];
    int i;
    for(i=0; i<s.length()-4; i+=4){
        four[0] = s[i];
        four[1] = s[i+1];
        four[2] = s[i+2];
        four[3] = s[i+3];

        four[0] = base64ToChar[four[0]];
        four[1] = base64ToChar[four[1]];
        four[2] = base64ToChar[four[2]];
        four[3] = base64ToChar[four[3]];

        char three[4] = {0};
        three[0] = (four[0]&0x3F)<<2 | (four[1]&0x30)>>4;
        three[1] = (four[1]&0x0F)<<4 | (four[2]&0x3C)>>2;
        three[2] = (four[2]&0x03)<<6 | (four[3]&0x3F);

        res.append(three);
    }
    if(s.length() - i == 4){
        four[0] = s[i];
        four[1] = s[i+1];
        four[2] = s[i+2];
        four[3] = s[i+3];

        char three[4] = {0};

        four[0] = base64ToChar[four[0]];
        four[1] = base64ToChar[four[1]];
        if(four[2]=='=' && four[3]=='='){
            three[0] = (four[0]&0x3F)<<2 | (four[1]&0x30)>>4;
        }
        else if(four[2]!='=' && four[3]=='='){
            four[2] = base64ToChar[four[2]];
            three[0] = (four[0]&0x3F)<<2 | (four[1]&0x30)>>4;
            three[1] = (four[1]&0x0F)<<4 | (four[2]&0x3C)>>2;
        }
        else if(four[2]!='=' && four[3]!='='){
            four[2] = base64ToChar[four[2]];
            four[3] = base64ToChar[four[3]];
            three[0] = (four[0]&0x3F)<<2 | (four[1]&0x30)>>4;
            three[1] = (four[1]&0x0F)<<4 | (four[2]&0x3C)>>2;
            three[2] = (four[2]&0x03)<<6 | (four[3]&0x3F);
        }
        res.append(three);
    }
    return res;
}

// transform a file into base64 coding 
void xml2bin(string xmlfile, string binfile){
    ofstream bin(binfile, ios::binary);
    ifstream xml(xmlfile, ios::in);
    if(bin.bad()){
        errHint("failed to open binary file: " + binfile);
        exit(0);
    }
    stringstream ss;
    ss << xml.rdbuf();
    string s = ss.str();
    string bs64 = str2Base64(s);
    const char *buf = bs64.c_str();
    // printf("%s\n", buf);
    bin.write(buf, (strlen(buf))*sizeof(char));

    bin.close();
    xml.close();
}
// get the original version of a base64 coding file
void bin2xml(string binfile, string xmlfile){
    ifstream bin(binfile, ios::binary);
    ofstream xml(xmlfile, ios::out);
    stringstream ss;
    ss << bin.rdbuf();

    string bs64 = ss.str();
    string s = aStr2Base64(bs64);
    xml << s;
    
    bin.close();
    xml.close();
}

template<class T> //a binary mode of XML serialization using base64
void xmlSerialize_bin(T x, string type, string outfile){
    int lv=0;
    xmlLabel begin("<serialization>", lv, LB_BEGIN);
    xmlLabel end("</serialization>", lv, LB_END);

    vector<xmlLabel> lbs;
    lbs.push_back(begin);

    vector<xmlLabel> res = xml_serialize(x, lv+1, type);
    for(int i=0; i<res.size(); i++){
        lbs.push_back(res[i]);
    }
    lbs.push_back(end);

    // write_xml(lbs, outfile);

    stringstream ss;
    for(int i=0; i<lbs.size(); i++){
        for(int j=0; j<lbs[i].level; j++){
            ss << "    ";
        }
        ss << lbs[i].name << endl;
    }
    string base64 = str2Base64(ss.str());

    fstream out;
    out.open(outfile, fstream::out);
    out << base64;
    out.close();
}

template<class T> //a binary mode of XML deserialization using base64
void xmlDeserialize_bin(T &x, string type, string infile){
    vector<xmlLabel> lbs;
    
    // read_xml(lbs, infile);

    fstream xml_in;
    xml_in.open(infile, fstream::in);
    stringstream sss;
    sss << xml_in.rdbuf();
    string bs64 = sss.str();
    string s = aStr2Base64(bs64);
    xml_in.close();
    
    stringstream ss;
    ss << s;

    string line;
    getline(ss, line);
    while(line != ""){
        xmlLabel lb(line);
        lbs.push_back(lb);
        getline(ss, line);
    }
    
    if(lbs.size() <= 2){
        errHint("too less labels for deserialization: " + lbs.size());
        exit(0);
    }
    if(lbs.front().name != "<serialization>"){
        errHint("illegal begin for deserialization: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</serialization>"){
        errHint("illegal end for deserialization: " + lbs.back().name);
        exit(0);
    }
    lbs.pop_back();
    T tmp;
    xml_deserialize(tmp, lbs, type);
    x = tmp;
}

}