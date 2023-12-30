#include "headers.h"
char home_dir[1024];
void get_username(char *username) {
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    
    if (pw == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    
    strncpy(username, pw->pw_name, PROMPT_SIZE);
}

void initshell()
{
 getcwd(home_dir,sizeof(home_dir));
}
void prompt() {
    char username[PROMPT_SIZE];
    get_username(username);

    char hostname[1024];
    if (gethostname(hostname, 1024) == -1) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    if(forg == 1)
    {   
        printf("<%s@%s:~%s>",username,hostname,finalpromt);
        forg=0;
    }
    else if(strcmp(cwd,home_dir) == 0)
    {
        printf("<%s@%s:~>",username,hostname);
    }
    else if (strncmp(cwd, home_dir, strlen(home_dir)) == 0) {
        // Inside home directory
        printf("<%s@%s:~%s>", username, hostname, cwd + strlen(home_dir));
    } else {
        // Outside home directory
        printf("<%s@%s:%s>", username, hostname, cwd);
    }
}
