#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int main(int argc, char * argv[])
{
    fprintf(stderr, "inside program1!\n");
    for(int i = 0; i < argc; i++)
        fprintf(stderr, "arg[%d]: %s\n", i, argv[i]);
    printf("hello world!\n");
    return 0;
}


