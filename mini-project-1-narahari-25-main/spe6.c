#include "headers.h"
struct BackgroundProcess background_processes[100];
int num_background_processes = 0;
int forg = 0;
char finalpromt[1024];
void spec6(char *input, int background)
{
    time_t start_time = time(NULL);
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
        char *args[32];
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execvp(args[0], args);
        
        exit(EXIT_FAILURE);
    }
    else if (child_pid > 0)
    {
        // Parent process
        if (background)
        {
            struct BackgroundProcess bg_process;
            bg_process.pid = child_pid;
            strncpy(bg_process.command, input, sizeof(bg_process.command));
            bg_process.command[sizeof(bg_process.command) - 1] = '\0';
            background_processes[num_background_processes++] = bg_process;
            printf("Background process created with PID: %d\n", child_pid);
        }
        else  
        {
            int status;
            waitpid(child_pid, &status, 0);
            time_t end_time = time(NULL);

            // Calculate the elapsed time
            int elapsed_time = (int)(end_time - start_time);

            // Print the prompt again
            printf("\r");

            // Clear the line and print the prompt again
            printf("\033[K"); // Clear to end of line

            // Print the elapsed time and process name if elapsed time > 2 seconds
            if (elapsed_time > 2)
            {
                forg=1;
                char caten[1024];
                char num[20];
                 char *token = strtok(input, " ");
                sprintf(num,"%d",elapsed_time);
                strcpy(caten, token);
                strcat(caten, " : ");
                strcat(caten, num);
                strcpy(finalpromt,caten);
               // printf("Foreground process '%s' took %d seconds to run\n", input, elapsed_time);
            }
        }
    }
    else
    {
        perror("fork");
    }
}
void check_completed_background_processes()
{
    int status;
    for (int i = 0; i < num_background_processes; i++)
    {
        pid_t result = waitpid(background_processes[i].pid, &status, WNOHANG);
        if (result > 0)
        {
            printf("Background process '%s' (PID: %d) finished", background_processes[i].command, background_processes[i].pid);
            if (WIFEXITED(status))
            {
                printf(" normally with exit status %d\n", WEXITSTATUS(status));
            }
            else
            {
                printf(" abnormally\n");
            }
        }
    }
}