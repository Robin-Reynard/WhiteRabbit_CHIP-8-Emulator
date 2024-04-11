#include "chip8.h"
#include <iostream>
#include <fstream>

using namespace std;

//--- MEMORY
//4096 8-bit memory, partially initialized with fontset
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


CHIP8::CHIP8()
{
    cout << "Init CHIP8" << endl;
    print_as_byte(program_counter);
    print_as_byte(memory[0]);
    print_as_byte(memory[1]);
}

void CHIP8::load_program(const char* file_path){
    cout << "Ready to load program" << endl;

    ifstream input_file(file_path, ios::binary);
    if(input_file.good()){
        std::cout << "Program file good! unga bunga";
        int count {0};
        int i {0};
        while(input_file >> i){
            memory[0x200 + count] = i;
            count++;
        }
    }
    input_file.close();
    /*for(int i = 0; i < 10; ++i){
        print_as_byte(memory[i]);
    }*/
    //qmemory[i + 512] = buffer[i];
}

void CHIP8::print_as_byte(int number){
    cout << "0x" << hex << number << endl;
}

void CHIP8:: hello(){
    cout << "Hello from CHIP8" << endl;
}
