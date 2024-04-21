#ifndef OPCODE_H
#define OPCODE_H

namespace opcode {
    typedef unsigned short u_short;
    typedef unsigned char u_char;
    void execute_0NNN();
    void execute_00E0(u_char& graphics);
    void execute_1NNN(u_short opcode, u_short& pc);
    void execute_2NNN(u_short opcode, u_short stack[], u_short& sp, u_short& pc);
    void execute_3XNN(u_short opcode, u_short V[], u_short& pc);
    void execute_4XNN(u_short opcode, u_short V[], u_short& pc);
    void execute_5XY0(u_short opcode, u_short V[], u_short& pc);
}

#endif // OPCODE_H
