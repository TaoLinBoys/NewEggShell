#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  printf("------------------------------MY SHELL------------------------------\n");


  while (1){
    wait(1);

    char path[100];
    getcwd(path, 100);
    printf("%s$ ",path);

    //taking in input
    char string[256];
  
    //splitting input
    char *commandArr[100];
    char *input = string;
    int ctr = 0;

    fgets(string,sizeof(string),stdin);
    string[strlen(string)-1] = 0; //replaces \n with null
    while(input){
      commandArr[ctr] = strsep(&input," ");
      ctr++;
    }
    commandArr[ctr] = 0;

    //running it
    int ppid = getpid();
    fork();
    if(ppid != getpid()){
      if (execvp(commandArr[0], commandArr) == -1){
	printf("SHELL_CRACKERONI (command not found): %s\n", commandArr[0]);
      }
      exit(0);
    }
  
      

    
  }
  
  return 0;
}
