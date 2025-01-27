#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "chip8.h"

namespace Utils {
    CHIP8::KeyStrokes convert_to_keystroke(QString key);
    void register_key_press(QString key, CHIP8* chip8);
    void register_key_release(QString key, CHIP8* chip8);
}

#endif // UTILS_H
