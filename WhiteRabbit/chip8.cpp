#include "chip8.h"
#include <iostream>

using namespace std;

//unsigned char memory[4096] {};
unsigned char V[16] {}; // registers
unsigned short I {}; //12 bits wide
unsigned short stack[16]{};
unsigned short delay_timer{}; // counts down 60Hz to 0
unsigned short sound_timer{}; // counts down 60Hz to 0; Beeping at non-zero values
unsigned short opcode {}; // 35 opcodes possible, all 2bytes long and stored big-endian
//unsigned short program_counter {};
unsigned short stack_pointer {};
unsigned char graphics[64*32] {}; // display resolution of 64*32 pixels, monochrome; XOR sprites
unsigned char keys[16] {}; // 16 keys, usually 8,4,6,2 used for directional input

CHIP8::CHIP8()
{
    std::cout << "Init CHIP8" << endl;

    // Program counter starts at 0x200 (512); The space 0-512 is assigned to fonts. Programs no touchie
    //program_counter = 0x200;

    print_as_byte(program_counter);
}

void CHIP8::print_as_byte(int number){
    std::cout << "0x" << std::hex << number << endl;
}

void CHIP8:: hello(){
    std::cout << "Hello from CHIP8" << endl;
}

void CHIP8::e(){
    program_counter = 0x200;
    print_as_byte(program_counter);
}

void CHIP8::ee(){
    print_as_byte(program_counter);
}
