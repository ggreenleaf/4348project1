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
	//underscores for easier dif from read/write unix functions
	void	_read(); 
	void	_write();

private:
	int 	_read(int); //retrun val at address in memory
	void	_write(int, int);

private:
	std::array<int,MEMSIZE> memory;
	
	int writeFd, readFd; //file discriptors for read/writing to processor 

};
















#endif