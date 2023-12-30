#include "headers.h"

int checkMatchingInput(const char *input) {
    char absp[1024];
     strcpy(absp,home_dir);
     strcat(absp,"/past.txt");
    FILE *file = fopen(absp, "r");
    if (file == NULL) {
        perror("Opening file");
        return 0; 
    }

    char lines[15][1024];
    int lineCount = 0;

    while (lineCount < 15 && fgets(lines[lineCount], sizeof(lines[lineCount]), file)) {
        lines[lineCount][strcspn(lines[lineCount], "\n")] = '\0'; 
        if (strcmp(input, lines[lineCount]) == 0) {
            fclose(file);
            return 1; 
        }
        lineCount++;
    }

    fclose(file);
    return 0; 
}

void pastevents(char input[100])
{  char absp[1024];
   if(strncmp(input,"pastevents",10) == 0)
   {
    return ;
   }
   if(strcmp(input,"") == 0)
   {
    return;
   }

     strcpy(absp,home_dir);
     strcat(absp,"/past.txt");
    FILE *file = fopen(absp, "a+");
    int linecount=0;
    char ch;
   if (checkMatchingInput(input) == 0)
   { while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            linecount++;
        }
    }
    fputs(input, file);
    fputs("\n", file);
    linecount++;
    if(linecount == 16)
    {
     fclose(file);
                char sbsp[1024];
                strcpy(sbsp,home_dir);
                strcat(sbsp,"/temp.txt");
                // Reopen the file in read and write mode
                FILE *tempFile = fopen(sbsp, "w");
                if (tempFile == NULL) {
                    printf("Unable to create temporary file.\n");
                    
                }

                // Copy lines from original file to tempFile, starting from the second line
                file = fopen(absp, "r");
                char line[256];
                fgets(line, sizeof(line), file); // Skip the first line
                while (fgets(line, sizeof(line), file) != NULL) {
                    fputs(line, tempFile);
                }
                
                // Close both files
                fclose(file);
                fclose(tempFile);

                // Replace the original file with the tempFile
                remove(absp);
                rename(sbsp, absp);

                linecount--;  
    }
    else
    {
        fclose(file);
    }
            
   }
    
}

void trim(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
    int start = 0;
    while (isspace(str[start])) {
        start++;
    }
    if (start > 0) {
        memmove(str, str + start, len - start + 1);
    }
}