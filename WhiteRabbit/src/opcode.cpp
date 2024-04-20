#include "opcode.h"
#include <iostream>

namespace Opcode {
    void execute_1NNN(unsigned short opcode, unsigned short &pc){
        pc = opcode & 0x0FFF;
    }

    void execute_2NNN(unsigned short opcode, unsigned short stack[], unsigned short &sp, unsigned short &pc){
        stack[sp] = pc;
        ++sp;
        pc = opcode & 0x0FFF;
    }
}

