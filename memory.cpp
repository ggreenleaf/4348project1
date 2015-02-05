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

}

void Memory::readfile(std::string filename)
{
	std::vector<char> v;
	if (FILE *fp = fopen(filename, "r"))
	{
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			v.insert(v.end(), buf, buf + len);
		fclose(fp);
	}
} 

