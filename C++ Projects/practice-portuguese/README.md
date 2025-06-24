### **Project Created**: Winter 2024


## The Idea

Why did I create this program? 

I created this program because I love learning new languages. I think its amazing learning what unique phrases different languages have, and how even within a language there are different words and expressions based on the region where it is spoken. I taught myself Spanish in the summer of 2023. How did I do it? I started with the verbs. I first learned how to conjugate the top 100 verbs in the present tense for yo, tu, ella/el/usted, nosotros, ellas/ellos/ustedes. Then I moved onto the preterite, then the past perfect, and I made my way through all the tenses, only studying the verbs. Soon I knew the top 100, then the top 300 most used verbs, I began to read sentences, then articles, and eventually books, all growing from the basic knowledge of the Spanish verbs.

The purpose of explaining my journey with learning Spanish is to highlight how I learned it by focusing on verbs. Learning the verbs and how to conjugate them allowed me to learn Spanish in a fast, effective way. So, when I decided that the next language I wanted to tackle was Portuguese, I decided to do it in the same way: start with the verbs. 

The issue with this approach, as I found out, is there is no program out there that allows you to just practice Portuguese verbs. When I learned Spanish, I used an app called Ella Verbs, which was for Spanish only. I could not find a program that was as effective that focuses on learning Portuguese verbs only. I knew this was the way I wanted to learn it, so since I couldn't find a suitable program online, I decided to create it for myself. 

This is one of my favorite things about programming. If there's something I want, I can go out and create it. I don't have to wait for something else to create an idea I already had, or settle for a version of something that I know isn't perfect for me. I have the ability to create great things, so why not use it?

## The Program 

First, the program starts by letting the user decide if they would like to be shown a portuguese verb and type the english translation, or be shown an english verb and type the portuguese translation. Then, they select which tense they would like to practice in. All the parameters are reference parameters, so all the users answers are saved and used later. 

Depending on what tense the user selected, the readenglishfile() and readfile() functions are called in order to read and store the list of portuguese and english verbs of that tense. Inside the same directory are .txt files that contain the same words in both english and portuguese, and in the past, present, and future. These functions read those files and create a vector of english words and a vector of portuguese words that are used later during the testing. A custom hashtable is also used in order to store the words so they can be found easily later on. 


The test is very simple. It outputs a conjugated verb in one language, and the user must type out the translation of that verb in the other language. All of the output and input is done directly in the command line.


```

Would You Like to Type Answer in English or Portuguese?
: English
Which Tense Would You Like to Learn?
         * Present
         * Simple Past
         * Past Imperfect
         * Simple Future
         * Conditional
: Present

Press Enter to Reveal Answer. Type 'q' To Exit.
ofereceis means: you offer
CONGRATS!

abris means: you open
CONGRATS!

```

## Additional Information

This is the first large project I worked on outside of the classroom, so I am very proud of it and wanted to include more information about each of the functions. If you're interested, there's an additional markdown file titled "moreInformation.md" that goes into more detail about each function. 
