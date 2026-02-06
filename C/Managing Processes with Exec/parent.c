#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "mio.h"

void child1(int rfd, int wfd)
{
    dup2(rfd, STDIN_FILENO);
    dup2(wfd, STDOUT_FILENO);
    execl("./oper1", "oper1", NULL);
    exit(0);    
                    
}


void child2(int rfd)
{
    dup2(rfd, STDIN_FILENO);
    execl("./oper2", "oper2", NULL);
    exit(0);
}

void parent(int wfd)
{
    MIO * wfile = mydopen(wfd, 2, 4096);
    char c;
    int go = 1;
    while(go)
    {
        if((c = getchar()) == EOF)
            go = 0;
        myputc(wfile, c);
    }

    myclose(wfile);
}


int setup()
{
    fprintf(stdout, "Parent started\n");
    fflush(stdout);

    pid_t child1pid;
    pid_t child2pid;

    int p1[2];  //p[0] = read. p[1] = write
    int p2[2];
    int status;

    pipe(p1);
    pipe(p2);

    child1pid = fork();
    if(child1pid < 0)
    {
        fprintf(stderr, "Error creating child1\n");
        return -1;
    }
    else if(child1pid == 0)
    {
        //CHILD1
        close(p1[1]);
        close(p2[0]);


        child1(p1[0], p2[1]);
        close(p1[0]);
        close(p2[1]);
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
        //CHILD2
        
        close(p1[0]);
        close(p1[1]);
        close(p2[1]);

        child2(p2[0]);
        close(p2[0]);
        exit(0);
    }
    
    //PARENT

    close(p1[0]);
    close(p2[0]);
    close(p2[1]);


    fprintf(stdout, "Parent ready:");  
    fflush(stdout);
    char * input = (char *)malloc(3);
    memset(input, '\0', 3);
    scanf("%2s", input);
    


    if(strcasecmp(input, "go") != 0)
    {   
        close(p1[1]);
        return -1;
    }

    char c = getchar(); //eats new line
    if(c == '\\')
        c = getchar();

    parent(p1[1]);
    close(p1[1]);


    
    waitpid(child1pid, &status, 0);
    fprintf(stdout, "Parent after wait 1 status=%d\n", status);

    waitpid(child2pid, &status, 0);
    fprintf(stdout, "Parent after wait 2 status=%d\n", status);

    return 0;

}


int main()
{
    if(setup() == -1)
    {
        fprintf(stdout, "Parent stop\n");
        return -1;
    }
    fprintf(stdout, "Parent done\n");
    return 0;
}
