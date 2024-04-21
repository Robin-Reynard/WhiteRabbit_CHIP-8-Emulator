#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <fstream>
#include <string>
class CHIP8
{
public:
    CHIP8();
    static void hello();
    static void print_as_byte(int number);
    void load_program(const std::string file_path);
    void emulate_cycle();

private:
    //--- MEMORY
    unsigned char memory[4096];
    //--- OPCODES
    // 35 opcodes possible, all 2bytes long and stored big-endian
    unsigned short opcode;
    unsigned short program_counter;
    //--- REGISTERS
    //16 8-bit registers V0 to VF
    unsigned char V[16];
    //Address register, 12 bits wide.
    unsigned short I;
    //---STACK
    unsigned short stack[16];
    unsigned short stack_pointer;
    //--- TIMERS
    //Counts down from 60Hz to 0
    unsigned short delay_timer;
    //Counts down from 60Hz to 0; beeping when value is non-zero
    unsigned short sound_timer;
    //--- INPUT
    //Done via hex keyboard (16 keys from 0 to F).
    unsigned char keys[16];
    //--- GRAPICS
    //Display resolution of 64*32 pixels, monochrome; XOR sprites
    unsigned char graphics[64*32];
};

#endif // CHIP8_H
