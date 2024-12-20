#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include "map.h"
#include "library.h";

using namespace std;

vector<string> stateabr;
vector<string> statename;
vector<intersection *> intersections;
hashtable HT;
priorityqueue Q;

int hashtable::realstate(string abr)
{
  int left = 0, right = stateabr.size();
  while(true)
  {
    int i = (left + right) / 2;
    if(stateabr[i] == abr)
    {
      return i;
    }
    if(stateabr[i] < abr)
    {
      left = i + 1;
    }
    else
    {
      right = i - 1;
    }
  }
  return -999;
}

void hashtable::placename(string city2, vector<string> &v)
{
  bool found = false;
  for(int i = 0; i < size; i++)
  {
    entry * e = table[i];
    while(e != nullptr)
    {
      if(e->data->city == city2)
      {
        found = true;
        v.push_back(e->data->state);
      }
      e = e->next;
    }
  }
  if(found == false)
  {
    v.push_back("NA");
  }
}

void readstates()
{
  string state, fullstate;
  ifstream file("states.txt");

  while(true)
  {
    string text;
    getline(file, text);
    if(file.fail())
    {
      break;
    }
    state = text.substr(0,2);
    stateabr.push_back(state);
    fullstate = text.substr(3, 30);
    statename.push_back(fullstate);
  }
}

void readplaces()
{
  int code, road, population;
  string state, city1;
  double area, lat, longi, distance;
  ifstream file("places.txt");
  while(true)
  {
    string text;
    getline(file, text);
    if(file.fail())
    {
      break;
    }
    state = text.substr(8, 2);
    city1 = text.substr(10, 50);
    string city;
    for(int i = 0; i < city1.size()-1; i++)
    {
      if(city1[i] == ' ' && city1[i+1] == ' ')
        break;
      city += city1[i];
    }
    string input;
    char * c;
    input = text.substr(0, 8);
    code = strtol(input.c_str(), &c, 10);

    input = text.substr(58,9);
    population = strtol(input.c_str(), &c, 10);

    input = text.substr(101, 6);
    road = strtol(input.c_str(), &c, 10);

    input = text.substr(67, 14);
    area = strtod(input.c_str(), &c);

    input = text.substr(81, 10);
    lat = strtod(input.c_str(), &c);

    input = text.substr(91, 11);
    longi = strtod(input.c_str(), &c);

    input = text.substr(107, 8);
    distance = strtod(input.c_str(), &c);

    place * p = new place(code, road, population, state, city, area, lat, longi, distance);
    HT.record(p);
    }
}

void readintersections()
{
  int number;
  double lat, longi, distance;
  string state, place;
  ifstream file("intersections.txt");

  int line = 0;
  while(true)
  {
    string text;
    getline(file, text);
    if(file.fail())
    {
      break;
    }
    longi = stod(text.substr(0, 9));
    lat = stod(text.substr(10, 9));
    distance = stod(text.substr(21, 5));
    state = text.substr(28,2);
    place = text.substr(31, 20);
    intersection * i = new intersection(line, lat, longi, distance, 999999999, state, place, nullptr, nullptr);
    intersections.push_back(i);
    line++;
  }
}

void readconnections()
{
  string name, type;
  double length;
  int indexA, indexB;
  intersection * A, * B;
  ifstream file("connections.txt");

  while(true)
  {
    file >> name >> type >> indexA >> indexB >> length;
    if(file.fail())
    {
      break;
    }

    A = intersections[indexA];
    B = intersections[indexB];
    length *= 10000;
    connection * c = new connection(name, type, int(length), A, B);
    A->set_road(c);
    B->set_road(c);
  }
}

place * place_input(string start_end)
{
    string city, state;
    place  * p;
    vector<string> v;

    cout << "Enter " << start_end << " City: ";
    getline(cin, city);
    if(city.empty())
        exit(1);
    HT.placename(city, v);

    if(v[0] == "NA")
        return nullptr;
    cout << "State Choices: ";
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
    cout << "Select A State: ";
    getline(cin, state);
    if(state.empty())
        exit(1);
    p = HT.search(city, state);
    if(p == nullptr)
    {
        cout << "Place Not Recognized.\n";
        return nullptr;
    }
    cout << "\n";
    return p;
}

bool search(vector<int> v, int target)
{
  for(int i = 0; i < v.size(); i++)
  {
    if(v[i] == target)
    {
        return true;
    }
  }
  return false;
}

void backtrack(intersection * end, vector<double> & coords, vector<connection *>& route, vector<intersection *>& inter)
{
    if(end->get_prev() == nullptr)
    {
        return;
    }
    backtrack(end->get_prev(), coords, route, inter);
    coords.push_back(end->get_lat());
    coords.push_back(end->get_long());
    route.push_back(end->get_prev_road());
    inter.push_back(end);

}

void drawmap(vector<double> coords)
{
	double minlat = coords[0], maxlat = coords[0], minlong = coords[1], maxlong = coords[1];
	for(int i = 2; i < coords.size(); i+=2)
	{
		if(coords[i] < minlat)
      minlat = coords[i];
		else if(coords[i] > maxlat)
	    maxlat = coords[i];
		
		if(coords[i+1] < minlong)
      minlong = coords[i+1];
		else if(coords[i+1] > maxlong)
	    maxlong = coords[i+1];
	}
  double map_minlat = 0, map_maxlat = 100, map_minlong, map_maxlong;
	string mapname;
  while(true)
  {
    double curr_minlat, curr_maxlat, curr_minlong, curr_maxlong;
    string currname;

    ifstream in("coverage.txt");
    while(true)
    {
        in >> curr_maxlat >> curr_minlat >> curr_maxlong >> curr_minlong >> currname;
        if(in.fail())
            break;
				curr_minlong = abs(curr_minlong);
				curr_maxlong = abs(curr_maxlong);

       if(curr_minlat <= minlat && curr_maxlat > maxlat &&
           curr_minlong < minlong && curr_maxlong > maxlong)
       {
            if(curr_maxlat - curr_minlat <= map_maxlat - map_minlat)
            {
                map_minlat = curr_minlat;
                map_maxlat = curr_maxlat;
                map_minlong = curr_minlong;
                map_maxlong = curr_maxlong;
                mapname = currname;
            }
       }
    }
    break;
  }
		string path = "all\\" + mapname;
    fstream map(path, ios::in | ios::binary);
		if(map.fail())
		{
			cerr << "Error Opening Map\n";
			return;
		}
		string row; 
		int rows, cols;
		short int pixel;
		getline(map, row);
		istringstream in(row);
		string word;
		while(true)
		{
			in >> word;
			if(in.fail())
				break;
			if(word == "rows")
				in >> rows;
			if(word == "columns")
				in>>cols;
		}
		make_window(cols, rows);
		map.seekg(2 * cols, ios::beg);
	  for(int y = 0; y < rows; y++)
		{
			for(int x = 0; x < cols; x++)
			{
				short int elevation;
				map.read( (char *) & elevation, sizeof(elevation));
			
				if(elevation < 0)
					set_pixel_color(x, y, color::blue);
				else
					set_pixel_color(x, y, make_color_hls(.333, double(elevation) / 9500 + .2, .5));
			}
		}
		int lat_mult = rows / (map_maxlat - map_minlat);
		int long_mult = cols / (map_maxlong - map_minlong);
		set_pen_color(color::red);
		set_pen_width(3);
		double longi = coords.back();
		coords.pop_back();
		double lat = coords.back();
		coords.pop_back();
		lat = (lat - map_minlat) * lat_mult;
		longi = (longi - map_minlong) * long_mult;
	  move_to(cols - longi, rows - lat);
		while(!coords.empty())
		{
			double longi = coords.back();
			coords.pop_back();
			double lat = coords.back();
			coords.pop_back();
			lat = (lat - map_minlat) * lat_mult;
			longi = (longi - map_minlong) * long_mult;
			draw_to(cols - longi, rows - lat);	
		}
}

void user()
{
  place * s, * e;
  intersection * inter, * other;
  connection * r;
  vector<int> closed;

  while(true)
  {
    s = place_input("Starting");
    if(s != nullptr)
      break;
  }
  while(true)
  {
    e = place_input("End");
    if(e != nullptr)
      break;
  }

  intersection * start = intersections[s->road];
  intersection * end = intersections[e->road];
  if(start->get_line() == end->get_line())
  {
    cout << "Start and End Same. Total Distance 0 Miles.\n";
    exit(-1);
  }
  start->set_distance(0);
  Q.push(start);
  while(!Q.empty())
  {
    intersection * curr = Q.pop();

    if(curr->get_line() == end->get_line())
    {
        cout << "Found! Total Distance: " << curr->get_distance() / 10000 << "\n";
        break;
    }
    if(search(closed, curr->get_line()))
        continue;

    for(int i = 0; i < curr->get_connections_size(); i++)
    {
        intersection * other = curr->get_road(i)->get_there(curr);
        int newdist = curr->get_distance() + curr->get_road(i)->get_length();
        if( newdist < other->get_distance())
        {
            other->set_distance(newdist);
            other->set_prev(curr);
            other->set_prev_road(curr->get_road(i));
            Q.push(other);
        }
    }
    closed.push_back(curr->get_line());
  }
  vector<double> coords;
  vector<connection *> route;
  vector<intersection *> inters;
  coords.push_back(start->get_lat());
  coords.push_back(start->get_long());
  backtrack(end, coords, route, inters);
  int prev = 0;
  string prevname = route[prev]->get_name();
  int prevlength = route[prev]->get_length();
  for(int i = 1; i < route.size(); i++)
  {
     string currname = route[i]->get_name();
     int currlength = route[i]->get_length();
     if(currname == prevname)
     {
         prevlength += currlength;
         continue;
     }
     cout << "Take " << prevname << " distance of "
          << double (prevlength) / 10000 << " miles to intersection #"
					<< inters[i-1]->get_line() << " " << inters[i-1]->get_nearest_dist() 
					<< " miles away from " << inters[i-1]->get_city() << ", " 
					<< inters[i-1]->get_state() << "\n";
     prev = i;
     prevname = currname;
     prevlength = currlength;
  }
  cout << "Take " << prevname << " distance of "
		<< double(prevlength) / 10000 << " miles to intersection #"
		<< end->get_line() << " " << end->get_nearest_dist() 
					<< " miles away from " << end->get_city() << ", "
					<< end->get_state() << "\n";
	drawmap(coords);
}

void main()
{
  readstates();
  readplaces();
  readintersections();
  readconnections();
  user();
}

