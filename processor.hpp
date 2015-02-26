#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#define TIMER_INTERRUPT 0
#define PROGRAM_INTERRUPT 1


#define INTERRUPT_HANDLER 1500 //location of program interrupt handler 
#define TIMER_HANDLER 1000 //location of timer interrupt handler
#define SYSTEM_MEMORY 1000 //can't read from this address or greater unless in system mode
#define SYSTEM_STACK 2000 //System stack pointer after saving PC, SP
#define TIMER_INTERRUPT 0
#define PROGRAM_INTERRUPT 1



class Processor
{
public:
	// Processor();
	Processor(int, int, int);
	// ~Processor();

	void 	fetch (); 
	bool	run();
	int 	fetch_operand();
	int 	read_from_memory(int addr);
	void	write_to_memory(int addr, int data);
	void	print_registers();



private: 	
		void	save_registers(); //save registers to memory to handle interrupts
		void	restore_registers(); //restore registers from interrupt

/*=================================================
=            Processor Instruction Set            =
=================================================*/
/*IR number*/
/*1*/	void	load_value (int val); //load value into AC
/*2*/	void	load_addr (int addr); //load value at address into AC
/*3*/	void	load_indr_addr(int addr); //load value from the adddress found in the address into AC
/*4*/	void	load_indxx_addr(int addr); //load the value at(addr+x) in the AC
/*5*/	void	load_indxy_addr(int addr); //load the value at(addr+y) in the AC
/*6*/	void 	load_sp_x(); //load from (sp+x) into AC
/*7*/	void	store_addr(int addr); //store value in the AC into the address
/*8*/	void	get(); //gets a random int[1,100] into AC
/*9*/	void	put_port(int mode); //port=1 writes AC as an int to screen if port=2 write ascii
/*10*/	void	add_x(); //add the value of x to AC
/*11*/	void	add_y(); //add the value of y to AC
/*12*/	void	sub_x(); //sub the value of x from AC 
/*13*/ 	void	sub_y(); //sub the value of y from AC
/*14*/	void	cpy_to_x();  //copy value in the AC to X
/*15*/	void	cpy_from_x(); //copy value in X to AC
/*16*/	void	cpy_to_y(); //copy value AC to the Y
/*17*/	void	cpy_from_y(); //copy value from Y to AC
/*18*/	void	cpy_to_sp(); //copy value from AC to SP
/*19*/	void	cpy_from_sp(); //copy value from SP to AC
/*20*/	void	jump_addr(int addr); //jump to address
/*21*/	void	jump_if_eq_addr(int addr); //jump to the address iff AC == 0
/*22*/	void	jump_if_neq_addr(int addr); //jump to the address iff AC != 0
/*23*/	void	call_addr(int addr); //push return address onto stack, jump to addr
/*24*/	void	ret(); //pop return address from stack, jump to addr
/*25*/	void 	inc_x(); //increment the value in X
/*26*/	void	dec_x(); //decrement the value of x
/*27*/	void	push(); //push AC onto Stack
/*28*/	void	pop(); //pop from stack into AC
/*29*/	void	interrupt(int); //interrupt set system mode, push SP and PC, set new SP and PC
/*30*/	void	interrupt_return(); //restore registers, set user mode
/*50*/	void 	end(); //end execution



private:
	int 	AC, SP, IR, X, PC, Y; //registers used by processor
	int 	writeFd, readFd; //file discriptors for writing/reading to memory process
	int 	instructionCount; //total num of instructions ran
	int 	instructionsPerInterrupt; //number of instructions to run before timer interrupt occurs
	bool	handlingInterrupt; //used to stop nested interrupts from occuring
	bool	isSystemMode; //check for reading/writing to system memory
	
};

#endif

