#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int main(int argc, char * argv[])
{
    fprintf(stderr, "inside program3!\n");
    for(int i = 0; i < argc; i++)
        printf("arg[%d]: %s\n", i, argv[i]);
    char input[50];
    fgets(input, sizeof(input), stdin);
    printf("input: %s\n", input);
    return 0;
}


