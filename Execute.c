#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


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

void changeDirectory(char ** commandArr){
  if (*(++commandArr) != NULL){//check if directory is specified 
    char path[256];
    if (!(**commandArr == '/')){ //if commandArr does not start with /
      getcwd(path,256); //copy path
      strcat(path,"/"); //turn path into path/
      strcat(path,*commandArr); // turn path/ into path/commandArr
    }else{
      strcat(path,*commandArr);
    }
    if (chdir(path)){
      printf("you broke the shell! (directory doesnt exist)\n");
    }
  }else{
    printf("you broke the shell! (no directory specified)\n");
  }
    
  //chdir(path);
}
int main(){
 
  printf("------------------------------MY SHELL------------------------------\n\n");

  while (1){
    printPath();
    
    char string[256];
    char * commandArr[100];
    commandLine(string,commandArr);

    //running it
    int ppid = getpid();
    
    if (strcmp(*commandArr,"cd") == 0){
      changeDirectory(commandArr);
    }
    else{
      fork();
      if(ppid != getpid()){
	if (execvp(commandArr[0], commandArr) == -1){
	  printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
	}
	exit(0);
      }
      wait(NULL);
    }
    }
  
  return 0;
}





