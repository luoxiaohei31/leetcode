#include<iostream>
#include<chrono>

//#include<Eigen/Core>
#include<fmt/format.h>

#include"leCo.hpp"


int main(){
    std::vector<char> v1{'h','e','l','l','o'};
    std::string str("aabaaf");
    auto t1=std::chrono::steady_clock::now();

    auto vi=lxj::next(str);

    auto t2=std::chrono::steady_clock::now();
    //fmt::print("\n{},{}", std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count(),w);
    for(auto c:str){
        fmt::print("{}, ",c);
    }
    fmt::print("\n");
    for(auto i:vi){
        fmt::print("{}, ",i);
    }

    std::cout<<'\n'<<std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()<<"mics\n";

    return 0;
}
