#include "binSerialization.hpp"

using namespace binSerialization;

// user defined type/class
class TestClass{
public:
    int test_int;
    std::string test_str;
    std::vector<int> test_vec;
};
// serialization inplementation for user defined type/class
void pack(std::stringstream& ss, const TestClass& data){
    pack(ss, data.test_int);
    pack(ss, data.test_str);
    pack(ss, data.test_vec);
}
// deserialization inplementation for user defined type/class
void unpack(std::stringstream& ss, TestClass& data){
    unpack(ss, data.test_int);
    unpack(ss, data.test_str);
    unpack(ss, data.test_vec);
}

// user defined type/class with inheriting
class TestInheritClass: public TestClass{
public:
    double test_double;
    std::map<int, std::string> test_map;
};
// serialization inplementation
void pack(std::stringstream& ss, const TestInheritClass& data){
    pack(ss, (TestClass)data);
    pack(ss, data.test_double);
    pack<int, std::string>(ss, data.test_map);
}
// deserialization inplementation
void unpack(std::stringstream& ss, TestInheritClass& data){
    TestClass base_data;
    unpack(ss, (TestClass&)data);
    unpack(ss, data.test_double);
    unpack<int, std::string>(ss, data.test_map);
}

enum TestEnum{
    MONDAY,
    TUESDAY
};

void test_bool(){
    bool x = true;
    std::string file = "test_bins/test_bool.data";
    binSerialize(x, file);

    bool y;
    binDeserialize(y, file);
    std::cout << "Test for bool:" << std::endl;
    std::cout << (y?"true":"false") << std::endl;
    std::cout << std::endl;
}

void test_int(){
    int x = 12;
    std::string file = "test_bins/test_int.data";
    binSerialize(x, file);

    int y;
    binDeserialize(y, file);
    std::cout << "Test for int:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_short(){
    short x = 12;
    std::string file = "test_bins/test_short.data";
    binSerialize(x, file);

    short y;
    binDeserialize(y, file);
    std::cout << "Test for short:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_llint(){
    int64_t x = 12;
    std::string file = "test_bins/test_llint.data";
    binSerialize(x, file);

    int64_t y;
    binDeserialize(y, file);
    std::cout << "Test for long_long:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_uint(){
    unsigned int x = 15;
    std::string file = "test_bins/test_uint.data";
    binSerialize(x, file);

    unsigned int y;
    binDeserialize(y, file);
    std::cout << "Test for unsigned_int:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_ushort(){
    unsigned short x = 15;
    std::string file = "test_bins/test_ushort.data";
    binSerialize(x, file);

    unsigned short y;
    binDeserialize(y, file);
    std::cout << "Test for unsigned_short:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_ullint(){
    uint64_t x = 15;
    std::string file = "test_bins/test_ullint.data";
    binSerialize(x, file);

    uint64_t y;
    binDeserialize(y, file);
    std::cout << "Test for unsigned_long_long:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_char(){
    char x = 'c';
    std::string file = "test_bins/test_char.data";
    binSerialize(x, file);

    char y;
    binDeserialize(y, file);
    std::cout << "Test for char:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_uchar(){
    unsigned char x = 'c';
    std::string file = "test_bins/test_uchar.data";
    binSerialize(x, file);

    unsigned char y;
    binDeserialize(y, file);
    std::cout << "Test for unsigned_char:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_float(){
    float x = 3.14159;
    std::string file = "test_bins/test_float.data";
    binSerialize(x, file);

    float y;
    binDeserialize(y, file);
    std::cout << "Test for float:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_dbl(){
    double x = 3.14159;
    std::string file = "test_bins/test_dbl.data";
    binSerialize(x, file);

    double y;
    binDeserialize(y, file);
    std::cout << "Test for double:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_str(){
    std::string x = "Hello world!";
    std::string file = "test_bins/test_str.data";
    binSerialize(x, file);

    std::string y;
    binDeserialize(y, file);
    std::cout << "Test for std_string:" << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;
}

void test_vector(){
    std::vector<std::vector<int>> x{{1,2,3}, {4,5,6}, {7,8,9}};

    std::string file = "test_bins/test_vector.data";
    binSerialize(x, file);

    std::vector<std::vector<int>> y;
    binDeserialize(y, file);

    std::cout << "Test for std_vector:" << std::endl;
    for(int i=0; i<y.size(); i++){
        for(int j=0; j<y[i].size(); j++){
            std::cout << y[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test_deque(){
    std::deque<std::deque<int>> x{{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
    std::string file = "test_bins/test_deque.data";
    binSerialize(x, file);

    std::deque<std::vector<int>> y;
    binDeserialize(y, file);

    std::cout << "Test for std_deque:" << std::endl;
    for(int i=0; i<y.size(); i++){
        for(int j=0; j<y[i].size(); j++){
            std::cout << y[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test_list(){
    std::list<std::string> x{"abc", "def", "aaa"};
    std::string file = "test_bins/test_list.data";
    binSerialize(x, file);

    std::list<std::string> y;
    binDeserialize(y, file);

    std::cout << "Test for std_list:" << std::endl;
    for(auto it=y.begin(); it!=y.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

void test_set(){
    std::set<double> x{1.23, 2.34, -5.67, 3.14};
    std::string file = "test_bins/test_set.data";
    binSerialize(x, file);

    std::set<double> y;
    binDeserialize(y, file);

    std::cout << "Test for std_set:" << std::endl;
    for(auto it=y.begin(); it!=y.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

void test_pair(){
    std::pair<std::string, std::string> x = std::make_pair("Hello", "world");
    std::string file = "test_bins/test_pair.data";
    binSerialize(x, file);

    std::pair<std::string, std::string> y;
    binDeserialize(y, file);

    std::cout << "Test for std_pair:" << std::endl;
    std::cout << y.first << ", " << y.second << std::endl;
    std::cout << std::endl;
}

void test_map(){
    std::map<int, std::string> x;
    x.insert(std::make_pair(1, "wa"));
    x.insert(std::make_pair(2, "wawa"));
    x.insert(std::make_pair(3, "wawawa"));
    std::string file = "test_bins/test_map.data";
    binSerialize(x, file);

    std::map<int, std::string> y;
    binDeserialize(y, file);

    std::cout << "Test for std_map:" << std::endl;
    for (auto it: y)
        std::cout << it.first << ", " << it.second << std::endl;
    std::cout << std::endl;
}

// test for user defined type
void test_UsrDefedClass(){
    TestClass x;
    x.test_int = 1;
    x.test_str = "hello";
    x.test_vec = {6,7,8};

    std::string file = "test_bins/test_udc.data";
    binSerialize(x, file);

    TestClass y;
    binDeserialize(y, file);

    std::cout << "Test for UserDefinedClass: " << std::endl;
    std::cout << y.test_int << std::endl;
    std::cout << y.test_str << std::endl;
    for(int i=0; i<y.test_vec.size(); i++){
        std::cout << y.test_vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

// test for user defined type with inheriting
void test_UsrDefedClass2(){
    TestInheritClass x;
    x.test_int = 1;
    x.test_str = "hello";
    x.test_vec = {1,2,3};
    x.test_double = 3.1415;
    x.test_map.insert(std::make_pair(1, "hello"));
    x.test_map.insert(std::make_pair(2, "world"));
    
    std::string file = "test_bins/test_udc2.data";
    binSerialize(x, file);

    TestInheritClass y;
    binDeserialize(y, file);

    std::cout << "Test for UserDefinedClass2:" << std::endl;
    std::cout << y.test_int << std::endl; 
    std::cout << y.test_str << std::endl; 
    for(auto it: y.test_vec){
        std::cout << it << " ";
    }
    std::cout << std::endl;
    for(auto it: y.test_map){
        std::cout << it.first << ", " << it.second << std::endl;
    }
    std::cout << std::endl;
}

int main(){
    test_bool();
    test_int();
    test_short();
    test_llint();
    test_uint();
    test_ushort();
    test_ullint();

    test_char();
    test_uchar();
    test_float();
    test_dbl();
    test_str();

    test_vector();
    test_deque();
    test_list();
    test_set();
    test_pair();
    test_map();

    test_UsrDefedClass();
    test_UsrDefedClass2();

    return 0;
}
