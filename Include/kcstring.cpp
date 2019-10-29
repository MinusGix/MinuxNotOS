#include "kcstring.hpp"

size_t KCString::getLength (const char* str, uint8_t ending_byte) {
    size_t length = 0;
    while (true) {
        if (str[length] == ending_byte) {
            break;
        }
        length++;
    }
    return length;
}

size_t KCString::getLengthWithEnding (const char* str, uint8_t ending_byte) {
    return getLength(str, ending_byte) + 1;
}