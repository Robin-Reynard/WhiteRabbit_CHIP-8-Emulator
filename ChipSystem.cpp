#include "ChipSystem.h"

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
    std::ifstream file("/home/robin/Desktop/Chip8 Games/INVADERS", std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        // Get size of file and allocate a buffer to hold the contents
        std::streampos size = file.tellg();
        char *buffer = new char[size];

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        // Load the ROM contents into the Chip8's memory, starting at 0x200
        for (long i = 0; i < size; ++i)
        {
            memory[512 + i] = buffer[i];
        }

        // Free the buffer
        delete[] buffer;
    }
}
void ChipSystem::runCycle()
{
    cout << "1 cycle is being run" << endl;
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc + 1];

    execute_00E0();

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

void ChipSystem::execute_00E0(){
    cout << "Executing 00E0";
}
