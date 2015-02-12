#declaring variables
CC=g++
CXXFLAGS = -std=c++0x


objects = memory.o processor.o main.o
sources = memory.cpp main.cpp processor.cpp

project1.out: $(objects)
	g++ $(CXXFLAGS) -o project1.out $(objects)

memory.o: memory.hpp
processor.o: processor.hpp
main.o: memory.hpp processor.hpp 

$(objects): $(sources)
		g++ $(CXXFLAGS) -c $(sources)
clean:
	rm $(objects) project1
