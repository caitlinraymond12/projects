Project Created: Fall 2024
Class: Algorithms 

This project was created to help decrease the time it takes to type out class definitions by reading an input file and outputting a file with a correctly formatted class definition. 

A sample input file and sample output file are included in this directory. When runing this program, on the command line you are able to type in the max amount of characters on each line, the name of the input file to read from, and the name of the output file to write to. 

The sample file must be formatted in a specific way. it must have the name of the class on one line and nothing else. Then it must include types followed by names of the variables. If the user wants to specifiy something as public they must include "pub" on a line all by itself, and anything following that line will be defined as public. Protected is the default. For all the variables in protected, the code will write set functions, that allows the user to change the value of these, and get functions, that returns the values. Finally, "end" must be on a line by itself to indicate that the class definition is over. 


For example and input file containing:

```
class person  
string - firstname lastname address city state phone  
int - ssn balance  
const cat * - pet  
pub  
string - favourite_colour  
end  
```

would output:

```
class person
{
    protected:
      string firstname, lastname, address, city, state, phone;
      int ssn, balance;
      const cat * pet;
    public:
      string favourite_colour;

      string get_firstname() const
      { return firstname; }

      void set_firstname (const string & v)
      { firstname = v; }

      string get_lastname() const
      { return lastname; }

      void set_lastname (const string & v)
      { lastname = v; }

      string get_address() const
      { return address; }

      void set_address (const string & v)
      { address = v; }

      string get_city() const
      { return city; }

      void set_city (const string & v)
      { city = v; }

      string get_state() const
      { return state; }

      void set_state (const string & v)
      { state = v; }

      string get_phone() const
      { return phone; }

      void set_phone (const string & v)
      { phone = v; }

      int get_ssn() const
      { return ssn; }

      void set_ssn (const int & v)
      { ssn = v; }

      int get_balance() const
      { return balance; }

      void set_balance (const int & v)
      { balance = v; }

      const cat * get_pet() const
      { return pet; }

      void set_pet (const cat * & v)
      { pet = v; }

      string get_favourite_colour() const
      { return favourite_colour; }

      void set_favourite_colour (const string & v)
      { favourite_colour = v; }

};
```


