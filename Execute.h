#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int die(int pid);
int piper(char ** commandArr);
void printPath();
int commandLine(char * string , char ** commandArr, char ** commandArr2 );
int changeDirectory(char ** commandArr);
