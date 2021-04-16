#pragma once
#include <string>
#define MAX 10000

using namespace std;
//-------------------------------------------------------------
class LargeInteger
{
private:
    string number;
    bool sign;
public:
    LargeInteger(); // empty constructor initializes zero
    LargeInteger(string s); // "string" constructor
    LargeInteger(string s, bool sin); // "string" constructor
    LargeInteger(int n); // "int" constructor
    void setNumber(string s);
    const string& getNumber(); // retrieves the number
    void setSign(bool s);
    const bool& getSign();
    LargeInteger absolute(); // returns the absolute value
    void operator = (LargeInteger b);
    bool operator == (LargeInteger b);
    bool operator != (LargeInteger b);
    bool operator > (LargeInteger b);
    bool operator < (LargeInteger b);
    bool operator >= (LargeInteger b);
    bool operator <= (LargeInteger b);
    LargeInteger& operator ++(); // prefix
    LargeInteger  operator ++(int); // postfix
    LargeInteger& operator --(); // prefix
    LargeInteger  operator --(int); // postfix
    LargeInteger operator + (LargeInteger b);
    LargeInteger operator - (LargeInteger b);
    LargeInteger operator * (LargeInteger b);
    LargeInteger operator / (LargeInteger b);
    LargeInteger operator % (LargeInteger b);
    LargeInteger& operator += (LargeInteger b);
    LargeInteger& operator -= (LargeInteger b);
    LargeInteger& operator *= (LargeInteger b);
    LargeInteger& operator /= (LargeInteger b);
    LargeInteger& operator %= (LargeInteger b);
    LargeInteger& operator [] (int n);
    LargeInteger operator -(); // unary minus sign
    operator string(); // for conversion from LargeInteger to string
private:
    bool equals(LargeInteger n1, LargeInteger n2);
    bool less(LargeInteger n1, LargeInteger n2);
    bool greater(LargeInteger n1, LargeInteger n2);
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string s);
};
