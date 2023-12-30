#include "headers.h"
int andcount=0;
void sleept(char input[100])
{
   char* args=input+6;
   char* token=strtok(args," ");
   int id=atoi(token);
   sleep(id);
}
void removeQuotes(char *input) {
    char *src = input;
    char *dest = input;

    while (*src) {
        if (*src != '"') {
            *dest = *src;
            dest++;
        }
        src++;
    }
    *dest = '\0';
}
void echos(char input[100])
{
   char* args=input+4;
   char* token=strtok(args," ");
   removeQuotes(token);
   printf("%s\n",token);
}
char** tokenise(char input[100], int* numTokens)
{
    char** inptok = (char**)malloc(2 * sizeof(char*)); // Allocate memory for 2 pointers
    if (inptok == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    int count = 0;
    char* token;
    if(strchr(input,'&') != NULL){
      andcount=1;
    token = strtok(input, "&");
    while (token != NULL)
    {   
        inptok[count] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (inptok[count] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }

        strcpy(inptok[count], token);
        token = strtok(NULL, "&");
        count++;
        
    }
    
    }
    else if(strchr(input,';') != NULL)
    {
      token=strtok(input,";");
      while (token != NULL)
    {   
        inptok[count] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (inptok[count] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }

        strcpy(inptok[count], token);
        token = strtok(NULL, ";");
        count++;
        
    }
    
    }
    
      

    
    
    
    *numTokens = count;
    return inptok;
}