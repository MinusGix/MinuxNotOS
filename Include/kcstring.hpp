#ifndef INCLUDE_KCSTRING_H
#define INCLUDE_KCSTRING_H

#include "stdint.h"

namespace KCString {
    // Returns length of string without ending_byte
    size_t getLength (const char* str, uint8_t ending_byte=0) {
        size_t length = 0;
        while (true) {
            if (str[length] == ending_byte) {
                break;
            }
            length++;
        }
        return length;
    }

    size_t getLengthWithEnding (const char* str, uint8_t ending_byte=0) {
        return getLength(str, ending_byte) + 1;
    }


};

#endif