#ifndef RSA_H
#define RSA_H

#include <string>
#include <LargeInteger.h>

class RSA
{
    LargeInteger P_Al, Q_Al, N_Al, d_Al, s_Al, e_Al;
    LargeInteger P_Bob, Q_Bob, N_Bob, d_Bob, s_Bob, e_Bob;

public:
    enum {Alice, Bob};
    void getData(LargeInteger &P_Al_, LargeInteger &Q_Al_, LargeInteger &N_Al_, LargeInteger &d_Al_, LargeInteger &s_Al_, LargeInteger &e_Al_, LargeInteger &P_Bob_, LargeInteger &Q_Bob_, LargeInteger &N_Bob_, LargeInteger &d_Bob_, LargeInteger &s_Bob_, LargeInteger &e_Bob_);
    void generateLargeInteger();
    string encode(string, int);
    string decode(string, int);

    RSA();
private:
    LargeInteger encChar(char c, LargeInteger publicKey, LargeInteger N);
    LargeInteger decChar(LargeInteger character, int flag);
    void generateP(), generateQ(),
         generateN(), generateD(),
         generateS(), generateE();
    bool isPrime(LargeInteger);
    LargeInteger greatestCommonDivisor(LargeInteger x, LargeInteger y);
    bool isCoPrime(LargeInteger x, LargeInteger y);
};

#endif // RSA_H
