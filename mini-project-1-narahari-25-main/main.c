#include "headers.h"

int main()
{
    initshell();
    while (1)
    {
        prompt();
        char input[100];
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            exit(EXIT_FAILURE);
        }
        size_t in_len = strlen(input);
        if (in_len > 0 && input[in_len - 1] == '\n')
        {
            input[in_len - 1] = '\0';
        }
        check_completed_background_processes();
        pastevents(input);
        int numTokens = 0;
        char **tokens = tokenise(input, &numTokens);
        if (numTokens == 0)
        {    
            if (strncmp(input, "sleep", 5) == 0)
            {
                spec6(input, 0);
            }
            else if (strncmp(input, "warp", 4) == 0)
            {
                spec6(input, 0);
                warp(input);
            }
            else if (strncmp(input, "exit", 4) == 0)
            {
                exit(0);
            }
            else if (strncmp(input, "peek", 4) == 0)
            {
                spec6(input, 0);
                peek(input);
            }
            else if (strncmp(input, "seek", 4) == 0)
            {
                spec6(input, 0);
                seek(input);
            }
            else if (strncmp(input, "proclore", 8) == 0)
            {
                spec6(input, 0);
                proclore(input);
            }
            else if (strncmp(input, "pastevents", 10) == 0)
            {
                char *args = input + 10;
                char *token = strtok(args, " ");
                if (token == NULL)
                {
                    const char *filename = "past.txt"; // Replace with your filename
                    FILE *file = fopen(filename, "r");
                    if (file == NULL)
                    {
                        printf("Unable to open the file.\n");
                    }

                    char ch;

                    while ((ch = fgetc(file)) != EOF)
                    {
                        putchar(ch);
                    }

                    fclose(file);
                }
                else if (strcmp(token, "execute") == 0)
                {
                    token = strtok(NULL, " ");
                    int id = atoi(token);
                    const char *filename = "past.txt"; // Replace with your filename
                    FILE *file = fopen(filename, "r");
                    if (file == NULL)
                    {
                        printf("Unable to open the file.\n");
                        return 1;
                    }

                    int lineNumber = 1;
                    char line[100]; // Adjust buffer size as needed

                    while (fgets(line, sizeof(line), file) != NULL)
                    {
                        if (lineNumber == 16 - id)
                        {
                            trim(line);
                            if (strncmp(line, "warp", 4) == 0)
                            {
                                warp(line);
                            }
                            else if (strncmp(line, "peek", 4) == 0)
                            {
                                peek(line);
                            }
                            else if (strncmp(line, "seek", 4) == 0)
                            {
                                seek(line);
                            }
                            else if (strncmp(line, "proclore", 8) == 0)
                            {
                                proclore(line);
                            }
                        }
                        lineNumber++;
                    }

                    fclose(file);
                }
                else if (strcmp(token, "purge") == 0)
                {
                    const char *filename = "past.txt"; // Replace with your filename
                    int result = truncate(filename, 0);

                    if (result == -1)
                    {
                        printf("Error truncating the file.\n");
                        return 1;
                    }
                }
            }
        }

        else
        {

            for (int i = 0; i < numTokens; i++)
            {
                if ((andcount == 1) && (numTokens == 1 || (i < numTokens - 1)))
                {
                    spec6(input, 1);
                    continue;
                }
                strcpy(input, tokens[i]);
                trim(input);
                if (strncmp(input, "sleep", 5) == 0)
                {
                    spec6(input, 0);
                }
                else if (strncmp(input, "echo", 4) == 0)
                {
                    spec6(input, 0);
                    echos(input);
                }
                else if (strncmp(input, "warp", 4) == 0)
                {
                    spec6(input, 0);
                    warp(input);
                }
                else if (strncmp(input, "peek", 4) == 0)
                {
                    spec6(input, 0);
                    peek(input);
                }
                else if (strncmp(input, "exit", 4) == 0)
                {
                    exit(0);
                }
                else if (strncmp(input, "seek", 4) == 0)
                {
                    spec6(input, 0);
                    seek(input);
                }
                else if (strncmp(input, "proclore", 8) == 0)
                {
                    spec6(input, 0);
                    proclore(input);
                }
                else if (strncmp(input, "pastevents", 10) == 0)
                {
                    char *args = input + 10;
                    char *token = strtok(args, " ");
                    if (token == NULL)
                    {
                        char absp[1024];
                        strcpy(absp, home_dir);
                        strcat(absp, "/past.txt");
                        const char *filename = absp; // Replace with your filename
                        FILE *file = fopen(filename, "r");
                        if (file == NULL)
                        {
                            printf("Unable to open the file.\n");
                        }

                        char ch;

                        while ((ch = fgetc(file)) != EOF)
                        {
                            putchar(ch);
                        }

                        fclose(file);
                    }
                    else if (strcmp(token, "execute") == 0)
                    {
                        token = strtok(NULL, " ");
                        int id = atoi(token);
                        char absp[1024];
                        strcpy(absp, home_dir);
                        strcat(absp, "/past.txt");
                        const char *filename = absp; // Replace with your filename
                        FILE *file = fopen(filename, "r");
                        if (file == NULL)
                        {
                            printf("Unable to open the file.\n");
                            return 1;
                        }

                        int lineNumber = 1;
                        char line[100]; // Adjust buffer size as needed

                        while (fgets(line, sizeof(line), file) != NULL)
                        {
                            if (lineNumber == 16 - id)
                            {
                                trim(line);
                                if (strncmp(line, "warp", 4) == 0)
                                {
                                    warp(line);
                                }
                                else if (strncmp(line, "peek", 4) == 0)
                                {
                                    peek(line);
                                }
                                else if (strncmp(line, "seek", 4) == 0)
                                {
                                    seek(line);
                                }
                                else if (strncmp(line, "proclore", 8) == 0)
                                {
                                    proclore(line);
                                }
                            }
                            lineNumber++;
                        }

                        fclose(file);
                    }
                    else if (strcmp(token, "purge") == 0)
                    {
                        char absp[1024];
                        strcpy(absp, home_dir);
                        strcat(absp, "/past.txt");
                        const char *filename = absp; // Replace with your filename
                        int result = truncate(filename, 0);

                        if (result == -1)
                        {
                            printf("Error truncating the file.\n");
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
