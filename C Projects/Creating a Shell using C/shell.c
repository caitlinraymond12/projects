#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <dirent.h>
#include "mio.h"
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


/*
MIO * mioin;
MIO * mioout;
MIO * mioerr;

*/

typedef int (* operation)(char **, int);

struct map{
    char * key;
    operation func;
};


int unknown(char ** array, int num)
{
    char * message = "Unknown Command. Use 'Help' for a list of commands\n";
    myputs(mioout, message, strlen(message));
    return 0;
}


int help(char ** array, int num)
{
    char * message =  "Usage: <action> <argument[s]>\n";
    myputs(mioout, message, strlen(message));
    return 0;
}

int quit(char ** array, int num)
{
    char * message = "Thank you for using MyShell by Caitlin Raymond\nContributions to support development can be sent to: ECE Department, College of Engineering, University of Miami c/o Dr. Nigel John\n";
    myputs(mioout, message, strlen(message));
    exit(0);
}


int run(char ** array, int num)
{
    pid_t childpid;
    int status;


    childpid = fork();
    if(childpid < 0)
    {
        fprintf(stderr, "Error creating child1\n");
        return -1;
    }
    else if(childpid == 0)
    {
        execv(array[0], array);
        exit(0);
    }

    
    wait(&status);
    return 0;
}



int pipe_helper(char ** argv1, char ** argv2)
{

    pid_t child1pid;
    pid_t child2pid;
    int status;
    int p1[2];
    pipe(p1);
    child1pid = fork();
    if(child1pid < 0)
    {
        fprintf(stderr, "Error creating child1\n");
        return -1;
    }
    else if(child1pid == 0)
    {
        close(p1[0]);
        dup2(p1[1], STDOUT_FILENO);
        execv(argv1[0], argv1);
        exit(0);
    }
    child2pid = fork();
    if(child2pid < 0)
    {
        fprintf(stderr, "Error creating child2\n");
        return -1;
    }
    else if(child2pid == 0)
    {
        close(p1[1]);
        dup2(p1[0], STDIN_FILENO);
        execv(argv2[0], argv2);
        exit(0);
    }
    close(p1[0]);
    close(p1[1]);
    waitpid(child1pid, &status, 0);
    waitpid(child2pid, &status, 0);
    return 0;
}



int run_pipe(char ** array, int num)
{

    char ** argv1 = (char **)malloc(num * sizeof(char *));
    char ** argv2 = (char **)malloc(num * sizeof(char *));
    int i = 0;
    while((strcmp(array[i], "pipe") != 0) && (strcmp(array[i], "Pipe") != 0)) {
        argv1[i] = array[i];
        i += 1;
    }
    argv1[i] = NULL;
    i += 1;
    int j = i;
    while(j < num)
    {
        argv2[j-i] = array[j];
        j += 1;
    }
    argv2[j] = NULL;
    j += 1;
    pipe_helper(argv1, argv2);
    return 0;
}

int run_to(char ** array, int num)
{
    char ** argv1 = (char **)malloc(num * sizeof(char *));
    int i = 0;
    while((strcmp(array[i], "to") != 0) && (strcmp(array[i], "To") != 0)) {
        argv1[i] = array[i];
        i += 1;
    }
    argv1[i] = NULL;
    i += 1;
    char * TCP;
    char * hostname;
    char * port; 
    char * delimiter = "/";
    TCP = strtok(array[i], delimiter);
    hostname = strtok(NULL, delimiter);
    port = strtok(NULL, delimiter);
    if(strcmp(TCP, "TCP") != 0 || hostname == NULL || port == NULL) {
        fprintf(stderr, "Must use TCP connection\n");
        return -1;
    }
    
    //connect to server
    struct addrinfo hints, *res0;
    int commsoc;
    int error;
    const char *cause = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    error = getaddrinfo(hostname, NULL, &hints, &res0);
    if(error) {
        fprintf(stderr, "Error getting address info\n");
        return -1;
    }
    
    commsoc = -1;
    commsoc = socket(res0->ai_family, res0->ai_socktype, res0->ai_protocol);
    if(commsoc < 0){
        fprintf(stderr, "Error getting socket\n");
        return -1;
    }

    struct sockaddr_in *inaddr = (struct sockaddr_in *)(res0->ai_addr);
    inaddr->sin_port = htons(atoi(port));

    if(connect(commsoc, res0->ai_addr, res0->ai_addrlen) < 0){
        fprintf(stderr, "Cannot connect\n");
        return -1;
    }
    
    //set up child
    pid_t childpid;
    int status;

    childpid = fork();
    if(childpid < 0)
    {
        fprintf(stderr, "Error creating child\n");
        return -1;
    }
    else if(childpid == 0)
    {
        dup2(commsoc, STDOUT_FILENO);
        execv(argv1[0], argv1);
        exit(0);
    }
    
    wait(&status);

    close(commsoc); 
    return 0;
}

int list(char ** array, int num)
{
    printf("list\n");
    if(num == 1)
    {    
        char * token = ".";
        array[num] = (char *)malloc(strlen(token) + 1);
        strcpy(array[num], token);
        array[num][strlen(token)] = '\0';
        num += 1;
    }
    run(array, num);

    return 0;
}

//ask him about. lot of procs. 
int procs(char ** array, int num)
{
    printf("processes\n");
    
    DIR *dp;
    struct dirent *de;
    dp = opendir("/proc");
    if(dp == NULL){
        printf("No processes currently running\n");
        return 0;
    }
    while((de = readdir(dp)) != NULL) {
        char * name = de->d_name;
        int print = 1;
        if(name[0] == '.')
            print = 0;
        for(int i = 0; name[i] != '\0'; i++)
            if(isalpha(name[i]))
                print = 0;
        if(print)
            printf("Process ID:%s\n", name);
    }
    return 0;
}

int killp(char ** array, int num)
{
    int pid = atoi(array[0]);
    int killed = kill(pid, SIGKILL);
    if(killed == 0)
        printf("Succesfully killed process %d\n", pid);
    else
        fprintf(stderr, "Could not kill process %d\n", pid);
    return killed;
}



struct map dtable[] = {{"unknown", unknown} , {"help", help}, {"quit", quit}, {"run", run}, {"run_pipe", run_pipe}, {"run_to", run_to}, {"list", list}, {"procs", procs}, {"kill", killp}};


char ** buildarray(char * input, int * len)
{
    int size = 32;
    char ** array = (char **)malloc(size * sizeof(char *));
    char * token;
    char * delimiter = " ";
    int num = 0;
    token = strtok(input, delimiter);
    if(strcmp(token, "list") == 0)
    {
        char * ls25 = "ls25";
        array[num] = (char *)malloc(strlen(ls25) + 1);
        strcpy(array[num], ls25);
        array[num][strlen(ls25)] = '\0';
        num += 1;
    }
    token = strtok(NULL, delimiter);
    while(token != NULL)
    {
        array[num] = (char *)malloc(strlen(token) + 1);
        strcpy(array[num], token);
        array[num][strlen(token)] = '\0';
        num += 1;
        token = strtok(NULL, delimiter);

    }
    *len = num;
    return array;
}


int shell()
{
    int dlen = sizeof(dtable) / sizeof(dtable[0]);
    while(1)
    {
        printf("Myshell> ");
        fflush(stdout);
        char * input = NULL;
        char * key;
        int len;

        //getting input and key
        input = mygetline(mioin, &len);
        if(strstr(input, "run ") || strstr(input, "Run "))
        {
            if(strstr(input, " pipe ") || strstr(input, " Pipe "))
                key = "run_pipe";
            else if(strstr(input, " to ") || strstr(input, " To "))
                key = "run_to";
            else
                key = "run";
        }
        else if(strstr(input, " kill ") || strstr(input, " Kill "))
            key = "kill";
        else{
            for(int i = 0; input[i] != '\0'; i++)
                input[i] = tolower(input[i]);    
            key = input;
        }


        int num;
        char ** array = buildarray(input, &num);

        int i = 1;
        while(i < dlen)
        {
            if(strcmp(key, dtable[i].key) == 0) {
                dtable[i].func(array, num);
                break;
            }
            i++;
        }
        if(i == dlen)
        {
            dtable[0].func(array, num);
        }
    }
    return 0;
}



int main(int argc, char * argv[])
{
   myinit();
   printf("Welcome to MyShell by Caitlin Raymond\nCopyright Caitlin Raymond 2025\n");
   shell();
}






