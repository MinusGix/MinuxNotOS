#ifndef INCLUDE_DESCRIPTOR_TABLES_H
#define INCLUDE_DESCRIPTOR_TABLES_H

#include "../Include/stdint.h"

namespace GDT {
    struct Entry {
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_middle;
        // access flags, what ring this segment can be used in
        // 7 | 6 5 | 4  | 3 2 1 0 |
        // P | DPL | DT | Type    |
        // P=Is Segment Present, DPL=Privilege Level, Ring 0-3
        // DT=Descriptor Type, Type=Segment type - code segment / data segment
        uint8_t access;
        // 7 | 6 | 5 | 4 | 3 2 1 0                 |
        // G | D | 0 | A | Segment length 19:16?? |
        // G=Granularity (0=1 byte, 1 = 1kbyte)
        // D = Operand size (0=16bit, 1=32bit)
        // 0=Always zero, A=Available for system use (zero)
        uint8_t granularity;
        uint8_t base_high;
    } __attribute__((packed));

    struct Pointer {
        // upper 16 bits of all selector limits
        uint16_t limit;
        // Address of the first GDTEntry
        uint32_t base;
    } __attribute__((packed));
}


namespace IDT {
    struct Entry {
        // Lower bits of address to jump to when this interrupt fires
        uint16_t base_low;
        // Kernel segment selector (???)
        uint16_t selector;
        // Always zero.
        uint8_t always0;
        // 7 | 6 5 | 4 3 2 1 0
        // P | DPL | Always 01110
        // P=entry is present
        // DPL = privilege level
        uint8_t flags;
        uint16_t base_high;
    } __attribute__((packed));

    struct Pointer {
        uint16_t limit;
        // address of fire element in interrupt array
        uint32_t base;
    } __attribute__((packed));
}

void init_descriptor_tables ();

#endif