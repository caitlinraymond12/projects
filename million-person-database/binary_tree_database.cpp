#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>


using namespace std;

struct person
{ int ssn, day, month, year, zip, age;
  string fname, lname, code, weekday, beatle;

  person()    //is making a defaul constructor like this necessary
  { ssn = 0;
    day = 0;
    month = 0;
    year = 0;
    age = 0;
    zip = 0;
    fname = " ";
    lname = " ";
    code = " ";
    weekday = " ";
    beatle = " "; }

  person(int s, int d, int m, int y, string f, string l, string c, int z, string w, string b)
  { ssn = s;
    day = d;
    month = m;
    year = y;
    zip = z;
    age = year * 100 + month * 10 + day;
    fname = f;
    lname = l;
    code = c;
    weekday = w;
    beatle = b; }


  void print()
  { cout << ssn << " " << day << " " << month << " " << year << " "
         << zip << " " << fname << " " << lname << " " << code << " "
         << weekday << " " << beatle << "\n"; }

};


class tree
{ protected:
    struct node
    { person * data;
      node * left, * right;

      node()
      { data = NULL;
        left = NULL;
        right = NULL; }

      node(person * p, node * l = NULL, node * r = NULL)
      { data = p;
        left = l;
        right = r; } };
    node * root;


    void insert(node *& curr, person * p)
    {
      if(curr == NULL)
        curr = new node(p);
      else if(p->lname < curr->data->lname)
        insert(curr->left, p);
      else if(p->lname > curr->data->lname)
        insert(curr->right, p);
      else
      { if(p->fname < curr->data->fname)
          insert(curr->left, p);
        else if(p->fname > curr->data->fname)
          insert(curr->right, p);
        else
        { if(p->year < curr->data->year)
            insert(curr->left, p);
          else if(p->year > curr->data->year)
            insert(curr->right, p);
          else
          { if(p->month < curr->data->month)
              insert(curr->left, p);
            else if(p->month > curr->data->month)
              insert(curr->right, p);
            else
            { if(p->day < curr->data->day)
                insert(curr->left, p);
              else if(p->day > curr->data->day)
                insert(curr->right, p);
              else
              { if(p->ssn < curr->data->ssn)
                  insert(curr->left, p);
                else
                  insert(curr->right, p); } } } } } }


    person * search(node * curr, string fname, string lname)
    { if(curr ==  NULL)
      { return NULL; }
      if(curr->data->fname == fname && curr->data->lname == lname)
      { return curr->data; }
      if(lname < curr->data->lname)
        return search(curr->left, fname, lname);
      else if(lname > curr->data->lname)
        return search(curr->right, fname, lname);
      else
      { if(fname < curr->data->fname)
          return search(curr->left, fname, lname);
        else
          return search(curr->right, fname, lname); } }

    void search2(node * curr, string fname, string lname, bool & found)
    { if(curr ==  NULL)
        return;
      if(curr->data->fname == fname && curr->data->lname == lname)
      { found = true;
        curr->data->print();
        search2(curr->left, fname, lname, found);
        search2(curr->right, fname, lname, found); }
      if(lname < curr->data->lname)
        search2(curr->left, fname, lname, found);
      else if(lname > curr->data->lname)
        search2(curr->right, fname, lname, found);
      else
      { if(fname < curr->data->fname)
          search2(curr->left, fname, lname, found);
        else
          search2(curr->right, fname, lname, found); } }



    void oldest(node * curr, person *& compare)
    { if(curr == NULL)
        return;
      if(curr->data->year < compare->year)
        compare = curr->data;
      else if(curr->data->year == compare->year && curr->data->month < compare->month)
        compare = curr->data;
      else if(curr->data->year == compare->year && curr->data->month < compare->month
                                                && curr->data->day < compare->day)
        compare = curr->data;
      oldest(curr->left, compare);
      oldest(curr->right, compare); }

    void count(node * curr, string beatle, int & number)
    { if(curr == NULL)
        return;
      if(curr->data->beatle == beatle)
        number+=1;
      count(curr->left, beatle, number);
      count(curr->right, beatle, number); }

    void save(node * curr, ofstream &newfile)
    { if(curr == NULL)
        return;
      newfile << curr->data->ssn << " " << curr->data->day << " " << curr->data->month << " " << curr->data->year << " "
         << curr->data->zip << " " << curr->data->fname << " " << curr->data->lname << " " << curr->data->code << " "
         << curr->data->weekday << " " << curr->data->beatle << "\n";
      save(curr->left, newfile);
      save(curr->right, newfile); }

    void familytree(node * curr, string lname, tree & newtree)
    { if(curr == NULL)
        return;
      if(curr->data->lname == lname)
      { newtree.insert(curr->data);
        familytree(curr->left, lname, newtree);
        familytree(curr->right, lname, newtree); }
      else if(lname < curr->data->lname)
        familytree(curr->left, lname, newtree);
      else
        familytree(curr->right, lname, newtree);
    }

    void print(node * curr)
    { if(curr == NULL)
        return;
      print(curr->left);
      curr->data->print();
      print(curr->right); }

    node * find_leftmost(node * curr)
    { if(curr->left == NULL)
        return curr;
      return find_leftmost(curr->left); }

    void remove(node *& curr, node *& prev, string fname, string lname, string & side)
    { if(curr == NULL)
        return;
      if(curr->data->fname == fname && curr->data->lname == lname)
      { return; }
      if(lname < curr->data->lname)
      { prev = curr;
        curr = curr->left;
        side = "left";
        remove(curr, prev, fname, lname, side); }
      else if(lname > curr->data->lname)
      { prev = curr;
        curr = curr->right;
        side = "right";
        remove(curr, prev, fname, lname, side); }
      else
      { if(fname < curr->data->fname)
        { prev = curr;
          curr = curr->left;
          side = "left";
          remove(curr, prev, fname, lname, side); }
        else
        { prev = curr;
          curr = curr->right;
          side = "right";
          remove(curr, prev, fname, lname, side); } } }

  public:
    tree()
    { root = NULL; }

    ~tree()
    { destroytree(root); }

    void destroytree(node * curr)
    { if(curr == NULL)
        return;
      destroytree(curr->left);
      destroytree(curr->right);
      delete curr; }

    void insert(person * p)
    { insert(root, p); }

    void print()
    { print(root); }

    void search(string fname, string lname)
    { bool found = false;
      search2(root, fname, lname, found);
      if(found == false)
        throw string("Person Not Found"); }

    void changepw(string fname, string lname, string pw)
    { person * p = search(root, fname, lname);
      if(p == NULL)
        throw string("Person not Found");
      else
        p->code = pw; }

    void oldest()
    { person * p = root->data;
      oldest(root, p);
      p->print(); }

    int count(string beatle)
    { int number = 0;
      count(root, beatle, number);
      return number; }

    void save(string name)
    { ofstream newfile;
      newfile.open(name);
      save(root, newfile); }

    void familytree(string lname)
    { tree newtree;
      familytree(root, lname, newtree);
      if(newtree.root == NULL)
      { cout << "Last Name Does Not Exist\n";
        return; }
      newtree.print(); }

    void remove(string fname, string lname)
    {  if(root == NULL)
         throw string("Empty Tree");

       person * p = search(root, fname, lname);
       if(p == NULL)
         throw string("Person Does Not Exist");

       string side = "error";
       node * curr = root, * prev = NULL;
       remove(curr, prev, fname, lname, side);

       if(curr == NULL)
         throw string("Person Does Not Exist");

       if(curr->left == NULL && curr->right == NULL)
       { if(side == "right")
         { delete prev->right->data;
           delete prev->right;
           prev->right = NULL; }
         else
         { delete prev->left->data;
           delete prev->left;
           prev->left = NULL; } }

       else if(curr->left == NULL)
       { if(side == "right")
         { node * hold = curr->right;
           delete prev->right->data;
           delete prev->right;
           prev->right = hold; }
         else
         { node * hold = curr->right;
           delete prev->left->data;
           delete prev->left;
           prev->left = hold; } }

       else if(curr->right == NULL)
       { if(side == "right")
         { node * hold = curr->left;
           delete prev->right->data;
           delete prev->right;
           prev->right = hold; }
         else
         { node * hold = curr->left;
           delete prev->left->data;
           delete prev->left;
           prev->left = hold; } }


       else
       { node * n = find_leftmost(curr->right);
         n->left = curr->left;
         if(prev == NULL)
         { node * hold = curr->right;
           delete root->data;
           delete root;
           root = hold; }
         else if(side == "right")
         { node * hold = curr->right;
           delete prev->right->data;
           delete prev->right;
           prev->right = hold; }
         else
         { node * hold = curr->right;
           delete prev->left->data;
           delete prev->left;
           prev->left = hold; } }
         }





};

void createtree(tree & database, string filename)
{ ifstream sample(filename);
  int ssn, day, month, year, zip;
  string fname, lname, code, dow, beatle;
  while(true)
  { sample >> ssn >> day >> month >> year >> fname >> lname >> code
           >> zip >> dow >> beatle;
    if(sample.eof())
      break;
    person * p = new person (ssn, day, month, year, fname, lname, code,
                             zip, dow, beatle);
    database.insert(p); } }


void user(tree & database)
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

      if(s == "find")
      { string in1, in2;
        in >> in1 >> in2;
        if(in.fail())
        { cout << "Please Enter Correct Number of Parameters\n";
          break; }
        try
        { database.search(in1, in2); }
        catch(string e)
        { cout << e << "\n"; }
        break; }

      else if(s == "print")
      { database.print();
        break; }

      else if(s == "change")
      { string in1, in2, in3;
        in >> in1 >> in2 >> in3;
        if(in.fail())
        { cout << "Please Enter Correct Number of Parameters\n";
          break; }
        try
        { database.changepw(in1, in2, in3); }
        catch(string e)
        { cout << e << "\n"; }
        break; }

      else if(s == "oldest")
      { database.oldest();
        break; }

      else if(s == "count")
      { string in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Enter Correct Number of Parameters\n";
          break; }
        if(in1 != "Paul" && in1 != "George" && in1 != "John" && in1 != "Ringo")
        { cout << "That's not a Beatle!\n";
          break; }
        int count = database.count(in1);
        cout << count << "\n";
        break; }

      else if(s == "save")
      { string in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Enter Correct Number of Parameters\n";
          break; }
        database.save(in1);
        break; }

      else if(s == "family")
      { string in1;
        in >> in1;
        if(in.fail())
        { cout << "Please Enter Correct Number of Parameters\n";
          break; }
        database.familytree(in1);
        break; }

      else if(s == "kill")
      { string in1, in2;
        in >> in1 >> in2;
        if(in.fail())
        { cout << "Please Enter Correct Number of Parameters\n";
          break; }
        try
        { database.remove(in1, in2); }
        catch(string e)
        { cout << e << "\n"; }
        break; }

      else
      { cout << "Sorry that command was not recognized. Please try again.\n";
        break; } } } }




int main(int argc, char * argr[])
{ tree database;

  if(argc == 1)
    createtree(database, "/home/218/million-database.txt");
  else
    createtree(database, argr[1]);

  user(database);

}

