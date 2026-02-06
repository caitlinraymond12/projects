### **Project Created**: Fall 2025 

### **Class**: Systems Programming

## Problem Description 
In this assignment, I created scripts using C Shell that allows me to quickly and easily backup multiple files at once, as well as restore multiple files. The backup script is able to be called with flags:
* -f Force overwrite in backup directory 
* -s Search backup directory; indicate if a file exists
* -l List all files in the backup.

The restore script is able to be called with flags:
* -f Force overwrite in target directory
* -D Delete files after they've been restored
* -c Clear backup.

## Solution Design 

#### backup.csh
In this file, we immediately jump into another switch statement based on the second argument. This argument will either be flags (-f, -s, -l), a file name, or a nonsense instruction. 
If the instruction is -f, the program enters a loop statement while the number of arguments in greater than 2. It checks to see if the file trying to be backed up is a real file. If it is, it copies it to the backup directory. If not, it prints out “Can only backup regular files”. Then, it shifts argv to the left so we are able to get the potential next file. 
If the instruction is -s, the program enters a loop statement while the number of arguments is greater than 2. It checks to see if the file exists in the backup directory. If it does, it prints the filename, and then the date of last modification. If it does not exist, the program prints out “File does not exist in backup directory.”
If the instruction is -l, then we set the variable files equal to ls backup, which will be a list of all the files in the backup directory. Then we enter a while loop while the number of files is not zero. We print the file name and the date of last medication. 
If the instruction starts with “-“ and is not immediately followed by f, l, or s, then it is not a recognized instruction, and is detected with case “-*” . This statement will print “Command Not Recognized”, and exit with a status of -1. 
The default case is if the user does not type any instructions and simply calls the script with one or more files. The program will enter a while loop while the number of arguments is greater than 1. First, it checks if the file exists in the backup. If it does, it will not overwrite it, and instead will print out information about the file. If it doesn’t, then it will check to ensure that it is a regular file. If it is, it will copy it into the backup directory. If it’s not, it will print “Can only backup regular files” and will move onto the next one. At the end it will shift argv so it can read the next file. 

#### restore.csh
In this file, we first check to see if any delete flag has been set by checking is argv[2] contains the letter D at all. If it does, the delete flag is set high. If not, then it remains low. Then we enter a switch statement based on the second argument. This argument will either be flags (-c, -f) or a file name.
If the instruction is -c, then we set the variable files equal to ls backup, which will give us a list of all the files in the backup directory. Then, we enter a while loop while the number of items in files is not zero. We go through each item and remove it from the backup directory. Then we shift files so we can get the next one. 
If the instruction contains the letter f, then we force restore the file. The reason why the case statement is “*f*” is to account for both -f and -fD flags in one case statement. We will detect if the D flag is high or low later in this statement to determine if we remove the file or not. The program enters a while loop while the number of arguments is greater than 2. If the file exists in the backup, then we check to make sure it’s a file. If it is, then we copy it from the backup into the parent directory. If the delete flag is set high, then we also remove it from the backup directory. If the file was not a regular file or it was not in the backup directory, then the program will let the user know. 
The default statement occurs if there were no flags set, or if only the -D flag was set. The program enters while loop while the number of arguments in argv is greater than 1. If this argument is the -D flag, we skip over it by shifting. If it is not the D flag, then we check if the file exists in the parent directory. If it does, we let the user know that it already exists. If not, then we check to make sure it’s a file. If it is, then we copy it from the backup into our parent. If the delete flag is set high, then we will delete it from the backup directory. If it is not a regular file, then the program will let the user know. 

If all of these instructions get executed, then the program exists with exit status 0. 

