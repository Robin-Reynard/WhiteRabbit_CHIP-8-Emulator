#include "opcode.h"
#include <iostream>

Opcode::Opcode()
{

}

void Opcode::execute_2NNN(unsigned short opcode, unsigned short stack[], unsigned short &sp, unsigned short &pc){
    stack[sp] = pc;
    ++sp;
    pc = opcode & 0x0FFF;
}

