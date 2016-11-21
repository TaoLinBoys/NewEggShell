#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main(){

  //taking in input
  char string[10];
  printf("insert command: ");
  fgets(string,sizeof(string),stdin);
  string[strlen(string)-1] = 0; //replaces \n with null

  //splitting input
  char *commandArr[100];
  char *input = string;
  int ctr = 0;
  while(input){
    commandArr[ctr] = strsep(&input," ");
    ctr++;
  }
  commandArr[ctr] = 0;

  //running it
  execvp(commandArr[0], commandArr);

  return 0;
}
