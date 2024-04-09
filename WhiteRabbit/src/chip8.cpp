#include "chip8.h"
#include <iostream>

using namespace std;

CHIP8::CHIP8()
{
    std::cout << "Init CHIP8" << endl;

    print_as_byte(program_counter);
    print_as_byte(memory[0]);
    print_as_byte(memory[81]);
}

void CHIP8::load_program(){
    std::cout << "Read to load program" << endl;
    //for(int i = 0; i < bufferSize; ++i)
    //qmemory[i + 512] = buffer[i];
}

void CHIP8::print_as_byte(int number){
    std::cout << "0x" << std::hex << number << endl;
}

void CHIP8:: hello(){
    std::cout << "Hello from CHIP8" << endl;
}
