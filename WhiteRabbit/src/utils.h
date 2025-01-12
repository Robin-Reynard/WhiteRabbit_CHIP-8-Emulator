#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "chip8.h"

namespace Utils {
    CHIP8::KeyStrokes convert_to_keystroke(QString key);
}

#endif // UTILS_H
