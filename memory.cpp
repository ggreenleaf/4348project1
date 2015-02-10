#include "memory.hpp"
#include <string>
#include <fstream>
#include <iostream>

/**
*
* parses a line in  program file and returns the number
* program file must me formatted correctly with one instruction per line
**/

int parse_line(std::string line)
{
	std::string num;
	for (int i=0; i < 2; i++)
	{
		num += line[i];
	}
	return atoi(num.c_str());
}


Memory::Memory()
{
	memory.fill(0);

}
Memory::Memory(std::string filename)
{
	memory.fill(0);
	std::fstream file;
	file.open(filename);
	int loader = 0; //memory address where instruction will be stored
	int data; 
	while (!file.eof())
	{
		std::string temp;
		getline(file,temp);
		if (temp[0] == '\n') //blankline loader
			continue;
		else if (temp[0] == '.') //move loader
			continue;
		else //continue
			data = parse_line(temp);
			memory[loader++] = data; //after loading data into memory increase loader index
	}
}

Memory::~Memory()
{

}


void Memory::print()
{
	int i = 0;
	//cant use foreach loop 
	//c++11 unvailable in linux machine
	for (std::array<int,MEMSIZE>::iterator iter = memory.begin();
			iter != memory.end();
			++iter )
	{
		std::cout << "address: 0x" << std::hex << i++ 
		<< " data: " << std::dec << *iter << std::endl; 
		
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


