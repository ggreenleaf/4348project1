#include "processor.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

Processor::Processor()
{
	AC = 0, PC = 0, IR = 0 ,X = 0, Y = 0, SP = 0 ;

}

/**
*
* constructor for Processor
* @param wfd file discriptor for writing to memory process
* @param rfd file discriptor for reading from memory process
* @param size of the user memory will be the start of user stack push down
* @param size of the system memory start of system stack
**/

Processor::Processor(int wfd, int rfd): Processor()
{
	writeFd = wfd;
	readFd = rfd;
	SP = 1000;
}

Processor::~Processor()
{

}

/**
* Fetches a single instruction from memory and stores in IR
*	Will fetch from memory at address PC
*	@param fd file discriptorr for read_from_memorying signal
*	@param fd2 file discriptor	for reading from signal
*	after fetch PC will be incremented
**/
void Processor::fetch()
{	
	//read_from_memory address to memory process
	// int sig = 0;
	// write(writeFd, &sig, sizeof(sig));
	
	// write (writeFd, &PC, sizeof(PC)); //read_from_memory program counter to memory process
	// //read IR from memory process
	// read (readFd,&IR,sizeof(IR));
	IR = read_from_memory(PC); //read_from_memory to memory and set IR to return value
	PC++;
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
	int data; //received data from memory
	int sig = 0;
	write(writeFd, &sig, sizeof(sig)); //read_from_memory memory signal to not write data to memory
	write(writeFd, &addr, sizeof(addr)); //read_from_memory address to memory process
	read(readFd, &data, sizeof(data)); //read from memory process into data
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
	write(writeFd, &sig, sizeof(sig));	
	write(writeFd, &addr, sizeof(addr));
	write(writeFd, &data, sizeof(data));
}


int Processor::get_operand()
{
	int op;
	// write(writeFd, &sig, sizeof(sig));
	// //read_from_memory address to memory process
	// write(writeFd, &PC, sizeof(PC)); //read_from_memory program counter to memory process
	// //read address from memory process
	// read(readFd,&op, sizeof(op));
	// PC++; //after reading increase PC
	op = read_from_memory(PC);
	PC++;
	return op;
}
//debugging purposes
void Processor::print_registers()
{
	printf("AC: %d IR: %d, PC: %d SP: %d X: %d Y: %d\n",AC,IR,PC,SP,X,Y);

	printf("value at SP: %d\n", read_from_memory(SP)); 
}


void Processor::run()
{
	int op; //if instruction needs operand store here. 
	switch(IR)
	{
		case 1:		op = get_operand();
					load_value(op);
					break;
					
		case 2:		op = get_operand();
					load_addr(op);
					break;
		
		case 3:		op = get_operand();
					load_indr_addr(op);
					break;
		
		case 4:		op = get_operand();
					load_indxx_addr(op);
					break;
		
		case 5:		op = get_operand();
					load_indxy_addr(op);
					break;
		
		case 6:		load_sp_x();
					break;

		case 7:		op = get_operand();
					store_addr(op);
					break;

		case 8:		get();
					break;

		case 9:		op = get_operand();
					put_port(op);
					break;
		
		case 10:	add_x();
					break;
		case 11:	
					add_y();
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
		
		case 20:	op = get_operand();
					jump_addr(op);
					break;
		
		case 21:	
					op = get_operand();
					jump_if_eq_addr(op);
					break;
		
		case 22:	op = get_operand();
					jump_if_neq_addr(op);
					break;
		
		case 23:	op = get_operand();
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
		
		case 29:	mode();
					break;
		
		case 30:	i_ret();
					break;

		case 50:	end();
					break;

		default:
					std::cout << "invalid instruction\n";
	}

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
	// int data;
	// data = read_from_memory(addr);
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
* will set PC to addr	
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
	write_to_memory(--SP, AC); //read_from_memory AC on to Stack
}
void Processor::pop()
{
	AC = read_from_memory(SP++);
}
void Processor::mode()
{

}
void Processor::i_ret()
{

}
void Processor::end()
{

}