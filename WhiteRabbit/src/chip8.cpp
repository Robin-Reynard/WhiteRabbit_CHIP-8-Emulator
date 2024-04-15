#include "chip8.h"
#include "opcode.h"

using namespace std;

//--- MEMORY
//4096 8-bit memory, partially initialized with fontset
unsigned char memory[4096] {
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

//--- OPCODES
// 35 opcodes possible, all 2bytes long and stored big-endian
unsigned short opcode {};
// Initialized to 0x200 (512) as everything before that in memory is assigned to fontset
unsigned short program_counter {0x200};

//--- REGISTERS
//16 8-bit registers V0 to VF
unsigned char V[16] {};
//Address register, 12 bits wide.
unsigned short I {};

//---STACK
unsigned short stack[16]{};
unsigned short stack_pointer {};

//--- TIMERS
//Counts down from 60Hz to 0
unsigned short delay_timer{};
//Counts down from 60Hz to 0; beeping when value is non-zero
unsigned short sound_timer{};

//--- INPUT
//Done via hex keyboard (16 keys from 0 to F).
unsigned char keys[16] {};


CHIP8::CHIP8()
{
    cout << "Init CHIP8" << endl;
}

void CHIP8::emulate_cycle(){
    opcode = 0x2001;
    cout << stack[stack_pointer] << endl;
    cout << stack_pointer << endl;
    cout << program_counter << endl;
    cout << "Executing" << endl;
    Opcode::execute_2NNN(opcode, stack, stack_pointer, program_counter);

    cout << stack[stack_pointer] << endl;
    cout << stack_pointer << endl;
    cout << program_counter << endl;
    /*print_as_byte(memory[program_counter]);
    print_as_byte(memory[program_counter + 1]);
    //Fetch opcode
    opcode = memory[program_counter] << 8 | memory[program_counter + 1];
    print_as_byte(opcode);

    //Decode opcode
    switch(opcode & 0xF000){
    case 0x0000:
        break;
    case 0x1000:
        program_counter = opcode & 0x0FFF;
        break;
    case 0x2000:
        stack[stack_pointer] = program_counter;
        stack_pointer++;
        program_counter = opcode & 0x0FFF;
        break;

    case 0xA000:
        I = opcode & 0x0FFF;
        program_counter += 2;
        break;
    default:
        printf ("Unknown opcode: 0x%X\n", opcode);
    }






    // Update timers
    if(delay_timer > 0){
        --delay_timer;
    }
    if(sound_timer > 0)
    {
        if(sound_timer == 1){
            printf("BEEP!\n");}
        --sound_timer;
    }*/
}

void CHIP8::load_program(const string file_path){
    cout << "Ready to load program " << file_path << endl;
    char data {};
    int index {0};

    ifstream input_file(file_path, ios::binary);

    if(input_file){
        while(input_file.good() && !input_file.eof()){
            input_file.read (&data,sizeof(char));
            memory[0x200 + index] = data;
            index++;
        }
        input_file.close();
        cout << "Program loaded sucessfully! :D" << endl;
    }
    else{
        cerr << "Could not load program T_T" << endl;
    }
}

void CHIP8::print_as_byte(int number){
    cout << "0x" << hex << number << endl;
}

void CHIP8:: hello(){
    cout << "Hello from CHIP8" << endl;
}
