#include "chip8.h"
using namespace std;

CHIP8::CHIP8()
    : memory {
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
          },
      opcode {}, program_counter {0x200},
      V {}, I {},
      stack {}, stack_pointer {},
      delay_timer {}, sound_timer {},
      keys {}, graphics {}
{
    cout << "Init CHIP8" << endl;
}

void CHIP8::emulate_cycle(){
    //Fetch opcode
    opcode = memory[program_counter] << 8 | memory[program_counter + 1];
    print_as_byte(opcode);

    //Decode opcode

    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x0FFF){
                case 0x0E0:
                    Opcode::execute_00E0(program_counter, graphics); break;
                default:
                    Opcode::execute_0NNN(program_counter); break;
            } break;
        case 0x1000:
            Opcode::execute_1NNN(opcode, program_counter); break;
        case 0x2000:
            Opcode::execute_2NNN(opcode, program_counter, stack, stack_pointer); break;
        case 0x3000:
            Opcode::execute_3XNN(opcode, program_counter, V); break;
        case 0x4000:
            Opcode::execute_4XNN(opcode, program_counter, V); break;
        case 0x5000:
            Opcode::execute_5XY0(opcode, program_counter,V); break;
        case 0x6000:
            Opcode::execute_6XKK(opcode, program_counter, V); break;
        case 0x7000:
            Opcode::execute_7XKK(opcode, program_counter, V); break;
        case 0x8000:
            switch (opcode & 0x000F){
                case 0:
                    Opcode::execute_8XY0(opcode, program_counter, V); break;
                case 1:
                    Opcode::execute_8XY1(opcode, program_counter, V); break;
                case 2:
                    Opcode::execute_8XY2(opcode, program_counter, V); break;
                case 3:
                    Opcode::execute_8XY3(opcode, program_counter, V); break;
                case 4:
                    Opcode::execute_8XY4(opcode, program_counter, V); break;
                case 5:
                    Opcode::execute_8XY5(opcode, program_counter, V); break;
                case 6:
                    Opcode::execute_8XY6(opcode, program_counter, V); break;
                case 7:
                    Opcode::execute_8XY7(opcode, program_counter, V); break;
                case E:
                    Opcode::execute_8XYE(opcode, program_counter, V); break;
                default:
                    cerr << "No such opcode " + opcode << endl;
            } break;
        case 0x9000:
            Opcode::execute_9XY0(opcode, program_counter, V); break;
        case 0xA000:
            Opcode::execute_ANNN(opcode, program_counter, I); break;
        case 0xB000:
            Opcode::execute_BNNN(opcode, program_counter, V[0]); break;
        case 0xC000:
            Opcode::execute_CXKK(opcode, program_counter, V); break;
        case 0xD000:
            Opcode::execute_DXYN(opcode, program_counter, memory, V, I, graphics); break;
        case 0xE000:
            switch(opcode & 0x00FF){
                case 0x9E:
                    Opcode::execute_EX9E(opcode, program_counter, V, keys); break;
                case 0xA1:
                    Opcode::execute_EXA1(opcode, program_counter, V, keys); break;
                default:
                    cerr << "No such opcode " + opcode << endl;
            } break;
        case 0xF000:
            switch(opcode & 0x00FF){
                case 0x07:
                    Opcode::execute_FX07(opcode, program_counter, V, delay_timer); break;
                case 0x0A:
                    Opcode::execute_FX0A(opcode, program_counter, V, keys); break;
                case 0x15:
                    Opcode::execute_FX15(opcode, program_counter, V, delay_timer); break;
                case 0x18:
                    Opcode::execute_FX18(opcode, program_counter, V, sound_timer); break;
                case 0x1E:
                    Opcode::execute_FX1E(opcode, program_counter, V, I); break;
                case 0x29:
                    Opcode::execute_FX29(opcode, program_counter, V, I); break;
                case 0x33:
                    Opcode::execute_FX33(opcode, program_counter, V, I, memory); break;
                case 0x55:
                    Opcode::execute_FX55(opcode, program_counter, V, I, memory); break;
                case 0x65:
                    Opcode::execute_FX65(opcode, program_counter, V, I, memory); break;
                default:
                    cerr << "No such opcode " + opcode << endl;
            } break;
        default:
            cerr << "No such opcode " + opcode << endl;
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
    }
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
