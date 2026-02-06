### **Project Created**: Fall 2025 

### **Class**: Systems Programming


The purpose of this assignment was to create a simple version of the ls command in C in order to show common information needed of files and diretories. Required great knowledge of how the file system works in C.


struct dentry
This is where I hold all the needed information for each entry in a given directory. It holds the directory name, the mode, the last modified date, the size, the user, and the group the user belongs to. 

char* getUser(uid_t userID), getGroup(gid_t, groupID) 
These are helper functions to keep my code in the readDirectory function clean. They take in either the userID or the groupID, and they utilize getpwuid and getgrgid to get the user and group name associated with the given id, and returns the char* for it.

struct dentry* readDirectory(const char *path, int *num)
This function takes in the given path, and an int* that will be filled with the amount of dentry structs there are. The function first goes through all the entries to get a count of how many there are, then it rewinds back to the beginning, and allocates memory based on the amount of dentry structs there were. Then, it goes through each of the entries, and fills the struct with the name, mode, last_modified, size, user, and group associated with that entry. Here is where we also utilize the lstat() function. Finally, we close to directory, set num equal to the number of directories, and return a pointer to where all the structs are located. 



int compare(const void *a, const void *b)
This is a compare function that is used with qsort to sort the data based on the name of the file. It will take in two dentry pointers.

void print(int a, int F, struct dentry * data, int size)
This function is responsible for printing the output. It takes in two flags a and F. It doesn’t take in the s flag because if that flag was set, the already sorted data would have been passed in as the next parameter, data. Finally, it takes in the number of dentry structs there are. It first prints out the column headings, then goes through each struct and formats and prints the appropriate information. If the a flag is set, it prints hidden files. If the F flag is set, it checks which mode it is in.

int main(int argc, char*argv[])
This function defines the size and the pointer to the eventual array of dentry structs. If the user puts in the wrong number of parameters, it catches it. Then it sets the three available flags to zero. If there are 3 arguments, then we know the user input flags, so we first check to make sure they wrote the write then, then we go through and check which flags they set. If there was only two arguments, we simply make sure they provided a correct path, then continue. If the s flag is set, then we sort the data using qsort() and the compare function defined above. Then, we call print giving it the remaining two flags, data, and size. Once the printing is done, we free up the allocated memory and return 0 since it was a success. 
