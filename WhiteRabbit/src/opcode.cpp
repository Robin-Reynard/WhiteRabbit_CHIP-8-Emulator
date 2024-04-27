#include "opcode.h"
#include <iostream>

namespace Opcode {
u_short extract_NNN(u_short opcode){
    return opcode & 0x0FFF;
}
u_short extract_X(u_short opcode){
    return opcode & 0x0F00;
}

u_short extract_Y(u_short opcode){
    return opcode & 0x00F0;
}
void execute_0NNN() {}
void execute_00E0(u_char graphics[]){
    for(int i {0}; i < 64*32 ; i++){
        graphics[i] = '\0';
    }
}
void execute_1NNN(u_short opcode, u_short& pc){
    pc = extract_NNN(opcode);
}
void execute_2NNN(u_short opcode, u_short stack[], u_short& sp, u_short& pc){
    stack[sp] = pc;
    ++sp;
    pc = extract_NNN(opcode);
}
void execute_3XNN(u_short opcode, u_short V[], u_short &pc){
    u_short x = extract_X(opcode);
    u_short nn = opcode & 0x00FF;
    if(V[x] == nn){
        pc += 2;
    }
}
void execute_4XNN(u_short opcode, u_short V[], u_short &pc){
    u_short x = extract_X(opcode);
    u_short nn = opcode & 0x00FF;
    if(V[x] != nn){
        pc += 2;
    }
}
void execute_5XY0(u_short opcode, u_short V[], u_short &pc){
    u_short x = extract_X(opcode);
    u_short y = extract_Y(opcode);
    if(V[x] == V[y]){
        pc += 2;
    }
}
}

