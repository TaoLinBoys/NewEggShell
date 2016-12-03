#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int die(int pid){
  kill(getpid(),SIGKILL);
}

void printPath(){
  char path[256];
  getcwd(path, 256);
  printf("%s$ ", path);
}

void  commandLine(char * string , char ** commandArr ){
  fgets(string,1000,stdin);
  *(strchr(string, '\n')) = 0; //replaces \n with null

  //printf("string = %s\n",string);
  int ctr = 0;
  while(string){
    commandArr[ctr] = strsep(&string," ");
    printf("%s, ",commandArr[ctr]);
    ctr++;
  }
  
  commandArr[ctr] = 0;
  
}

void changeDirectory(char ** commandArr){
  //commandArr = ["cd", "directory",null]
  if (*(++commandArr) != NULL){//check if directory is specified
    char path[256];
    
    if (**commandArr != '/'){ //if commandArr does not start with /
      getcwd(path,256); //copy path
      //printf("path = %s\n",path);
      strcat(path,"/"); //turn path into path/
      //printf("path + / = %s\n",path);
      strcat(path,*commandArr); // turn path/ into path/commandArr
      //printf("path + / + commandArr = %s\n",path);
    }else{
      strcat(path,*commandArr);
    }
    if (chdir(path)){
      printf("you broke the shell! (directory doesnt exist)\n");
    }
    
  }else{
    printf("you broke the shell! (no directory specified)\n");
  }
    
     
}

int piping(char** commandArr){
  //printf("piping\n");
  while (*commandArr){
    //printf("%s\n", *commandArr);
    if (strcmp(*commandArr,">") == 0){
      printf("aw shit");
    }
    
    commandArr++;
  }
}


int main(){
 
  printf("------------------------------MY SHELL------------------------------\n\n");

  while (1){
    printPath();
    
    char string[1000];
    char * commandArr[256]; 
    commandLine(string,commandArr);

    //running it
    int ppid = getpid();
    
    if (strcmp(*commandArr,"cd") == 0){
      changeDirectory(commandArr);
    }
    else if (strcmp(*commandArr,"exit") == 0){
      die(getpid());
    }
    else{
      fork();
      if(ppid != getpid()){
	//0 = >
	//1 = <
	//2 = |
	if (piping(commandArr) == 0){
	
	  umask(0);
	  int f = open("stdout.txt",O_CREAT | O_WRONLY | O_TRUNC, 0644);
	  dup2(f,1);
	  close(f);
	}
	if (piping(commandArr) == 1){
	}
	if (piping(commandArr) == 2){
	}
	  
	if (execvp(commandArr[0], commandArr) == -1){
	  printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
	}
	die(getpid());
      }
      


      
      
    }
  }
  
  return 0;
}





