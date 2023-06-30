#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void Wait(void);

int Check_Parm(const char *Sfile, int argc, int pronum);

int Block(const char *Sfile,int pronum);

int Pro_Create(const char *Sfile,const char *Dfile,int Blockszie,int pronum);