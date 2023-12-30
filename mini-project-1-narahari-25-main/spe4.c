#include "headers.h"
void dira(const char *cwd) {
    struct dirent **namelist;
    int n;

    n = scandir(cwd, &namelist, NULL, alphasort);
    if (n < 0) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        // Build the complete path to the entry
        char entry_path[1024];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", cwd, namelist[i]->d_name);

        struct stat file_stat;
        if (stat(entry_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(file_stat.st_mode)) {
            printf(ANSI_COLOR_BLUE);  // Blue for directories
        } else if (file_stat.st_mode & S_IXUSR) {
            printf(ANSI_COLOR_GREEN); // Green for executables
        } else {
            printf(ANSI_COLOR_WHITE); // White for regular files
        }

        printf("%s\n", namelist[i]->d_name);
        printf(ANSI_COLOR_RESET);
       free(namelist[i]);
    }
    
    free(namelist);
}

int compare_lexicographic(const void *a, const void *b) {
    return strcmp((*(struct dirent **)a)->d_name, (*(struct dirent **)b)->d_name);
}

void dirl(const char *cwd) {
    struct dirent **namelist;
    int n;

    n = scandir(cwd, &namelist, NULL, alphasort);
    if (n < 0) {
        return;
    }

    qsort(namelist, n, sizeof(struct dirent *), compare_lexicographic);

    for (int i = 0; i < n; ++i) {
        struct dirent *entry = namelist[i];

        // Skip hidden files and . and ..
        if (entry->d_name[0] == '.') {
            continue;
        }

        // Build the complete path to the entry
        char entry_path[1024];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", cwd, entry->d_name);

        struct stat file_stat;
        if (stat(entry_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // File type and permissions
        printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
        printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %2lu", file_stat.st_nlink); // Number of links

        // Owner and Group
        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        printf(" %s", pw ? pw->pw_name : "Unknown");
        printf(" %s", gr ? gr->gr_name : "Unknown");

        // File size
        printf(" %6lld", (long long)file_stat.st_size);

        // Last modified time
        char time_buffer[100];
        strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", localtime(&file_stat.st_mtime));
        printf(" %s", time_buffer);

        // File/directory name
        if (S_ISDIR(file_stat.st_mode)) {
            printf(ANSI_COLOR_BLUE);  // Blue for directories
        } else if (file_stat.st_mode & S_IXUSR) {
            printf(ANSI_COLOR_GREEN); // Green for executables
        } else {
            printf(ANSI_COLOR_WHITE); // White for regular files
        }

        printf(" %s\n", entry->d_name);
        printf(ANSI_COLOR_RESET);
    }

    free(namelist);
}
void dirla(char cwd[1024]) {
    struct dirent **namelist;
    int n;

    n = scandir(cwd, &namelist, NULL, alphasort);
    if (n < 0) {
        return;
    }

    qsort(namelist, n, sizeof(struct dirent *), compare_lexicographic);

    for (int i = 0; i < n; ++i) {
        struct dirent *entry = namelist[i];

        
       

        // Build the complete path to the entry
        char entry_path[1024];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", cwd, entry->d_name);

        struct stat file_stat;
        if (stat(entry_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }


        // File type and permissions
        printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
        printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

        // Number of links
        printf(" %2lu", file_stat.st_nlink);

        // Owner and Group
        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        printf(" %s", pw ? pw->pw_name : "Unknown");
        printf(" %s", gr ? gr->gr_name : "Unknown");

        // File size
        printf(" %6lld", (long long)file_stat.st_size);

        // Last modified time
        char time_buffer[100];
        strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", localtime(&file_stat.st_mtime));
        printf(" %s", time_buffer);

        // File/directory name
        if (S_ISDIR(file_stat.st_mode)) {
    printf(ANSI_COLOR_BLUE);  // Blue for directories
} else if (file_stat.st_mode & S_IXUSR) {
    printf(ANSI_COLOR_GREEN); // Green for executables
} else {
    printf(ANSI_COLOR_WHITE); // White for regular files
}

printf(" %s\n", entry->d_name);
printf(ANSI_COLOR_RESET);
        
    }

 free(namelist);
}

void peek(char input[100])
{   
    char *args = input + 5;
    char *token = strtok(args, " ");
    char token1[1024],token2[1024];
    
    char cwd[1024];
    if(token != NULL) {
        strcpy(token1,token);
        token=strtok(NULL," ");
        if(token != NULL)
        strcpy(token2,token);

       
        if ((strcmp(token1, "-a") == 0) && ((strcmp(token2, ".") == 0) || (token == NULL) )){
            
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                perror("getcwd");
                return;
            }
            dira(cwd);
            
        }
        else if((strcmp(token1,"-a") == 0) && (strcmp(token2,"..") == 0))
        { char curr[1024];
            getcwd(cwd,sizeof(cwd));
            strcpy(curr,cwd);
           chdir("..");
           getcwd(cwd,sizeof(cwd));
           dira(cwd);
           chdir(curr);

            
        }
        else if((strcmp(token1,"-a") == 0) && (strcmp(token2,"~") == 0))
        { dira(home_dir);

            
        }
        else if((strcmp(token1,"-a") == 0) && (strcmp(token2,"-") == 0))
        { dira(pre_dir);

            
        }
        else if((strcmp(token1,"-l") == 0) && ((strcmp(token2,".") == 0)|| (token == NULL) ))
        {
            getcwd(cwd,sizeof(cwd));
            dirl(cwd);
             
        }
        else if((strcmp(token1,"-l") == 0) && (strcmp(token2,"~") == 0))
        {

            dirl(home_dir);
             
        }
        else if((strcmp(token1,"-l") == 0) && (strcmp(token2,"-") == 0))
        {

            dirl(pre_dir);
             
        }
        else if((strcmp(token1,"-l") == 0) && (strcmp(token2,"..") == 0))
        {  char curr[1024];
            getcwd(cwd,sizeof(cwd));
            strcpy(curr,cwd);
            chdir("..");
           getcwd(cwd,sizeof(cwd));
           dirl(cwd);
           chdir(curr);
        }
        else if(((strcmp(token1,"-la") == 0) || (strcmp(token1,"-al") == 0)) && ((strcmp(token2,".") == 0) || (token == NULL)))
        {
           getcwd(cwd,sizeof(cwd));
           dirla(cwd);
        }
        else if(((strcmp(token1,"-la") == 0) || (strcmp(token1,"-al") == 0)) && (strcmp(token2,"~") == 0))
        {
           
           dirla(home_dir);
        }
        else if(((strcmp(token1,"-la") == 0) || (strcmp(token1,"-al") == 0)) && (strcmp(token2,"-") == 0))
        {
           
           dirla(pre_dir);
        }
        else if(((strcmp(token1,"-la") == 0) || (strcmp(token1,"-al") == 0)) && (strcmp(token2,"..") == 0))
        {
          char curr[1024];
            getcwd(cwd,sizeof(cwd));
            strcpy(curr,cwd);
            chdir("..");
           getcwd(cwd,sizeof(cwd));
           dirla(cwd);
           chdir(curr);
        }
        else if(((strcmp(token1,"-la") == 0) || (strcmp(token1,"-al") == 0)))
        {
            char absp[1024];
            if(token2[0] == '~')
            {
              strcpy(absp,home_dir);
              strcat(absp,&token2[1]);
              dirla(absp);
            }
            else{
                dirla(token2);
            }
        }
        if(token != NULL){
        token=strtok(NULL," ");

        if(((strcmp(token1,"-l") == 0) && (strcmp(token2,"-a") == 0)) || ((strcmp(token1,"-a") == 0) && (strcmp(token2,"-l") == 0))){
            if((token == NULL)||(strcmp(token,".") == 0))
            {
              getcwd(cwd,sizeof(cwd));
              dirla(cwd);
            }
            else if((strcmp(token,"..") == 0))
            {
                char curr[1024];
            getcwd(cwd,sizeof(cwd));
            strcpy(curr,cwd);
            chdir("..");
           getcwd(cwd,sizeof(cwd));
           dirla(cwd);
           chdir(curr);
            }
            else if((strcmp(token,"~") == 0))
            {
                dirla(home_dir);
            }
            else if((strcmp(token,"-") == 0))
            {
                dirla(pre_dir);
            }
            else
            {
               char absp[1024];
            if(token2[0] == '~')
            {
              strcpy(absp,home_dir);
              strcat(absp,&token2[1]);
              dirla(absp);
            }
            else{
                dirla(token2);
            } 
            }
        }
        else if((strcmp(token1,"-a") == 0)  )
        {   char absp[1024];
            if(token2[0] == '~')
            {
              strcpy(absp,home_dir);
              strcat(absp,&token2[1]);
              dira(absp);
            }
            else{
                dira(token2);
            }
        }
         else if((strcmp(token1,"-l") == 0)  )
        {   char absp[1024];
            if(token2[0] == '~')
            {
              strcpy(absp,home_dir);
              strcat(absp,&token2[1]);
              dirl(absp);
            }
            else{
                dirl(token2);
            }
        }
        }
    }
       
    }
