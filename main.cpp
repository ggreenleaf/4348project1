#include <unistd.h>
#include <stdio.h>
#include <string.h> //c style string library
#include <string> 
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include "memory.hpp"


#define READ 0
#define WRITE 1
#define MEMSIZE 2000
#define NUMREGISTERS 6

int cpuToMem [2]; //pipe for communication cpu -> memory
int memToCpu [2]; //pipe for communication memory -> cpu


int registers[NUMREGISTERS];


int main() 
{
	pid_t pid;
	
	//need two pipes because they are not able to read/write from both ends

	
	pipe(cpuToMem); //close[0] in child close[1] in parent 
	pipe(memToCpu); //close[1] in child close[0] in parent
	

	char readBuffer[80];
	Memory mem;

	pid = fork();
	if (pid < 0) //error checking fork
	{
		perror("fork error");
		exit(1);
	}
	
	else if (pid == 0) //child process will represent memory
	{	
		// int memory [MEMSIZE];
		// printf("in Child Process\n");
		// close(cpuToMem[WRITE]);
		// close(memToCpu[READ]);
		
		// //test send string through pipe
		// std::cin >> testString;
		// write(memToCpu[WRITE],testString.c_str(),testString.length() + 1);
		mem.print();
	}
	
	else //parent process will represent cpu
	{
		// int nbytes;
		printf("Parent Process\n");
		// close(memToCpu[WRITE]);
		// close(cpuToMem[READ]);
		
		// nbytes = read(memToCpu[READ], readBuffer, sizeof(readBuffer));
		
		// printf("Received string in pid %d: %s\n", pid, readBuffer);

		// testString = readBuffer;
		// testString += "appending\n";
	

	wait(NULL); //waits for child process to complete
	}



return 0;
}