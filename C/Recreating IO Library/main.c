
int main()
{
    MIO *file = myopen("string.txt", 0);
    char readFile[100];
    int x = myread(file, readFile, 100);
    readFile[x] = '\0';
    printf(readFile);
    printf("\n");
    myclose(file);
    
    char c;
    int x = mygetc(file, &c);
    printf("%c", c); 

    int len;
    char * first = mygets(file, &len);
    printf("%s%d", first, len);

    myclose(file);
}


