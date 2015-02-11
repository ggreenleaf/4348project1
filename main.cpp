#include <unistd.h>
#include <stdio.h>
#include <string.h> //c style string library
#include <string> 
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include "memory.hpp"
#include "processor.hpp"
#include <time.h>
#define READ 0
#define WRITE 1
#define MEMSIZE 2000
#define NUMREGISTERS 6
#define FETCH 0 //processor requesting instruction be sent
#define LOAD 1
#define STORE 2


int cpuToMem [2]; //pipe for communication cpu -> memory
int memToCpu [2]; //pipe for communication memory -> cpu


int main(int argc, char *argv[]) 
{
	pid_t pid;
	std::string filename = argv[1];
	//need two pipes because they are not able to read/write from both ends
	pipe(cpuToMem); //sending from processor(parent) -> memory(child)
	pipe(memToCpu); //sending from memory(child) -> processor(parent)
	

	int readInt; //number sent from processor to memory all message sent are numbers
	srand(time(NULL));
	//Memory mem("../sample4.txt");
	Memory mem(filename);
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
		//signal sent by cpu
		int addr;
		mem.print();

		// while (addr != 50)
		// {	
		// read(cpuToMem[READ],&addr,sizeof(&addr));
		// // read(cpuToMem[READ], &addr, sizeof(&addr));
		// int pc = mem.read(addr);
		// write(memToCpu[WRITE],&pc, sizeof(pc));
		// }
	}
	
	else //parent process will represent cpu
	{

		close(cpuToMem[READ]);
		close(memToCpu[WRITE]);
		// while(cpu.get_pc() != 1000)
		// 	cpu.fetch(cpuToMem[WRITE],memToCpu[READ]);

	wait(NULL); //waits for child process to complete
	}



return 0;
}