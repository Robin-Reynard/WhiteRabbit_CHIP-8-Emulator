#ifndef CHIP8_H
#define CHIP8_H
#include <fstream>
#include "opcode.h"
using namespace Opcode;

class CHIP8
{
public:
    CHIP8();
    CHIP8(std::string program_path);
    // Keyboard inputs
    enum KeyStrokes {key_0, key_1, key_2, key_3, key_4, key_5, key_6, key_7,
                     key_8, key_9, key_A, key_B, key_C, key_D, key_E, key_F};

    // Reduces the number of times the screen has to be redrawn
    bool new_drawing_available {false};

    // Load program into memory
    void load_program(const std::string file_path);

    // Decodes and runs the next opcode
    void execute_next_opcode();

    // Display-related methods
    bool* get_display();
    void display_graphics_ascii();

    // Keyboard and keyboard-event related methods
    bool* get_keyboard();
    void press_key(KeyStrokes keystroke);
    void release_key(KeyStrokes keystroke);

    // Returns whether the CHIP8 is making sound
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

    static void print_as_byte(int number);
};

#endif // CHIP8_H
