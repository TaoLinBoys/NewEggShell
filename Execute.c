#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void printPath(){
  char path[256];
  getcwd(path, 256);
  printf("%s$ ", path);
}

void  commandLine(char * string , char ** commandArr ){
  
  char * input = string;
  int ctr = 0;
  fgets(string,sizeof(string),stdin);
  *(strchr(string, '\n')) = 0; //replaces \n with null
  while(input){
    commandArr[ctr] = strsep(&input," ");
    ctr++;
  }
  commandArr[ctr] = 0;
}


int main(){
 
  printf("------------------------------MY SHELL------------------------------\n\n");

  while (1){
    wait(1);
 
    printPath();
    
    char string[256];
    char * commandArr[100];
    commandLine(string,commandArr);

    //running it
    int ppid = getpid();
    fork();
    if(ppid != getpid()){
      if (execvp(commandArr[0], commandArr) == -1){
	printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
      }
      exit(0);
    }
  }
  return 0;
}




