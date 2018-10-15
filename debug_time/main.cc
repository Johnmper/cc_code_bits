#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include <functional>

#define DEBUG_TIME
#include"debug_time.hh"

struct A{
public:
    int id;
    float time;
    std::string name;
};


void f1(std::vector<struct A>& t, unsigned int sz){
    t.resize(1);
    t.shrink_to_fit();
    for(unsigned int ii=0;  ii < sz; ++ii){
        t.push_back(A());
    }
}

unsigned int string2int(std::string str){
    unsigned int res = 0;
    for(unsigned int ii = 0; ii < str.size(); ++ii){
        res = res + str[ii];
    }
    return res;
}


int main(int argc, char** argv){

    std::vector<struct A> t;

    while(1){
        std::string tmp = "asdasdasdasdasd";
        DEBUG_TIME_FUNC(std::hash<std::string>{}(tmp));
        std::cout << debug_time_ptr->total << std::endl;

        DEBUG_TIME_FUNC(string2int(tmp));
        std::cout << debug_time_ptr->total << std::endl;

        getchar();
    }
    return EXIT_SUCCESS;
}
