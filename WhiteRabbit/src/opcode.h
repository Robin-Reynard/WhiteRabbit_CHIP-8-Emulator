#ifndef OPCODE_H
#define OPCODE_H


class Opcode
{
public:
    Opcode();
    static void execute_2NNN(unsigned short opcode, unsigned short stack[], unsigned short& sp, unsigned short& pc);
};

#endif // OPCODE_H
