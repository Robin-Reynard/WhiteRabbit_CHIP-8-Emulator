#include "opcode.h"

namespace Opcode {
    u_short extract_NNN(u_short opcode){
        return opcode & 0x0FFF;
    }
    u_short extract_KK(u_short opcode){
        return opcode & 0x00FF;
    }
    u_short extract_X(u_short opcode){
        return (opcode & 0x0F00) >> 8;
    }
    u_short extract_Y(u_short opcode){
        return (opcode & 0x00F0) >> 4;
    }

    void execute_0NNN() {
        return;
    }

    void execute_00E0(bool graphics[]){
        for(int i {0}; i < 64*32 ; i++){
            graphics[i] = 0;
        }
    }

    void execute_00EE(u_short &pc, byte &sp, u_short stack[]){
        pc = stack[sp];
        stack[sp] = 0x0000;
        if(sp != 0){
            sp--;
        }
    }

    void execute_1NNN(u_short opcode, u_short& pc){
        pc = extract_NNN(opcode);
    }

    void execute_2NNN(u_short opcode, u_short& pc, u_short stack[], byte& sp){
        if(sp >= 15)
            throw std::runtime_error("Exception at 0x2NNN; Stack is full!");
        ++sp;
        stack[sp] = pc;
        pc = extract_NNN(opcode);
    }

    void execute_3XNN(u_short opcode, u_short& pc, byte V[]){
        u_short x = extract_X(opcode);
        u_short nn = extract_KK(opcode);
        if(V[x] == nn) {
            pc += 2;
        }
    }

    void execute_4XNN(u_short opcode, u_short& pc, byte V[]){
        u_short x = extract_X(opcode);
        u_short nn = extract_KK(opcode);
        if(V[x] != nn) {
            pc += 2;
        }
    }

    void execute_5XY0(u_short opcode, u_short& pc, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        if(V[x] == V[y]){
            pc += 2;
        }
    }

    void execute_6XKK(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short kk = extract_KK(opcode);
        V[x] = kk;
    }

    void execute_7XKK(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short kk = extract_KK(opcode);
        V[x] += kk;
    }

    void execute_8XY0(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] = V[y];
    }

    void execute_8XY1(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] |= V[y];
    }

    void execute_8XY2(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] &= V[y];
    }

    void execute_8XY3(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[x] ^= V[y];
    }

    void execute_8XY4(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[0xF] = V[x] + V[y] > 0xFF ? 1 : 0;
        V[x] += V[y];
    }

    void execute_8XY5(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[0xF] = V[x] > V[y] ? 1 : 0;
        V[x] -= V[y];
    }

    void execute_8XY6(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        V[0xF] = V[x] & 0x1;
        V[x] >>= 1;
    }

    void execute_8XY7(u_short opcode, byte V[]) {
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        V[0xF] = V[y] > V[x] ? 1 : 0;
        V[x] = V[y] - V[x];
    }

    void execute_8XYE(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        V[0xF] = V[x] & 0x1;
        V[x] <<= 1;
    }

    void execute_9XY0(u_short opcode, u_short &pc, byte V[]){
        u_short x = extract_X(opcode);
        u_short y = extract_Y(opcode);
        if(V[x] != V[y]){
            pc += 2;
        }
    }

    void execute_ANNN(u_short opcode, u_short &I){
        I = extract_NNN(opcode);
    }

    void execute_BNNN(u_short opcode, u_short& pc, byte& V0){
        pc = extract_NNN(opcode) + V0;
    }

    void execute_CXKK(u_short opcode, byte V[]){
        u_short x = extract_X(opcode);
        u_short kk = extract_KK(opcode);
        byte random_byte = byte (std::rand() % 0xFF);

        V[x] = random_byte & kk;
    }

    void execute_DXYN(u_short opcode, byte memory[], byte V[], u_short &I, bool graphics[]){
        byte x_pos = V[extract_X(opcode)];
        byte y_pos = V[extract_Y(opcode)];
        byte height = opcode & 0x000F;
        V[0xF] = 0;

        for(byte y {0}; y < height; y++){
            byte sprite_data = memory[I + y];
            for(byte x {0}; x < 8; x++){
                if ((sprite_data & (0x80 >> x)) != 0){
                    if(graphics[x_pos + x + ((y + y_pos) * 64)] == 1){
                        // Collision encountered
                        V[0xF] = 1;
                    }
                    graphics[x_pos + x + ((y + y_pos) * 64)] ^= 1;
                }
            }
        }
    }

    void execute_EX9E(u_short opcode, u_short &pc, byte V[], bool keys[]){
        byte x = extract_X(opcode);
        if(keys[V[x]] == true){
            keys[V[x]] = false;
            pc += 2;
        }
    }

    void execute_EXA1(u_short opcode, u_short &pc, byte V[], bool keys[]){
        byte x = extract_X(opcode);
        if(keys[V[x]] == false){
            pc += 2;
        }
    }

    void execute_FX07(u_short opcode, byte V[], byte &delay_timer){
        byte x = extract_X(opcode);
        V[x] = delay_timer;
    }

    void execute_FX0A(u_short opcode, u_short &pc, byte V[], bool keys[]){
        byte x = extract_X(opcode);

        for(int i {0}; i < 16; i++){
            if (keys[i] == true){
                V[x] = i;
                keys[i] = false;
                return;
            }
        }
        pc -= 2;
    }

    void execute_FX15(u_short opcode, byte V[], byte &delay_timer){
        delay_timer = V[extract_X(opcode)];
    }

    void execute_FX18(u_short opcode, byte V[], byte &sound_timer){
        sound_timer = V[extract_X(opcode)];
    }

    void execute_FX1E(u_short opcode, byte V[], u_short &I){
        byte Vx = V[extract_X(opcode)];
        I += Vx;
        V[0xF] = I > 0xFFF ? 1 : 0;
    }

    void execute_FX29(u_short opcode, byte V[], u_short &I){
        I = V[extract_X(opcode)] * 0x5;
    }

    void execute_FX33(u_short opcode, byte V[], u_short &I, byte memory[]){
        if(I >= 4094)
            throw std::runtime_error("Exception in 0xFX33; I overshoots memory!");

        byte Vx = V[extract_X(opcode)];
        memory[I] = Vx / 100;
        memory[I+1] = (Vx % 100) / 10;
        memory[I+2] = Vx % 10;
    }

    void execute_FX55(u_short opcode, byte V[], u_short &I, byte memory[]){
        u_short x = extract_X(opcode);
        if(I + x >= 4096)
            throw std::runtime_error("Exception in 0xFX55; I+X overshoots memory!");

        for(int i {0}; i <= x; i++){
            memory[I + i] = V[i];
        }
    }

    void execute_FX65(u_short opcode, byte V[], u_short &I, byte memory[]){
        u_short x = extract_X(opcode);
        if(I + x >= 4096)
            throw std::runtime_error("Exception in 0xFX65; I+X overshoots memory!");

        for(int i {0}; i <= x; i++){
            V[i] = memory[I + i];
        }
    }
}

