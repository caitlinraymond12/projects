#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <istream>

using namespace std;

struct person
{ int ssn, day, month, year, zip;
  string fname, lname, code, weekday, beatle;
  person(int s, int d, int m, int y, string f, string l, string c, int z, string w, string b);
  void print();
};

struct Link
{ person * data;
  Link * next;
  Link();
  Link(person * p, Link * n = NULL);
};


class List
{ protected:
    Link * first, * last;

  public:
    List();
    ~List();
    void sublist(int a, int b);
    void addf(person * p);
    void addb(person * p);
    void findzip(int zip);
    void findfn(string name);
    void findln(string name);
    void findname(string fname, string lname);
    int countb(string b);
    void savelist(string filename);
    void removessn(int ssn);
    void removeyear(int year);
    void reverse();
    void oldest();
};


void createlist(List & list);
