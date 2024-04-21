#include "opcode.h"
#include <iostream>

namespace Opcode {
    void execute_0NNN() {}
    void execute_00E0(u_char graphics[]){
        for(int i {0}; i < 64*32 ; i++){
            graphics[i] = '\0';
        }
    }
    void execute_1NNN(u_short opcode, u_short& pc){
        pc = opcode & 0x0FFF;
    }
    void execute_2NNN(u_short opcode, u_short stack[], u_short& sp, u_short& pc){
        stack[sp] = pc;
        ++sp;
        pc = opcode & 0x0FFF;
    }
    void execute_3XNN(u_short opcode, u_short V[], u_short &pc){
        u_short x = opcode & 0x0F00;
        u_short nn = opcode & 0x00FF;
        if(V[x] == nn){
            pc += 2;
        }
    }
    void execute_4XNN(u_short opcode, u_short V[], u_short &pc){
        u_short x = opcode & 0x0F00;
        u_short nn = opcode & 0x00FF;
        if(V[x] != nn){
            pc += 2;
        }
    }
    void execute_5XY0(u_short opcode, u_short V[], u_short &pc){
        u_short x = opcode & 0x0F00;
        u_short y = opcode & 0x00F0;
        if(V[x] == V[y]){
            pc += 2;
        }
    }
}

