#ifndef MOCKOPCODE_H
#define MOCKOPCODE_H
using namespace std;
typedef unsigned short u_short;
typedef unsigned char byte;
void execute_0NNN(u_short& pc) {cout << "Executing 0NNN" << endl;}
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
void execute_9XY0(u_short opcode, u_short& pc, byte V[]);
void execute_ANNN(u_short opcode, u_short& pc, u_short& I);
void execute_BNNN(u_short opcode, u_short& pc, byte& V0);
void execute_CXKK(u_short opcode, u_short& pc, byte V[]);
void execute_DXYN(u_short opcode, u_short& pc, byte memory[], byte V[], u_short& I, byte graphics[]);
void execute_EX9E(u_short opcode, u_short& pc, byte V[], byte keys[]);
void execute_EXA1(u_short opcode, u_short& pc, byte V[], byte keys[]);
void execute_FX07(u_short opcode, u_short& pc, byte V[], byte& delay_timer);
void execute_FX0A(u_short opcode, u_short& pc, byte V[], byte keys[]);
void execute_FX15(u_short opcode, u_short& pc, byte V[], byte& delay_timer);
void execute_FX18(u_short opcode, u_short& pc, byte V[], byte& sound_timer);
void execute_FX1E(u_short opcode, u_short& pc, byte V[], byte& I);
void execute_FX29(u_short opcode, u_short& pc, byte V[], byte& I);
void execute_FX33(u_short opcode, u_short& pc, byte V[], byte& I, byte memory[]);
void execute_FX55(u_short opcode, u_short& pc, byte V[], byte& I, byte memory[]);
void execute_FX65(u_short opcode, u_short& pc, byte V[], byte& I, byte memory[]);

#endif // MOCKOPCODE_H
