#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <strings.h>
#include "map.h"

using namespace std;

queue::queue(int n)
{
  Q = new intersection * [n];
  count = 0;
  beg = 0;
  end = -1;
  size = n;
}

bool queue::empty()
{
  if(count == 0)
    return true;
  return false;
}

void queue::grow(int n)
{
  intersection * * newQ = new intersection * [n];
  int i = 0;
  int countsave = count;
  while(count != 0)
  {
    newQ[i] = remove();
    i++;
  }
  beg = 0;
  end = size - 1;
  delete[] Q;
  Q = newQ;
  size = n;
  count = countsave;
}




void queue::add(intersection * i)
{
  end++;
  if(end == size)
    end = 0;
  Q[end] = i;
  count++;
  if(count == size)
    grow(size*2);
}

intersection * queue::remove()
{
  if(count == 0)
    return nullptr;
  intersection * i = Q[beg];
  count--;
  beg++;
  if(beg == size)
    beg = 0;
  return i;
}

void queue::print()
{
  int i = beg, c = 0;
  while(c < count)
  {
    cout << "i: " << i << "\n";
    c++;
    i++;
    if(i == size)
      i = 0;
   }
 }

connection::connection(string n, string t, int l, intersection * a, intersection * b)
{
  name = n;
  type = t;
  length = l;
  total = l;
  A = a;
  B = b;
}

void connection::print()
{
  cout << name << " " << length << "\n";
}

void connection::print_from_to(intersection * from)
{
  intersection * to = get_there(from);
  cout << "Take road " << name << " from " << from->get_city()
       << " distance of " << length << " miles to "
       << to->get_city() << "\n";
}

string connection::get_name()
{
  return name;
}

string connection::get_type()
{
  return type;
}

void connection::increase_total(int x)
{
    total+=x;
}


int connection::get_total()
{
    return total;
}

int connection::get_length()
{
  return length;
}

intersection * connection::get_there(intersection * inter)
{
  if(inter->get_line() == A->get_line())
    return B;
  return A;
}

intersection::intersection(int li, double la, double lo, double near, double d, string st, string place, intersection * p, connection * c)
{
  line = li;
  lat = la;
  longi = lo;
  nearest_place_distance = near;
  dist = d;
  state = st;
  nearest_place_name = place;
  connections;
  prev = p;
  prev_road = c;
}

void intersection::print()
{
  cout << line << " " << lat << " " << longi << " " << nearest_place_distance << " " << state << " " << nearest_place_name << "\n";
}

int intersection::get_line()
{
  return line;
}

string intersection::get_state()
{
  return state;
}

void intersection::set_prev(intersection * p)
{
  prev = p;
}

void intersection::set_prev_road(connection * r)
{
  prev_road = r;
}

connection * intersection::get_prev_road()
{
  return prev_road;
}

void intersection::set_distance(double d)
{
  dist = d;
}

double intersection::get_distance()
{
  return dist;
}

double intersection::get_lat()
{
    return lat;
}

double intersection::get_long()
{
    return longi;
}

double intersection::get_nearest_dist()
{
    return nearest_place_distance;
}

intersection * intersection::get_prev()
{
  return prev;
}

int intersection::get_connections_size()
{
  return connections.size();
}

connection * intersection::get_road(int i)
{
  return connections[i];
}

void intersection::set_road(connection * c)
{
  connections.push_back(c);
}

string intersection::get_city()
{
  return nearest_place_name;
}

place::place(int co, int r, int p, string s, string c, double a, double la, double lo, double d)
{
  code = co;
  road = r;
  population = p;
  state = s;
  city = c;
  area = a;
  lat = la;
  longi = lo;
  intersection_distance = d;

}

void place::print()
{
  cout << code << " " << state << " " << city << " " << fixed << setprecision(6) << population
       << " " << area << " " << lat << " " << longi << " "
       << road << " " << intersection_distance << "\n";
}

string place::get_name()
{
  return city;
}

string place::get_state()
{
  return state;
}

int place::get_inter()
{
  return road;
}

double place::get_lat()
{
    return lat;
}

double place::get_long()
{
    return longi;
}

hashtable::entry::entry(place * p, entry * n)
{
  data = p;
  next = n;
}

unsigned int hashtable::hash(const string & name)
{
  unsigned int v = 192749357;
  for(int i = 0; i < name.size(); i++)
  {
    v = v * 169 + name[i];
  }
  return v;
}

hashtable::hashtable()
{
  size = 16;
  number = 0;
  table = new entry *[size];
  bzero(table, size * sizeof(entry *));
}

hashtable::~hashtable()
{
  for(int i = 0; i < size; i++)
  {
    entry * e = table[i];
    while(e != nullptr)
    {
      entry * nxt = e->next;
      delete e;
      e = nxt;
    }
  }
  delete []table;
}

void hashtable::record(place * p)
{
  int hv = hash(p->city) & (size-1);
  table[hv] = new entry(p, table[hv]);
  number++;
  if(number * 2 > size)
  {
    grow(size<<1);
  }
}


void hashtable::grow(int newsize)
{
  entry * * newtable;
  newtable = new entry *[newsize];
  bzero(newtable, newsize * sizeof(entry *));
  for(int i = 0; i < size; i++)
  {
    entry * e = table[i];
    while(e != nullptr)
    {
      entry * next = e->next;
      int hv = hash(e->data->city) & (newsize-1);
      e->next = newtable[hv];
      newtable[hv] = e;
      e = next;
    }
  }

  delete [] table;
  table = newtable;
  size = newsize;
}

void hashtable::print()
{
  for(int i = 0; i < size; i++)
  {
    entry * e = table[i];
    while(e != nullptr)
    {
      e->data->print();
      e = e->next;
    }
  }
}



place * hashtable::search(string city, string state)
{
   int HV = hash(city) & (size-1);
   entry * e = table[HV];
   while(e != nullptr)
   {
      if(e->data->city == city && e->data->state == state)
      {
        return e->data;
      }
      e = e->next;
   }
   return nullptr;

}


void priorityqueue::upheapify()
{
    int n = num-1;
    while(n > 0)
    {
        int parent = (n-1) / 2;
        if( v[n]->get_distance() < v[parent]->get_distance())
        {
            swap(v[n], v[parent]);
            n = parent;
        }
        else
            break;

    }
}

void priorityqueue::downheapify()
{
    int n = 0;
    while(true)
    {
        int left = n * 2 + 1;
        int right = n * 2 + 2;
        int smallest = n;

        if(left < num && v[left]->get_distance() < v[smallest]->get_distance())
            smallest = left;
        if(right < num && v[right]->get_distance() < v[smallest]->get_distance())
            smallest = right;

        if(smallest != n)
        {
            swap(v[n], v[smallest]);
            n = smallest;
        }
        else
            break;
    }
}


priorityqueue::priorityqueue()
{
    num = 0;
}

bool priorityqueue::empty()
{
   if(num == 0)
        return true;
    return false;
}

void priorityqueue::push(intersection *& i)
{
    v.push_back(i);
    num++;
    upheapify();

}

intersection * priorityqueue::pop()
{
    intersection * i = v[0];
    v[0] = v[num-1];
    num--;
    v.pop_back();
    downheapify();
    return i;
}

void priorityqueue::print()
{
    for(int i = 0; i < num; i++)
    {
        cout << v[i]->get_line() << ": " <<
                v[i]->get_distance() << ". ";
    }
    cout << "\n";
}

