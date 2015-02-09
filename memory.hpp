#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>

#define MEMSIZE 2000

class Memory
{

public:
			Memory();
			~Memory();
	void	print(); //print the contents of the memory
	void	readfile (std::string); //reads program into memory from file
	


private:
	int memory [MEMSIZE];

};
















#endif