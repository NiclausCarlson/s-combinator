#include <iostream>
#include <functional>
#include <string>

template<typename T>
void Print(const T& expected, const T& actual){
    std::cout<<"Expected: "<<expected<<" Actual: "<<actual<<std::endl;
}

template<typename A, typename B, typename C>
A S(const std::function<A(B, C)>& f, const std::function<C(B)> & g, B x) {
    return f(x, g(x));
}

void IntTest(){
    std::function<int32_t(int32_t, int32_t)> f1 = [](int32_t x, int32_t g_result){
        return x + g_result;
    };

    std::function<int32_t(int32_t)> g1 = [](int32_t x){
        return x + 1;
    };
    Print(3, S(f1, g1, 1));
    Print(11, S(f1, g1, 5));
}

void StringTest(){
    std::function<std::string(std::string, std::string)> f = [](std::string str, std::string g_result){
        return str + g_result;
    };
    std::function<std::string(std::string)> g = [](std::string str){
        return std::to_string(str.size());
    };
    Print(std::string("abc3"), S(f, g, std::string("abc")));
    Print(std::string("cdef4"), S(f, g, std::string("cdef")));
}

void HighFunctionTest() {
    using GG = std::function<int32_t(int32_t)>;
    std::function<int32_t(int32_t, GG)> f = [](int32_t x, GG g){
        return x + g(x);
    };
    std::function<GG(int32_t)> g = [](int32_t x){
        GG res = [=](int32_t y){
            return x + y;
        };
        return res;
    };
    Print(3, S(f, g, 1));
    Print(15, S(f, g, 5));    
}

int main() {
   IntTest();
   StringTest();
   HighFunctionTest();
}
