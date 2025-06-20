#include <log.hpp>
#include <iostream>

namespace tbd{
    void print(int x){
        std::cout << x << '\n';
    }

    void print(float x){
        std::cout << x << '\n';
    }

    void print(std::string x){
        std::cout << x << '\n';
    }
        
}