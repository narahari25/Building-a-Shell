#ifndef __sp6_H
#define __sp6_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
struct BackgroundProcess {
    pid_t pid;
    char command[4096];
};
void spec6(char *input,int background);
void check_completed_background_processes();
 
#endif
