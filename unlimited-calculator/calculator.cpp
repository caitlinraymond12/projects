#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include "super.h"

using namespace std;

typedef unsigned char uchar;


template<typename T>
  class vector
  { protected:
      int cap, num;
      T* data;
    public:
      vector()
      { cap = 0;
        num = 0;
        data = NULL; }

      vector(int c)
      { cap = c;
        num = 0;
        data = new T[cap]; }

      vector(const vector<T> & x)
      { cap = x.cap;
        num = x.num;
        data = new T[cap];
        for(int i = 0; i < num; i++)
          data[i] = x.data[i]; }

      vector(int c, T array1[])
      { cap = c;
        num = c;
        data = new T[cap];
        for(int i = 0; i < c; i++)
        { data[i] = array1[i]; }  }

      ~vector()
      { delete[] data; }

      void push_back(T x)
      { if(num >= cap)
          grow();
        data[num] = x;
        num += 1; }

      void pop_back()
      { if(num <= 0)
          throw string("empty vector");
        num -= 1; }

      T& back()
      { if(num <= 0)
          throw string("empty vector");
        return data[num-1]; }

      void grow()
      { if(cap <= 0)
          cap = 1;
        else
          cap *= 2;
        T* newdata = new T[cap];
        for (int i = 0; i < num; i++)
          newdata[i] = data[i];
        delete[] data;
        data = newdata; }

      T pop()
      { if(num <= 0)
          throw string("empty vector");
        num -= 1;
        return data[num]; }

      int size()
      { return num; }

      void clear()
      { num = 0; }

      T& at(int x)
      { return data[x]; }

      vector<T> & operator=(const vector & other)
      { if(this == &other)
          return *this;
        delete data;
        cap = other.cap;
        num = other.num;
        data = new T[cap];
        for(int i = 0; i < num; i++)
          data[i] = other.data[i];
        return *this; }

      T& operator[](int i)
      { if(i < 0 || i >= num)
          throw string("Out of Range");
        return data[i]; }

      bool empty()
      { if(num == 0)
          return true;
        return false; }

      T reduce(int f(T, T), T x)
      { T r = x;
        for(int i = 0; i < num; i++)
        { r = f(data[i], r); }
        return r; }

      void apply(void f(T&))
      { for(int i = 0; i < num; i++)
        { f(data[i]); } }

      void apply(void f(T))
      { for(int i = 0; i < num; i++)
        { f(data[i]); } }

      void print()
      { for(int i = 0; i < num; i++)
        { if(i == num-1)
            cout << data[i] << "\n";
          else
            cout << data[i] << " "; } }
 };

vector<bigint> values;
vector<string> names;
vector<bigint> nums;

bigint period()
{ bigint save = nums.back();
  nums.pop_back();
  if(nums.empty())
    return save;
  throw(string("Not Enough Operators")); }

void equals(vector<string> input, int & i)
{ if(input.size() == i+1)
    throw(string("No Variable Given"));
  if(nums.empty())
    throw(string("Nothing to Assign"));
  bool search = 0;
  int pos;
  for(int v = 0; v < names.size(); v++)
  { if(names[v] == input[i+1])
    { search = 1;
      pos = v; } }
  if(search == 0)
  { names.push_back(input[i+1]);
    values.push_back(nums.back()); }
  if(search == 1)
  { values[pos] = nums.back(); }
    i = i + 2; }


void equals2(string variable, int & i)
{ bool search = 0;
  int pos = 0;
  for(int v = 0; v < names.size(); v++)
  { if(names[v] == variable)
    { search = 1;
      pos = v;
      break; } }
  if(search == 0)
  { cout << "No variable given\n";
    return; }
  values[pos] = nums.back(); }

void op3(string compare, bigint & x)
{ x = nums.back();
  nums.pop_back();

  if(compare == "++")
    x++;
  if(compare == "--")
    x--;
  nums.push_back(x); }

void op2(string compare, bigint & x, bigint & y)
{ x = nums.back();
  nums.pop_back();
  y = nums.back();
  nums.pop_back();

  if(compare == "+=")
    y+=x;
  else if(compare == "-=")
    y-=x;
  else if(compare == "/=")
    y/=x;
  else if(compare == "*=")
    y*=x;
  else if(compare == "%=")
    y%=x;

  nums.push_back(y); }

void op(string compare, bigint & x, bigint & y)
{ if(nums.size() <= 1)
    throw(string("Too Many Operators"));
  x = nums.back();
  nums.pop_back();
  y = nums.back();
  nums.pop_back();

  if(compare == "+")
    nums.push_back(y + x);

  else if(compare == "-")
    nums.push_back(y - x);

  else if(compare == "/")
    nums.push_back(y / x);

  else if(compare == "%")
    nums.push_back(y % x);

  else if(compare == "*")
    nums.push_back(y * x);

  else if(compare == "?")
  { int hold = y.compare(x);
    bigint r = hold;
    nums.push_back(r); } }

void var(string compare)
{ int pos = -999;
  for(int v = 0; v <  names.size(); v++)
  { if(names[v] == compare)
      pos = v; }
  if(pos == -999)
    throw(string("Variable Does Not Exist"));
  nums.push_back(values[pos]); }

void num(string compare)
{ bigint r = compare;
  nums.push_back(r); }

bigint polish(vector<string> input)
{ nums.clear();
  bigint x, y;
  int i = 0;
  while(i < input.size())
  { string compare = input[i];

    if(compare == "=")
    { equals(input, i);
      continue; }

    else if(compare == "+"  || compare == "-"  ||
            compare == "*"  || compare == "/"  ||
            compare == "%"  || compare == "?" )
      op(compare, x, y);

    else if(compare == "+="  || compare == "-="  ||
            compare == "*="  || compare == "/="  ||
            compare == "%=")
    { op2(compare, x, y);
      equals2(input[0], i); }

    else if(compare == "++" || compare == "--")
    { op3(compare, x);
      equals2(input[0], i); }

    else if(compare == "!")
    { x = nums.back();
      nums.pop_back();
      int a = x.toint();
      nums.push_back(factorial(a)); }

    else if(compare[0] >= 'a' && compare[0] <= 'z' ||
            compare[0] >= 'A' && compare[0] <= 'Z')
      var(compare);

     else
       num(compare);

  i = i + 1; }
  return period(); }

void input()
{ bigint answer;
  while(true)
  { vector<string> data;
    string line;
    getline(cin, line);
    istringstream in(line);
    while(true)
    { string s;
      in >> s;
      if(in.fail())
        break;
      data.push_back(s); }
    try
    { answer = polish(data); }
    catch(string e)
    { string error = e;
      cout << error << "\n";
      continue; }
    answer.niceprint(cout); } }


int main()
{ input(); }
