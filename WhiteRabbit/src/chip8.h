#ifndef CHIP8_H
#define CHIP8_H

class CHIP8
{
public:
    CHIP8();
    static void hello();
    static void print_as_byte(int number);
    void load_program(const char* file_path);

    //--- GRAPICS
    //Display resolution of 64*32 pixels, monochrome; XOR sprites
    unsigned char graphics[64*32] {};

private:

};

#endif // CHIP8_H
