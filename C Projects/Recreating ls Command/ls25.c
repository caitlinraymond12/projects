#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <langinfo.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>



struct dentry {
    char *dname; 
    mode_t mode;
    struct timespec last_modified;
    off_t size;
    char *user;
    char *group;
};



char* getUser(uid_t userID)
{
    struct passwd* user = getpwuid(userID);
    return user->pw_name;
}

char* getGroup(gid_t groupID)
{
    struct group* group = getgrgid(groupID);
    return group->gr_name;
}


struct dentry *readDirectory(const char *path, int *num) {
    

    DIR *dp;
    struct stat stats;
    struct dirent *de;
    int dcount = 0;
    struct dentry *data = NULL;
    int rcount = 0;
    dp = opendir(path);
    if (dp == NULL) { 
        return NULL;
                }
    while ((de = readdir(dp)) != NULL) dcount++;
    if(dcount == 0)
        return NULL;

    rewinddir(dp);
    data = (struct dentry *)malloc(dcount*sizeof(struct dentry));
   
    
    while ((de = readdir(dp)) != NULL) { 
        char fullpath[strlen(path) + strlen(de->d_name) + 10];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, de->d_name);

        if(lstat(fullpath, &stats) == -1)
            continue;
        data[rcount].dname = strdup(de->d_name);
        data[rcount].mode = stats.st_mode;
        data[rcount].last_modified = stats.st_mtim;
        data[rcount].size = stats.st_size;
        data[rcount].user = getUser(stats.st_uid);
        data[rcount].group = getGroup(stats.st_gid);
        rcount++;
        }

    closedir(dp);
    *num = rcount;
    return data;
}




int compare(const void *a, const void *b)
{
    return strcmp( ((struct dentry*)a)->dname, ((struct dentry*)b)->dname);
}


void print(int a, int F, struct dentry * data, int size)
{
    
    printf("%-19s ", "Name of File");
    printf("%-15s ", "File Size");
    printf("%-20s ", "User");
    printf("%-20s ", "Group");
    printf("%s\n", "Last Modified");
    
    for(int i = 0; i < size; i++)
    {
        if(data[i].dname[0] == '.' && !a)
            continue;
        
        struct tm* ts = localtime(&data[i].last_modified.tv_sec);
        char datestring[256];   
        strftime(datestring, sizeof(datestring), "%a %Y-%m-%d %H:%M:%S %Z", ts);
        char* name = data[i].dname;
        char* type = "";
 
        if(F && name[0] != '.')
        {
            mode_t mode = data[i].mode; 
            if(S_ISDIR(mode))
                type = "/";
            else if(S_ISFIFO(mode))
                type = "|";
            else if(S_ISLNK(mode))
                type = "@";
            
            else if( (mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH) )
                type = "*";
                
        }
        char nametype[strlen(name) + 2];
        snprintf(nametype, sizeof(nametype), "%s%s", name, type);

        printf("%-20s", nametype);
        printf("%-15jd ", data[i].size);
        printf("%-20s ", data[i].user);
        printf("%-20s ", data[i].group);
        printf("%s\n", datestring);

    }
}


int main(int argc, char *argv[]) {
    int size;
    struct dentry *data = NULL;
    int i;
    if (argc<2 || argc>3) {
        fprintf(stderr,"USAGE: %s [-aFs] <directory_path>\n", argv[0]);
        return -1;
    }   
    int a = 0, F = 0, s = 0;
    
 


    if(argc == 3)
    {
        char* flags = argv[1];
        if(flags[0] != '-'){
            fprintf(stderr, "USAGE: %s [-aFs] <directory_path>\n", argv[1]);
            return -1;
        }
        

        data = readDirectory(argv[2],&size);
        if(data == NULL)
        {
            fprintf(stderr, "%s", "Please Provide a Valid Path\n");
            return -1;
        }
     
        for(int j = 0; j < strlen(flags); j += 1)
        {
            if(flags[j] == 'a')
                a = 1;
            if(flags[j] == 'F')
                F = 1;
            if(flags[j] == 's')
                s = 1;
        }
    }           
    else
    {
        char* path = argv[1];
        if(path[0] == '-')
        {
            fprintf(stderr, "USAGE: %s [-aFs] <directory_path>\n", argv[1]);
            return -1;

        }
        data = readDirectory(path, &size);
        if(data == NULL)
        {
            fprintf(stderr, "%s", "Please Provide a Valid Path\n");
            return -1;
        }

    }
        
    if(s)
        qsort(data, size, sizeof(struct dentry), compare);

    print(a, F, data, size);


    for(i=0;i<size;i++) {
        free(data[i].dname);
    }
    free(data);
    return 0;
}


