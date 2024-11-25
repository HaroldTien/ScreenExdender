#include "../include/ConnectionCodeGeneration.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

string ConnectionCodeGeneration() {
    const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int codeLength = 8;
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, charset.length() - 1);
    
    std::string code;
    code.reserve(codeLength);
    
    for (int i = 0; i < codeLength; ++i) {
        code += charset[distribution(generator)];
    }
    
    return code;
}