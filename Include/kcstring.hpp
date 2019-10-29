#ifndef INCLUDE_KCSTRING_H
#define INCLUDE_KCSTRING_H

#include "stdint.h"

namespace KCString {
    // Returns length of string without ending_byte
    size_t getLength (const char* str, uint8_t ending_byte=0);

    size_t getLengthWithEnding (const char* str, uint8_t ending_byte=0);


};

#endif