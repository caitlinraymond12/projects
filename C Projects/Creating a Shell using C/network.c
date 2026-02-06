#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int main(int argc, char * argv[])
{
    fprintf(stdout, "inside network!\n");
    for(int i = 0; i < argc; i++)
        fprintf(stdout, "arg[%d]: %s\n", i, argv[i]);
    return 0;
}


