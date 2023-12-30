#include "headers.h"
char pre_dir[1024];
int doe=0;
void warp(char input[100])
{
char *args=input+5;
            char* token=strtok(args," ");
            if(token == NULL)
            {
                getcwd(pre_dir,sizeof(pre_dir));
                    chdir(home_dir);
            } 
            while(token != NULL)
            {   
                if(strcmp(token,"~") == 0)
                {  
                    getcwd(pre_dir,sizeof(pre_dir));
                    
                    chdir(home_dir);
                }
                else if(strcmp(token,".") == 0)
                {
                  
                    getcwd(pre_dir,sizeof(pre_dir));
                    
                }
                else if(strcmp(token,"..") == 0)
                { 
                    getcwd(pre_dir,sizeof(pre_dir));
                  
                    chdir("..");
                }
                else if(strcmp(token,"-") == 0)
                {
                    chdir(pre_dir);
                }
                else{
                     
                    getcwd(pre_dir,sizeof(pre_dir));
                    
                    if(chdir(token) != 0)
                    {
                      doe=1;
                      printf("No such file exist\n");
                    }
                }
                 
            token = strtok(NULL, " "); 
            char cwd[1024];
            getcwd(cwd,sizeof(cwd));
            if(doe == 0)
            {
            if(strcmp(cwd,home_dir) == 0)
            {
                printf("%s\n",home_dir);
            }
            else
            printf("%s\n",cwd);
            }
            doe=0;
            
            }
}