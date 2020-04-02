#include "rsa.hpp"


RSA::RSA() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    engine.seed(seed);
    auto nums = generateNumbers();
    fprintf(stdout,"First num %ld \n",nums.first);
    fprintf(stdout,"Second num %ld  \n",nums.second);


}

bool RSA :: isPrime(const ul& num)
{
    if(num < 2) return false;
    if(num == 2) return true;
    if((num & 0x01) == 0) return false;
    for(ul i = 0, n = std::sqrt(num) ; i <= n ; ++i)
        if( num % i == 0) return false;

    return true;

}

ul RSA :: getPrimeNumber()
{
    std::uniform_int_distribution<ul> dist(1000,1000000);
    bool primeFound = false;
    ul num;
    while(!primeFound) {
        num = dist(engine);
        if(isPrime(num))
            primeFound = true;
    }
    return num;

}

std::pair<ul,ul> RSA :: generateNumbers()
{
    return (std::make_pair(getPrimeNumber(),getPrimeNumber()));
}

std::string RSA :: encrypt(const std::string& message)
{
    return nullptr;

}


std::string RSA :: decrypt(const std::string& encryptText)
{
    return nullptr;

}

RSA :: ~RSA()
{

}
