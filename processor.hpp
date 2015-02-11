#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP


enum MemorySignals  {FETCH, LOAD, STORE};


class Processor
{
public:
	Processor();
	~Processor();


	void fetch (int, int); 
	
	/**
	* run runs a single instruction
	* @param operand of instruction
	**/
	void run(int operand); 
	void run();
	int get_pc();
private: //The instruction set(functions) for the processor 
	
private:
	int AC, SP, IR, X, PC, Y; //registers used by processor


};

#endif

