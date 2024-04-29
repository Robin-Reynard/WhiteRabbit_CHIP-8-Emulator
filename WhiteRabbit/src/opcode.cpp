#include "opcode.h"
#include <iostream>

namespace Opcode {
    u_short extract_NNN(u_short opcode){
        return opcode & 0x0FFF;
    }
    u_short extract_X(u_short opcode){
        return (opcode & 0x0F00) >> 8;
    }

    u_short extract_Y(u_short opcode){
        return (opcode & 0x00F0) >> 4;
    }
    void execute_0NNN(u_short &pc) {
        pc += 2;
    }
    void execute_00E0(u_char graphics[], u_short &pc){
        for(int i {0}; i < 64*32 ; i++){
            graphics[i] = '\0';
        }
        pc += 2;
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
        pc += V[x] == nn ? 4 : 2;
    }
    void execute_4XNN(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short nn = opcode & 0x00FF;
        pc += V[x] != nn ? 4 : 2;
    }
    void execute_5XY0(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        pc += V[x] == V[y] ? 4 : 2;
    }

    void execute_6XKK(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short kk = opcode & 0x00FF;
        V[x] = kk;
        pc += 2;
    }

    void execute_7XKK(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short kk = opcode & 0x00FF;
        V[x] += kk;
        pc += 2;
    }

    void execute_8XY0(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] = V[y];
        pc += 2;
    }

    void execute_8XY1(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] |= V[y];
        pc += 2;
    }

    void execute_8XY2(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] &= V[y];
        pc += 2;
    }

    void execute_8XY3(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] ^= V[y];
        pc += 2;
    }

    void execute_8XY4(u_short opcode, u_short V[], u_short &pc){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        u_short sum = V[x] + V[y];

        V[0xF] = sum > 255 ? 1 : 0;
        V[x] = sum & 0xFF;
        pc += 2;
    }
}

