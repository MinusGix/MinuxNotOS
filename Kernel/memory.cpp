#include "memory.hpp"

void memset (void* ptr, uint8_t v, size_t size)  {
    for (size_t i = 0; i < size; i++) {
        *(((char*)ptr)+i) = v;
    }
}