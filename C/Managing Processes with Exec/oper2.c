#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>



void oper2()
{   
    unsigned int final = 0;
    char in[4];
    int c;
    int go = 1;
    unsigned int res = 0;
    unsigned int mod = (unsigned int)pow(2.0, 32.0);

    while(go)
    {
        int i = 0;
        for(i = 0; i < 4; i++)
        {
            if((c = getchar()) == EOF)
                break;
            in[i] = c;
        }
        while(i < 4)
        {
            in[i] = 'z';
            i += 1;
            go = 0;
        }


        res = 0;
        res = res | (in[1] << 24);
        res = res | (in[3] << 16);
        res = res | (in[2] << 8);
        res = res | in[0];
        final += res;
        if(go)
            fprintf(stdout, "result=%u\n", final);   
    }
    fclose(stdin);
    final %= mod;
    fprintf(stdout, "final result=%u\n", final);
    exit(0);
}


int main()     
{
    oper2();
    return 0;
}



