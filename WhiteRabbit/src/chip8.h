#ifndef CHIP8_H
#define CHIP8_H

class CHIP8
{
public:
    CHIP8();
    static void hello();
    static void print_as_byte(int number);
    static void load_program();

    //--- GRAPICS
    //Display resolution of 64*32 pixels, monochrome; XOR sprites
    unsigned char graphics[64*32] {};

private:
    //--- MEMORY
    //4096 8-bit memory, pre-loaded with fontset
    unsigned char memory[4096] {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    //--- OPCODES
    // 35 opcodes possible, all 2bytes long and stored big-endian
    unsigned short opcode {};
    // Initialized to 0x200 (512) as everything before that in memory is assigned to fontset
    unsigned short program_counter {0x200};

    //--- REGISTERS
    //16 8-bit registers V0 to VF
    unsigned char V[16] {};
    //Address register, 12 bits wide.
    unsigned short I {};

    //---STACK
    unsigned short stack[16]{};
    unsigned short stack_pointer {};

    //--- TIMERS
    //Counts down from 60Hz to 0
    unsigned short delay_timer{};
    //Counts down from 60Hz to 0; beeping when value is non-zero
    unsigned short sound_timer{};

    //--- INPUT
    //Done via hex keyboard (16 keys from 0 to F).
    unsigned char keys[16] {};
};

#endif // CHIP8_H
