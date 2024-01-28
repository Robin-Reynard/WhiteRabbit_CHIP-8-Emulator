#include "ChipSystem.h"
using namespace std;

unsigned short opcode;
unsigned char memory[4096];
unsigned char V[16];        // 8-bit registers, VE is the carry flag
unsigned short I;           // index register
unsigned short pc;          // program counter (from 0x000 to 0xFFF)
unsigned char gfx[64 * 32]; // display
unsigned char delay_timer;
unsigned char sound_timer;
unsigned short stack[16];
unsigned short sp;     // stack pointer
unsigned char key[16]; // keypad
unsigned char fontset[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void ChipSystem::initialize()
{
    cout << "Init!!!!" << endl;
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;

    // Clear display
    // Clear stack
    // Clear registers V0-VF
    // Clear memory

    // Load fontset
    for (int i = 0; i < 80; ++i)
        memory[i] = fontset[i];

    // Reset timers

    // Load program into memory, starting at 0x200
    //  using fopen in binary mode
    // for(int i = 0; i < bufferSize; ++i)
    // memory[i + 512] = buffer[i];
}
void ChipSystem::runCycle()
{
    cout << "1 cycle is being run" << endl;
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc + 1];

    // Decode Opcode
    switch (opcode & 0xF000)
    {
    // Execute Opcode
    case 0x000:
        switch (opcode & 0x000F)
        {
        // 0x00E0: Clears the screen
        case 0x0000:
            cout << "clear screen!" << endl;
            break;
        // 0x00EE: Returns from subroutine
        case 0x000E:
            cout << "return from subroutine!" << endl;
            break;
        default:
            printf("Unknown opcode [0x0000]: 0x%X\n", opcode);
        }
    // ANNN: Sets I to the address NNN
    case 0xA000:
        I = opcode & 0x0FFF;
        pc += 2;
        break;
    default:
        cout << ("Unknown opcode, " + opcode) << endl;
    }

    // Update timers
    if (delay_timer > 0)
    {
        delay_timer--;
    }
    if (sound_timer > 0)
    {
        if (sound_timer == 1)
        {
            cout << "BEEP" << endl;
        }
        sound_timer--;
    }
}
