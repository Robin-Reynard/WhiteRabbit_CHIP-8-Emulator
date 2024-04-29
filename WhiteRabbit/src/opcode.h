#ifndef OPCODE_H
#define OPCODE_H

namespace Opcode {
    typedef unsigned short u_short;
    typedef unsigned char byte;
    void execute_0NNN(u_short& pc);
    void execute_00E0(u_short& pc, byte graphics[]);
    void execute_1NNN(u_short opcode, u_short& pc);
    void execute_2NNN(u_short opcode, u_short& pc, u_short stack[], byte& sp);
    void execute_3XNN(u_short opcode, u_short& pc, byte V[]);
    void execute_4XNN(u_short opcode, u_short& pc, byte V[]);
    void execute_5XY0(u_short opcode, u_short& pc, byte V[]);
    void execute_6XKK(u_short opcode, u_short& pc, byte V[]);
    void execute_7XKK(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY0(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY1(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY2(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY3(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY4(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY5(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY6(u_short opcode, u_short& pc, byte V[]);
    void execute_8XY7(u_short opcode, u_short& pc, byte V[]);
    void execute_8XYE(u_short opcode, u_short& pc, byte V[]);

    u_short extract_NNN(u_short opcode);
    u_short extract_X(u_short opcode);
    u_short extract_Y(u_short opcode);
}

#endif // OPCODE_H
