#include <iostream>
#include "ChipSystem.h"
using namespace std;

int main() {
    cout << "hello there" << endl;
    ChipSystem chip8system;
    

   //Setup graphics
   //Setup input

   //Init chip8
   chip8system.initialize();
   //Load game

   ///while (true){
    //Emulate cycle
    chip8system.runCycle();
    // If the draw flag is set, update the screen
        //Draw graphics

    // Store key press state (Press and Release)
    //myChip8.setKeys();
   //}
   
   return 0;
}