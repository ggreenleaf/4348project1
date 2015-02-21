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

//print cpu registers use for debugging code. 
void print_registers(Processor& cpu)
{
	cpu.print_registers();

}

int main(int argc, char *argv[]) 
{
	int interruptCount = -1;  
	int cpuToMem [2]; //pipe for communication cpu -> memory
	int memToCpu [2]; //pipe for communication memory -> cpu

	pid_t pid;
	std::string filename = argv[1]; //program file name
	if (argc == 3)	{
		interruptCount = atoi(argv[2]);
	}

	//need two pipes because they are not able to read/write from both ends
	pipe(cpuToMem); //sending from processor(parent) -> memory(child)
	pipe(memToCpu); //sending from memory(child) -> processor(parent)
	

	srand(time(NULL)); //set seed for random in cpu.get()
	
	//pass file discriptors to class so class can send and write across pipe
	Memory mem(filename, memToCpu[WRITE], cpuToMem[READ]); 
	Processor cpu(cpuToMem[WRITE], memToCpu[READ], interruptCount);

	pid = fork();
	if (pid < 0) { //error checking fork 
		perror("fork error");
		exit(1);
	}
	else if (pid == 0) { //child process will represent memory
		close(cpuToMem[WRITE]); 
		close(memToCpu[READ]);
		//signal sent by cpu
		int sig; //used for switch case to read or write and will close when processor sends signal 2
		bool keep_reading = true;
		while(keep_reading) {	
			//wait for signal from cpu
			read(cpuToMem[READ], &sig, sizeof(sig));
			switch (sig)
			{
				case 0:	
						mem._read();
						break;
				case 1:
						mem._write();
						break;
				case 2:
						keep_reading = false;
						break;
				default:
						mem.print();
						break;
			}
			
		}
	}
	else { //parent process will represent cpu
		close(cpuToMem[READ]);
		close(memToCpu[WRITE]);
		while(true) {
			
			cpu.fetch();
			// std::cout << "before exec: \n";
			// cpu.print_registers();
			cpu.run();
			// std::cout << "after exec: \n";
			// cpu.print_registers();
			
			if (cpu.get_ir() == 50) {
				break;
			}
		}
	wait(NULL); //waits for child process to complete
	}

return 0;
}
