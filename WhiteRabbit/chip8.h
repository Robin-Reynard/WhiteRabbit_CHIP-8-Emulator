#ifndef CHIP8_H
#define CHIP8_H

class CHIP8
{
public:
    CHIP8();
    static void hello();
    static void print_as_byte(int number);
    void e();
    void ee();
private:
    unsigned char memory[4096] {};
    unsigned short program_counter {};
};

#endif // CHIP8_H
