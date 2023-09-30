#include <iostream>
#include <string>

template<typename T>
void Print(const T& expected, const T& actual){
    std::cout<<"Expected: "<<expected<<" Actual: "<<actual<<std::endl;
}

template<typename F, typename G, typename X>
auto S(F f, G g, X x) {
    return f(x)(g(x));
}

void IntTest(){
    auto f1 = [](int32_t x){
        return [=](auto g_result){
            return x + g_result;
        };
    };

    auto g1 = [](int32_t x){
        return x + 1;
    };
    Print(3, S(f1, g1, 1));
    Print(11, S(f1, g1, 5));
}

void StringTest(){
    auto f = [](std::string str){
        return [=](auto g_result){
            return str + g_result;
        };
    };
    auto g = [](std::string str){
        return std::to_string(str.size());
    };
    Print(std::string("abc3"), S(f, g, "abc"));
    Print(std::string("cdef4"), S(f, g, "cdef"));
}

void HighFunctionTest() {
    auto f = [](int32_t x){
        return [=] (auto g){
            return x + g(x);
        };
    };
    auto g = [](int32_t x){
        return [=](int32_t y){
            return x + y;
        };
    };
    Print(3, S(f, g, 1));
    Print(15, S(f, g, 5));    
}

int main() {
   IntTest();
   StringTest();
   HighFunctionTest();
}
