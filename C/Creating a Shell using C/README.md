### **Project Created**: Fall 2025 

### **Class**: Systems Programming

int unknown(char ** array, int num)
Prints Unknown Command message to MIOOUT.

int help(char ** array, int num)
Prints Help message to MIOOUT.

int quit(char ** array, int num)
Prints Quit message to MIOOUT and exits the program.

int run(char ** array, int num)
Takes in an array of elements. The first element is the program name. Any remaining elements are the program arguments. Creates a child, and in the child uses execv() to run program given in the char ** array along with all of its arguments.

int pipe_helper(char ** argv1, char ** argv2)
Takes in two array of elements. The first element in each array in the program name, and any remaining elements are the arguments to the programs. This function creates two children, and in each of the children uses execv to run the program given. Creates a pipe so each of the children can talk to one another. The first child dupes to write end of the pipe to STDOUT, and the second child dupes the read end of the pipe to STDIN.

int run_pipe(char ** array, int num)
Takes in an array of elements. In this array, there are two program names, along with arguments for each program, separated by the keyword “pipe.” This function separates this one array into two separate arrays, where each array starts with the program name and contains any arguments to that program. Then, this function calls pipe_helper() with the two arrays it just created. 

int run_to(char ** array, int num)
First, the function builds a second array, argv1, to store the program name and all the program arguments to be used with execv() later. Once the program array is build, then the TCP connection is broken down into TCP, hostname, and port number by using strtok. Then, it is checked to ensure that it is a TCP connection and that the hostname and port number are not NULL. Then, we connect to the server using the code that was provided in the class notes, printing errors where necessary. Then, we set up the child, and dupe the socket descriptor we just created to STDOUT_FILENO, and then use execv() to run the given program. Once the child has finished executing, the commsoc is closed, and the program is returned. 

int list(char ** array, int num)
This function utilizes the run() function already created to run the ls25 program that we created in lab one. The user can type in list with any of the arguments (-aFs) and run the ls25 program. If the user just types list, then this function will add a second argument of “.” to the array to tell the ls25 program to list the current directory.

int procs(char ** array, int num)
This function created a DIR * dp, and a struct dirent * de. Then, we set the dp directory to the /proc directory, which lists all the open processes. Then, we go through each entry one by one. We set a Boolean variable print equal to 1. If the process starts with a “.”, then we set the Boolean equal to 0, and we won’t print that process number. Then, we go through each character in the entry, and ensure that there is no alphabetic character in it. If there is, then we also set print equal to zero. Else, we will print the process ID number.

int killp(char ** array, int num)
First, the function converts the first value in the array to an integer, then it runs the kill() function on it and send it with the signal SIGKILL. Then, the function checks the kill status, and prints a message accordingly. 

struct map dtable[] = {{"unknown", unknown} , {"help", help}, {"quit", quit}, {"run", run}, {"run_pipe", run_pipe}, {"run_to", run_to}, {"list", list}, {"procs", procs}, {"kill", killp}};
This program uses a dtable in order to match and run each of the function needed to execute.

char ** buildarray(char * input, int * len)
This function is responsible for breaking down the input and putting it into an array to be sent to the functions. It uses strtok to accomplish this. If the user types “list”, this means they want to list all of the files in a certain directory, which uses the ls25 program, so this function automatically sets the program name equal to ls25. For the rest of the functions, it simply isolates the string and adds it to the array. Finally, it sets the length of the array equal to the final index (num) that was loaded, and returns a pointer to the array.

int shell()
First, the program calculates the size of the dtable to be used later. Then, while in a continuous loop, it prints out “Myshell>” and uses mygetline() with MIOIN to get each line of input by the user. Then, it compares each input string to determine what the proper key should be so it knows which function to call. It is case insensitive, so if the line contains either “run” or “Run” and “pipe” or “Pipe” then the key will be set to “run_pipe”. It only checks the program that could have multiple strings on the input line like this. If it is not a run or kill command, then it won’t have any extra lines, for example, “quit” is simple “quit.” So, the program converts the entire input line to lowercase, and set the key equal to input. Then, the buildarray() function is ran, and then the dtable is searched in order to find a matching function for the given key. 

int main(int argc, char * argv[])
Where the program starts. Prints out the initial welcome message and runs the shell() function.

Conclusion: This project brought together every topic that we had learned in this course by asking us to recreate the tool we have been using throughout the semester: The shell. The program integrates our MIO library that we created by asking us to read the input from the input line using mygetline(), and to print output to the command line by using myputs(), and to accomplish this by using the MIOIN and MIOOUT objects that we created that connect to the STDIN_FILENO and STDOUT_FILENO. This project integrates processes by asking us to go beyond just reading and writing from the command line and actually creating children and using execv() to run entirely different programs. Additionally, we were able to combine our simple run() function with run_to() and run_pipe() to introduce two more topics: networking and pipes. We were able to successfully connect to a network and send data to it, and we were able to use the dup2() function to facilitate inter-process communication between two different programs using pipes. Finally, in the extra credit portion, there was the opportunity to further connect the projects completed throughout the semester, and allow the user to run the ls25 program through the shell that we created. This was accomplished by utilizing the general run() function and setting the program to be ran equal to ls25. Overall, this project explored various critical topics to systems programming such as file descriptors, STDIN/STDOUT, processes, pipes, the exec() library, and networking. It accomplishes this by integrating projects previously worked on in the semester, such as ls25 and the mio library, and general knowledge gained throughout the course.
