#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "List.h"

using namespace std;

void user(List & database)
{ string input;
  while(input != "exit")
  { cout << "> ";
    getline(cin, input);
    istringstream in(input);
    while(true)
    { string s;
      in >> s;
      if(s == "exit")
        return;

      if(s == "count")
      { string in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        cout << database.countb(in1) << "\n";
        break; }

      else if(s == "sublist")
      { int in1, in2;
        in >> in1 >> in2;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        try
        { database.sublist(in1, in2); }
        catch(string e)
        { cout << e << "\n"; }
        break; }

      else if(s == "save")
      { string in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        database.savelist(in1);
        break; }

      else if(s == "zip")
      { int in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        database.findzip(in1);
        break; }

      else if(s == "find")
      { string in1, in2;
        in >> in1 >> in2;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        database.findname(in1, in2);
        break; }

      else if(s == "findfn")
      { string in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        database.findfn(in1);
        break; }

      else if(s == "findln")
      { string in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        database.findln(in1);
        break; }

      else if(s == "remove")
      { int in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        database.removessn(in1);
        break; }

      else if(s == "unyear")
      { int in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Provide the Correct Parameters\n";
          break; }
        database.removeyear(in1);
        break; }

      else if(s == "reverse")
      { database.reverse();
        break; }

      else if(s == "oldest")
      { try
        { database.oldest(); }
        catch(string e)
        { cout << e << "\n"; }
        break; }

      else
      { cout << "Sorry that command was not recognized. Please try again.\n";
        break; }

     }
} }


int main()
{ List database;
  createlist(database);
  user(database);
  }

