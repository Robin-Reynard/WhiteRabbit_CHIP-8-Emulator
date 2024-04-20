#ifndef OPCODE_H
#define OPCODE_H

namespace Opcode {
    void execute_1NNN(unsigned short opcode, unsigned short& pc);
    void execute_2NNN(unsigned short opcode, unsigned short stack[], unsigned short& sp, unsigned short& pc);
}

#endif // OPCODE_H
