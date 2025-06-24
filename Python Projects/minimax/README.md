### **Project Created**: Spring 2025 

### **Class**: Principles of Artificial Intelligence


This project was based on the game Nim, which is a game in which there are two players, and there X piles of sticks with Y sticks in each pile. The players each take turns, and in each turn they may only take sticks from one of the pile, but may take any number of stick they'd like. You lose the game if you take the last stick from the last pile. 

So, the assignment was to create an agent that would always select the most optimal move, based on the minimax strategy. 

First, the player enters how many sticks will be in each pile. Then, the game begins. Either the game plays against itself or the player. When it's the agent's turn, the function minimax() returns the optimal move to take as well as what the piles look like after the move is taken. 

The function minimax() recursively calls itself up until the depth that is requested by the program, and that is how many steps ahead in the game it looks to decided which move to take. 

I also adjusted my program so that the player was able to choose their difficulty level. On Easy, the agent would only search the next 5 possible moves. Medium the agent would search the next 10 possible moves. Finally, on Impossible, the agent would search the next 30 possible moves. This is enough to guarantee the agent winning, with one exception. If the game starts in a negative positive against the agent, and the player makes a perfect move every time, then the agent will lose. However this is just something that could happen in the game, an no agent would be able to avoid it.