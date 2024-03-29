#ifndef INCLUDE_MEMORY_H
#define INCLUDE_MEMORY_H

#include "../Include/stdint.h"

namespace Memory {
    void memset (void* ptr, uint8_t v, size_t size);
};

#endif