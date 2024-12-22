using namespace std;

class intersection;


class connection
{
  protected:
    string name, type;
    int length, total;
    intersection * A;
    intersection * B;

  public:
    connection(string n, string t, int l, intersection * a, intersection * b);
    void print();
    void print_from_to(intersection * from);
    string get_name();
    string get_type();
    void increase_total(int x);
    int get_total();
    int get_length();
    intersection * get_there(intersection * inter);
};


class intersection
{
  protected:
    int line;
    double lat, longi, nearest_place_distance, dist;
    string state, nearest_place_name;
    vector<connection *> connections;
    intersection * prev;
    connection * prev_road;

  public:
    intersection(int li, double la, double lo, double near, double d, string st, string place, intersection * p, connection * c);
    void print();
    int get_line();
    void set_prev(intersection * p);
    void set_prev_road(connection * r);
    connection * get_prev_road();
    void set_distance(double d);
    double get_distance();
    double get_nearest_dist();
    intersection * get_prev();
    int get_connections_size();
    connection * get_road(int i);
    void set_road(connection * c);
    string get_city();
    string get_state();
    double get_lat();
    double get_long();

};

struct place
{
    int code, road, population;
    string state, city;
    double area, lat, longi, intersection_distance;

    place(int co, int r, int p, string s, string c, double a, double la, double lo, double d);
    void print();
    string get_name();
    string get_state();
    int get_inter();
    double get_lat();
    double get_long();
};



class hashtable
{
  protected:
    struct entry
    {
      place * data;
      entry * next;
      entry(place * p, entry * n);
    };

    entry * * table;
    int size, number;
    unsigned int hash(const string & name);
  public:
    hashtable();
    ~hashtable();
    void record(place * p);
    double fullness();
    void grow(int newsize);
    void print();
    int realstate(string abr);
    void placename(string city, vector<string>& v);
    place * search(string city, string state);
};


class queue
{
  protected:
    intersection * * Q;
    int count, beg, end, size;

  public:
    queue(int n = 10);
    bool empty();
    void grow(int n);
    void add(intersection * i);
    intersection * remove();
    void print();
};



class priorityqueue
{
    protected:
        vector<intersection *> v;
        int num;
        void upheapify();
        void downheapify();
    public:
        priorityqueue();
        bool empty();
        void push(intersection *& i);
        intersection * pop();
        void print();
};


