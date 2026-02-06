### **Project Created**: Fall 2025 

### **Class**: Systems Programming


parent.c
int setup():
This function sets up the two child processes and their pipes. It uses fork to create each process, and decides which process is currently executing based on the pid of the process. Each of the processes closes the pipe ends that it will not interact with and then calls its appropriate function. The parent process takes in input from the user using scanf() and strcasecmp() to compare it to “go.” If the user types in “go,” the program executes. If not, then the program stops and returns back to main. If the program executes, then the parent will wait for both children to finish before exiting. 

void parent(int wfd):
This function is given a file descriptor for the write end of pipe one, and the opens it using fdopen(). Then, it reads in input character by character from stdin, and writes it to this pipe that was just opened. At the end, it closes the file.

void child1(int rfd, int wfd):
This function duplicates the read file descriptor to stdin and duplicates the write file descriptor to stdout. The reason for this is because once this function calls execl(), all open files descriptors except stdin, stdout, and stderr will be lost. So, we duplicate them to these that will not close in order to preserve them. Then, we call execl(“./oper1”, “oper1”, NULL) in order to execute our oper1 program. Then, it calls exit(0); just incase anything goes wrong so that it will still send the exit code.

void child2(int rfd):
This function duplicates the read file descriptor into stdin, and then calls execl() in order to execute our oper2 program. Then, it calls exit(0); just incase anything goes wrong so that it will still send the exit code.

oper1.c
void oper1()
This function allocates four bytes for in and four bytes for out. Then, it sets a go variable that acts as a Boolean that will tell us when to exit out of our while loop. Then, we set the memory for in and out equal to the null terminator ‘\0’, and then begin to read input from stdin. However, we are actually reading in from pipe1 that was created in the parent file, and we just duplicated the file descriptor so that we are able to read from stdin and have it read from that pipe. We set I equal to zero, and call getchar() while I < 4, incrementing each time. If we get an end of file, we break out of the if statement. Then, while I is less than 4, we pad the remaining spaces with the letter ‘z’, increase I, and set go equal to zero which will break us out of the while loop on the next iteration. Then, we perform the operations on each character of in to result in out[0], out[1], out[2], and out[3]. Then, we call fprintf(stdout, …), in order to print each result to stdout. However, since stdout was duplicated to the be the write end of pipe two, we are actually writing to the pipe here. Once there are no more characters to read from stdin (pipe1), we free the memory that was used for in and out, close stdout, and exit with status code zero.



oper2.c
void oper2():
This function defines and unsigned int and sets it equal to zero. This will be the final result that will be updated each iteration. Then we define the in which will be the input from stdin, char c which will be each character we read in, go which will act as a Boolean for our while loop, another unsigned int res that will be the result of each iteration, and a mod value of 2^32 that will be used to take the mod of the final result. Then, while go, we read in four characters from the stdin, which is actually pipe2. If we get to an EOF, we break out of the if statement, and pad the remaining spaces with ‘z’. Then, we perform the necessary operations to get our result for that iteration, and then we add that result to the overall result as long as go is equal to one. After the while loop, we close stdin, take the mod of the final result, print that result to stdout, and then exit with a status code of 0. 

