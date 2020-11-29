#include <iostream>
#include "xmlSerialization.hpp"

using namespace std;
using namespace xmlSerialization;

void test_int(){
    int x = 22;
    string type = "int";
    string file = "test_xmls/test_int.xml";
    xmlSerialize(x, type, file);

    int y;
    xmlDeserialize(y, type, file);

    cout << "Test for int:" << endl;
    cout << y << endl << endl;
}

void test_short(){
    short x = 33;
    string type = "short";
    string file = "test_xmls/test_short.xml";
    xmlSerialize(x, type, file);

    short y;
    xmlDeserialize(y, type, file);

    cout << "Test for short:" << endl;
    cout << y << endl << endl;
}

void test_llint(){
    long long x=2;
    string type = "long_long";
    string file = "test_xmls/test_llint.xml";
    xmlSerialize(x, type, file);

    long long y;
    xmlDeserialize(y, type, file);

    cout << "Test for long_long:" << endl;
    cout << y << endl << endl;
}

void test_uint(){
    unsigned int x = 22;
    string type = "unsigned_int";
    string file = "test_xmls/test_uint.xml";
    xmlSerialize(x, type, file);

    unsigned int y;
    xmlDeserialize(y, type, file);

    cout << "Test for unsigned_int:" << endl;
    cout << y << endl << endl;
}

void test_ushort(){
    unsigned short x = 33;
    string type = "unsigned_short";
    string file = "test_xmls/test_ushort.xml";
    xmlSerialize(x, type, file);

    unsigned short y;
    xmlDeserialize(y, type, file);

    cout << "Test for unsigned_short:" << endl;
    cout << y << endl << endl;
}

void test_ullint(){
    unsigned long long x=2;
    string type = "unsigned_long_long";
    string file = "test_xmls/test_ullint.xml";
    xmlSerialize(x, type, file);

    unsigned long long y;
    xmlDeserialize(y, type, file);

    cout << "Test for unsigned_long_long:" << endl;
    cout << y << endl << endl;
}

void test_bool(){
    bool x = true;
    string type = "bool";
    string file = "test_xmls/test_bool.xml";
    xmlSerialize(x, type, file);

    bool y;
    xmlDeserialize(y, type, file);

    cout << "Test for bool:" << endl;
    string boolstr = y ? "true" : "false";
    cout << boolstr << endl << endl;
}

void test_float(){
    float x = 3.14159;
    string type = "float";
    string file = "test_xmls/test_float.xml";
    xmlSerialize(x, type, file);

    float y;
    xmlDeserialize(y, type, file);

    cout << "Test for float:" << endl;
    cout << y << endl << endl;
}

void test_dbl(){
    double x = 2.71828;
    string type = "double";
    string file = "test_xmls/test_dbl.xml";
    xmlSerialize(x, type, file);

    double y;
    xmlDeserialize(y, type, file);

    cout << "Test for double:" << endl;
    cout << y << endl << endl;
}

void test_char(){
    char x = 'c';
    string type = "char";
    string file = "test_xmls/test_char.xml";
    xmlSerialize(x, type, file);

    char y;
    xmlDeserialize(y, type, file);

    cout << "Test for char:" << endl;
    cout << y << endl << endl;
}

void test_uchar(){
    unsigned char x = 'c';
    string type = "unsigned_char";
    string file = "test_xmls/test_uchar.xml";
    xmlSerialize(x, type, file);

    unsigned char y;
    xmlDeserialize(y, type, file);

    cout << "Test for unsigned_char:" << endl;
    cout << y << endl << endl;
}

void test_str(){
    string x = "Hello world!";
    string type = "std_string";
    string file = "test_xmls/test_string.xml";
    xmlSerialize(x, type, file);

    string y;
    xmlDeserialize(y, type, file);

    cout << "Test for string:" << endl;
    cout << y << endl << endl;
}

void test_map(){
    int x=12;

    vector<int> vint;
    vint.push_back(x);
    vint.push_back(x+1);
    vint.push_back(x+2);
    vint.push_back(x+3);

    map<string, vector<int>> msv;
    msv["Hello world"] = vint;
    msv["wa wa wa"] = vint;

    string type = "std_map<std_string,std_vector<int>>";
    string file = "test_xmls/test_map.xml";
    xmlSerialize(msv, type, file);

    map<string, vector<int>> res;
    xmlDeserialize(res, type, file);

    cout << "Test for map:" << endl;
    for(auto it = res.begin(); it != res.end(); it++){
        cout << it->first << endl;
        for(int i=0; i< it->second.size(); i++){
            cout << it->second[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void test_set(){
    vector<string> vstr1;
    vstr1.push_back("wa");
    vstr1.push_back("wa wa");
    vstr1.push_back("wa wa wa");
    vstr1.push_back("hello");

    vector<string> vstr2;
    vstr2.push_back("wawa");
    vstr2.push_back("wa");
    vstr2.push_back("wa wa wa");
    vstr2.push_back("hello world");

    set<vector<string>> sv;
    sv.insert(vstr1);
    sv.insert(vstr2);

    string type = "std_set<std_vector<std_string>>";
    string file = "test_xmls/test_set.xml";
    xmlSerialize(sv, type, file);

    set<vector<string>> res;
    xmlDeserialize(res, type, file);

    cout << "Test for set:" << endl;
    for(auto it=res.begin(); it!=res.end(); it++){
        for(int i=0; i<it->size(); i++){
            cout << it->at(i) << endl;
        }
        cout << endl;
    }
    cout << endl;
}

void test_list(){
    set<int> si1;
    si1.insert(13);
    si1.insert(14);
    si1.insert(15);
    si1.insert(16);

    set<int> si2;
    si2.insert(21);
    si2.insert(22);
    si2.insert(23);
    si2.insert(24);

    list<set<int>> ls;
    ls.push_back(si1);
    ls.push_back(si2);

    string type = "std_list<std_set<int>>";
    string file = "test_xmls/test_list.xml";
    xmlSerialize(ls, type, file);

    list<set<int>> res;
    xmlDeserialize(res, type, file);

    cout << "Test for list:" << endl;
    for(auto it=res.begin(); it!=res.end(); it++){
        for(auto itt=it->begin(); itt!=it->end(); itt++){
            cout << *itt << endl;
        }
        cout << endl;
    }
    cout << endl;
}

void test_vector(){
    list<float> lf1;
    lf1.push_back(1.2);
    lf1.push_back(1.3);
    lf1.push_back(1.4);
    lf1.push_back(1.5);

    list<float> lf2;
    lf2.push_back(2.2);
    lf2.push_back(2.3);
    lf2.push_back(2.4);
    lf2.push_back(2.5);

    vector<list<float>> vl;
    vl.push_back(lf1);
    vl.push_back(lf2);

    string type = "std_vector<std_list<float>>";
    string file = "test_xmls/test_vector.xml";
    xmlSerialize(vl, type, file);

    vector<list<float>> res;
    xmlDeserialize(res, type, file);

    cout << "Test for vector:" << endl;
    for(int i=0; i<res.size(); i++){
        for(auto it=res[i].begin(); it!=res[i].end(); it++){
            cout << *it << endl;
        }
        cout << endl;
    }
    cout << endl;
}

void test_pair(){
    vector<char> vc;
    vc.push_back('~');
    vc.push_back('Q');
    vc.push_back('A');
    vc.push_back('Q');
    vc.push_back('~');

    pair<string, vector<char>> psv;
    psv.first = "hello world";
    psv.second = vc;

    string type = "std_pair<std_string,std_vector<char>>";
    string file = "test_xmls/test_pair.xml";
    xmlSerialize(psv, type, file);

    pair<string, vector<char>> res;
    xmlDeserialize(res, type, file);

    cout << "Test for pair:" << endl;
    cout << res.first << endl;
    for(int i=0; i<res.second.size(); i++){
        cout << res.second[i] << endl;
    }
    cout << endl;
}

void test_queue(){
    queue<unsigned> qu;
    qu.push(12);
    qu.push(13);
    qu.push(14);
    qu.push(15);
    qu.push(16);

    string type = "std_queue<unsigned_int>";
    string file = "test_xmls/test_queue.xml";
    xmlSerialize(qu, type, file);

    queue<unsigned> res;
    xmlDeserialize(res, type, file);

    cout << "Test for queue:" << endl;
    while(!res.empty()){
        cout << res.front() << endl;
        res.pop();
    }
    cout << endl;
}

void test_deque(){
    deque<unsigned long long> qu;
    qu.push_back(12);
    qu.push_back(13);
    qu.push_back(14);
    qu.push_back(15);
    qu.push_back(16);

    string type = "std_deque<unsigned_long_long>";
    string file = "test_xmls/test_deque.xml";
    xmlSerialize(qu, type, file);

    deque<unsigned long long> res;
    xmlDeserialize(res, type, file);

    cout << "Test for deque:" << endl;
    while(!res.empty()){
        cout << res.front() << endl;
        res.pop_front();
    }
    cout << endl;
}

void test_stack(){
    stack<unsigned short> qu;
    qu.push(12);
    qu.push(13);
    qu.push(14);
    qu.push(15);
    qu.push(16);

    string type = "std_stack<unsigned_short>";
    string file = "test_xmls/test_stack.xml";
    xmlSerialize(qu, type, file);

    stack<unsigned short> res;
    xmlDeserialize(res, type, file);

    cout << "Test for stack:" << endl;
    while(!res.empty()){
        cout << res.top() << endl;
        res.pop();
    }
    cout << endl;
}

// a user defined type
struct UserDefinedType {
    int idx;
    std::string name;
    std::vector<double> data;
};
// serialization inplementation for user defined type
void xmlSerialize_usr(UserDefinedType x, string outfile){
    xmlLabel ser_begin("<serialization>", 0, LB_BEGIN);
    xmlLabel ser_end("</serialization>", 0, LB_END);
    xmlLabel idx_begin("<idx>", 1, LB_BEGIN);
    xmlLabel idx_end("</idx>", 1, LB_END);
    xmlLabel name_begin("<name>", 1, LB_BEGIN);
    xmlLabel name_end("</name>", 1, LB_END);
    xmlLabel data_begin("<data>", 1, LB_BEGIN);
    xmlLabel data_end("</data>", 1, LB_END);

    vector<xmlLabel> lb_idx = xml_serialize(x.idx, 2, "int");
    vector<xmlLabel> lb_name = xml_serialize(x.name, 2, "std_string");
    vector<xmlLabel> lb_data = xml_serialize(x.data, 2, "std_vector<double>");
    
    vector<xmlLabel> lbs;
    lbs.push_back(ser_begin);

    lbs.push_back(idx_begin);
    for(int i=0; i<lb_idx.size(); i++){
        lbs.push_back(lb_idx[i]);
    }
    lbs.push_back(idx_end);

    lbs.push_back(name_begin);
    for(int i=0; i<lb_name.size(); i++){
        lbs.push_back(lb_name[i]);
    }
    lbs.push_back(name_end);

    lbs.push_back(data_begin);
    for(int i=0; i<lb_data.size(); i++){
        lbs.push_back(lb_data[i]);
    }
    lbs.push_back(data_end);

    lbs.push_back(ser_end);
    write_xml(lbs, outfile);
}
// deserialization inplementation for user defined type
void xmlDeserialize_usr(UserDefinedType &x, string infile){
    vector<xmlLabel> lbs;
    read_xml(lbs, infile);
    if(lbs.size() <= 8){
        errHint("too less labels for UserDefinedType");
        for(int i=0; i<lbs.size(); i++){
            cout << lbs[i].name << endl;
        }
        exit(0);
    }
    if(lbs.front().name != "<serialization>"){
        errHint("unmatched begin for serailization: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    if(lbs.back().name != "</serialization>"){
        errHint("unmatched begin for serailization: " + lbs.front().name);
        exit(0);
    }
    lbs.pop_back();

    if(lbs.front().name != "<idx>"){
        errHint("unmatched begin for idx: " + lbs.front().name);
        exit(0);
    }
    int lv = lbs.front().level;
    lbs.erase(lbs.begin());
    vector<xmlLabel> lb_idx;
    while((!lbs.empty()) && (lbs.front().level != lv)){
        lb_idx.push_back(lbs.front());
        lbs.erase(lbs.begin());
    }
    if(lbs.empty()){
        errHint("incomplete idx");
        exit(0);
    }

    if(lbs.front().name != "</idx>"){
        errHint("unmatched end for idx: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    xml_deserialize(x.idx, lb_idx, "int");

    if(lbs.front().name != "<name>"){
        errHint("unmatched begin for name: " + lbs.front().name);
        exit(0);
    }
    lv = lbs.front().level;
    lbs.erase(lbs.begin());
    vector<xmlLabel> lb_name;
    while((!lbs.empty()) && (lbs.front().level != lv)){
        lb_name.push_back(lbs.front());
        lbs.erase(lbs.begin());
    }
    if(lbs.empty()){
        errHint("incomplete name");
        exit(0);
    }
    if(lbs.front().name != "</name>"){
        errHint("unmatched end for name: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    xml_deserialize(x.name, lb_name, "std_string");

    if(lbs.front().name != "<data>"){
        errHint("unmatched begin for data: " + lbs.front().name);
        exit(0);
    }
    lv = lbs.front().level;
    lbs.erase(lbs.begin());
    vector<xmlLabel> lb_data;
    while((!lbs.empty()) && (lbs.front().level != lv)){
        lb_data.push_back(lbs.front());
        lbs.erase(lbs.begin());
    }
    if(lbs.empty()){
        errHint("incomplete data");
        exit(0);
    }
    if(lbs.front().name != "</data>"){
        errHint("unmatched end for data: " + lbs.front().name);
        exit(0);
    }
    lbs.erase(lbs.begin());
    xml_deserialize(x.data, lb_data, "std_vector<double>");

    if(!lbs.empty()){
        errHint("too many labels for UserDefinedType");
        for(int i=0; i<lbs.size(); i++){
            cout << lbs[i].name << endl;
        }
        exit(0);
    }
}

// test the user defined type
void test_userDefinedType(){
    UserDefinedType x;
    x.idx = 12;
    x.name = "Zhang San";
    x.data.push_back(3.1);
    x.data.push_back(3.2);
    x.data.push_back(3.3);
    x.data.push_back(3.4);
    x.data.push_back(3.5);

    string file = "test_xmls/test_udt.xml";
    xmlSerialize_usr(x, file);

    UserDefinedType y;
    xmlDeserialize_usr(y, file);

    cout << "Test for UserDefinedType:" << endl;
    cout << y.idx << endl;
    cout << y.name << endl;
    for(int i=0; i<y.data.size(); i++){
        cout << y.data[i] << endl;
    }
    cout << endl;
}

void test_unique_ptr(){
    vector<int> x = {21, 22, 23, 24, 25, 26};
    auto p = make_unique<vector<int>>(x);
    string type = "std_unique_ptr<std_vector<int>>";
    string file = "test_xmls/test_unique_ptr.xml";
    xmlSerialize(p, type, file);

    unique_ptr<vector<int>> q;
    xmlDeserialize(q, type, file);
    vector<int> y = *q;
    cout << "Test for unique_ptr:" << endl;
    if(y.empty()){
        cout << "empty" << endl << endl;
        return;
    }
    for(auto it: y){
        cout << it << " ";
    }
    cout << endl << endl;
}

void test_shared_ptr(){
    vector<int> x = {31, 32, 33, 34, 35, 36};
    auto p = make_shared<vector<int>>(x);
    // p = NULL;
    string type = "std_shared_ptr<std_vector<int>>";
    string file = "test_xmls/test_shared_ptr.xml";
    xmlSerialize(p, type, file);

    shared_ptr<vector<int>> q;
    xmlDeserialize(q, type, file);
    vector<int> y = *q;
    cout << "Test for shared_ptr:" << endl;
    if(y.empty()){
        cout << "empty" << endl << endl;
        return;
    }
    for(auto it: y){
        cout << it << " ";
    }
    cout << endl << endl;
}

void test_weak_ptr(){
    vector<int> x = {41, 42, 43, 44, 45, 46};
    auto p = make_shared<vector<int>>(x);
    weak_ptr<vector<int>> wp(p);
    string type = "std_weak_ptr<std_vector<int>>";
    string file = "test_xmls/test_weak_ptr.xml";
    xmlSerialize(wp, type, file);

    weak_ptr<vector<int>> q;
    xmlDeserialize(q, type, file);
    shared_ptr<vector<int>> sq = q.lock();
    if(sq == NULL){
        cout << "Test for weak_ptr:" << endl;
        cout << "NULL" << endl;
        cout << endl;
        return;
    }
    vector<int> y = *(sq);
    cout << "Test for weak_ptr:" << endl;
    if(y.empty()){
        cout << "empty" << endl << endl;
        return;
    }
    for(auto it: y){
        cout << it << " ";
    }
    cout << endl << endl;
}

// test the binary mode of xml serialization using base64
void test_xml_bin(){
    vector<int> x = {2,3,12,13};
    string type = "std_vector<int>";
    string file = "test_xml_bin/xml_bin.data";
    xmlSerialize_bin(x, type, file);

    vector<int> y;
    xmlDeserialize_bin(y, type, file);
    
    cout << "Test for the binary mode of xml serialization:" << endl;
    for(auto it: y){
        cout << it << " ";
    }
    cout << endl << endl;
}

int main(){
    test_map();
    test_pair();
    test_list();
    test_vector();
    test_set();
    test_queue();
    test_deque();
    test_stack();

    test_int();
    test_short();
    test_llint();
    test_uint();
    test_ushort();
    test_ullint();
    test_bool();
    test_float();
    test_dbl();
    test_char();
    test_uchar();
    test_str();

    test_userDefinedType();

    test_xml_bin();

    test_unique_ptr();
    test_shared_ptr();
    test_weak_ptr();

    return 0;
}
