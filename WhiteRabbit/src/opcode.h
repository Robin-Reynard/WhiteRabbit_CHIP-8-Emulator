#ifndef OPCODE_H
#define OPCODE_H

#include "chip8.h"

class Opcode
{
public:
    Opcode();
    static void execute_2NNN(unsigned short opcode, unsigned short stack[], unsigned short& sp, unsigned short& pc);
private:
};

#endif // OPCODE_H
