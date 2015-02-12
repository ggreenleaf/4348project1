#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP



class Processor
{
public:
	Processor();
	Processor(int, int);
	~Processor();


	void fetch (); 
	
	/**
	* run runs a single instruction
	* @param operand of instruction
	**/
	void 	run();
	int 	get_ir();
	int 	get_operand();

private: //The instruction set for the processor 	
	void	load_value (int val); //load value into AC
	void	load_addr (int addr); //load value at address into AC
	void	load_indr_addr(int addr); //load value from the adddress found in the address into AC
	void	load_indxx_addr(int addr); //load the value at(addr+x) in the AC
	void	load_indxy_addr(int addr); //load the value at(addr+y) in the AC
	void 	load_sp_x(int x); //load form (sp+x) into AC
	void	store_addr(int addr); //store value in teh AC into the address
	void	get(); //gets a random int[1,100] into AC
	void	put_port(int mode); //port=1 writes AC as an int to screen if port=2 write ascii
	void	add_x(); //add the value of x to AC
	void	add_y(); //add the value of y to AC
	void	sub_x(); //sub the value of x from AC 
 	void	sub_y(); //sub the value of y from AC
	void	cpy_to_x();  //copy value in the AC to X
	void	cpy_from_x(); //copy value in X to AC
	void	cpy_to_y(); //copy value Y to the AC
	void	cpy_from_y(); //copy value from AC to Y
	void	cpy_to_sp(); //copy value from AC to SP
	void	cpy_from_sp(); //copy value from SP to AC
	void	jump_addr(int addr); //jump to address
	void	jump_if_eq_addr(int addr); //jump to the address iff AC == 0
	void	jump_if_neq_addr(int addr); //jump to the address iff AC != 0
	void	call_addr(int addr); //push return address onto stack, jump to addr
	void	ret(); //pop return address from stack, jump to addr
	void 	inc_x(); //increment the value in X
	void	dec_x(); //decrement the value of x
	void	push(); //push AC onto Stack
	void	pop(); //pop from stack into AC
	void	mode(); //int set system mode, push SP and PC, set new SP and PC
	void	i_ret(); //restore registers, set user mode
	void 	end(); //end execution



private:
	int AC, SP, IR, X, PC, Y; //registers used by processor
	int writeFd, readFd; //file discriptors for writing/reading to memory process

};

#endif

