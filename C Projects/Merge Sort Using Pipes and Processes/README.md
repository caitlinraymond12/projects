### **Project Created**: Fall 2025 

### **Class**: Systems Programming


I used my MIO function to complete this assignment. The only place where <stdio> is used is for printing out the appropriate statements for gradescope. 

##	Problem Description
The purpose of this program was to read a text file where each line contained one word, and output a file with all the same words in sorted order. This was accomplished through various pipes and parent-child processes. To do this, a parent process reads the file, and outputs every word to two child processes in alternating order. Then, each of these child processes sort the list of words that they were given and then send their information through two different pipes to the same child, child3. Child3 takes in the input, and sorts it, and write it to the output file.


##	Solution Design
a.	Main Program:
int main(int argc, char * argv[])
This function accepts the name of a file from the command line. It checks to make sure the user put in two prompts on the command line, and attempts to open the file based on the file name given in the second part of the prompt to ensure that it is a real, readable file. If that all works, then it calls setup(), and based on the value return by setup, either prints “Parent stop” or “Parent done”;

int setup(char * filename)
This function sets up all the pipes, the status integer, and all the child processes. It forks for each child, and uses if-else statements to determine which child is currently running. Inside each child, it closes the pipes that it does not need and runs its child#() function. Once all the children are set up, the parent function runs, and then waits for each of the children to complete.
void parent(int wfd1, int wfd2, char * filename)
The wfd1 is the write end of pipe 1, and the wfd2 is the write end of pipe 2. This function opens the appropriate files and sets an int write1 = 1. This acts as a Boolean value and alternates each time a string is read and written so that the parent fills each pipe alternatively. Then, we enter a do{} statement, where each string is read from the file and written either to pipe 1 or pipe2. Once they are all written, we close each of the files.

b.	Function:
void child1(int rfd, int wfd)
The rfd is the read end of pipe 1. The wfd is the write end of pipe 3. This function opens all the file and then creates an array of pointers to strings of size ARRAYSIZE, which is 256. Then, it continually reads each string from pipe1, which was filled by the parent function, and it puts each string in the array, growing it if it gets too full. Then, it calls qsort() in order to sort the array of strings, then goes through each object in the array and writes it to pipe3, which will then be read by child3. Then it exits with code 0.

void child2(int rfd, int wfd)
The rfd is the read end of pipe 2. The wfd is the write end of pipe 4. This function behaves in the exact same way as does child1. The only difference is that it writes the sorted data to pipe4 rather than pipe3. Then it exits with code 0.

void child3(int r3fd, int r4fd) 
The r3fd is the read end of pipe 3. The r4fd is the read end of pipe 4. This functions opens all the appropriate files and creates the final output file. It also creates an array of pointers to strings and then goes into two do{} statements. The first statement reads each string from pipe3, filled by child1, and adds it to the array. The second statement reads each string from pipe4, filled by child2, and adds it to the array. Finally, it sorts the array of string, and then one-by-one writes each string to the output file. Then it exits with code 0.
