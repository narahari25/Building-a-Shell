#ifndef __spe8_H
#define __spe8_H
#include<dirent.h>
#include <sys/stat.h>
void seek(char input[100]);
void printDirectories(const char *path, const char *targetName,char *act_path);
void printFileContents(const char *filePath) ;
void onefile(const char *path, const char *targetName, char *act_path);
void printFiles(const char *path, const char *targetName, char *act_path);
int search_in_directory(const char *dir_path, const char *target_name,const char *act_path) ;
#endif
