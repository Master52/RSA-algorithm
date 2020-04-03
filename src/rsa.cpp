#include "rsa.hpp"


RSA::RSA() {
    std::random_device rd;
    engine.seed(rd());
    auto nums = generateNumbers();

    p_num1 = nums.first;
    p_num2 = nums.second;

    N = p_num1 * p_num2;

    PHI = (p_num1 - 1) * (p_num2 -1 );

    E_KEY = generateEncKey();

    D_KEY = generateDecKey(E_KEY,PHI);


#ifdef __DEBUG__
    fprintf(stdout,"p_num1 = %ld \n",p_num1);
    fprintf(stdout,"p_num2 = %ld  \n",p_num2);
    fprintf(stdout,"N = %ld  \n",N);
    fprintf(stdout,"PHI =  %ld  \n",PHI);
    fprintf(stdout,"E_KEY =   %ld  \n",E_KEY);
    fprintf(stdout,"D_KEY =   %ld  \n",D_KEY);
#endif


}

bool RSA :: isPrime(const ul& num)
{
    if(num < 2) return false;
    if(num == 2) return true;
    if((num & 0x01) == 0) return false;
    for(ul i = 3, n = std::sqrt(num) ; i <= n ; i = i + 2)
        if( num % i == 0) return false;

    return true;

}

ul RSA :: getPrimeNumber(const int& lower,const int& upper,const int& offset)
{
    std::uniform_int_distribution<ul> dist(lower,upper);
    bool primeFound = false;
    ul num;
    while(!primeFound) {
        num = dist(engine) + offset;
        if(isPrime(num))
            primeFound = true;
    }
    return num;

}

std::pair<ul,ul> RSA :: generateNumbers()
{
    return (std::make_pair(getPrimeNumber(1,32767,4096),getPrimeNumber(1,61440,2)));
}

std::string RSA :: encrypt(const std::string& message)
{
    return nullptr;

}


std::string RSA :: decrypt(const std::string& encryptText)
{
    return nullptr;

}

ul RSA :: generateEncKey()
{
    std::uniform_int_distribution<ul> dist(1,61440);
    ul e = dist(engine) + 4096;
    while( e < PHI ) {
        if( gcd(e,PHI) == 1) break;
        else ++e;
    }

    return e;

}

int RSA :: gcd (ul e,ul phi)
{
    ul temp;
    while( true ) {
        temp = e % phi;
        if( temp == 0 ) {
            return phi;
        }
        e = phi;
        phi = temp;
    }

}
ul RSA :: generateDecKey(ul e, ul phi)
{
    e = e % phi;
    ul d = 0;
    for (ul i = 1 ; i < phi ; ++i)
       if ((e * i) %  phi == 1)
       {
          d =  i;
          break;
       }
    return d;

}
RSA :: ~RSA()
{

}
