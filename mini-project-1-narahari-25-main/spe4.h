#ifndef __spe4_H
#define __spe4_H
#include<dirent.h>
#include<sys/stat.h>
#include<grp.h>
#include<time.h>
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
void peek(char input[100]);
void dira(const char *cwd);
int compare_lexicographic(const void *a, const void *b);
void dirl(const char *cwd);
void dirla(char cwd[1024]);
#endif
