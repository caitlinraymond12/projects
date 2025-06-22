#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <istream>
#include <strings.h>


using namespace std;


int maxlinesize = 120;
string infile = "sampleinput.txt";
string outfile = "sampleoutput.txt";

class hashtable
{
        protected:
                struct entry
                {
                        string data;
                        entry * next;

                        entry(string d, entry * n = nullptr)
                        {
                                data = d;
                                next = n;
                        }
                };

                entry * * table;
                int size, count;

                unsigned int hash(string s)
                {
                        unsigned int v = 12098419;
                        for(int i = 0; i < s.size(); i++)
                                v = v * 169 + s[i];
                        return v;
                }
        public:
        hashtable(int sz = 100)
        {
                size = sz;
                table = new entry *[size];
                bzero(table, size * sizeof(entry *));
                count = 0;
        }

        ~hashtable()
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
                delete [] table;
        }

        void add(string s)
        {
                int hv = hash(s) % size;
                table[hv] = new entry(s, table[hv]);
                if(2*count >= size)
                        grow(size * 2);
        }

        void grow(int newsize)
        {
                entry * * newtable;
                newtable = new entry *[newsize];
                bzero(newtable, size * sizeof(entry *));
                for(int i = 0; i < size; i++)
                {
                        entry * e = table[i];
                        while(e != nullptr)
                        {
                                entry * nxt = e->next;
                                int hv = hash(e->data) % newsize;
                                e->next = newtable[hv];
                                newtable[hv] = e;
                                e = nxt;
                        }
                }
                delete [] table;
                table = newtable;
                size = newsize;

        }

        bool contains(string s)
        {
                int hv = hash(s) % size;
                entry * e = table[hv];
                while(e != nullptr)
                {
                        if(e->data == s)
                                return true;
                        e=e->next;
                }
                return false;
        }

        void addreservednames()
        {
                add("string");
                add("int");
                add("const");
                add("bool");
                add("double");
                add("if");
                add("void");
                add("else");
        }
};


void createnames(ofstream & out, int indent, queue<string> & q, bool method)
{
        string type;
        if(method == true)
                type = "static const int ";
        else
                type = "const int ";
        while(!q.empty())
        {
                if(indent != 0)
                        out << setw(indent) << " ";
                int linestart = indent + type.size(), linesize = linestart;
                out << type;
                string identifier = q.front();
                q.pop();
                int i = 1;
                while(true)
                {
                        string hold = q.front();
                        q.pop();
                        if(hold == "ENDENDEND")
                                break;
                        if(hold == "-")
                                continue;
                        linesize += identifier.size() + 1 + hold.size() + 2;
                        if(linesize + hold.size() > maxlinesize)
                        {
                                linesize = linestart + identifier.size() + 1 + hold.size();
                                out << "\n" << setw(linestart) << " ";
                        }
                        out << identifier << "_" << hold << " = " << i << " ";
                        i++;
                }
                out << "\n\n";
        }
        out << "\n";
}

void creategetset(ofstream & out, int indent, queue<string> & q)
{

        while(!q.empty())
        {

                string type, name;
                type = q.front();
                q.pop();
                bool constant = false, pointer = false;
                if(type == "const")
                {
                        type = type + " " + q.front();
                        q.pop();
                        constant = true;

                }
                if(q.front() == "*")
                {
                        type = type + " " + q.front();
                        q.pop();
                        pointer = true;
                }
                while(true)
                {
                        name = q.front();
                        q.pop();
                        if(name == "ENDENDEND")
                                break;

                        out << setw(indent) << " ";


                        if(constant && !pointer)
                        {
                                out << type.substr(6) << " get_" << name
                                    << "() const\n";
                        }
                        else
                                out << type << " get_" << name << "() const\n";
                        out << setw(indent) << " ";
                        out << "{ return " << name << "; }\n\n";


                        out << setw(indent) << " ";
                        if(constant || pointer)
                                out << "void set_" << name << " ("
                                    << type << " & v)\n";
                        else
                                out << "void set_" << name << " (const "
                                    << type << " & v)\n";
                        out << setw(indent) << " ";
                        out << "{ " << name << " = v; }\n\n";

                }

        }

}



void createclass(ifstream & in, ofstream & out, string name, int & linenum)
{
        queue<string> q, getset;
        hashtable set;
        set.addreservednames();
        bool priv = false;
        bool pub = false;
        out << "class " << name << "\n{\n";
        while(true)
        {
                string line;
                getline(in, line);
                istringstream s(line);
                linenum++;
                if(line == "")
                {
                        break;
                }
                while(true)
                {
                        string word;
                        s >> word;
                        if(s.fail())
                                break;
                        if(word == "end")
                        {
                                s >> word;
                                if(s.fail())
                                        break;
                                cerr << "Error on line " << linenum
                                     << " 'end' must be on a line alone.\n";
                                break;
                        }
                        else if(word == "pub")
                        {
                                string test;
                                s >> test;
                                if(!s.fail())
                                        cerr << "Error on line " << linenum
                                             << " 'pub' must be on a line alone.\n";
                                pub = true;
                                priv = false;
                                out << "    public:\n";
                        }
                        else if(word == "pro")
                        {
                                string test;
                                s >> test;
                                if(!s.fail())
                                        cerr << "Error on line " << linenum
                                             << " 'pro' must be on a line alone.\n";
                                pub = false;
                                priv = true;
                                out << "    protected:\n";
                        }
                        else if(word == "names")
                        {
                                int count = 0;
                                while(true)
                                {
                                        string x;
                                        s >> x;
                                        if(s.fail())
                                                break;
                                        if(set.contains(x))
                                        {
                                                cerr << "Error on line " << linenum << " Variable Name '"
                                                     << x << "' Taken.\n";
                                        }
                                        if(x == "-")
                                        {
                                                if(count == 0)
                                                {
                                                        count++;
                                                        continue;
                                                }
                                                else
                                                {
                                                        getline(in, line);
                                                        s.clear();
                                                        s.str(line);
                                                        linenum++;
                                                        continue;
                                                }
                                        }
                                        set.add(x);
                                        q.push(x);
                                }
                                q.push("ENDENDEND");

                        }
                        else
                        {
                                bool ptr = false;
                                if(priv == false && pub == false)
                                {
                                        priv = true;
                                        out << "    protected:\n";
                                }
                                out << "      " << word << " ";
                                if(word == "const")
                                {
                                        getset.push(word);
                                        s >> word;
                                        out << word << " ";
                                }
                                getset.push(word);
                                string x;
                                s >> x;
                                if(x == "*")
                                {
                                        ptr = true;
                                        out << x << " ";
                                        getset.push(x);
                                        s >> x;

                                }
                                if(x == "-")
                                        s >> x;
                                out << x;
                                set.add(x);
                                getset.push(x);
                                while(true)
                                {
                                        s >> x;
                                        if(s.fail())
                                                break;
                                        if(set.contains(x))
                                        {
                                                cerr << "Error on line " << linenum << " Variable Name '"
                                                     << x << "' Taken.\n";
                                        }
                                        set.add(x);
                                        if(x == "-")
                                        {
                                                getline(in, line);
                                                s.clear();
                                                s.str(line);
                                                continue;
                                        }
                                        getset.push(x);
                                        if(ptr)
                                                out << ", * " << x;
                                        else
                                                out << ", " << x;
                                }
                                out << ";\n";
                                getset.push("ENDENDEND");
                        }
                }

        }
        if(pub == false)
                out << "    public:\n";

        createnames(out, 6, q, true);
        creategetset(out, 6, getset);

        out << "};\n\n";

}


void create(ifstream & in, ofstream & out)
{
        int linenum = 0;
        hashtable set;
        set.addreservednames();

        while(true)
        {
                string line;
                getline(in, line);
                istringstream s(line);
                if(in.eof())
                        return;
                while(true)
                {
                        string word;
                        s >> word;
                        if(s.fail())
                                break;
                        if(word == "class")
                        {
                                string name, test;
                                s >> name;
                                s >> test;
                                if(!s.fail())
                                        cerr << "Error on line " << linenum << ". Line must only contain Class and Name of Class.\n";
                                createclass(in, out, name, linenum);
                                linenum++;

                        }
                        else if(word == "names")
                        {
                                queue<string> q;
                                int count = 0;
                                while(true)
                                {
                                        string x;
                                        s >> x;
                                        if(s.fail())
                                                break;
                                        if(set.contains(x))
                                        {
                                                cerr << "Error on line " << linenum
                                                     << " Variable Name '" << x
                                                     << "' Taken.\n";
                                        }
                                        if(x == "-")
                                        {
                                                if(count == 0)
                                                {
                                                        count++;
                                                        continue;
                                                }
                                                else
                                                {
                                                        getline(in, line);
                                                        s.clear();
                                                        s.str(line);
                                                        linenum++;
                                                        continue;
                                                }
                                        }
                                        set.add(x);
                                        q.push(x);
                                }
                                q.push("ENDENDEND");
                                createnames(out, 0, q, false);
                                linenum+=2;


                        }
                        else if(word == "pub" || word == "pro")
                        {
                                cerr << "Error on line " << linenum
                                     << "'" << word << "' May Only Be Used Inside A Class.\n";
                        }
                }
        }

}


int main(int argc, char * argv[])
{
        if(argc != 1)
        {
                maxlinesize = stoi(argv[1]);
                infile = argv[2];
                outfile = argv[3];
        }
        ifstream in(infile);
        ofstream out(outfile);

        if(in.fail() || out.fail())
        {
                cerr << "Error Opening File.\n";
                exit(1);
        }
        create(in, out);
        in.close();
        out.close();
}
