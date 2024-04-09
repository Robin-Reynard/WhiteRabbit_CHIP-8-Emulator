#include "chip8.h"
#include <iostream>

using namespace std;

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
