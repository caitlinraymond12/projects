#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

typedef unsigned char uchar;


class bigint
{ protected:
    int cap, num;
    bool neg;
    uchar *data;

  public:
    bigint();
    bigint(const bigint & other);
    bigint(const string & user_num);
    bigint(int n);
    ~bigint();
    bigint & operator=(int n);
    bigint & operator=(const bigint & other);
    bigint & operator=(const string & user_num);
    void remove();
    uchar get(int pos) const;
    void set(int pos, int newnum1);
    void grow();
    void print(ostream & out) const;
    void niceprint(ostream & out) const;
    int compare(const bigint & other) const;
    int compare2(const bigint & other) const;
    int toint();
    void shift(int step);
    void reverse();
    void clear();
    static void uadd(const bigint & a, const bigint & b, bigint & r);
    static void usub(const bigint & a, const bigint & b, bigint & r);
    static void bigmult(const bigint & a, const bigint & b, bigint & r);
    static void mult(const bigint & a, const int & b, bigint & r);
    static void add(const bigint & a, const bigint & b, bigint & r);
    static void subtract(const bigint & a, const bigint & b, bigint & r);
    static void division(const bigint & a, const int & b1, bigint & r);
    static bigint modulo(const bigint & a, const int & b);
    static void bigdivision(const bigint & a1, const bigint & b1, bigint & r);
    static bigint bigmodulo(const bigint & a1, const bigint & b1);
    bigint operator+(const bigint & b);
    bigint operator-(const bigint & b);
    bigint operator*(const bigint & b);
    bigint operator*(const int & b);
    bigint operator/(const int &b);
    bigint operator/(const bigint &b);
    bigint operator%(const int &b);
    bigint operator%(const bigint &b);
    void operator+=(const int &b);
    void operator+=(const bigint &b);
    void operator++(int);
    void operator--(int);
    void operator-=(const int &b);
    void operator-=(const bigint &b);
    void operator*=(const bigint &b);
    void operator*=(const int &b);
    void operator/=(const bigint &b);
    void operator/=(const int &b);
    void operator%=(const bigint &b);
    void operator%=(const int &b);
 };


ostream & operator<<(ostream & out, const bigint & value);

istream & operator>>(istream & in, bigint & variable);

bigint factorial(int n);
