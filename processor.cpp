#include "processor.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

Processor::Processor()
{
	AC = 0, PC = 0, IR = 0 ,X = 0, Y = 0, SP = 0;

}

/**
*
* constructor for Processor
* @param wfd file discriptor for writing to memory process
* @param rfd file discriptor for reading from memory process
**/

Processor::Processor(int wfd, int rfd): Processor()
{
	writeFd = wfd;
	readFd = rfd;
}

Processor::~Processor()
{

}

/**
* Fetches a single instruction from memory and stores in IR
*	Will fetch from memory at address PC
*	@param fd file discriptorr for sending signal
*	@param fd2 file discriptor	for reading from signal
*	after fetch PC will be incremented
**/
void Processor::fetch()
{	
	//send address to memory process
	// int sig = 0;
	// write(writeFd, &sig, sizeof(sig));
	
	// write (writeFd, &PC, sizeof(PC)); //send program counter to memory process
	// //read IR from memory process
	// read (readFd,&IR,sizeof(IR));
	IR = send(PC); //send to memory and set IR to return value
	PC++;
}
int Processor::get_ir()
{
	return IR;
}

/**
* send data over pipe to request data at memory address addr
* @param address to read from memory
* return the value memory sends back over pipe
**/
int Processor::send(int addr)
{
	int data; //received data from memory
	int sig = 0;
	write(writeFd, &sig, sizeof(sig)); //send memory signal to not write data to memory
	write(writeFd, &addr, sizeof(addr)); //send address to memory process
	read(readFd, &data, sizeof(data)); //read from memory process into data
	return data;
}
/**
* send data over pipe to request data at memory address addr
* @param address to read from memory
* @param data to write at address
**/
void Processor::send_for_store(int addr, int data)
{
	int sig = 1;
	write(writeFd, &sig, sizeof(sig));
	write(writeFd, &addr, sizeof(addr));
	write(readFd, &data, sizeof(data));
}


int Processor::get_operand()
{
	int op;
	// write(writeFd, &sig, sizeof(sig));
	// //send address to memory process
	// write(writeFd, &PC, sizeof(PC)); //send program counter to memory process
	// //read address from memory process
	// read(readFd,&op, sizeof(op));
	// PC++; //after reading increase PC
	op = send(PC);
	PC++;
	return op;
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
		
		case 10:	op = get_operand();
					add_x();
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
	// data = send(addr);
	AC = send(addr);
}

void Processor::load_indr_addr(int addr)
{
	int addr2; //address stored at addr
	addr2 = send(addr);
	AC = send(addr2);
}

void Processor::load_indxx_addr(int addr)
{
	AC = send(addr + X);
}

void Processor::load_indxy_addr(int addr)
{
	AC = send(addr + Y);
}

void Processor::load_sp_x()
{
	AC = send(SP+X);
}
void Processor::store_addr(int addr)
{
	send_for_store(addr, AC);
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
		std::cout << (AC);
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

}
void Processor::ret()
{

}
/**
*
* Increment X by 1
*
**/
void Processor::inc_x()
{
	X++;
}

/**
*
* Decrement X by 1
*
**/
void Processor::dec_x()
{
	X--;
}
void Processor::push()
{

}
void Processor::pop()
{

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