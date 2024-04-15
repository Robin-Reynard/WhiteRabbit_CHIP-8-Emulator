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

    //--- GRAPICS
    //Display resolution of 64*32 pixels, monochrome; XOR sprites
    unsigned char graphics[64*32] {};

private:

};

#endif // CHIP8_H
