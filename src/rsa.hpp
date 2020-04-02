#ifndef __RSA__
#define __RSA__

#include <iostream>
#include <random>
#include <chrono>
#include <utility>

typedef unsigned long ul;

class RSA {
    private:
        std::mt19937 engine;
        bool isPrime(const ul& num);
        ul getPrimeNumber();
        std::pair<ul,ul> generateNumbers();


    public:
        RSA();

        std::string encrypt(const std::string& plainText);
        std::string decrypt(const std::string& encryptText);

        ~RSA();

};

#endif
