#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <strings.h>
#include <cstdlib>

using namespace std;

struct englishword;


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

hashtable english_present;
hashtable english_past;
hashtable english_future;
hashtable english_conditional;


vector<portugueseword *> portuguesewords;
vector<englishword *> englishwords;


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
    {
        correct_HT = &english_future;
    }

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

bool checkanswer(string answer, vector<string> answers)
{
    for(int i = 0; i < answers.size(); i++)
        if(answer == answers[i])
            return true;
    return false;
}

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
                    correct = "you " + e->secondPersonSingular;
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
        if(answer.empty() || answer == "q")
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