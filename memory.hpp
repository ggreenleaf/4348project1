#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>
#include <array>


#define MEMSIZE 2000

class Memory
{

public:
			// Memory();
			// ~Memory();
			Memory(std::string, int, int);
	// void	print(); //print the contents of the memory
	
	void	read_from_mem(); 
	void	write_to_mem();

private:
	int 	read_from_mem(int); //retrun val at address in memory
	void	write_to_mem(int, int);

private:
	std::array<int,MEMSIZE> memory;
	
	int writeFd, readFd; //file discriptors for read/writing to processor process

};
















#endif