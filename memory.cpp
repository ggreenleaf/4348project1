#include "memory.hpp"
#include <fstream>

Memory::Memory()
{
	for (int i = 0; i < MEMSIZE; i++)
	{
		memory[i] = 0; 
	}

}

Memory::~Memory()
{

}


void Memory::print()
{
	for (int i = 0; i < MEMSIZE; i++)
	{
		printf("address %i\tdata %i\n",i,memory[i]);
	}
}
/**
* get the data on a certain memory address
*@param return the data at this address
*@return the data at 
**/

int Memory::read(int address)
{
	return memory[address];
}

void Memory::write(int addresss, int data)
{

}


