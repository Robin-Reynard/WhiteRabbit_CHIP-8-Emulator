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
}

void CHIP8::load_program(const string file_path){
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

void CHIP8::emulate_cycle(){
    //Fetch opcode
    opcode = memory[program_counter] << 8 | memory[program_counter + 1];
    print_as_byte(opcode);

    // Increment program counter here to avoid code duplication
    program_counter += 2;

    //Decode opcode
    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x0FFF){
                case 0x0E0:
                    Opcode::execute_00E0(graphics);
                    display_graphics_ascii();
                    break;
                case 0x0EE:
                    Opcode::execute_00EE(program_counter, stack_pointer, stack); break;
                default:
                    Opcode::execute_0NNN(); break;
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
            Opcode::execute_6XKK(opcode, V); break;
        case 0x7000:
            Opcode::execute_7XKK(opcode, V); break;
        case 0x8000:
            switch (opcode & 0x000F){
                case 0x0:
                    Opcode::execute_8XY0(opcode, V); break;
                case 0x1:
                    Opcode::execute_8XY1(opcode, V); break;
                case 0x2:
                    Opcode::execute_8XY2(opcode, V); break;
                case 0x3:
                    Opcode::execute_8XY3(opcode, V); break;
                case 0x4:
                    Opcode::execute_8XY4(opcode, V); break;
                case 0x5:
                    Opcode::execute_8XY5(opcode, V); break;
                case 0x6:
                    Opcode::execute_8XY6(opcode, V); break;
                case 0x7:
                    Opcode::execute_8XY7(opcode, V); break;
                case 0xE:
                    Opcode::execute_8XYE(opcode, V); break;
                default:
                    cerr << "No such opcode " + opcode << endl;
            } break;
        case 0x9000:
            Opcode::execute_9XY0(opcode, program_counter, V); break;
        case 0xA000:
            Opcode::execute_ANNN(opcode, I); break;
        case 0xB000:
            Opcode::execute_BNNN(opcode, program_counter, V[0]); break;
        case 0xC000:
            Opcode::execute_CXKK(opcode, V); break;
        case 0xD000:
            Opcode::execute_DXYN(opcode, memory, V, I, graphics);
            display_graphics_ascii();
            break;
        case 0xE000:
            switch(opcode & 0x00FF){
                case 0x9E:
                    Opcode::execute_EX9E(opcode, program_counter, V, keys); break;
                case 0xA1:
                    Opcode::execute_EXA1(opcode, program_counter, V, keys); break;
                default:
                    cerr << "No such opcode " + opcode << endl; break;
            } break;
        case 0xF000:
            switch(opcode & 0x00FF){
                case 0x07:
                    Opcode::execute_FX07(opcode, V, delay_timer); break;
                case 0x0A:
                    Opcode::execute_FX0A(opcode, program_counter, V, keys); break;
                case 0x15:
                    Opcode::execute_FX15(opcode, V, delay_timer); break;
                case 0x18:
                    Opcode::execute_FX18(opcode, V, sound_timer); break;
                case 0x1E:
                    Opcode::execute_FX1E(opcode, V, I); break;
                case 0x29:
                    Opcode::execute_FX29(opcode, V, I); break;
                case 0x33:
                    Opcode::execute_FX33(opcode, V, I, memory); break;
                case 0x55:
                    Opcode::execute_FX55(opcode, V, I, memory); break;
                case 0x65:
                    Opcode::execute_FX65(opcode, V, I, memory); break;
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

void CHIP8::print_as_byte(int number){
    cout << "0x" << hex << number << endl;
}

void CHIP8::display_graphics_ascii(){
    for(int i {0}; i < 2048; i++){
        if(graphics[i] == 0){
            cout << " ";
        }
        else{
            cout << "*";
        }
        if(i % 64 == 0){
            cout << endl;
        }
    }
    cout << endl;
}

bool* CHIP8::get_display(){
    return graphics;
}

void CHIP8::press_key(KeyStrokes keystroke){
    keys[static_cast<int>(keystroke)] = 1;
}

void CHIP8::release_key(KeyStrokes keystroke){
    keys[static_cast<int>(keystroke)] = 0;
}
