#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP





class Processor
{
public:
	Processor();
	~Processor();

	/**
	* Fetches a single instruction from memory and stores in IR
	* @param the address in memory to fetch instruction
	*	after fetch PC will be incremented
	**/
	void fetch (int address); 
	
	/**
	* run runs a single instruction
	* @param operand of instruction
	**/
	void run(int operand); 
	void run();
private: //The instruction set(functions) for the processor 
	
private:
	int AC, SP, IR, X, PC, Y; //registers used by processor


};

#endif

