#ifndef __headers_H
#define __headers_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include "prompt.h"
#include "spe3.h"
#include "spe4.h"
#include "spe8.h"
#include "spe7.h"
#include "spe5.h"
#include "spe2.h"
#include "spe6.h"
#define PROMPT_SIZE 100
extern char home_dir[1024];
extern char pre_dir[1024];
extern int filecount;
extern int dircount;
extern int andcount;
extern int forg;
extern char finalpromt[1024];
extern int doe;
#endif
