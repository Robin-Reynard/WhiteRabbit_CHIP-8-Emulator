#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <fstream>
#include <string>
#include "opcode.h"
using namespace Opcode;

class CHIP8
{
public:
    CHIP8();
    static void hello();
    static void print_as_byte(int number);
    void load_program(const std::string file_path);
    void emulate_cycle();
    void display_graphics_ascii();
    byte* get_display();

private:
    //--- MEMORY
    byte memory[4096];
    //--- OPCODES
    // 35 opcodes possible, all 2bytes long and stored big-endian
    u_short opcode;
    u_short program_counter;
    //--- REGISTERS
    //16 8-bit registers V0 to VF
    byte V[16];
    //Address register, 12 bits wide.
    u_short I;
    //---STACK
    u_short stack[16];
    byte stack_pointer;
    //--- TIMERS
    //Counts down from 60Hz to 0
    byte delay_timer;
    //Counts down from 60Hz to 0; beeping when value is non-zero
    byte sound_timer;
    //--- INPUT
    //Done via hex keyboard (16 keys from 0 to F).
    byte keys[16];
    //--- GRAPICS
    //Display resolution of 64*32 pixels, monochrome; XOR sprites
    byte graphics[64*32];
};

#endif // CHIP8_H
