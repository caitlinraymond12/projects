#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "mio.h"

void oper1()  
{
    char * in = (char *)malloc(4);
    char * out = (char *)malloc(4);  
                           
    int go = 1;
    char c;
    while(go)
    {
        memset(in, '\0', 4);
        memset(out, '\0', 4);
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
        out[0] = (in[0] | in[1]) & (in[2] | in[3]);
        out[1] = in[2];
        out[2] = in[1];
        out[3] = in[1] & in[2] & in[3];

        myputc(mioout, out[0]);
        myputc(mioout, out[1]);
        myputc(mioout, out[2]);
        myputc(mioout, out[3]);
        myflush(mioout);

        //fprintf(stdout, "%c", out[0]);
        //fprintf(stdout, "%c", out[1]);
        //fprintf(stdout, "%c", out[2]);
        //fprintf(stdout, "%c", out[3]);
    }
    free(in);
    free(out);
    fclose(stdout); 
    exit(0);        

}






int main()
{
    oper1();
    return 0;
}

