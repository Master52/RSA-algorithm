#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define __DEBUG__

struct PUBLIC_KEY {
    int64_t value;
};

struct PRIVATE_KEY {
    int64_t value;
};

struct RSA {
    struct PUBLIC_KEY E_KEY;
    struct PRIVATE_KEY D_KEY;
    int64_t N;
    int64_t PHI;

};

int is_Prime(int64_t* num)
{
    if(*num < 2) return 0;
    if(*num == 2) return 1;
    if((*num & 0x01) == 0) return 0;
    for( int64_t i = 3, n = sqrt(*num); i <= n ; i = i + 2)
        if ( *num % i == 0) return 0;

    return 1;

}

int64_t getPrime()
{
    int64_t num ;
    do {
        num = rand() % 100;
    }while(!is_Prime(&num));

    return num;

}

void putPrimeNumbers(int64_t* p1, int64_t* p2)
{
    *p1 = getPrime();
    *p2 = getPrime();
#ifdef __DEBUG__
    fprintf(stdout,"Generated Prime Numbers are: (%lu,%lu) \n",*p1,*p2);
#endif
}

int gcd(int64_t e, int64_t phi)
{
    int64_t temp;
    while(1) {
        temp = e % phi;
        if (temp == 0)
            return phi;
        e = phi;
        phi = temp;
    }
}

void getEncryptionKey(int64_t* phi,int64_t *e)
{
    *e = rand() % 5;
    while( *e < *phi) {
        if(gcd(*e,*phi)) break;
        else (*e)++;
    }
}

int64_t xgcd(int64_t a , int64_t b, int64_t *x, int64_t *y)
{
    if ( a == 0 ) {
        *x = 0;
        *y = 1;
        return b;
    }
    int64_t x1,y1;
    int64_t gcd = xgcd(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;

}

void getDecryptionKey(int64_t* phi,int64_t* d,int64_t *e)
{
    int64_t x,y;
    *d = xgcd(*phi,*e,&x,&y);

}


struct RSA* generateKeys() {
    srand(time(0));

    struct RSA *rsa = (struct RSA*)(malloc(sizeof(struct RSA)));
    int64_t p_num1,p_num2;
    putPrimeNumbers(&p_num1,&p_num2);
    rsa->N = p_num1 * p_num2;
    rsa->PHI = ( p_num1 - 1) * ( p_num2 - 1);

#ifdef __DEBUG__
    fprintf(stdout,"N: %lu\nPHI: %lu\n",rsa->N,rsa->PHI);
#endif

   getEncryptionKey(&rsa->PHI,&rsa->E_KEY.value);
   getDecryptionKey(&rsa->PHI,&rsa->D_KEY.value,&rsa->E_KEY.value);

   fprintf(stdout,"\nGenerate Keys:\n\tPrivate Key:%lu\n\tPublic Key:%lu \n",
           rsa->D_KEY.value,rsa->E_KEY.value);
   return rsa;

}

int64_t calcNegativeMod(int64_t* c, int64_t* N)
{
    *c = abs(*c);
    int64_t i = 1;
    while( ((*N) * i) < *c) i++;
    return (((*N) * i ) - *c);

}

char* encrypt(char *msg,struct RSA *rsa) {
    char *cipherText = (char*)(malloc(sizeof(char) * 512));

#ifdef __DEBUG__
    fprintf(stdout,"Encrypting...\n Original: %s \n",msg);
#endif
    int i;
    for( i = 0; msg[i] != '\0'; ++i) {
        int ascii_value = (int)(msg[i]);
        fprintf(stdout,"%d \n",ascii_value);
        int64_t c = powl(ascii_value,rsa->E_KEY.value);
        c = c % rsa->E_KEY.value;
        if( c < 0)
            c = calcNegativeMod(&c,&rsa->N);
        cipherText[i] = (char)c;
    }
    cipherText[i] = '\0';
    return cipherText;

}

int main (int argc, char* argv[])
{
    struct RSA *r = generateKeys();
    char plainText[] = {"This is plain Text"};
    char *c  = encrypt(plainText,r);
    fprintf(stdout,"%s \n",c);
    free(r);
    free(c);
}
