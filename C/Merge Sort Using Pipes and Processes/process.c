#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "mio.h"


#define ARRAYSIZE 256;

int compare(const void *a, const void *b)
{
   const char *str1 = *(char **)a;
   const char *str2 = *(char **)b;
   return strcmp(str1, str2);
}

void child1(int rfd, int wfd)
{
    MIO *rfile = mydopen(rfd, 0, 4096);
    MIO *wfile = mydopen(wfd, 2, 4096);
    MIO *child1out = myopen("child1.txt", 2, 4096);
    char *str = NULL;
    int size = ARRAYSIZE;
    int i = 0;
    char **array = (char **)malloc(size * sizeof(char *));
    do {
        int len;
        str = mygets(rfile, &len);
        if(str == NULL)
            break;
       // fprintf(stderr, "child1: got <%s> with length %d \n", str, len);
        array[i] = (char *)malloc(strlen(str) + 2);
        strcpy(array[i], str);
        array[i][strlen(str)] = '\n';
        array[i][strlen(str) + 1] = '\0';
        i += 1;
        if(i == size)
        {
            size *= 2;
            char ** tempArray =(char **)realloc(array, size * sizeof(char *));
            array = tempArray;
        }

    } while(1);
    array = (char **)realloc(array, size * sizeof(char *));
    myclose(rfile);
    qsort(array, i, sizeof(char *), compare);
    for(int j = 0; j < i; j+=1)
    {
        mywrite(child1out, array[j], strlen(array[j]));
        mywrite(wfile, array[j], strlen(array[j]));
        free(array[j]);
    }
    myclose(wfile);
    myclose(child1out);
    free(array);
    exit(0);       
}


void child2(int rfd, int wfd)
{
    MIO *rfile = mydopen(rfd, 0, 4096);
    MIO *wfile = mydopen(wfd, 2, 4096);
    MIO *child2out = myopen("child2.txt", 2, 4096);
    char * str = NULL;
    int size = ARRAYSIZE;
    int i = 0;
    char ** array = (char **)malloc(size * sizeof(char *));
    do {
        int len;
        str = mygets(rfile, &len);
        if(str == NULL)
            break;
        //fprintf(stderr, "child2: got <%s>\n", str);
        array[i] = (char *)malloc(strlen(str) + 2);
        strcpy(array[i], str);
        array[i][strlen(str)] = '\n';
        array[i][strlen(str) + 1] = '\0';
        i += 1;
        if(i == size)
        {
            size *= 2;
            char ** tempArray = (char **)realloc(array, size * sizeof(char *));
            array = tempArray;
        }

    } while(1);
    array = (char **)realloc(array, size * sizeof(char *));
    myclose(rfile); 
    qsort(array, i, sizeof(char *), compare);
    for(int j = 0; j < i; j+=1)
    {   
        mywrite(child2out, array[j], strlen(array[j]));
        mywrite(wfile, array[j], strlen(array[j]));
        free(array[j]);
    }
    myclose(wfile);
    myclose(child2out);
    free(array);
    exit(0);        
}

void child3(int r3fd, int r4fd)
{
    MIO *r3file = mydopen(r3fd, 0, 4096);
    MIO *r4file = mydopen(r4fd, 0, 4096);
    MIO *output = myopen("child3.txt", 2, 4096);
    char * str = NULL;
    int size = ARRAYSIZE;
    int i = 0;
    char ** array = (char **)malloc(size * sizeof(char *));
    
    //read everything from pipe 3
    do{
        int len;
        str = mygets(r3file, &len);
        if(str == NULL)
            break;
        array[i] = (char *)malloc(strlen(str) + 2);
        strcpy(array[i], str);
        array[i][strlen(str)] = '\n';
        array[i][strlen(str) + 1] = '\0';
        i += 1;
        if(i == size)
        {
            size *= 2;
            char ** tempArray = (char **)realloc(array, size * sizeof(char *));
            array = tempArray;
        }
    } while(1);

    //read everything from pipe 4
    do{
        int len;
        str = mygets(r4file, &len);
        if(str == NULL)
            break;
        array[i] = (char *)malloc(strlen(str) + 2);
        strcpy(array[i], str);
        array[i][strlen(str)] = '\n';
        array[i][strlen(str) + 1] = '\0';
        i += 1;
        if(i == size)
        {
            size *= 2;
            char ** tempArray = (char **)realloc(array, size * sizeof(char *));
            array = tempArray;
        }
    
    }while(1);
    myclose(r3file);
    myclose(r4file);

    qsort(array, i, sizeof(char *), compare);
    for(int j = 0; j < i; j +=1)
    {
        mywrite(output, array[j], strlen(array[j]));
        free(array[j]);
    }
    myclose(output);
    free(array);
    exit(0);
}




void parent(int wfd1, int wfd2, char * filename)
{
     
     MIO *wfile1 = mydopen(wfd1, 2, 4096);
     MIO *wfile2 = mydopen(wfd2, 2, 4096);

     int write1 = 1;
     MIO *word_list = myopen(filename, 0, 4096);
    char * str = NULL;
        do {
            int len;
            str = mygets(word_list, &len); 
            if(str == NULL) 
                break;             
            if(write1)
            {
                //fprintf(stderr, "parent got: %s\n", str);
                char * str_write = (char *)malloc(strlen(str) + 2);
                strcpy(str_write, str);
                str_write[strlen(str)] = '\n';
                str_write[strlen(str) + 1] = '\0';
                mywrite(wfile1, str_write, strlen(str_write));   
                write1 = 0;
            }
            else
            {
                char * str_write = (char *)malloc(strlen(str) + 2);
                strcpy(str_write, str);
                str_write[strlen(str)] = '\n';
                str_write[strlen(str) + 1] = '\0';
                mywrite(wfile2, str_write, strlen(str_write));
                write1 = 1;
            }
        } while(1);
    myclose(wfile1);  
    myclose(wfile2);

}

int setup(char * filename)      //is this whole function supposed to be the parent?
{
    fprintf(stdout, "Parent started\n");
    fflush(stdout);

    pid_t child1pid;
    pid_t child2pid;
    pid_t child3pid;
    int status;     // do i need multiple statuses
    int p1[2];
    int p2[2];
    int p3[2];
    int p4[2];  //p[0] is read p[1] is write

    pipe(p1);
    pipe(p2);
    pipe(p3);
    pipe(p4);


    child1pid = fork();
    if(child1pid < 0){
        fprintf(stderr, "fork1 failed\n");
        return -1;
    }
    else if(child1pid == 0)
    {
        //CHILD 1
        close(p1[1]);
        close(p2[0]);
        close(p2[0]);
        close(p3[0]);
        close(p4[0]);
        close(p4[1]);

        child1(p1[0], p3[1]);
        close(p1[0]);
        close(p3[1]);
        exit(0);
    }

    child2pid = fork();
    if(child2pid < 0){
        fprintf(stderr, "fork2 failed\n");
        return -1;
    }
    else if(child2pid == 0)
    {
        //CHILD 2
        close(p1[0]);
        close(p1[1]);
        close(p2[1]);
        close(p3[0]);
        close(p3[1]);
        close(p4[0]);


        child2(p2[0], p4[1]);
        close(p2[0]);
        close(p4[1]);
        exit(0);    //for safety incase it didn't exit
    }




    child3pid = fork();
    if(child3pid < 0){
        fprintf(stderr, "fork2 failed\n");
        return -1;
    }
    else if(child3pid == 0)
    {
        //CHILD 3
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        close(p3[1]);
        close(p4[1]);

        child3(p3[0], p4[0]);
        close(p3[0]);
        close(p4[0]);
        exit(0);
    }

    //PARENT


    close(p1[0]);
    close(p2[0]);
    close(p3[1]);
    close(p4[1]);
    close(p3[0]);
    close(p4[0]);


    
    fprintf(stdout, "Parent ready:");  //fprintf or printf
    fflush(stdout);
    char * input = (char *)malloc(21);
    memset(input, '\0', 21);
    scanf("%s", input);
    
    if(strcasecmp(input, "go") != 0)
        return -1;
    fprintf(stderr, "here\n");

    parent(p1[1], p2[1], filename);
    close(p1[1]);
    close(p2[1]);

    waitpid(child1pid, &status, 0);
    fprintf(stdout, "Parent after wait 1 status=%d\n", status);


    waitpid(child2pid, &status, 0);
    fprintf(stdout, "Parent after wait 2 status=%d\n", status);


    waitpid(child3pid, &status, 0);
    fprintf(stdout, "Parent after wait 3 status=%d\n", status);


    return 0;
}


//MAKE SURE OT CLOSE ALL FILES WHEN DONE IN EACH FUNCTION
int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage:./hw3 <filename>\n");
        return -1;
    }
    char * filename = argv[1];

    FILE * test = fopen(filename, "r");
    if(test == NULL)
    {   
        fprintf(stderr, "ERROR:%s does not exist or is not readable\n", filename);
        return 0;
    }
    fclose(test);


    if(setup(filename) == -1)
    {
        printf("Parent stop\n");
        return -1;
    }
    printf("Parent done\n");
    return 0;
}




