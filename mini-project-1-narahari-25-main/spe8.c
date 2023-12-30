#include "headers.h"
int filecount = 0;
int dircount = 0;
int dirc = 0;
int fic = 0;
void oned(const char *path, const char *targetName, char *act_path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue; // Skip "." and ".." directories
            }

            if (strcmp(entry->d_name, targetName) == 0)
            {
                dircount++;
            }

            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            printDirectories(new_path, targetName, act_path); // Recursively check subdirectories
        }
    }

    closedir(dir);
}

void printDirectories(const char *path, const char *targetName, char *act_path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    char foundFilePath[1024];
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue; // Skip "." and ".." directories
            }

            if (strcmp(entry->d_name, targetName) == 0)
            {
                printf("\x1B[34m.%s/%s\x1B[0m\n", path + strlen(act_path), entry->d_name);
                dirc++;
                if (dircount == 1)
                {
                    snprintf(foundFilePath, sizeof(foundFilePath), "%s/%s", path, entry->d_name);
                    chdir(foundFilePath);
                }
            }

            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            printDirectories(new_path, targetName, act_path); // Recursively check subdirectories
        }
    }

    closedir(dir);
}
void printFileContents(const char *filePath)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(file);
}
void onefile(const char *path, const char *targetName, char *act_path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    char foundFilePath[1024];
    size_t targetNameLength = strlen(targetName);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        { // Check if it's a regular file
            // Extract the file name without extension
            char *lastDot = strrchr(entry->d_name, '.');
            if (lastDot != NULL)
            {
                if (strncmp(entry->d_name, targetName, targetNameLength) == 0)
                {
                    filecount = filecount + 1;
                }
            }
        }
        else if (entry->d_type == DT_DIR)
        { // Check if it's a directory
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                // Recursive call for subdirectories
                char subDirPath[1024];
                snprintf(subDirPath, sizeof(subDirPath), "%s/%s", path, entry->d_name);
                onefile(subDirPath, targetName, act_path);
            }
        }
    }

    closedir(dir);
}
void printFiles(const char *path, const char *targetName, char *act_path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

    size_t targetNameLength = strlen(targetName);

    struct dirent *entry;
    char foundFilePath[1024];
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        { // Check if it's a regular file
            // Extract the file name without extension
            char *lastDot = strrchr(entry->d_name, '.');
            if (lastDot != NULL)
            {
                if (strncmp(entry->d_name, targetName, targetNameLength) == 0)
                {
                    fic++;
                    printf("\x1B[32m.%s/%s\x1B[0m\n", path + strlen(act_path), entry->d_name);
                    if (filecount == 1)
                    {
                        snprintf(foundFilePath, sizeof(foundFilePath), "%s/%s", path, entry->d_name);
                        printFileContents(foundFilePath);
                    }
                }
            }
        }
        else if (entry->d_type == DT_DIR)
        { // Check if it's a directory
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                // Recursive call for subdirectories
                char subDirPath[1024];
                snprintf(subDirPath, sizeof(subDirPath), "%s/%s", path, entry->d_name);
                printFiles(subDirPath, targetName, act_path);
            }
        }
    }

    closedir(dir);
}

int search_in_directory(const char *dir_path, const char *target_name, const char *act_path)
{
    DIR *dir = opendir(dir_path);
    if (dir == NULL)
    {
        perror("opendir");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if the entry name contains the target name
        if (strstr(entry->d_name, target_name) != NULL)
        {
            fic++;
            if (entry->d_type == DT_DIR)
                printf("\x1B[34m.%s/%s\x1B[0m\n", dir_path + strlen(act_path), entry->d_name);
            else
                printf("\x1B[32m.%s/%s\x1B[0m\n", dir_path + strlen(act_path), entry->d_name);
        }

        // Build the complete path to the entry
        char entry_path[1024];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", dir_path, entry->d_name);

        // Use stat to determine if it's a directory
        struct stat file_stat;
        if (stat(entry_path, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }

        if (S_ISDIR(file_stat.st_mode))
        {
            // Entry is a directory, search inside it
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                search_in_directory(entry_path, target_name, act_path);
            }
        }
    }

    closedir(dir);
}
void seek(char input[100])
{
    char *args = input + 5;
    char *token = strtok(args, " ");
    char cwd[1024];
    char target[1024];
    if ((strcmp(token, "-e") == 0))
    {
        token = strtok(NULL, " ");
        if (strcmp(token, "-f") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(target, token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                getcwd(cwd, sizeof(cwd));
                filecount = 0;
                onefile(cwd, target, cwd);
                if (filecount == 1)
                {
                    printFiles(cwd, target, cwd);
                }
                else if (filecount == 0)
                {
                    printf("No file found");
                }
            }
            else
            {
                if (token[0] == '.')
                {
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, &token[1]);
                    filecount = 0;
                    onefile(cwd, target, cwd);
                    if (filecount == 1)
                    {
                        printFiles(cwd, target, cwd);
                    }
                    else if (filecount == 0)
                    {
                        printf("No file found");
                    }
                }
                else if (token[0] == '~')
                {
                    char absp[1024];
                    strcpy(absp, home_dir);
                    strcat(absp, &token[1]);
                    filecount = 0;
                    onefile(absp, target, absp);
                    if (filecount == 1)
                    {
                        printFiles(absp, target, absp);
                    }
                    else if (filecount == 0)
                    {
                        printf("No file found");
                    }
                }
                else if (token[0] == '/')
                {
                    filecount = 0;
                    onefile(token, target, token);
                    if (filecount == 1)
                    {
                        printFiles(token, target, token);
                    }
                    else if (filecount == 0)
                    {
                        printf("No file found");
                    }
                }
                else
                {
                    filecount = 0;
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, &token[0]);
                    onefile(cwd, target, cwd);
                    if (filecount == 1)
                    {
                        printFiles(cwd, target, cwd);
                    }
                    else if (filecount == 0)
                    {
                        printf("No file found");
                    }
                }
            }
        }

        else if (strcmp(token, "-d") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(target, token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                getcwd(cwd, sizeof(cwd));
                dircount = 0;
                oned(cwd, target, cwd);
                if (dircount == 1)
                {
                    printDirectories(cwd, target, cwd);
                }
                else if (dircount == 0)
                {
                    printf("No directory found");
                }
            }

            else
            {
                if (token[0] == '.')
                {
                    getcwd(cwd, sizeof(cwd));
                    dircount = 0;
                    oned(cwd, target, cwd);
                    if (dircount == 1)
                    {
                        printDirectories(cwd, target, cwd);
                    }
                    else if (dircount == 0)
                    {
                        printf("No directory found");
                    }
                }
                else if (token[0] == '~')
                {
                    char absp[1024];
                    strcpy(absp, home_dir);
                    dircount = 0;
                    oned(absp, target, absp);
                    if (dircount == 1)
                    {
                        printDirectories(absp, target, absp);
                    }
                    else if (dircount == 0)
                    {
                        printf("No directory found");
                    }
                }

                else if (token[0] == '/')
                {
                    dircount = 0;
                    oned(token, target, token);
                    if (dircount == 1)
                    {
                        printDirectories(token, target, token);
                    }
                    else if (dircount == 0)
                    {
                        printf("No match found");
                    }
                }
                else
                {
                    dircount = 0;
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, &token[0]);
                    onefile(cwd, target, cwd);
                    if (dircount == 1)
                    {
                        printDirectories(cwd, target, cwd);
                    }
                    else if (dircount == 0)
                    {
                        printf("No match found");
                    }
                }
            }
        }
    }

    else if (((strcmp(token, "-f") == 0) && (strcmp(token + 3, "-d") == 0)) || ((strcmp(token, "-d") == 0) && (strcmp(token + 3, "-f") == 0)))
    {
        printf("Invalid flags");
    }

    else if (strcmp(token, "-d") == 0)
    {
        token = strtok(NULL, " ");
        if (strcmp(token, "-e") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(target, token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                getcwd(cwd, sizeof(cwd));
                dircount = 0;
                oned(cwd, target, cwd);
                if (dircount == 1)
                {
                    printDirectories(cwd, target, cwd);
                }
                else if (dircount == 0)
                {
                    printf("No match found");
                }
            }
            else
            {
                if (token[0] == '.')
                {
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, &token[1]);
                    dircount = 0;
                    oned(cwd, target, cwd);
                    if (dircount == 1)
                    {
                        printDirectories(cwd, target, cwd);
                    }
                    else if (dircount == 0)
                    {
                        printf("No match found");
                    }
                }
                if (token[0] == '~')
                {
                    char absp[1024];
                    strcpy(absp, home_dir);
                    strcat(absp, &token[1]);
                    dircount = 0;
                    oned(absp, target, absp);
                    if (dircount == 1)
                    {
                        printDirectories(absp, target, absp);
                    }
                    else if (dircount == 0)
                    {
                        printf("No match found");
                    }
                }
                else if (token[0] == '/')
                {
                    dircount = 0;
                    oned(token, target, token);
                    if (dircount == 1)
                    {
                        printDirectories(token, target, token);
                    }
                    else if (dircount == 0)
                    {
                        printf("No match found");
                    }
                }
                else
                {
                    dircount = 0;
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, &token[0]);
                    oned(cwd, target, cwd);
                    if (dircount == 1)
                    {
                        printDirectories(cwd, target, cwd);
                    }
                    else if (dircount == 0)
                    {
                        printf("No match found");
                    }
                }
            }
        }
        else
        {
            strcpy(target, token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                dircount = 0;
                getcwd(cwd, sizeof(cwd));
                dirc = 0;
                printDirectories(cwd, target, cwd);
                if (dirc == 0)
                {
                    printf("No directory found");
                }
            }
            else
            {
                if (token[0] == '.')
                {
                    dircount = 0;
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, &token[1]);
                    dirc = 0;
                    printDirectories(cwd, target, cwd);
                    if (dirc == 0)
                    {
                        printf("No directory found");
                    }
                }
                if (token[0] == '~')
                {
                    dircount = 0;
                    char absp[1024];
                    strcpy(absp, home_dir);
                    dirc = 0;
                    printDirectories(absp, target, absp);
                    if (dirc == 0)
                    {
                        printf("No directory found");
                    }
                }
                else if (token[0] == '/')
                {
                    dircount = 0;
                    dirc = 0;
                    printDirectories(token, target, token);
                    if (dirc == 0)
                    {
                        printf("No directory found");
                    }
                }
                else
                {
                    dircount = 0;
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, &token[0]);
                    dirc = 0;
                    printDirectories(cwd, target, cwd);
                    if (dirc == 0)
                    {
                        printf("No directory found");
                    }
                }
            }
        }
    }
    else if (strcmp(token, "-f") == 0)
    {
        token = strtok(NULL, " ");
        if (strcmp(token, "-e") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(target, token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                getcwd(cwd, sizeof(cwd));
                filecount = 0;
                onefile(cwd, target, cwd);
                if (filecount == 1)
                {
                    printFiles(cwd, target, cwd);
                }
                else if (filecount == 0)
                {
                    printf("No match found");
                }
            }
            else
            {
                if (token[0] == '.')
                {
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, &token[1]);
                    filecount = 0;
                    onefile(cwd, target, cwd);
                    if (filecount == 1)
                    {
                        printFiles(cwd, target, cwd);
                    }
                    else if (filecount == 0)
                    {
                        printf("No match found");
                    }
                }
                if (token[0] == '~')
                {
                    char absp[1024];
                    strcpy(absp, home_dir);
                    strcat(absp, &token[1]);
                    filecount = 0;
                    onefile(absp, target, absp);
                    if (filecount == 1)
                    {
                        printFiles(absp, target, absp);
                    }
                    else if (filecount == 0)
                    {
                        printf("No match found");
                    }
                }
                else if (token[0] == '/')
                {
                    filecount = 0;
                    onefile(token, target, token);
                    if (filecount == 1)
                    {
                        printFiles(token, target, token);
                    }
                    else if (filecount == 0)
                    {
                        printf("No match found");
                    }
                }
                else
                {
                    filecount = 0;
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, &token[0]);
                    onefile(cwd, target, cwd);
                    if (filecount == 1)
                    {
                        printFiles(cwd, target, cwd);
                    }
                    else if (filecount == 0)
                    {
                        printf("No match found");
                    }
                }
            }
        }
        else
        {
            strcpy(target, token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                filecount = 0;
                getcwd(cwd, sizeof(cwd));
                fic = 0;
                printFiles(cwd, target, cwd);
                if (fic == 0)
                {
                    printf("No file found");
                }
            }
            else
            {
                if (token[0] == '.')
                {
                    filecount = 0;
                    getcwd(cwd, sizeof(cwd));
                    fic = 0;
                    printFiles(cwd, target, cwd);

                    if (fic == 0)
                    {
                        printf("No file found");
                    }
                }
                if (token[1] == '~')
                {
                    filecount = 0;
                    char absp[1024];
                    strcpy(absp, home_dir);
                    strcat(absp, &token[1]);
                    fic = 0;
                    printFiles(absp, target, absp);
                    if (fic == 0)
                    {
                        printf("No file found");
                    }
                }
                else if (token[0] == '/')
                {
                    filecount = 0;
                    fic = 0;
                    printFiles(token, target, token);
                    if (fic == 0)
                    {
                        printf("No file found");
                    }
                }
                else
                {
                    filecount = 0;
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, &token[0]);
                    fic = 0;
                    printFiles(cwd, target, cwd);
                    if (fic == 0)
                    {
                        printf("No file found");
                    }
                }
            }
        }
    }
    else
    {

        strcpy(target, token);
        token = strtok(NULL, " ");
        if (token == NULL)
        {
            getcwd(cwd, sizeof(cwd));
            fic = 0;
            int res = search_in_directory(cwd, target, cwd);
            if (fic == 0)
            {
                printf("No file/directory found");
            }
        }
        else if (token != NULL)
        {
            if (token[0] == '.')
            {
                getcwd(cwd, sizeof(cwd));
                strcat(cwd, &token[1]);
                fic = 0;
                int res = search_in_directory(cwd, target, cwd);
                if (fic == 0)
                {
                    printf("No file/directory found");
                }
            }
            else if (token[0] == '~')
            {
                char absp[1024];
                strcpy(absp, home_dir);
                strcat(absp, &token[1]);
                fic = 0;
                int res = search_in_directory(absp, target, absp);
                if (fic == 0)
                {
                    printf("No file/directory found");
                }
            }
        }
    }
}
