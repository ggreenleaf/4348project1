#include "memory.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>


/**
* contructor for memory will load a program file(.txt) into memory
* @param filename the filename of the program to load into memory
* @param wfd file descriptor for writing to cpu process
* @param rfd file descriptor for reading to cpu process
**/
Memory::Memory(std::string filename, int wfd, int rfd): writeFd(wfd), readFd(rfd)
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
			int moveLoader = std::stoi(line.substr(1,line.size())); //move period convert to number stoi not in c++0x
			loader = moveLoader;
		}
		else {
			memory[loader] = std::stoi(line);
			loader++;
		}
	}
	file.close();
}

// Memory::~Memory() {}


void Memory::print()
{
	int i = 0;
	//cant use foreach loop 
	//c++11 unvailable in linux machine
	for (int data : memory) {
		std::cout << "address: "<< i++ << " data: " << data << std::endl;
	}
}

void Memory::read_from_mem()
{
	int addr;
	int data;
	//read address from cpu process
	read(readFd,&addr, sizeof(addr));
	
	data = read_from_mem(addr); //get data at addr
	//write data back to cpu process
	write(writeFd,&data,sizeof(addr));
}
/**
* get the data on a certain memory address
*@param return the data at this address
*@return the data at 
**/
int Memory::read_from_mem(int addr)
{
	return memory[addr];
}

/**
* write data to memory address
* @param address to write to
* @param data that is to be written
**/
void Memory::write_to_mem(int addr, int data)
{
	memory[addr] = data;
}
/**
* public write_to_mem will handle communication between processes
* and then call write_to_mem with the addr and data to save to memory
**/
void Memory::write_to_mem()
{
	int addr, data;
	//read address form cpu process
	read(readFd, &addr, sizeof(addr));
	//read data to write to addr
	read(readFd, &data, sizeof(data));
	
	write_to_mem(addr, data);
}


