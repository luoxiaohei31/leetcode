#include<iostream>
#include<chrono>

//#include<Eigen/Core>
#include<fmt/format.h>

#include"leCo.hpp"


int main(){
    std::vector<int> v1{-1,0,1,2,-1,-4};
    auto t1=std::chrono::steady_clock::now();

    bool b=lxj::canConstruct("aaa", "aab");

    auto t2=std::chrono::steady_clock::now();
    //fmt::print("\n{},{}", std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count(),w);
    fmt::print("{}", b);

    std::cout<<'\n'<<std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()<<"mics\n";

    return 0;
}
