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
#include <signal.h>
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
	std::string filename = argv[1]; //program file name
	
	//need two pipes because they are not able to read/write from both ends
	pipe(cpuToMem); //sending from processor(parent) -> memory(child)
	pipe(memToCpu); //sending from memory(child) -> processor(parent)
	

	srand(time(NULL)); //set seed for random in cpu.get()
	
	Memory mem(filename, memToCpu[WRITE], cpuToMem[READ]);
	Processor cpu(cpuToMem[WRITE], memToCpu[READ]);


	pid = fork();
	if (pid < 0) { //error checking fork 
		perror("fork error");
		exit(1);
	}
	
	else if (pid == 0) { //child process will represent memory
		close(cpuToMem[WRITE]); 
		close(memToCpu[READ]);
		//signal sent by cpu
		int sig; //used for switch case to read or write
		while(true) {	
			//wait for signal from cpu
			read(cpuToMem[READ], &sig, sizeof(sig));
			switch (sig)
			{
				case 0:	mem._read();
						break;
				case 1:
						mem._write();
						break;
				default:
						break;
			}
			
		}


	}
	else { //parent process will represent cpu
		
		close(cpuToMem[READ]);
		close(memToCpu[WRITE]);
		
		while(true) {
			
			cpu.fetch();
			cpu.run();
			

			if (cpu.get_ir() == 50) {
				kill(pid, SIGKILL); 
				break;
			}
		}	

	wait(NULL); //waits for child process to complete
	}


return 0;
}
