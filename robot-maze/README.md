Project Created: Fall 2023 
Class: Intro to Programming

This was the final project for my intro to programming class. The program reads in a text file and interprets where the player starts (marked by +), where the player must end (marked by E), and any borders the player cannot cross (marked by #). The two files used are in this directory, and I will copy one into this file for reference. 

```
###############################  
#~E#~~~~~~~~~~#~~~~~##~#~~~~~~#  
#~##~###~###~####~#~~#~#~#~##~#  
#~~##~~#~##~~~#~#~##~~~#~~~#~~#  
##~~##~#~~~~#~~~~~###~##~###~##  
#~#~#~~~~#~~#~###~~#~~#~~#~#~~#  
#~#~~#~########~#####~~~~#~##~#  
#~#~~~~~~~~##+~~~~~#####~~~##~#  
#~~~##~###~~##~#~###~~~###~#~~#  
#~#~#~~~~~~~~~~~~~~~~#~~~#~#$~#  
###############################  
```

To play the game, the user uses the wasd keys to move around the maze. The gaol is to make it to the treasure while avoiding the maze monsters. 

There are 2 enemy monsters that the player must also avoid when naviating through the maze. The cyan robot will make it's way directly to the treasure, so the player must move fast to beat this one. The purple robot will move about the maze randomly, often getting in the player's way. 

If one of the monsters gets to the treasure first, or if the player touches a monster, the game is over. If the player successfuly makes it to the treasure, then they win, and the path that they took will light up in yellow. 

Even though the player could backtrack, go in circles, or even visit every sqaure on the back, the yellow brick road at the end will only show their correct path to the treasure, and will not color in any wrong turns taken. 

