#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>
#include <array>
#define MEMSIZE 2000

class Memory
{

public:
			Memory();
			~Memory();
			Memory(std::string, int, int);
	void	print(); //print the contents of the memory
	void	readfile (std::string); //reads program into memory from file
	int 	read(int addresss);
	void	write(int address, int data);
	

private:
	std::array<int,MEMSIZE> memory;
	int writeFd, readFd; //file discriptors for read/writing to processor 

};
















#endif