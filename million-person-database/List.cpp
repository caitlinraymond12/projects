#include <string>
#include "List.h"

person::person(int s, int d, int m, int y, string f, string l, string c, int z, string w, string b)
{ ssn = s;
  day = d;
  month = m;
  year = y;
  fname = f;
  lname = l;
  code = c;
  zip = z;
  weekday = w;
  beatle = b; }

void person::print()
{ cout << ssn << " " << day << " " << month << " " << year << " " << zip << " " << fname << " " << lname << " " << code << " " << weekday << " " << beatle << "\n"; }


Link::Link()
{ data = NULL;
  next = NULL; }

Link::Link(person * p, Link * n)
{ data = p;
  next = n; }


List::List()
{ first = NULL; }

List::~List()
{ delete[] first; }

void List::sublist(int a, int b)
{ if(a < 0 || a > b)
    throw string("Out of Range");
  Link * ptr = first, * test = first;
  int i = 1;
  while(i < a)
  { if(ptr == NULL)
      throw string("Out of Range");
    ptr = ptr->next;
    i+=1; }
  int v = i;
  while(v <= b)
  { if(test == NULL)
      throw string("Out of Range");
    test = test->next;
    v++; }
  while(i <= b)
  { ptr->data->print();
    ptr=ptr->next;
    i+=1; } }

void List::addf(person * p)
{ first = new Link(p, first);
  if(last == NULL)
    last = first; }

void List::addb(person * p)
{ if(last == NULL)
  { first = new Link(p, NULL);
    last = first;
    return; }
  last->next = new Link(p, NULL);
  last = last->next; }

void List::findzip(int zip)
{ Link * ptr = first;
  while(ptr != NULL)
  { if(ptr->data->zip == zip)
      ptr->data->print();
    ptr=ptr->next; } }

void List::findfn(string name)
{ Link * ptr = first;
  bool found = false;
  while(ptr != NULL)
  { if(ptr->data->fname == name)
    { found = true;
      ptr->data->print(); }
    ptr=ptr->next; }
  if(found == false)
    cout << "No Person Found With First Name: " << name << "\n"; }

void List::findln(string name)
{ Link * ptr = first;
  bool found = false;
  while(ptr != NULL)
  { if(ptr->data->lname == name)
    { found = true;
      ptr->data->print(); }
    ptr=ptr->next; }
  if(found == false)
    cout << "No Person Found With Last Name: " << name << "\n"; }

void List::findname(string fname, string lname)
{ Link * ptr = first;
  bool found = false;
  while(ptr != NULL)
  { if(ptr->data->fname == fname && ptr->data->lname == lname)
    { found = true;
      ptr->data->print(); }
    ptr=ptr->next; }
  if(found == false)
    cout << "No Person Found With Name: " << fname << " " << lname << "\n"; }

int List::countb(string b)
{ Link * ptr = first;
  int count = 0;
  while(ptr != NULL)
  { if(ptr->data->beatle == b)
      count++;
    ptr=ptr->next; }
  return count; }

void List::savelist(string filename)
{ ofstream test;
  test.open(filename);
  Link * ptr = first;
  person * p;
  while(ptr != NULL)
  { p = ptr->data;
    test << p->ssn << " " << p->day << " " << p->month << " " << p->year << " " << p->fname << " " << p->lname << " " << p->code << " " << p->zip << " " << p->weekday << " " << p->beatle << "\n";
    ptr=ptr->next; } }

void List::removessn(int ssn)
{ Link * ptr = first, * prev = NULL;
  while(ptr != NULL)
  { if(ptr->data->ssn == ssn)
    { if(ptr == first)
      { first = first->next;
        return; }
      if(ptr->next == NULL)
      { prev->next = NULL;
        return; }
      prev->next = ptr->next;
      return; }
  prev = ptr;
  ptr=ptr->next; } }

void List::removeyear(int year)
{ Link * ptr = first, * prev = NULL;
  while(ptr != NULL)
  { if(ptr->data->year == year)
    { if(ptr == first)
      { ptr=ptr->next;
        first = first->next; }
      else if(ptr->next == NULL)
      { prev->next = NULL;
        return; }
      else
      { prev->next = ptr->next;
        ptr = ptr->next; } }
    else
    { prev = ptr;
      ptr = ptr->next; } } }

void List::reverse()
{ Link * curr = first, * next = NULL, * prev = NULL;
 while(curr != NULL)
 { next = curr->next;
   curr->next = prev;
   prev = curr;
   curr = next; }
 first = prev; }

void List::oldest()
{ if (first == NULL)
   throw string("List is Empty");
 Link * holder = first, * ptr = first->next;
 while(ptr != NULL)
 { int oldyear = holder->data->year;
   int oldmonth = holder->data->month;
   int oldday = holder->data->day;
   int newyear = ptr->data->year;
   int newmonth = ptr->data->month;
   int newday = ptr->data->month;
   if(newyear < oldyear)
     holder = ptr;
   else if(newyear == oldyear && newmonth < oldmonth)
     holder = ptr;
   else if(newyear == oldyear &&
           newmonth == oldmonth &&
           newday < oldday)
     holder = ptr;
   ptr = ptr->next; }
 holder->data->print(); }

void createlist(List & list)
{ ifstream sample ("/home/218/million-database.txt");
  int ssn, day, month, year, zip;
  string fname, lname, code, dow, beatle;
  while(true)
  { sample >> ssn >> day >> month >> year >> fname >> lname >> code >> zip >> dow >> beatle;
    if(sample.eof())
      break;
    person * p = new person(ssn, day, month, year, fname, lname, code, zip, dow, beatle);
    list.addb(p);
    } }
