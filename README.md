Processor Memory Project 1 README

github repo


Files
	processor.cpp
	processor.hpp
	memory.hpp
	memory.cpp
	program.txt
	main.cpp
	makefile

Processor files
	The processor cpp and hpp files contain all the code for the processor class which will represent the CPU in the program

Memory files
	The memory cpp and hpp files contain all the code for the memory class which will represent the memory in the program.

main and makefile
	the main.cpp file will be the entry point of the program where forking into two processes takes place. Communication between processes is handled in each class

	The makefile compiles the program. To compile and run the program type
	run these commands in the linux terminal
	compile
		make
	running program
		./project1	<program file> [timer interrupt]
		timer interrupt is optional the program file must support it. 


program file
	my program that I had to create is called program.txt it will draw this to the screen

	_________
	\_   ___ \      __          __
	/    \  \/   __|  |___   __|  |___
	\     \____ /__    __/  /__    __/
	 \______  /    |__|        |__|
	        \/

	The program is a repeat of this pattern
	2
	151
	16
	1
	1
	14
	23
	100
	it repeatedly calls a looping function to draw the amount of chars in a row for example
	in the first line it draws _________ which is 9 underscores it loads the loop count(9) and the the underscore code then starts looping and printing.
		
