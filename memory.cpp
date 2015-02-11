#include "memory.hpp"
#include <string>
#include <fstream>
#include <iostream>

/**
*
* parses a line in  program file and returns the number
* program file must me formatted correctly with one instruction per line
**/

Memory::Memory()
{
	memory.fill(0);

}
Memory::Memory(std::string filename)
{
	memory.fill(0);
	
	std::fstream file;
	file.open(filename); //add error checking on file
	int loader = 0; //memory address where instruction will be stored
	int data; 
	std::string::size_type n;
	std::string::size_type space_indx; 
	std::string line;	
	
	while (!file.eof()) {
		getline(file,line);
		
		if (line.size() == 0 || std::isspace(line[0])) { //ignore blank lines 
			continue;
		}

		if ((space_indx = line.find(" ") ) != std::string::npos) //found a space in the line 
			line = line.substr(0,space_indx); //get substring before space

		if ((n = line.find(".")) != std::string::npos ) { //found . move loader
			int moveLoad = atoi(line.substr(1,line.size()).c_str()); //move period convert to number stoi not in c++0x
			loader = moveLoad;
		}
		else {
			memory[loader] = atoi(line.c_str());
			loader++;
		}
	}

	file.close();
}

Memory::~Memory()
{

}


void Memory::print()
{
	int i = 0;
	//cant use foreach loop 
	//c++11 unvailable in linux machine
	for (std::array<int,MEMSIZE>::iterator iter = memory.begin(); iter != memory.end(); ++iter ) {
		std::cout << "address: "<< i++ << " data: " << *iter << std::endl;
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


