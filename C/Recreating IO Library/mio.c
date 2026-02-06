#include "mio.h"


MIO *mioin;
MIO *mioout;
MIO *mioerr;

MIO *myopen(const char *name, const int mode, const int bsize)
{
    int fd;
    if(mode == MODE_R)
        fd = open(name, O_RDONLY);
    
    else if(mode == MODE_WA)
         fd = open(name, O_WRONLY | O_CREAT | O_APPEND);
    
    else if(mode == MODE_WT)
        fd = open(name, O_WRONLY |  O_CREAT | O_TRUNC);

    else{
        fprintf(stderr, "Error: Mode Not Recognized");
        return NULL;
    }
    if(fd == -1)
    {
        fprintf(stderr, "Error: Could not open file\n");
        return NULL;
    }
    return mydopen(fd, mode, bsize);
    
}


MIO *mydopen(const int fd, const int mode, const int bsize)
{
    if(bsize < 0)
    {
        fprintf(stderr, "Error: Buffer Size Less Than Zero\n");
        return NULL;
    }
    MIO *file = (MIO *)malloc(sizeof(MIO));
    file->fd = fd;
    file->rw = mode;
    if(bsize > 0)
    {
        char* rb = (char *)malloc(bsize);
        memset(rb, 0, bsize);
        char* wb = (char *)malloc(bsize);
        memset(wb, 0, bsize);
        file->rb = rb;
        file->wb = wb;
    }
    else
    {
        file->rb = NULL;
        file->wb = NULL;
    }
    file->rs = 0;
    file->re = 0;
    file->ws = 0;
    file->we = 0;
    file->bufferSize = bsize;
    return file;

}


int myclose(MIO *m)
{
    if(m == NULL)
        return -1;
    if(M_ISMW(m->rw))
        myflush(m);
    free(m->rb);
    free(m->wb);
    int x = close(m->fd);
    free(m);
    return x;
}

int myflush(MIO *m)
{
    if(m == NULL)
        return -1;
    int x = write(m->fd, m->wb, m->we - m->ws);
    if(x < 0)
    {
        fprintf(stderr, "Error: Flushing File");
        return -1;
    }

    memset(m->wb, 0, MBSIZE);
    return x;
}

//Reading


int myread(MIO * m, char * b, const int size)
{
    if(m == NULL || b == NULL)
        return -1;
    if(m->bufferSize == 0)
    {
        int x = read(m->fd, b, size);
        if(x < 0)
        {
            fprintf(stderr, "Error: Reading From Unbuffered File.\n");
            return -1;
        }
        return x;
    }

    int bytesRead = 0;
    while(bytesRead < size)
    {
        if(m->rs == m->re)
        {
            int x = read(m->fd, m->rb, m->bufferSize);
            if(x < 0)
            {
                fprintf(stderr, "Error: Reading From file.\n");
                return -1;
            }
            if(x == 0)
                return bytesRead;
            m->re = x;
            m->rs = 0;
        }
        int toRead = m->re - m->rs;
        if(size - bytesRead < toRead)
            toRead = size - bytesRead;

        memcpy(b + bytesRead, m->rb + m->rs, toRead);
        m->rs += toRead;
        bytesRead += toRead;

    }
    return bytesRead;
}


int mygetc(MIO *m, char *c){
    if(m == NULL || c == NULL)
        return -1;
    int x = myread(m, c, 1);
    if(x < 0)
    {
        fprintf(stderr, "Error: Reading Character");
        return -1;
    }
    return x;
}


char *mygets(MIO *m, int *len)
{
    if (m == NULL || len == NULL)
    {
        return NULL;
    }

    int size = MBSIZE;
    char *s = (char *)malloc(size);
    if (s == NULL)
        return NULL;

    int i = 0;
    char c;


    if (mygetc(m, &c) != 1)
    {
        free(s);
        return NULL;
    }


    while (M_ISWS(c))
    {
        if (mygetc(m, &c) != 1)
        {
            free(s);
            return NULL;
        }
    }


    while (!M_ISWS(c))
    {
        if (i >= size - 1)
        {
            size *= 2;
            char *tmp = (char *)realloc(s, size);
            if (!tmp)
            {
                free(s);
                return NULL;
            }
            s = tmp;
        }

        s[i] = c;
        i+=1;

        if (mygetc(m, &c) != 1)
        {

            break;
        }
    }

    s[i] = '\0';
    *len = i;
    s = (char *)realloc(s, i + 1);
    return s;
}



char *mygetline(MIO *m, int *len)
{
    if (m == NULL || len == NULL)
    {
        return NULL;
    }

    int size = MBSIZE;
    char *line = (char *)malloc(size);
    if (line == NULL)
        return NULL;

    int i = 0;
    char c;

    if (mygetc(m, &c) != 1)
    {
        free(line);
        return NULL;
    }

    while(c == '\n')
    {
        if(mygetc(m, &c) != 1)
        {
            free(line);
            return NULL;
        }
    }



    while (c != '\n')
    {
        if (i >= size - 1)
        {
            size *= 2;
            char *tmp = (char *)realloc(line, size);
            if (!tmp)
            {
                free(line);
                return NULL;
            }
            line = tmp;
        }

        line[i] = c;
        i+=1;

        if (mygetc(m, &c) != 1)
        {
            break;
        }
    }
    if(i > 0 && line[i-1] == '\r')
    {
        i-= 1;
    }

    line[i] = '\0';
    *len = i;
    line = (char *)realloc(line, i + 1);
    return line;
}





//Writing


int mywrite(MIO * m, const char * b, const int size)
{
    if(m == NULL || b == NULL)
        return -1;

    if(m->bufferSize == 0)
    {
        int x = write(m->fd, b, size);
        if(x < 0){
            fprintf(stderr, "Error: Could Not Write to Unbuffered File\n");
            return -1;
        }
        return x;
    }


    int bytesWritten = 0;
    while(bytesWritten < size)
    {
        int toWrite = m->bufferSize - m->we;
        if(size - bytesWritten < toWrite)
            toWrite = size - bytesWritten;
        memcpy(m->wb + m->we, b + bytesWritten, toWrite);
        m->we += toWrite;
        bytesWritten += toWrite;
        if(m->we == m->bufferSize)
        {
            int x = write(m->fd, m->wb, m->bufferSize);
            if(x < 0){
                fprintf(stderr, "Error: Could Not Write\n");
                return -1;
            }
            m->we = 0;
        }
    }
    return bytesWritten;
 }

int myputc(MIO * m, const char c)
{
    if(m == NULL)
        return -1;
    int x = mywrite(m, &c, 1);
    if(x == 0){
        fprintf(stderr, "Error: Writing Character");
        return -1;
    }
    return x;


}

int myputs(MIO * m, const char *str, const int len)
{
    if(m == NULL || str == NULL)
        return -1;
    int i;
    for(i = 0; i < len; i++)
    {
        int x = myputc(m, str[i]);
        if(x < 0)
        {
            if(i > 0)
                return i;
            return -1;
        }
    }
    return i;

}


void myinit()
{
    mioin = mydopen(STDIN_FILENO, MODE_R, MBSIZE);
    mioout = mydopen(STDOUT_FILENO, MODE_WA, 0);
    mioerr = mydopen(STDERR_FILENO, MODE_WA, 0);
}




int main()
{
    MIO *file = myopen("string.txt", 0, MBSIZE);
    char readFile[100];
    int length;
    char * line = mygetline(file, &length);
    printf("%s%d", line, length);
}


    /*
    int x = myread(file, readFile, 100);
    readFile[x] = '\0';
    printf(readFile);
    printf("\n");
    myclose(file);
}
    /*
    char c;
    int x = mygetc(file, &c);
    printf("%c", c); */
/*
    int len;
    char * first = mygets(file, &len);
    printf("%s%d", first, len);

    //char * test = "    chloe";
   // char * test1 = "chloe";

   // MIO *writeFile = myopen("write.txt", 2);
   // MIO *writeFile1 = myopen("write1.txt", 2);
   // int y = myputs(writeFile, test, 5);
   // int x = myputs(writeFile1, test1, 5);

   // myclose(writeFile1);
    //myclose(writeFile);
    myclose(file);
}

/*
    MIO *writeFile = myopen("write.txt", 2);
    char * test = "chloe";
    char a = 'a';
    char b = 'b';
    char c = 'c';
    int x = myputs(writeFile, test, 5); //only writes the one word if i do the num of characters, not the size, and dont add the '/0' to the end
    myclose(writeFile);
    printf("%d", x);*/

