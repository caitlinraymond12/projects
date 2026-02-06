### **Project Created**: Fall 2025 

### **Class**: Systems Programming

##	Problem Description
In this project, I created my own IO library named MIO, and recreated all the functions that are found in the standard library. I first had to create my own MIO object, that acts as a file struct does in standard IO. Then, I used that MIO in all the functions, starting from the lowest level to the highest. The lowest level works directly with the OS and utilizes the basic read() and write() function. These simple starting functions are built on level by level until we have the highest level functions such as getline(). My implementation uses a buffered IO approach.


##	Solution Design

#### MIO *myopen(const char *name, const int mode);
The function defines the variable fd. Then, it checks the mode the user typed in against the macros MODE_R, MODE_WA, MODE_WT. This tells the function how to open the file, either read, write append, or write truncate. Then, this function called mydopen() using that file descriptor. 

#### MIO *mydopen(const int fd, const int mode, const int bsize);
First, I check to see if bsize is a valid size. If it’s not, I return NULL. Then, the MIO object is created using malloc. The appropriate variables are set. If bsize is greater than 0, then the read buffer (rb) and the write buffer (wb) get memory allocated to them and they are initially set to zero. If bsize is equal to zero, then these get set to null. The MIO object has a new variable, bufferSize, and that gets set to bsize. Then, the function returns a pointer to the newly created MIO object.

int myclose(MIO *m);
First, the function ensures that the MIO object is not null. If it is, it returns with -1. If not, then it checks if it’s a write file by using the marco M_ISMW. If it is, it flushes the buffer. Then, it frees the read and write buffers, then it closes the file, then it frees the space the MIO object took up. 

int myflush(MIO *m);
First, the function ensures that the MIO object is not null. If it is, it returns with -1. Then, it writes whatever is on the write buffer to the disk. Then, it resets everything in the buffer to zeros, then returns x, the number of bytes written.


int myread(MIO *m, char *b, const int size);
First, the function ensures that the MIO object and the b char are not null. If they are, it returns with -1. Then, it checks the buffer size of the MIO object. If it is zero, then we are performing an unbuffered read, and so we use the read() function directly on the buffer that was passed in. We either return -1 with an error or the number of bytes read. If buffer size is greater than 0, then it begins by keeping track of number of bytes read. While the number of bytes read is less than the size requested, it will go in the while loop. If the start pointer is equal to the end pointer (they are both equal to zero initially), then it will read from the file into the read buffer. It sets rs back to zero, and sets re to the number of bytes read. Then, we calculate how many bytes we can read on this loop. If we requested less than what remains, then we will only read that much. If we requested more, then we will read the max amount that we can and get the rest on the next loop. Then, we use memcpy() to copy the data in the read buffer to the b parameter. Then, we increment rs and bytesRead by the number that was read. We will return the number of bytesRead. If there is an error reading from the file, we will return -1.

int mygetc(MIO *m, char *c);
First, the function ensures that the MIO object and the c char are not null. If they are, it returns with -1. Then, it reads one character using myread() and stores it into the c parameter. The number of bytes read is stored in x. If x is less than or equal to 0, there was an error. If not, then it’s fine, and 1 is returned.

char *mygets(MIO *m, int *len);
First, the function ensures that the MIO object and the int len pointer are not null. If they are, it returns with NULL. Then, it defines a size equal to MBSIZE. This will be the size of the memory that we allocate to begin. It checks to make sure that the memory we allocated was not NULL. Then, we get the first character and make sure it’s valid. Then, while the first characters are white space, we continually go through them until we get to the first real character. So, while M_ISWS(c) is false, we go through the file. We keep track of an index I, that we increase after each iteration. If I becomes equal to the size – 1, then we double the size of the memory allocated. We set it equal to size – 1 to keep a place for the NULL terminator at the end. After the loop, we set s[i] = ‘\0’, and put I into the len pointer passed in as a parameter. We realloc the space to free up any unused space, and return a pointer to the string that we just created.  

char *mygetline(MIO *m, int *len)
First, the function ensures that the MIO object and the int len pointer are not null. If they are, it returns with NULL. Then, it defines a size equal to MBSIZE. This will be the size of memory that we allocate to begin. It checks to make sure that memory allocated was not NULL. Then, we get the first character and make sure it’s valid. Then, while the character we took in is not equal to ‘\n’, we go through the loop, taking in a character from the file each time. We keep track of an index I, that we increase after each iteration. If I becomes equal to the size - 1, then we double the size of the memory allocated. We set it equal to size – 1 to keep a place for the NULL terminator at the end. Once we break out of the loop, we check if the last character saved as a ‘\r’. We do this because WindowsOS saves with a new line character of ‘\r\n’ , so if we detect a ‘\n’ we have to also check to make sure we didn’t encounter a ‘\r’ before. If we did, we decreased the index of I so we don’t count it in our line. Then, we set the last index of the line equal to ‘\0’. We set the len equal to the index I, and we realloc line so we free up any unused space. Then we return line.


int mywrite(MIO *m, const char *b, const int size);
First, the function ensures that the MIO object and the b char are not null. If they are, it returns with -1. Then, we check if bufferSize is equal to 0. If it is, then we are performing an unbuffered write, so we write directly into the buffer that was passed in, and either return -1 with an error or return the number of bits written. If there is a buffer, then we keep track of number of bytes written. While the number of bytes written is less than the size requested to write, we continue the loop. First, we determine how much exactly to write. We calculate the max amount that we can write based on what’s left in the buffer, and the amount we want to write, and choose the smallest one. Then, we copy from the buffer passed in as a parameter to the file’s write buffer. Then, we increase the we and the bytesWritten by the actual number that was written. If we is equal to the size of the buffer, that means the write buffer is full, so we write to the file. After the loop is over, we return the number of bytes written.

int myputc(MIO *m, const char c);
First, the function ensures that the MIO object is not null. If it is, it returns with -1. Then, we write one character by using mywrite(). If the operation was unsuccessful, then we print an error and return -1. If not, we return the number of bytes written, which should be 0. 

int myputs(MIO *m, const char *str, const int len);
First, the function ensures that the MIO object and the str char are not null. If they are, it returns with -1. Then, initialize index I to 0 and go through the entire length of the string, saved as the len parameter. For each position in s, we write it to the file passed in. If at any point myputc() returns -1, then we return how many bytes we have written up until that point. If we haven’t written any, then we return -1. After the for loop, we return I, which is the number of bits successfully written.

void myinit()
This function initializes our mioin, mioout, and mioerr. We use mydopen and pass in the file descriptor as the first parameter, the mode in the second parameter (although this isn’t necessary, it’s only here because in .h file mydopen has a second mode parameter), and finally the buffersize. mioout and mioerr are unbuffered, and the buffer for mioin is set to MBSIZE.
