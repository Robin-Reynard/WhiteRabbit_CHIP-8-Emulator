#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include "opcode.h"
using namespace Opcode;

class CHIP8
{
public:
    CHIP8();
    CHIP8(std::string program_path);
    enum KeyStrokes {key_1, key_2, key_3, key_C,
                     key_4, key_5, key_6, key_D,
                     key_7, key_8, key_9, key_E,
                     key_A, key_0, key_B, key_F};
    bool new_drawing_available {false};

    void load_program(const std::string file_path);
    void press_key(KeyStrokes keystroke);
    void release_key(KeyStrokes keystroke);

    void emulate_cycle();
    void display_graphics_ascii();
    bool* get_display();
    bool* get_keyboard();
    //void set_delay_between_instructions(uint ms_delay);
    bool is_beeping();


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
    bool keys[16];
    //--- GRAPICS
    //Display resolution of 64*32 pixels, monochrome; XOR sprites
    bool graphics[64*32];

    //uint ms_delay_between_instructions;
    static void print_as_byte(int number);
};

#endif // CHIP8_H
