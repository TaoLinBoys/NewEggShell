#include "Execute.h"

//exit
int die(int pid){
  kill(getpid(),SIGKILL);
}

int piper(char ** commandArr){
	
}


//printPath
void printPath(){
  char path[256];
  getcwd(path, 256);
  printf("%s$ ", path);
}


//will return 0 if no piping detected
//will return 1 if > detected
//return 2 if < detected
//return 3 if | detected
int commandLine(char * string , char ** commandArr, char ** commandArr2 ){
  fgets(string,1000,stdin);
  *(strchr(string, '\n')) = 0; //replaces \n with null

  //printf("string = %s\n",string);
  int ctr = 0;
  int pipe = 0;
  char** editme = commandArr;
  while(string){
    
    char*x = strsep(&string," ");
    if (strstr(x,">>")){ 
      pipe = 4;
      editme[ctr] = 0;
      editme = commandArr2;
      ctr = 0;
    }else if (strchr(x,'<')){
      pipe = 2;
      editme[ctr] = 0;
      editme = commandArr2;
      ctr = 0;
    }else if (strchr(x,'|')){
      pipe = 3;
      editme[ctr] = 0;
      editme = commandArr2;
      ctr = 0;
    }else if (strchr(x,'>')){//had to change >> and >
      pipe = 1;
      editme[ctr] = 0;
      editme = commandArr2;
      ctr = 0;
    }else{
      editme[ctr] = x;
      ctr++;
    }
    
  }
  editme[ctr] = 0;
  
  return pipe;
}

//returns 0 if success, -1 if fail
int changeDirectory(char ** commandArr){
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
      return -1;
    }
    return 0;
    
  }else{
    printf("you broke the shell! (no directory specified)\n");
    return -1;
  }
    
     
}




int main(){
 
  printf("------------------------------MY SHELL------------------------------\n\n");

  while (1){
    printPath();
    
    char string[1000];
    char * commandArr[256];
    char * commandArr2[256];
    
    int pipe = commandLine(string,commandArr,commandArr2);
    
    printf("value of pipe: %d\n", pipe);
    /*
    //printingout the array
    int ctr = 0;
    printf("[ ");
    while(commandArr[ctr]!=NULL){
      printf("%s, ", commandArr[ctr]);
      ctr++;
    }
    printf(" ]\n");
    */

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
	
	//1 = >
	//2 = <
	//3 = |
	//4 = >>
	if (pipe == 0){
	  if (execvp(commandArr[0], commandArr) == -1){
	    printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
	  }
	}
	else if (pipe == 1){
	  umask(0);
	  printf("second value in commandArr: %s\n", commandArr[1]);
	  int f = open(commandArr2[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	  dup2(f,1);
	  close(f);
	  if (execvp(commandArr[0], commandArr) == -1){
	    printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
	  }
	}else if (pipe == 3){
	  int f;
	  dup2(f,1);
	  if (execvp(commandArr[0],commandArr) == -1){
	     printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
	  }
	  
	  int cpid = getpid();
	  fork();
	  if (cpid != getpid()){
	    printf("wtf");
	    dup2(f,0);
	    if (execvp(commandArr2[0],commandArr2) == -1){
	      printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr2[0]);
	    }
	  }
	  
	}else if (pipe == 2){
	  int f = open(commandArr2[0], O_RDONLY, 0644);
	  dup2(f,0);
	  close(f);
	  if (execvp(commandArr[0], commandArr) == -1){
	    printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
	  }
	}else if (pipe == 4){
	  int f = open(commandArr2[0], O_CREAT | O_APPEND, 0644);
	  dup2(f,1);
	  close(f);
	  if (execvp(commandArr[0], commandArr) == -1){
		  printf("riperoni pepperoni shelleroni (command not found): %s\n", commandArr[0]);
	  }
	}
	
	  

	die(getpid());
      }
      
      wait(0);
      
      
    }
  }
  
  return 0;
}





