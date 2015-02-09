#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP





class Processor
{
public:
	Processor();
	~Processor();
	enum RegisterLocations {
		AC, //accumulator
		SP, //stack pointer
		IR, //instruction stored here
		PC, //Program Counter
		X, //X,Y are local vars for storing operands
		Y };

	/**
	* Fetches a single instruction from memory and stores in IR
	* @param address the address in memory to fetch instruction
	*
	**/
	void fetch (int address); 
	
	/**
	*
	* run runs a single instruction then increments PC
	* @param operand is if a instruction requires an operand
	**/
	void run(int operand); 
	void run();
private: //The instruction set(functions) for the processor 

private:
	int registers[5];

};

#endif

