#include "utils.h"

namespace Utils {
    CHIP8::KeyStrokes convert_to_keystroke(QString key){
        key = key.toUpper();
        if(key == "0"){
            return CHIP8::key_0;
        }
        else if(key == "1"){
            return CHIP8::key_1;
        }
        else if(key == "2"){
            return CHIP8::key_2;
        }
        else if(key == "3"){
            return CHIP8::key_3;
        }
        else if(key == "4"){
            return CHIP8::key_4;
        }
        else if(key == "5"){
            return CHIP8::key_5;
        }
        else if(key == "6"){
            return CHIP8::key_6;
        }
        else if(key == "7"){
            return CHIP8::key_7;
        }
        else if(key == "8"){
            return CHIP8::key_8;
        }
        else if(key == "9"){
            return CHIP8::key_9;
        }
        else if(key == "0"){
            return CHIP8::key_0;
        }
        else if(key == "A"){
            return CHIP8::key_A;
        }
        else if(key == "B"){
            return CHIP8::key_B;
        }
        else if(key == "C"){
            return CHIP8::key_C;
        }
        else if(key == "D"){
            return CHIP8::key_D;
        }
        else if(key == "E"){
            return CHIP8::key_E;
        }
        else{
            return CHIP8::key_F;
        }
    }

    void register_key_press(QString key, CHIP8* chip8){
        if(key == "0"){
            chip8->press_key(CHIP8::KeyStrokes::key_0);}
        else if (key == "1"){
            chip8->press_key(CHIP8::KeyStrokes::key_1);}
        else if (key == "2")        {
            chip8->press_key(CHIP8::KeyStrokes::key_2);}
        else if (key == "3"){
            chip8->press_key(CHIP8::KeyStrokes::key_3);}
        else if (key == "4"){
            chip8->press_key(CHIP8::KeyStrokes::key_4);}
        else if (key == "5"){
            chip8->press_key(CHIP8::KeyStrokes::key_5);}
        else if (key == "6"){
            chip8->press_key(CHIP8::KeyStrokes::key_6);}
        else if (key == "7"){
            chip8->press_key(CHIP8::KeyStrokes::key_7);}
        else if (key == "8"){
            chip8->press_key(CHIP8::KeyStrokes::key_8);}
        else if (key == "9"){
            chip8->press_key(CHIP8::KeyStrokes::key_9);}
        else if (key == "A"){
            chip8->press_key(CHIP8::KeyStrokes::key_A); }
        else if (key == "B"){
            chip8->press_key(CHIP8::KeyStrokes::key_B);}
        else if (key == "C"){
            chip8->press_key(CHIP8::KeyStrokes::key_C); }
        else if (key == "D"){
            chip8->press_key(CHIP8::KeyStrokes::key_D);}
        else if (key == "E"){
            chip8->press_key(CHIP8::KeyStrokes::key_E);}
        else if (key == "F"){
            chip8->press_key(CHIP8::KeyStrokes::key_F); }
    }

    void register_key_release(QString key, CHIP8 *chip8){
        if(key == "0"){
            chip8->release_key(CHIP8::KeyStrokes::key_0);}
        else if (key == "1"){
            chip8->release_key(CHIP8::KeyStrokes::key_1);}
        else if (key == "2"){
            chip8->release_key(CHIP8::KeyStrokes::key_2);}
        else if (key == "3"){
            chip8->release_key(CHIP8::KeyStrokes::key_3);}
        else if (key == "4"){
            chip8->release_key(CHIP8::KeyStrokes::key_4);}
        else if (key == "5"){
            chip8->release_key(CHIP8::KeyStrokes::key_5);}
        else if (key == "6"){
            chip8->release_key(CHIP8::KeyStrokes::key_6);}
        else if (key == "7"){
            chip8->release_key(CHIP8::KeyStrokes::key_7);}
        else if (key == "8"){
            chip8->release_key(CHIP8::KeyStrokes::key_8);}
        else if (key == "9"){
            chip8->release_key(CHIP8::KeyStrokes::key_9);}
        else if (key == "A"){
            chip8->release_key(CHIP8::KeyStrokes::key_A); }
        else if (key == "B"){
            chip8->release_key(CHIP8::KeyStrokes::key_B);}
        else if (key == "C"){
            chip8->release_key(CHIP8::KeyStrokes::key_C); }
        else if (key == "D"){
            chip8->release_key(CHIP8::KeyStrokes::key_D);}
        else if (key == "E"){
            chip8->release_key(CHIP8::KeyStrokes::key_E);}
        else if (key == "F"){
            chip8->release_key(CHIP8::KeyStrokes::key_F); }
    }
}
