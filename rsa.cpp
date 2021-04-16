#include "rsa.h"
#include <QDebug>
#include <ctime>
#include <QCoreApplication>

void RSA::getData(LargeInteger &P_Al_, LargeInteger &Q_Al_, LargeInteger &N_Al_, LargeInteger &d_Al_, LargeInteger &s_Al_, LargeInteger &e_Al_, LargeInteger &P_Bob_, LargeInteger &Q_Bob_, LargeInteger &N_Bob_, LargeInteger &d_Bob_, LargeInteger &s_Bob_, LargeInteger &e_Bob_)
{
    P_Al_= P_Al; Q_Al_= Q_Al; N_Al_= N_Al; d_Al_= d_Al; s_Al_= s_Al; e_Al_= e_Al;
    P_Bob_= P_Bob; Q_Bob_= Q_Bob; N_Bob_= N_Bob; d_Bob_= d_Bob; s_Bob_= s_Bob; e_Bob_= e_Bob;
}

void RSA::generateLargeInteger()
{
    generateP(), generateQ(), generateN(),
            generateD(), generateS(), generateE();
}

string RSA::encode(string toEncode, int flag)
{
    string output = "";
    LargeInteger publicKey = 1, N = 1;
    if(flag == Alice)
    {
        N = N_Bob;
        publicKey = s_Bob;
    }
    else if(flag == Bob)
    {
        N = N_Al;
        publicKey = s_Al;
    }

    for (int i = 0; i < (int)toEncode.length(); i++)
    {
        LargeInteger number = encChar(toEncode[i], publicKey, N);
        output.append(number.getNumber());
        output += "|";
    }

    return output;
}

string RSA::decode(string toDecode, int flag)
{
    string decoded = "";

    size_t pos = 0;
    string token;
    string delimetre = "|";

    while ((pos = toDecode.find(delimetre)) != std::string::npos)
    {
        token = toDecode.substr(0, pos);
        LargeInteger character(token);
        LargeInteger decryptedChar = decChar(character, flag);

        decoded += (char) atoi(decryptedChar.getNumber().c_str());

        toDecode.erase(0, pos + delimetre.length());
    }

    return decoded;
}

LargeInteger RSA::modexp(LargeInteger x, LargeInteger y, LargeInteger N)// x^y % N
{
  if (y == 0) return 1;
  LargeInteger z = modexp(x, y / 2, N);
  if (y % 2 == 0)
    return (z*z) % N;
  else
    return (x*z*z) % N;
}

LargeInteger RSA::decChar(LargeInteger character, int flag)
{
    LargeInteger current(character);
    LargeInteger result(1);
    LargeInteger privateKey = 0, N = 0;

    if(flag == Alice)
    {
        N = N_Al;
        privateKey = e_Al;
    }
    else if(flag == Bob)
    {
        N = N_Bob;
        privateKey = e_Bob;
    }

    LargeInteger ost = modexp(current,privateKey,N);

    return ost;
}

LargeInteger RSA::encChar(char c, LargeInteger publicKey, LargeInteger N)
{
    LargeInteger charPos = LargeInteger((c));
    LargeInteger current = LargeInteger(charPos.getNumber());

    LargeInteger ost = modexp(current,publicKey,N);
    return ost;
}

void RSA::generateP()
{
    P_Al = LargeInteger((rand()%(100 - 31)) + 31);
    while (!isPrime(P_Al))
    {
        P_Al++;
    }
    P_Bob = LargeInteger((rand()%(100 - 31)) + 31);
    while (!isPrime(P_Bob))
    {
        P_Bob++;
    }
}

void RSA::generateQ()
{
    Q_Al = LargeInteger((rand()%(100 - 31)) + 31);
    while (!isPrime(Q_Al))
    {
        Q_Al++;
    }
    Q_Bob = LargeInteger((rand()%(100 - 31)) + 31);
    while (!isPrime(Q_Bob))
    {
        Q_Bob++;
    }
}

void RSA::generateN()
{
    N_Al = P_Al * Q_Al;
    N_Bob = P_Bob * Q_Bob;
}

void RSA::generateD()
{
    d_Al = (P_Al - 1)*(Q_Al - 1);
    d_Bob = (P_Bob - 1)*(Q_Bob - 1);
}

void RSA::generateS()
{
    LargeInteger number = rand()%(200);
    while (!isCoPrime(number, d_Al) || s_Al > d_Al)
    {
        number++;
    }
    s_Al = number;

    number = rand()%(200);
    while (!isCoPrime(number, d_Bob) || s_Al > d_Bob)
    {
        number++;
    }
    s_Bob = number;
}

void RSA::generateE()
{
    LargeInteger k = 1;
    while (true)
    {
        k = k + d_Al;

        if (k % s_Al == 0)
        {
            e_Al = (k / s_Al);
            break;
        }
    }

    k = 1;
    while (true)
    {
        k = k + d_Bob;

        if (k % s_Bob == 0)
        {
            e_Bob = (k / s_Bob);
            break;
        }
    }
}

bool RSA::isPrime(LargeInteger number)
{
    bool flag = true;

    if(number > 2)
    for (LargeInteger i = 2; i <= (number / 2); ++i)
    {
        if (number % i == 0)
        {
            flag = false;
            break;
        }
    }

    return flag;
}

LargeInteger RSA::greatestCommonDivisor(LargeInteger x, LargeInteger y)
{
    if (y == 0)
        return x;
    return greatestCommonDivisor(y, x % y);
}

bool RSA::isCoPrime(LargeInteger x, LargeInteger y)
{
    return greatestCommonDivisor(x, y) == 1;
}

RSA::RSA()
{
    P_Al = 1, Q_Al = 1, N_Al = 1, d_Al = 1, s_Al = 1, e_Al = 1;
    P_Bob = 1, Q_Bob = 1, N_Bob = 1, d_Bob = 1, s_Bob = 1, e_Bob = 1;
    srand(time(0));
}
