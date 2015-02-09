#include <unistd.h>
#include <stdio.h>
#include <string.h> //c style string library
#include <string> 
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include "memory.hpp"
#include "processor.hpp"

#define READ 0
#define WRITE 1
#define MEMSIZE 2000
#define NUMREGISTERS 6

int cpuToMem [2]; //pipe for communication cpu -> memory
int memToCpu [2]; //pipe for communication memory -> cpu


int main() 
{
	pid_t pid;
	
	//need two pipes because they are not able to read/write from both ends
	pipe(cpuToMem); //sending from processor(parent) -> memory(child)
	pipe(memToCpu); //sending from memory(child) -> processor(parent)
	

	int readInt; //number sent from processor to memory all message sent are numbers
	
	Memory mem;
	Processor cpu;

	pid = fork();
	if (pid < 0) //error checking fork
	{

		perror("fork error");
		exit(1);
	}
	
	else if (pid == 0) //child process will represent memory
	{	
		close(cpuToMem[WRITE]); 
		close(memToCpu[READ]);
		//sample write 			{
		// write(memToCpu[WRITE],&i, sizeof(i));	

	}
	
	else //parent process will represent cpu
	{
		close(cpuToMem[READ]);
		close(memToCpu[WRITE]);

		//constantly read from buffer
		while (true)
		{

			read(memToCpu[READ], &readInt, sizeof(readInt));
			if (readInt == 55)
				 break;	
		}

	wait(NULL); //waits for child process to complete
	}



return 0;
}