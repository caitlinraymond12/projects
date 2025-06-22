#include <iostream>
#include "Super.h"

bigint::bigint()
{ cap = 0;
  num = 0;
  neg = false;
  data = NULL; }

bigint::bigint(const bigint & other)
{ data = NULL;
  operator=(other); }

bigint::bigint(const string & user_num)
{ data = NULL;
  operator=(user_num); }

bigint::bigint(int n)
{ data = NULL;
  operator=(n); }

bigint::~bigint()
{ delete[] data; }

bigint& bigint::operator=(int n)
{ int npos = n;
  neg = false;
  if(n < 0)
  { neg = true;
    npos *= -1; }
  int len = 0;
  for(int i = npos; i >= 1; i/=10)
    len += 1;
  if(n == 0)
    len = 1;
  num = len;
  cap = len;
  delete[] data;
  data = new uchar[len];
  for(int v = 0; v < len; v++)
  { data[v] = npos%10;
    npos /= 10; }
  remove();
  return *this; }

bigint& bigint::operator=(const bigint & other)
{ if(this == &other)
    return *this;
  cap = other.cap;
  num = other.num;
  neg = other.neg;
  delete [] data;
  data = new uchar[cap];
  for(int i = 0; i < num; i++)
    data[i] = other.data[i];
  remove(); 
  return *this; }

bigint& bigint::operator=(const string & user_num)
{ neg = false;
  int negsign = 0;
  if(user_num[0] == '-')
  { neg = true;
    negsign = 1; }
  int len = user_num.length() - negsign;
  cap = len;
  num = len;
  delete [] data;
  data = new uchar[len];
  for(int i = 0, j = len - 1 + negsign; i < len; i++, j--)
  { if(user_num[j] < '0' || user_num[j] > '9')
      throw string("Not a digit!");
    data[i] = user_num[j] - '0'; }
  remove();
  return *this; }

void bigint::remove()
{ for(int i = num - 1; i > 0; i--)
  { if(data[i] == 0)
      num -= 1;
    else
      break; } }

uchar bigint::get(int pos) const
{ if(pos < 0 || pos >= num)
    return 0;
  return data[pos]; }

void bigint::set(int pos, int newnum1)
{ uchar newnum = newnum1;
  if(pos < 0)
    throw string("Position does not exist");
  else if(pos < num)
    data[pos] = newnum;
  else if(pos >= cap)
  { while(pos >= cap)
      grow(); }
  if(pos > num)
  { for(int i = num; i < pos; i++)
      data[i] = 0;
    data[pos] = newnum; }
  else
    data[pos] = newnum;
  num = pos+1; }

void bigint::grow()
{ if(cap <= 0)
    cap = 1;
  else
    cap *= 2;
  uchar * newdata = new uchar[cap];
  for (int i = 0; i < num; i++)
    newdata[i] = data[i];
  delete[] data;
  data = newdata; }

void bigint::print(ostream & out) const
{ if(neg == true)
    out << "-";
  for(int i = num-1; i >= 0; i--)
    out << int(data[i]);
  cout << "\n"; }

void bigint::niceprint(ostream & out) const
{ if(neg == true)
    out << "-";
  else
    out << " ";
  int line = 0;
  for(int i = num-1; i >= 0; i--)
  { if(line >= 50)
    { out << "\n ";
      out << int(data[i]);
      line = 1; }
    else
    { out << int(data[i]);
      line += 1; } }
  out << "\n"; }

int bigint::compare(const bigint & other) const
{ if(neg > other.neg)
    return -1;
  else if(neg < other.neg)
    return 1;
  if(num > other.num)
    return 1;
  else if(num < other.num)
    return -1;
  for(int i = num - 1; i >= 0; i--)
  { if(data[i] > other.data[i])
      return 1;
    if(data[i] < other.data[i])
      return -1; }
  return 0; }

int bigint::compare2(const bigint & other) const
{ if(num > other.num)
    return 1;
  else if(num < other.num)
    return -1;
  for(int i = num - 1; i >= 0; i--)
  { if(data[i] > other.data[i])
      return 1;
    if(data[i] < other.data[i])
      return -1; }
  return 0; }

int bigint::toint()
{ int a = 0;
  for(int i = num - 1; i >= 0; i--)
    a = a*10 + data[i];
  if(neg == true)
    a = -a;
  return a; }

void bigint::shift(int step)
{ int newnum = num + step;
  for(int i = newnum - 1, v = num - 1; i >= step; i--, v--)
  { uchar x = data[v];
    set(i, x); }
  for(int z = 0; z < step; z++)
    set(z, 0);
  num = newnum; }

void bigint::reverse()
{ bigint holder;
  for(int i = 0, v = num - 1; i < num; i++, v--)
  { holder.set(i, data[v]); }
  operator=(holder); }

void bigint::clear()
{ num = 0;
  neg = false; }

void bigint::uadd(const bigint & a, const bigint & b, bigint & r)
{ r.clear();
  int carry = 0;
  int n = max(a.num, b.num);
  for(int i = 0; i < n; i++)
  { int total = a.get(i) + b.get(i) + carry;
    if(total < 10)
    { r.set(i, total);
      carry = 0; }
    else
    { r.set(i, total - 10);
      carry = 1; } }
  r.set(n, carry);
  r.remove(); }

void bigint::usub(const bigint & a, const bigint & b, bigint & r)
{ r.clear();
  if(a.compare2(b) == -1)
  { usub(b, a, r);
    r.neg = true; }
  else
  { int borrow = 0;
    int n = max(a.num, b.num);
    for(int i = 0; i < n; i++)
    { int x = a.get(i) - b.get(i) - borrow;
      borrow = 0;
      if(x < 0)
      { x = x + 10;
        borrow = 1; }
      r.set(i, x); } }
   r.remove();}

void bigint::bigmult(const bigint & a, const bigint & b, bigint & r)
{ r.clear();
  if(a.neg != b.neg)
    r.neg = true;
  int carry = 0;
  for(int pos = 0; pos < a.num+b.num; pos++)
  { int total = 0;
    for(int i = 0; i <= pos; i++)
    { int j = pos - i;
      total += a.get(i) * b.get(j); }
    total += carry;
    int x = total % 10;
    r.set(pos, x);
    carry = total / 10; } }

void bigint::mult(const bigint & a, const int & b1, bigint & r)
{ r.clear();
  if(a.neg == true && b1 > 0 || a.neg == false && b1 < 0)
    r.neg = true;
  int b = b1;
  if(b1 < 0)
    b = -b1;
  int carry = 0;
  int total = 0;
  for(int i = 0; i < a.num || carry > 0; i++)
  { total = b * a.get(i) + carry;
    int x = total % 10;
    r.set(i, x);
    carry = total / 10; }
  r.remove();}


void bigint::add(const bigint & a, const bigint & b, bigint & r)
{ if(a.neg == false && b.neg == false)
    uadd(a, b, r);
  else if(a.neg == true && b.neg == false)
    usub(b, a, r);
  else if(a.neg == false && b.neg == true)
     usub(a, b, r);
  else if(a.neg == true && b.neg == true)
  { uadd(a, b, r);
    r.neg = true; } }

void bigint::subtract(const bigint & a, const bigint & b, bigint & r)
{ if(a.neg == false && b.neg == false)
    usub(a, b, r);
  else if(a.neg == true && b.neg == false)
  { uadd(a, b, r);
    r.neg = true; }
  else if(a.neg == false && b.neg == true)
    uadd(a, b, r);
  else if(a.neg == true && b.neg == true)
    usub(b, a, r);  }

void bigint::division(const bigint & a, const int & b1, bigint & r)
{ r.clear();
  if(b1 == 0)
    throw string("Cannot Divide by 0");
  if(a.neg == true && b1 > 0 || a.neg == false && b1 < 0)
    r.neg = true;
  int b = b1;
  if(b1 < 0)
    b = -b1;
  int carry = 0;
  for(int i = a.num - 1, v = 0; i >= 0; i--, v++)
  { carry = carry * 10 + a.get(i);
    int x = carry / b;
    r.set(v, x);
    carry = carry % b; }
  r.reverse(); }

bigint bigint::modulo(const bigint & a, const int & b)
{ if(b == 0)
    throw string("Cannot Take Modulo of 0");
  int carry = 0;
  for(int i = a.num - 1, v = 0; i >= 0; i--, v++)
  { carry = carry * 10 + a.get(i);
    carry = carry % b; }
  return bigint(carry); }

void bigint::bigdivision(const bigint & a1, const bigint & b1, bigint & r)
{ r.clear();
  if(b1.num == 1 && b1.data[0] == 0)
    throw string("Cannot Divide by 0");
  bigint a = a1;
  bigint b = b1;
  bigint c;
  for(int shift = a.num - b.num, i = 0; shift >= 0; shift--, i++)
  { b = b1;
    b.shift(shift);
    c = 0;
    int step = 0;
    while(true)
    { c = c + b;
      step = step + 1;
      if(c.compare(a) > 0)
      { c = c - b;
        step = step - 1;
        break; } }
    a = a - c;
    b = b / 10;
    r.set(i, step); }
  r.reverse(); }

bigint bigint::bigmodulo(const bigint & a1, const bigint & b1)
{ if(b1.num == 1 && b1.data[0] == 0)
    throw string("Cannot Take Modulo of 0");
  bigint a = a1;
  bigint b = b1;
  bigint c;
  for(int shift = a.num - b.num, i = 0; shift >= 0; shift--, i++)
  { b = b1;
    b.shift(shift);
    c = 0;
    int step = 0;
    while(true)
    { c = c + b;
      step = step + 1;
      if(c.compare(a) > 0)
      { c = c - b;
        step = step - 1;
        break; } }
    a = a - c;
    b = b / 10; }
  return a; }

bigint bigint::operator+(const bigint & b)
{ bigint r;
  bigint::add(*this, b, r);
  return r; }

bigint bigint::operator-(const bigint & b)
{ bigint r;
  bigint::subtract(*this, b, r);
  return r; }

bigint bigint::operator*(const bigint & b)
{ bigint r;
  bigint::bigmult(*this, b, r);
  return r; }

bigint bigint::operator*(const int & b)
{ bigint r;
  bigint::mult(*this, b, r);
  return r; }

bigint bigint::operator/(const int &b)
{ bigint r;
  if(b == 0)
    throw string("Cannot Divide by 0");
  bigint::division(*this, b, r);
  return r; }

bigint bigint::operator/(const bigint &b)
{ bigint r;
  if(b.num == 1 && b.data[0] == 0)
    throw string("Cannot Divide by 0");
  if (compare(b) == 0)
  { r = 1;
    return r; }
  else if(compare(b) < 0)
  { r = 0;
    return r; }
  bigint::bigdivision(*this, b, r);
  return r; }

bigint bigint::operator%(const int &b)
{ if(b == 0)
    throw string("Cannot Take Modulo of 0");
  bigint r = bigint::modulo(*this, b);
  return r; }

bigint bigint::operator%(const bigint &b)
{ if(b.num == 1 && b.data[0] == 0)
    throw string("Cannot Take Modulo of 0");
  bigint r = bigint::bigmodulo(*this, b);
  return r; }

void bigint::operator+=(const int &b)
{ bigint r;
  bigint::add(*this, bigint(b), r);
  operator=(r); }

void bigint::operator+=(const bigint &b)
{ bigint r;
  bigint::add(*this, b, r);
  operator=(r); }

void bigint::operator++(int)
{ bigint r;
  bigint::add(*this, bigint(1), r);
  operator=(r); }

void bigint::operator--(int)
{ bigint r;
  bigint::subtract(*this, bigint(1), r);
  operator=(r); }

void bigint::operator-=(const int &b)
{ bigint r;
  bigint::subtract(*this, bigint(b), r);
  operator=(r); }

void bigint::operator-=(const bigint &b)
{ bigint r;
  bigint::subtract(*this, b, r);
  operator=(r); }

void bigint::operator*=(const bigint &b)
{ bigint r;
  bigint::bigmult(*this, b, r);
  operator=(r); }

void bigint::operator*=(const int &b)
{ bigint r;
  bigint::mult(*this, b, r);
  operator=(r); }

void bigint::operator/=(const bigint &b)
{ bigint r;
  if(b.num == 1 && b.data[0] == 0)
    throw string("Cannot Divide by 0");
  bigint::bigdivision(*this, b, r);
  operator=(r); }

void bigint::operator/=(const int &b)
{ bigint r;
  if(b == 0)
    throw string("Cannot Divide by 0");
  bigint::division(*this, b, r);
  operator=(r); }

void bigint::operator%=(const bigint &b)
{ bigint r;
  if(b.num == 1 && b.data[0] == 0)
    throw string("Cannot Take Modulo of 0");
  r = bigint::bigmodulo(*this, b);
  operator=(r); }

void bigint::operator%=(const int &b)
{ bigint r;
  if(b == 0)
    throw string("Cannot Take Modulo of 0");
  r = bigint::modulo(*this, b);
  operator=(r); }

ostream & operator<<(ostream & out, const bigint & value)
{ value.print(out);
  return out; }

istream & operator>>(istream & in, bigint & variable)
{ string s;
  in >> s;
  variable=s;
  return in;  }

bigint factorial(int n)
{ if(n == 0)
    return bigint(1);
  if(n < 0)
    throw string("Cannot take Factorial of Negative");
  bigint r = 1;
  for(int i = 1; i <= n; i++)
  { r = r * i; }
  return r; }

