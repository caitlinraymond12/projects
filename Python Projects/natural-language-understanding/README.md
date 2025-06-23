### **Project Created**: Spring 2025 

### **Class**: Principles of Artificial Intelligence


The focus of this assignment was not necessarily the actual coding, but more on manipulating the given files to allow the program to parse a wider range of sentences. 

The purpose of this program was to type a sentence, and it would then parse the sentence and tell you if it was a valid setence, and output all the different ways it could be parsed and the type of sentences they were. For example, the sentence "the cat frightened the dog near the door" can be interpreted two different ways. One way is to understand that the cat frightened the dog that is near the door, the dog being what is close to the door. The second way to understand it is the cat did the frightening of the dog near the door, the whole situation took place near the door.

```
 <- the cat frightened the dog near the door
['the', 'cat', 'frightened', 'the', 'dog', 'near', 'the', 'door'] as sentence-cnj

***************************************************************************
 sentence-cnj
     statement
         np
             art "the" ({'num': {'p', 's'}, 'typ': {'def'}},)
             nn "cat" ({'num': {'s'}, 'ani': {'true'}, 'gen': {'m', 'n', 'f'}},)
         vp
             vb "frightened" ({'num': {'p', 's'}, 'tns': {'ps'}, 'typ': {'t', 'i'}},)
         np
             art "the" ({'num': {'p', 's'}, 'typ': {'def'}},)
             nn "dog" ({'num': {'s'}, 'ani': {'true'}, 'gen': {'m', 'n', 'f'}},)
             prpp
                 prp "near" ({},)
                 np
                     art "the" ({'num': {'p', 's'}, 'typ': {'def'}},)
                     nn "door" ({'num': {'s'}, 'gen': {'n'}},)

***************************************************************************
 sentence-cnj
     statement
         np
             art "the" ({'num': {'p', 's'}, 'typ': {'def'}},)
             nn "cat" ({'num': {'s'}, 'ani': {'true'}, 'gen': {'m', 'n', 'f'}},)
         vp
             vb "frightened" ({'num': {'p', 's'}, 'tns': {'ps'}, 'typ': {'t', 'i'}},)
         np
             art "the" ({'num': {'p', 's'}, 'typ': {'def'}},)
             nn "dog" ({'num': {'s'}, 'ani': {'true'}, 'gen': {'m', 'n', 'f'}},)
         prpp
             prp "near" ({},)
             np
                 art "the" ({'num': {'p', 's'}, 'typ': {'def'}},)
                 nn "door" ({'num': {'s'}, 'gen': {'n'}},)

finished, ambiguous: 2 successful parses
************************************************************

```

For the project, the files grammar.txt, vocab.txt, and atn.py were given. However, they were only able to successfully parse a few sentences. The assignment was to add a wider range of vocabulary to the vocab.txt file and to add new grammar rules to the grammar.txt so that it would be able to successfully parse almost any sentence that could be typed in. 
