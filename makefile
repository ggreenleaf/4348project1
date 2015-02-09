#declaring variables
CC=g++
CFLAGS = -I

objects = memory.o processor.o main.o
sources = memory.cpp main.cpp processor.cpp

project1: $(objects)
	g++ -o project1 $(objects)

memory.o: memory.hpp
processor.o: processor.hpp
main.o: memory.hpp processor.hpp 

$(objects): $(sources)
		g++ -c $(sources)
clean:
	rm $(objects) project1
