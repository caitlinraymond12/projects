## Structs and Hashtables

There are two structs in my program, one to represent a portuguese word, and one to represent an english word.

### Portuguese Struct

```cpp
struct portugueseword
{
    vector<englishword *> englishwords;
    string portuguese;
    string firstPersonSingular, secondPersonSingular, thirdPersonSingular,
    firstPersonPlural, secondPersonPlural, thirdPersonPlural;
    bool irregular;

    portugueseword(vector<englishword *> e, string p, string fps, string sps, string tps, string fpp, string spp, string tpp, bool i)
    {
        englishwords = e;
        portuguese = p;
        firstPersonSingular = fps;
        secondPersonSingular = sps;
        thirdPersonSingular  = tps;
        firstPersonPlural = fpp;
        secondPersonPlural = spp;
        thirdPersonPlural = tpp;
        irregular = i;
    }

};

```

The portuguese struct contains a vector of english words. The reason why this is a vector instead of a simple string or a pointer to the englishword object is because some portuguese verbs mean multiple things in english. For example:

```
Dizer: To talk, to speak
Fazer: To do, to make
```

Therefore in order to reflect all of a words meanings, there is a vector of pointers to english words. 

The next part in the struct are strings. These strings contain the infinitive of the verb in portuguese, such as "falar", and the following strings have it conjugated in the different personal tenses: 

```
firstPersonSingular: "falo"
secondPersonSingular:  "falas"
thirdPersonSingular: "fala"
firstPersonPlural: "falamos"
secondPersonPlural:  "falais"
thirdPersonPlural: "falam"
```

These translate to english as I speak, you speak, he/she speaks, we speak, you guys/you all speak, they speak.


The final part of this struct is a bool, that signals whether or not the verb is irregular. 




### English Struct

```cpp
struct englishword
{
    string english;
    string firstPersonSingular, secondPersonSingular, thirdPersonSingular,
    firstPersonPlural, secondPersonPlural, thirdPersonPlural;
    portugueseword * portuguese;


    englishword(string e, string fps, string sps, string tps,
                string fpp, string spp, string tpp, portugueseword * p = nullptr)
    {
        english = e;
        firstPersonSingular = fps;
        secondPersonSingular = sps;
        thirdPersonSingular  = tps;
        firstPersonPlural = fpp;
        secondPersonPlural = spp;
        thirdPersonPlural = tpp;
        portuguese = p;
    }
};

```
The english struct contains a pointer to a single portuguese verb that it can be translated to. 

It also contains strings that hold what the word is, "to talk", as well as it conjugated in all the personal tenses.

Something interesting about English is we do actually conjugate, just as many other languages do, just not to the same extent. 

For example, "I talk" and "She talks". The infinitve of the verb "To Talk" is being conjugated here, "talk" for first person singular, and "talks" for third person singular. However, the conjugation is often the same between different personal tenses, which is why in English we have to use pronouns such as "I", "We", "She", while other languages don't have to. 

```
firstPersonSingular: "talk"
secondPersonSingular:  "talk"
thirdPersonSingular: "talks"
firstPersonPlural: "talk"
secondPersonPlural:  "talk"
thirdPersonPlural: "talk"
```
With the appropiate pronouns these become I talk, you talk, he/she talks, we talk, you all/you guys talk, they talk.


### Hashtable

In this program, I defined my own hashtable class.

My hashtable uses *open hashing* when dealing with collisions within the hashtable, which means that if two different keys map to the same place, a linked list is formed to hold all the entries. 

```cpp
class hashtable
{
    protected:
        struct entry
        {
            englishword * node;
            entry * next;

            entry(englishword * e, entry * n)
            {
                node = e;
                next = n;
            }
        };

        entry ** table;
        int size, number;

        unsigned int hash(const string & word)
        {
            unsigned int v = 12309124;
            for(int i = 0; i < word.size(); i++)
                v = v * 169 + word[i];
            return v;
        }
    public:
        hashtable()
        {
            size = 16;
            number = 0;
            table = new entry * [size];
            bzero(table, size * sizeof(entry *));
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

        void record(englishword * e)
        {
          int hv = hash(e->english) & (size-1);
          table[hv] = new entry(e, table[hv]);
          number++;
          if(number * 2 > size)
          {
            grow(size<<1);
          }
        }

        void grow(int newsize)
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
              int hv = hash(e->node->english) & (newsize-1);
              e->next = newtable[hv];
              newtable[hv] = e;
              e = next;
            }
          }

          delete [] table;
          table = newtable;
          size = newsize;
        }

        englishword * search(string word)
        {
           int HV = hash(word) & (size-1);
           entry * e = table[HV];
           while(e != nullptr)
           {
              if(e->node->english == word)
              {
                return e->node;
              }
              e = e->next;
           }
           return nullptr;

        }

};

```

Each entry in my hashtable is defined by an entry struct. It contains a pointer to the englishword object, which is the node, and a pointer to another entry object, which is used to connect the entries in a linked list if needed. 

Then I create a pointer to a pointer of entries which will serve as the table that holds all the objects, as well as an int for the maximum size of table and number of entries current in it.  

In order to optimize my code, I used bitwise operations where possible in my hashtable class. To do this, I initilize the size of the table to 16, which is 2^4. The size of the table is only ever a power of two, simply being double whenever it has to grow. A bitwise operation is used to do this growing, calling *grow(size<<1)* which shifts the binary representation of this number to the left by one bit, and fills the now open bit with a zero. 16 becomes 32 easily as *00010000* shifts to the left by one bit becoming *00100000*. 

When recording the values, first we get the value of the hash based on the key provided. However, we must modulo this hashvalue by the current size of the table. Again, we use bitwise operations to achieve this. Because the size will always be a power of 2, we can use a bitwise & to module the number by (size -1). 

## English/Portuguese Files

This program reads in 9 different files that I created. Each file has the same 100 verbs, all conjugated in different ways. 

Portuguese Files:
* portuguese_conditional.txt
* portuguese_past-imperfect.txt
* portuguese_present.txt
* portuguese_simple-future.txt
* portuguese_simple-past.txt

These are all the tense that portuguese has in the indicative mood, which is the most commonly used mood and used when discussing facts and things that actually happen. Portuguese also has a subjunctive mood for talking about things such as wishes and desires, and an imperative mood for commands. My program only focuses on the indicative mood *for now.*

All the portuguese files are structured the same. It starts with the english translation of the word in quotation marks, some having more than one translation. Then it gives the infinitive of the verb, which is the unconjugated form. Then, it conjugates the form in 6 tenses, first person singular, second person singular, etc. Finally, it has a true or false value, indicating whether or not the verb is irregular. 

```

"to be" ser sou és é somos sois são true
"to have" ter tenho tens tem temos tendes têm true
"to do" "to make" fazer faço fazes faz fazemos fazeis fazem true
"to say" dizer digo dizes diz dizemos dizeis dizem true
"to go" ir vou vais vai vamos ides vão true

```

English Files:
* english_conditional.txt
* english_future.txt
* english_past.txt
* english_present.txt

There is one less english file than portuguese files. The reason for this is because there are two past tenses in portuguese. There's the preterite, which refers to completed actions in the past. Such as "Yesterday, I bought an apple." There's also the imperfect, which refers to habitual actions in the past, such as "When I was 10, I rode my bike to school everyday." In english, however, we only have one way of conjugating in the past tense, and make no distinction whether it was an act that happened once or an act that used to happen all the time. 

The english_past and english_present files have almost the same structure as the portuguese files, although the conjugation is hardly noticable because as mentioned before, English conjugations are often the same between different personal tenses. 

```
"to be" am are is are are are
"to have" have have has have have have
"to do" do do does do do do
"to say" say say says say say say
"to go" go go goes go go go

```

The english_conditional and english_future files are formatting differently, only containing the unconjugated form of the verb. The reason for this is in English, the future and conditional tense is not conjugated at all. 

For example, if I wanted to use the verb "to go" in the future, it would be:

* I will go
* You will go
* He will go
* We will go
* You (plural) will go
* They will go

It always ends in "will go". The same goes for the conditional, becoming "would go" instead. 

So, because the verb doesn't ever conjugate, the file is able to be less complex. 

```
to be
to have
to do
to say
to go
```



### Quick Conjugation Lesson

What does conjugation mean?

Conjugating a verb means changing the verb based on who it refers to.
All verbs in portuguese end in -ar, -er, or -ir. Each of these endings have their own rules of conjugation, based on which person is speaking and which tense they are speaking in. 

**Present Tense Conjugation:**

| Personal Tense  | -ar | -er | -ir |
|----------|----------|----------|----------|
| Eu | -o | -o| -o |
| Tu | -as | -es | -es |
| Você / Ele / Ela | -a | -e | -e |
| Nós | -amos | -emos | -imos |
| Vós | -ais | -eis | -is |
| Vocês / Eles / Elas | -am | -em | -em |

So when you're conjugating a verb, you drop the ending (-ar, -er, ir), and add the appropiate ending. 

For example, if I wanted to say "we talk":

* Take the unconjugated form: *falar*
* Drop the ending: *fal*
* Find the nós ending for -ar verbs: *amos*
* Combine: *falamos* 

If a verb is *irregular*, it means it doesn't follow these rules of conjugation. For example, take the verb *dizer* which means  "to say". 

If I wanted to say "I say", I would expect to find the *eu* ending for -er verbs, which is *-o*, and conjugate using this, which would result in *dizo*. However, this is not what the actual conjugation is. The correct *eu* form for dizer is *digo*, which does not follow the expected form, therefore it is irregular. 

## Reading in Files

There are three different functions for reading in these 9 files. The first is readenglishsimple(string filename), that reads in the english files for future and conditional. Then there is readenglish(string filename), that reads in the other two english files. The final is readfile(string filename), that reads in all the portuguese files. There are different functions because there are three different ways the files can be formatted. 

### readenglishsimple(string filename)

This function reads in the simpler english files, the ones that only have the unconjugated form of the verb.

```cpp
void readenglishsimple(string filename)
{
    ifstream file(filename);
    if(file.fail())
    {
        cout << "Issue Opening File\n";
        return;
    }

    string will_would;
    hashtable * correct_HT;
    if(filename == "english_future.txt")
    {
        will_would = "will ";
        correct_HT = &english_future;
    }
    else
    {
        will_would = "would ";
        correct_HT = &english_conditional;
    }
    string english, conjugated;
    string firstPersonSingular, secondPersonSingular, thirdPersonSingular,
           firstPersonPlural, secondPersonPlural, thirdPersonPlural;

    while(true)
    {
        getline(file, english);
        if(file.fail())
            break;

        conjugated = will_would + english.substr(3);
        firstPersonSingular = conjugated;
        secondPersonSingular = conjugated;
        thirdPersonSingular = conjugated;
        firstPersonPlural = conjugated;
        secondPersonPlural = conjugated;
        thirdPersonPlural = conjugated;


        englishword * w = new englishword(english, firstPersonSingular,
        secondPersonSingular, thirdPersonSingular, firstPersonPlural,
        secondPersonPlural, thirdPersonPlural);
        correct_HT->record(w);
        englishwords.push_back(w);
    }

}
```

It begins by opening the file and ensuring the file was opened correctly. Then, it defines a string *will_would* that can either be assigned to the string "will" for the future tense, and "would" for the conditional tense. Then, a pointer to a hashtable is defined. 

Next, the program checks the filenames. If the file is *english_future.txt*, then the english_future hashtable is selected, and will_would is set to "will ". Otherwise, the english_conditional hashtable is selected, and will_would is set to "would."

Then, we enter a while loop that continues until the end of the file. It reads the entire line of the file into the variable **english**. Since the conjugation is the same in every personal tense for the future and conditional tenses, the conjugation is set to the variable **conjugated**, and each of the six tenses is then set equal to that variable.

Finally, the *englishword* object is created, and it is recorded to the correct hashtable and pushed back onto the global englishwords vector.


### readenglishfile(string filename)

This function is used to read the english files that contain all the conjugated tenses. 

```cpp
void readenglishfile(string filename)
{
    if(filename == "english_future.txt" || filename == "english_conditional.txt")
    {
        readenglishsimple(filename);
        return;
    }

    hashtable * correct_HT;
    if(filename == "english_present.txt")
        correct_HT = &english_present;

    else if(filename == "english_past.txt")
        correct_HT = &english_past;

    else
    {
        cout << "File Name is not Recognized\n";
        return;
    }


    ifstream file(filename);
    if(file.fail())
    {
        cout << "Issue Opening File\n";
        return;
    }
    string english, line;
    string firstPersonSingular, secondPersonSingular, thirdPersonSingular,
    firstPersonPlural, secondPersonPlural, thirdPersonPlural;

    while(true)
    {
        english.clear();
        getline(file, line);
        if(file.fail())
            break;
        istringstream in(line);
        while(true)
        {
            string word;
            in >> word;
            int len = word.length() - 1;
            if(in.fail())
                break;

             if(word[len] == '"')
             {
                word = word.substr(0, len);
                english += word;
                break;
             }

            if(word[0] == '"')
                 word = word.substr(1);

            english = english + word + " ";

        }

        in >> firstPersonSingular >> secondPersonSingular
           >> thirdPersonSingular >> firstPersonPlural >> secondPersonPlural
           >> thirdPersonPlural;
        englishword * w = new englishword(english, firstPersonSingular,
        secondPersonSingular, thirdPersonSingular, firstPersonPlural,
        secondPersonPlural, thirdPersonPlural);
        correct_HT->record(w);
        englishwords.push_back(w);
    }

}
```

This function first checks the name of the file. If it is *english_future.txt* or *english_conditional.txt*, then the *readenglishsimple(filename)* function is called and this function ends. 

If the file being read is not either of those files, then a pointer to a hashtable is defined, and the correct hashtable is chosen based on the name of the current file. 

Next, the program opens the file and ensures that it has been opened correct. 

It then defines all the needed variables to create the englishword object. 

Then, it runs through two while loops in a similar way as the *readenglishsimple* function did. 

Finally, the variables are filled and the *englishword* object is created. It is recorded in its correct hashtable and pushed onto the englishwords vector. 

### readfile(string filename)

This function serves to read in all 5 of the portuguese files. 

```cpp

void readfile(string filename)
{
    ifstream file(filename);
    if(file.fail())
    {
        cout << "Issue Opening File\n";
        return;
    }

    hashtable * correct_HT;
    if(filename == "portuguese_present.txt")
        correct_HT = &english_present;
    else if(filename == "portuguese_simple-future.txt")
        correct_HT = &english_future;

    else if(filename == "portuguese_conditional.txt")
        correct_HT = &english_conditional;
    else
        correct_HT = &english_past;


    string english, other, line, irr_string;
    string firstPersonSingular, secondPersonSingular, thirdPersonSingular,
    firstPersonPlural, secondPersonPlural, thirdPersonPlural;
    englishword * e;

    bool irregular;

    while(true)
    {
        vector<englishword *> englishwords;
        getline(file, line);
        if(file.fail())
            break;
        istringstream in(line);
        while(true)
        {
            string word;
            in >> word;
            int len = word.length() - 1;
            if(in.fail())
                break;

             if(word[len] == '"')
             {
                word = word.substr(0, len);
                english += word;
                e = correct_HT->search(english);
                englishwords.push_back(e);
                english.clear();
                in >> word;
                if(word[0] != '"')
                {
                    other = word;
                    break;
                }
             }

            if(word[0] == '"')
                 word = word.substr(1);

            english = english + word + " ";

        }

        in >> firstPersonSingular >> secondPersonSingular
           >> thirdPersonSingular >> firstPersonPlural >> secondPersonPlural
           >> thirdPersonPlural >> irr_string;
        if(irr_string == "true")
            irregular = true;
        else
            irregular = false;
        portugueseword * w = new portugueseword(englishwords, other, firstPersonSingular,
        secondPersonSingular, thirdPersonSingular, firstPersonPlural,
        secondPersonPlural, thirdPersonPlural, irregular);
        portuguesewords.push_back(w);

        for(int i = 0; i < w->englishwords.size(); i++)
            w->englishwords[i]->portuguese = w;
    }
}

```

To begin, this function opens the file and ensures that it can be opened without issue. Then, a pointer to a hashtable is defined and the correct hashtable is set based on the name of the file. 

Then, all the needed variables to create a *portugueseword* object are defined, and we enter the first while loop. 

Inside the first while loop, and englishwords vector is defined. This vector is used to hold the different english translations that one portuguese word can produce. For example, *Fazer* translates to both "To make" *and* "To do", so we need to record both. 

Then, we read the file line by line, entering a second while loop in which each line of the file is broken down into the individual words. 

The purpose of this second while loop is to select all the english translations of the given portuguese word. All the english translations are wrapped in quotation marks, which is how it knows what part of the line is english and when the portuguese starts. 

The *if (word [len] == ' " ')* is to determine if we are at the end of a quotation, which means we have build the english translation. If so, we search the correct hashtable for the pointer to the *englishword* object, and add it to the englishwords vector. The, we read in the next word. If the next word is another english translation, then the while loop continues. If not, *if (word[0] != ' " ')*, then we have come across the infinitive of the portuguese verb. So, the word is set to the variable *other*, and the while loop is broken out of. 

Then, the rest of the variables are filled, and the *portugueseword* is created. It is pushed back into the *portuguesewords* vector. However, this function has one extra step. Each *englishword* object contains a pointer to a *portugueseword* object. So, every *englishword* object that is associated with this portuguese word will now have it's *portugueseword* object set to this portuguese word. 

```cpp
        for(int i = 0; i < w->englishwords.size(); i++)
            w->englishwords[i]->portuguese = w;
```


### Reading in Files Summary


When we read in the english files, an *englishword* is created. This english word is added to the appropiate hashtable, and pushed back into the englishwords global vector. 

When we read in the portuguese files, we find an english translation enclosed in quotation marks. We take this english translation we have found and search the appropiate hashtable so that we can return an *englishword* object. We need the object rather than the string because the *portugueseword* object contains a vector of *englishword* objects. 

Once we have created our *portugueseword* object, the *englishword* object(s) associated with it are found and the newly created *portugueseword* is set to a variable within that *englishword*.

There are global vectors englishwords and portuguesewords that hold all of the words that have been read in. There are only hashtables for englishwords. This is because the portugueseword variable inside the *englishword* is intially set to null, and later filled in. It is filled in because the *portuguseword* uses the hashtables to find the correct *englishword*. 

Each of these three functions requires the use of a hashtable. At the begining of every function, a pointer to a hashtable is defined, and the address of the correct hashtable is found by using conditional statements. The reason for doing this at the begining of the function is it makes my program more efficient. Rather than searching for the correct hashtable after every object is created to decide which one it should go into and directly inputting it, I utilize pointers and addresses to allow the correct one to be selected just once and utilized throughout the rest of the function. 

## User Input 

### int main() 

```cpp
int main()
{
    string filename, englishfile, answer_with;
    user(filename, englishfile, answer_with);
    readenglishfile(englishfile);
    readfile(filename);


    if(answer_with == "english")
        test1();
    else
        test2();
}

```

In my main function, I define a filename, englishfile, and answer with variables. They are then put into the *user* function as reference variables where they are filled with the correct information. 

The filename is filled with the name for the correct portuguese file, englishfile is filled the the name for the correct english file, and answer_with is filled with either "english" or "portuguese", depending on what language the user would like the type answers in. 

Then, the *readenglishfile* and *readfile* functions are executed, and the correct *test* function is selected based on the answer_with variable. If the user wanted to type the answer in english, *test1* is called. If they want to type the answer in portuguse, *test2* is called. 


### void user(string & filename, string & englishfile, string & answer_with)

This functions prompts the user and allows them to personalize how they want to be test. 

```cpp
void user(string & filename, string & englishfile, string & answer_with)
{
    string answer;
    while(true)
    {

        cout << "Would You Like to Type Answer in English or Portuguese?\n";
        cout << ": ";

        getline(cin, answer);
        for(int i = 0; i < answer.size(); i++)
            answer[i] = tolower(answer[i]);
        if(answer == "portuguese" || answer == "english")
        {
            answer_with = answer;
            break;
        }
        else
        {
            cout << "Not Valid Answer. Please Type 'English' or 'Portuguese'\n";
        }
    }

    while(true)
    {
        cout << "Which Tense Would You Like to Learn?\n";
        cout << "\t * Present \n\t * Simple Past \n\t * Past Imperfect";
        cout << "\n\t * Simple Future \n\t * Conditional\n";
        cout << ": ";

        getline(cin, answer);
        cout << "\n";
        for(int i = 0; i < answer.size(); i++)
            answer[i] = tolower(answer[i]);
        if(answer.empty() || answer == 'q')
            exit(-1);
        else if(answer == "present")
        {
            filename = "portuguese_present.txt";
            englishfile = "english_present.txt";
        }

        else if(answer == "simple past")
        {
            filename = "portuguese_simple-past.txt";
            englishfile = "english_past.txt";
        }

        else if(answer == "past imperfect")
        {
            filename = "portuguese_past-imperfect.txt";
            englishfile = "english_past.txt";
        }

        else if(answer == "simple future")
        {
            filename = "portuguese_simple-future.txt";
            englishfile = "english_future.txt";
        }

        else if(answer == "conditional")
        {
            filename = "portuguese_conditional.txt";
            englishfile = "english_conditional.txt";
        }

        else
        {
            cout << "Not Valid Selection. Select Again or Press Enter To Exit.\n";
            continue;
        }
        break;
    }

}
  
```

First, this functions asks the user if they want to answer in english or spanish.


 The provided input is set to lowercase, to allow for case insensitivity, and if the answer is "portuguese" or "english", the answer_with variable is set and the function continues. If not, the program tells the user that the input was not valid, and the question is outputted again.

Once the user has selected in which language they would like to answer, they are then prompted to select the tense. 

The answer is again set to all lowercase, and the correct filename and englishfile name are selected based on the answer choice. 

If the user types something not listed, they will be asked to select again or exit the program, and the question will be outputted again.

**Example Output**
```
Would You Like to Type Answer in English or Portuguese?
: English
Which Tense Would You Like to Learn?
         * Present
         * Simple Past
         * Past Imperfect
         * Simple Future
         * Conditional
:Present
```

 


### void test1()

This function is called if the user choses to type their answers in English. 

```cpp
void test1()
{
    cout << "Press Enter to Reveal Answer. Type 'q' To Exit. \n";
    while(true)
    {
        srand(time(0));
        int i = rand() % portuguesewords.size();
        int c = rand() % 6;
        portugueseword * w = portuguesewords[i];
        englishword * e;
        vector<string> answers;
        string conjugated, correct, answer;
        switch(c)
        {
            case 0:
            {
                conjugated = w->firstPersonSingular;

                for(int i = 0; i < w->englishwords.size(); i++)
                {
                    correct.clear();
                    e = w->englishwords[i];
                    correct = "i " + e->firstPersonSingular;
                    answers.push_back(correct);
                }
                break;
            }
            case 1:
            {
                conjugated = w->secondPersonSingular;
                for(int i = 0; i < w->englishwords.size(); i++)
                {
                    correct.clear();
                    e = w->englishwords[i];
                    correct = "you " + e->secondPersonSingular;
                    answers.push_back(correct);
                }
                break;
            }
            case 2:
            {
                conjugated = w->thirdPersonSingular;
                for(int i = 0; i < w->englishwords.size(); i++)
                {
                    correct.clear();
                    e = w->englishwords[i];
                    correct = "he " + e->thirdPersonSingular;
                    answers.push_back(correct);
                    correct = "she " + e->thirdPersonSingular;
                    answers.push_back(correct);
                }
                break;
            }
            case 3:
            {
                conjugated = w->firstPersonPlural;
                for(int i = 0; i < w->englishwords.size(); i++)
                {
                    correct.clear();
                    e = w->englishwords[i];
                    correct = "we " + e->firstPersonPlural;
                    answers.push_back(correct);
                }
                break;
            }
            case 4:
            {
                conjugated = w->secondPersonPlural;
                for(int i = 0; i < w->englishwords.size(); i++)
                {
                    correct.clear();
                    e = w->englishwords[i];
                    correct = "you " + e->secondPersonPlural;
                    answers.push_back(correct);
                }
                break;
            }
            case 5:
            {
                conjugated = w->thirdPersonPlural;
                for(int i = 0; i < w->englishwords.size(); i++)
                {
                    correct.clear();
                    e = w->englishwords[i];
                    correct = "they " + e->thirdPersonPlural;
                    answers.push_back(correct);
                }
                break;
            }
        }
        cout << conjugated << " means: ";
        getline(cin, answer);
        bool answeredCorrectly;
        for(int i = 0; i < answer.length(); i++)
            answer[i] = tolower(answer[i]);
        if(answers.size() > 1)
            answeredCorrectly = checkanswer(answer, answers);
        else
            answeredCorrectly = (answer == answers[0]);
        if(answer == "q")
            return;
        if(answeredCorrectly)
            cout << "CONGRATS!\n";
        else
        {
            cout << "Incorrect. The correct answer is: " << answers[0] << ". The verb "
                 << w->portuguese << " means " << w->englishwords[0]->english << ".\n";
        }

        cout << "\n";

    }
}
```

**Check Answer Function**
```cpp
bool checkanswer(string answer, vector<string> answers)
{
    for(int i = 0; i < answers.size(); i++)
        if(answer == answers[i])
            return true;
    return false;
}

```

This function uses srand(time(0)) and rand() to randomly select two numbers; one number is used to randomly select a portuguese word from the portuguesewords vector, and the other is to randomly select one of the 6 avaiable tenses. 

A vector<string> answers is defined because there can be mulitple correct answers. For example, the word *faz* can mean:

* He does
* She does
* You do
* He makes
* She makes
* You make

Therefore there must be a vector of correct answers, not just one.

The variable **conjugated** is used to store the conjugated verb which will be ouput for the user to translate. The variable **correct** is the correct answer(s) that will be added to the answers vector. The variable **answer** is the user's inputted answer.

Then, we enter a switch statement, based on the int c. This will bring us directly to any of the 6 avaliable cases, each representing a different personal tense. First, the variable **conjugated** is filled based on the tense chosen. Then we enter a for statement that runs through each english word that is associated with the randomly chosen portuguese word. For each english word, the correct pronoun is added to the **correct** variable, and it is pushed onto the answers vector. 

Then, the program outputs the **conjugated** variable, and the user must type their answer. The answer is converted to all lowercase, and it is checked against the entries in the answers vector. If it is answered correct, the program outputs "CONGRATS". If not, the user is told they have input an incorrect answer and the correct answer is shown. Further, they are shown the infinitive of the verb and told what it means. 

**Example Output**
```
Press Enter to Reveal Answer. Type 'q' To Exit.
falamos means: we talk
CONGRATS!

encontram means: they find
Incorrect. The correct answer is: they meet. The verb encontrar means to meet.
```


### void test2()

This function is called if the user choses to type their answers in Portuguese. 

```cpp
void test2()
{
    cout << "Press Enter to Reveal Answer. Type 'q' To Exit. \n";
    while(true)
    {
        srand(time(0));
        int i = rand() % englishwords.size();
        int c = rand() % 6;
        englishword * e = englishwords[i];
        portugueseword * w = e->portuguese;
        string conjugated, correct, answer;

        switch(c)
        {

            case 0:
            {
                conjugated = "I " + e->firstPersonSingular;
                correct = w->firstPersonSingular;
                break;
            }
            case 1:
            {
                conjugated = "You " + e->secondPersonSingular;
                correct = w->secondPersonSingular;
                break;
            }
            case 2:
            {
                conjugated = "He " + e->thirdPersonSingular;
                correct = w->thirdPersonSingular;
                break;
            }
            case 3:
            {
                conjugated = "We " + e->firstPersonPlural;
                correct = w->firstPersonPlural;
                break;
            }
            case 4:
            {
                conjugated = "You (plural) " + e->secondPersonPlural;
                correct = w->secondPersonPlural;
                break;
            }
            case 5:
            {
                conjugated = "They " + e->thirdPersonPlural;
                correct = w->thirdPersonPlural;
                break;

            }
        }
        cout << conjugated << " means: ";
        string correct_no_accents = remove_accents(correct);
        getline(cin, answer);
        for(int i = 0; i < answer.length(); i++)
            answer[i] = tolower(answer[i]);
        if(answer == "q")
            return;
        if(answer == correct_no_accents)
            cout << "CONGRATS!\n";
        else
        {
            cout << "Incorrect. The correct answer is: " << correct
                 << ". The verb " << w->portuguese << " means " << e->english << ".\n";
        }

        cout << "\n";

    }
}
```

**Remove Accent Function**

```cpp
string remove_accents(string word)
{
    string newword = "";
    for(int i = 0; i < word.size(); i++)
    {

        if(int(word[i]) == -61)
        {
            i++;

            if(word[i] == -83)
                newword += 'i';
            if(word[i] == -89)
                newword += 'c';
            if(word[i] == -93 || word[i] == -95)
                newword += 'a';
        }

        else
            newword += word[i];

    }
    return newword;
}
```

Again, this function utilizes srand(time(0)) and rand() in order to select two random numbers. The first random number selects a random *englishword* object from the englishwords vector, and the second random number randomly selects a tense. 

An englishword * is set to the randomly selected englishword, and the portugueseword * is set to the portuguese word associated with the selected english word. 

The variable **conjugated** is used to store the conjugated verb which will be ouput for the user to translate. The variable **correct** is the correct answer(s) that will be added to the answers vector. The variable **answer** is the user's inputted answer.

With the second randomly selected number, we enter a switch statement, that takes us directly to our selected tense. In each of the 6 cases, the *conjugated* variable is set to the appropiate prounoun + the appropiate tense. The *correct* variable is set to the corresponding appropiate tense in portuguese. 

The program outputs the conjugated verb and the user must type in the translation in portuguese. A new variable is defined, **correct_no_accents** which removes all accents from the answer that the user input is being checked against. This function is needed because the user is not able to type in accented characters easily while using a regular keyboard. It serves to make the program more user-friendly. The user input is also set to all lowercase. 

User input is checked against the correct answer. If correct a congratulations statement is printed. If wrong, the correct answer (with accents) is shown, and the correct translation of the verb is shown. 

**Example Output**
```
Would You Like to Type Answer in English or Portuguese?
: Portuguese
Which Tense Would You Like to Learn?
         * Present
         * Simple Past
         * Past Imperfect
         * Simple Future
         * Conditional
: Present

Press Enter to Reveal Answer. Type 'q' To Exit.
You say means: dizes
CONGRATS!

We turn means: tornamos
Incorrect. The correct answer is: viramos. The verb virar means to turn.
```