#include "processor.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#define INTERRUPT_HANDLER 1500 //location of program interrupt handler 
#define TIMER_HANDLER 1000 //location of timer interrupt handler
#define SYSTEM_MEMORY 1000 //can't read from this address or greater unless in system mode
#define SYSTEM_STACK 2000 //System stack pointer after saving PC, SP
#define INTERRUPT_INST 29 //instruction code for interrupt
#define TIMER_INTERRUPT 0
#define PROGRAM_INTERRUPT 1

Processor::Processor() {}
/**
*
* constructor for Processor
* @param wfd file discriptor for writing to memory process
* @param rfd file discriptor for reading from memory process
* @param size of the user memory will be the start of user stack push down
* @param size of the system memory start of system stack
* @param number of instructions to run before interrupt is exec. 
**/
Processor::~Processor() {};
Processor::Processor(int wfd, int rfd , int count):
	AC(0), PC(0), IR(0), X(0),Y(0), SP(SYSTEM_MEMORY),
	writeFd(wfd), readFd(rfd),
	instructionsPerInterrupt(count), instructionCount(0),
	isSystemMode(false), handlingInterrupt(false) {}
/**
* Fetches a single instruction from memory and stores in IR
*	Will fetch from memory at address PC
**/
void Processor::fetch()
{	
	IR = read_from_memory(PC++); 
}

int Processor::get_ir()
{
	return IR;
}

/**
* read_from_memory data over pipe to request data at memory address addr
* @param address to read from memory
* return the value memory read_from_memorys back over pipe
**/
int Processor::read_from_memory(int addr)
{
	int data = 0; //received data from memory
	int sig = 0;
	
	if (addr >= SYSTEM_MEMORY && !isSystemMode) {
		std::cout << "Error can't read system memory address (" << addr << ")\n";
	}
	else {
		write(writeFd, &sig, sizeof(sig)); //send memory signal to not write data to memory
		write(writeFd, &addr, sizeof(addr)); //send address to memory process
		read(readFd, &data, sizeof(data)); //read from memory process into data
	}
	return data;
}
/**
* read_from_memory data over pipe to request data at memory address addr
* @param address to read from memory
* @param data to write at address
**/
void Processor::write_to_memory(int addr, int data)
{
	int sig = 1;
	if (addr >= SYSTEM_MEMORY && !isSystemMode) {
		std::cout << "Error can't write to system memory address (" << addr << ")\n";
	}
	else {
		write(writeFd, &sig, sizeof(sig));	
		write(writeFd, &addr, sizeof(addr));
		write(writeFd, &data, sizeof(data));
	}
}


int Processor::fetch_operand()
{
	int op;
	op = read_from_memory(PC++);
	return op;
}

//debugging purposes
void Processor::print_registers()
{
	printf("int Count: %d AC: %d IR: %d, PC: %d SP: %d X: %d Y: %d\n",instructionCount, AC,IR,PC,SP,X,Y);
}


void Processor::run()
{
	int op; //if instruction needs operand store here. 
	bool interruptHandler = PROGRAM_INTERRUPT;
	if (instructionCount && instructionCount % instructionsPerInterrupt == 0 && instructionsPerInterrupt != -1) {
		std::cout << "handle interrupt!!!\n";
		interruptHandler = TIMER_INTERRUPT;
		IR = 29; //cause interrupt instruction
	}

	switch(IR)
	{
		case 1:		op = fetch_operand();
					load_value(op);
					break;
					
		case 2:		op = fetch_operand();
					load_addr(op);
					break;
		
		case 3:		op = fetch_operand();
					load_indr_addr(op);
					break;
		
		case 4:		op = fetch_operand();
					load_indxx_addr(op);
					break;
		
		case 5:		op = fetch_operand();
					load_indxy_addr(op);
					break;
		
		case 6:		load_sp_x();
					break;

		case 7:		op = fetch_operand();
					store_addr(op);
					break;

		case 8:		get();
					break;

		case 9:		op = fetch_operand();
					put_port(op);
					break;
		
		case 10:	add_x();
					break;
		
		case 11:	add_y();
					break;
		
		case 12:	sub_x();
					break;	
		
		case 13:	sub_y();
					break;

		case 14:	cpy_to_x();
					break;
		
		case 15:	cpy_from_x();
					break;
		
		case 16:	cpy_to_y();
					break;
		
		case 17:	cpy_from_y();
					break;
		
		case 18:	cpy_to_sp();
					break;
		
		case 19:	cpy_from_sp();
					break;
		
		case 20:	op = fetch_operand();
					jump_addr(op);
					break;
		
		case 21:	op = fetch_operand();
					jump_if_eq_addr(op);
					break;
		
		case 22:	op = fetch_operand();
					jump_if_neq_addr(op);
					break;
		
		case 23:	op = fetch_operand();
					call_addr(op);
					break;
		
		case 24:	ret();
					break;
		
		case 25:	inc_x();
					break;
		
		case 26:	dec_x();
					break;
		
		case 27:	push();
					break;	
		
		case 28:	pop();
					break;
		
		case 29:	interrupt(interruptHandler);
					break;
		
		case 30:	interrupt_return();
					break;

		case 50:	end();
					break;

		default:	
					std::cout << "invalid instruction: " << IR << "\n";
	}

	instructionCount++;

	
}

/*=================================================
=            Instruction Set Functions            =
=================================================*/
void Processor::load_value(int val)
{
	AC = val;
}

void Processor::load_addr(int addr)
{	

	AC = read_from_memory(addr);

}

void Processor::load_indr_addr(int addr)
{
	int addr2; //address stored at addr
	addr2 = read_from_memory(addr);
	AC = read_from_memory(addr2);
}

void Processor::load_indxx_addr(int addr)
{
	AC = read_from_memory(addr + X);
}

void Processor::load_indxy_addr(int addr)
{
	AC = read_from_memory(addr + Y);
}

void Processor::load_sp_x()
{
	AC = read_from_memory(SP + X);
}

void Processor::store_addr(int addr)
{
	write_to_memory(addr, AC);
}

void Processor::get()
{
	AC = rand() % 100 + 1;
}

/**
* Print the value of AC to the screen
* @param mode if 1 print int if 2 print char (ASCII)
**/
void Processor::put_port(int mode)
{
	 if (mode - 1)
	 	std::cout << (char)AC;
	 else
		std::cout << AC;
}

void Processor::add_x() 
{
	AC += X;
}

void Processor::add_y()
{
	AC += Y;
}

void Processor::sub_x()
{
	AC -= X;
}

void Processor::sub_y()
{
	AC -= Y;
}

void Processor::cpy_to_x()
{
	X = AC;
}

void Processor::cpy_from_x()
{
	AC = X;
}

void Processor::cpy_to_y()
{
	Y = AC;
}

void Processor::cpy_from_y()
{
	AC = Y;
}
void Processor::cpy_to_sp()
{
	SP = AC;
}
void Processor::cpy_from_sp()
{
	AC = SP;
}
/**
*
* will jump to an address
* @param address to jump to
**/
void Processor::jump_addr(int addr)
{
	PC = addr;
}
/**
* if data at AC == 0 jump to a address
* by setting PC to addr
* @param addr address to jump to 
**/
void Processor::jump_if_eq_addr(int addr)
{
	if (!AC)
		PC = addr; 
}
/**
* if data at AC != 0 jump to a address
* will set PC to addr	
* @param addr address to jump to
**/
void Processor::jump_if_neq_addr(int addr)
{
	if (AC) 
		PC = addr;
}
void Processor::call_addr(int addr)
{
	write_to_memory(--SP, PC);
	jump_addr(addr);
}
void Processor::ret()
{
	int addr;
	addr = read_from_memory(SP++);
	jump_addr(addr);
}
/**
* Increment X by 1
**/
void Processor::inc_x()
{
	X++;
}
/**
* Decrement X by 1
**/
void Processor::dec_x()
{
	X--;
}
void Processor::push()
{
	write_to_memory(--SP, AC); //write AC on to Stack
}
void Processor::pop()
{
	AC = read_from_memory(SP++);
}
/**
*
* interrupt handler will handle saving registers and moving PC
* to correct hanlder based on interruptHandler
*
**/

void Processor::interrupt(int handler)
{
	isSystemMode = true; 
	handlingInterrupt = true; //stop nested interrupts (possibly redundant) 
	save_registers();	
	
	switch(handler)
	{
		case TIMER_INTERRUPT:
								PC = TIMER_HANDLER;
								break;
		case PROGRAM_INTERRUPT:
								PC = INTERRUPT_HANDLER;
								break;
		default:
								std::cout << "no valid interrupt handler\n";
								break;
	}
}

void Processor::interrupt_return()
{
	restore_registers();
	std::cout << "PC after restore: " << PC << "\n";
	isSystemMode = false;
	handlingInterrupt = false;
}

void Processor::end()
{
	int sig = 2; //signal memory process to exit while loop
	write(writeFd, &sig, sizeof(sig));

}
/**
* save current state of registers to memory's system stack (all of them? or just SP, PC)
* and set SP to System Stack
**/
void Processor::save_registers()
{
	int tempSP = SP;
	SP = SYSTEM_STACK;
	write_to_memory(--SP, tempSP); //save orignal SP at 1999
	write_to_memory(--SP, PC); //save PC at 1998
}
/**
* restore the registors from that last interrupt
**/
void Processor::restore_registers()
{
	int sig = 3;
	write(writeFd,&sig, sizeof(sig)); // on restore print memory
	int tempSP = SYSTEM_STACK;
	SP = read_from_memory(--tempSP); //SP saved at [1999] before interrupt 
	PC = read_from_memory(--tempSP); //PC saved at [1998] before interrupt

}
