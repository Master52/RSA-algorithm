#ifndef __RSA__
#define __RSA__

#include <iostream>
#include <random>
#include <chrono>
#include <utility>

#define __DEBUG__

typedef unsigned long ul;

class RSA {
    private:
        std::mt19937 engine;

        /* Prime Numbers */
        ul p_num1 = 0, p_num2 = 0;

        /* Used in a part for generating public Key*/
        ul N = 0;

        ul PHI = 0;

        ul E_KEY = 0; // Encryption Key
        ul D_KEY = 0; // Decryption Key

        bool isPrime(const ul& num);
        ul getPrimeNumber(const int& lower,const int& upper,const int& offset);
        std::pair<ul,ul> generateNumbers();

        int gcd(ul e,ul phi);
        ul generateEncKey();
        ul generateDecKey(ul e,ul phi);



    public:
        RSA();

        std::string encrypt(const std::string& plainText);
        std::string decrypt(const std::string& encryptText);

        ~RSA();

};

#endif
