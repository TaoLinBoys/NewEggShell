#NewEggShell
     Created by Harry Lum, Leon Loi, Tao Lin

##Features:
	- Shows the full path
	- Executes commands like a regular bash
	- Has basic redirecting capabilities (< >)

##Attempted:
	- >>, but for some reason, I cannot get the file name in this function

##Bugs:
	- 
	
##Files & Function Headers:
###Execute.c
	- int die(int pid)
	    takes in the pid of a process and kills it
	
	- void printPath()
	    prints out the current working directory
 
	- void commandLine(char * string, char ** commandArr)
	    takes in stdin and replaces the \n at the end with NULL, strseps it into array commandArr, and adds a NULL at the end of commandArr
	    
	- void changeDirectory(char ** commandArr)
	    if the stdin is cd, this command is executed
	    checks if there is any directory indicated in stdin, if none an error message is printed
	    processes stdin so that it can be put into chdir to change the directory
	
	- main()
	    incorporates all the above commands into a loop that askes for input from the user
