#include "processor.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

Processor::Processor()
{
	AC = 0, PC = 0, IR = 0 ,X = 0, Y = 0, SP = 0;
}


Processor::~Processor()
{

}

/**
* Fetches a single instruction from memory and stores in IR
*	Will fetch from memory at address PC
*	@param fd file discriptorr for sending signal
*	@param fd2 file discriptor	for reading from signal
*	after fetch PC will be incremented
**/
void Processor::fetch(int fd1, int fd2)
{	
	//send signal for memory to expect address
	write(fd1, &PC, sizeof(PC)); //send program counter to memory process
	read(fd2,&IR,sizeof(IR));
	std::cout << IR << std::endl;
	PC++;
}

int Processor::get_pc()
{
	return PC;
}

void Processor::get()
{
	AC = rand() % 100 + 1;
}