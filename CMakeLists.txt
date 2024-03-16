cmake_minimum_required(VERSION 3.25)

project(LeetCode VERSION 1.0.0 LANGUAGES CXX)

#set(CMAKE_PREFIX_PATH "E:/C++files/C++ third_party_lib/FMT")
list(APPEND CMAKE_PREFIX_PATH "E:/C++files/C++ third_party_lib/FMT" "E:/C++files/C++ third_party_lib/Eigen3")
find_package(fmt COMPONENTS REQUIRED)
find_package(Eigen3 COMPONENTS REQUIRED)

include_directories("./*.hpp")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    fmt::fmt
    Eigen3::Eigen
    )