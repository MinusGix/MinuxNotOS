#ifndef INCLUDE_ISR_H
#define INCLUDE_ISR_H

#include "../Include/stdint.h"

struct Registers {
    uint32_t ds; // data segment selector
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
} __attribute__((packed));

struct StackState {
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

extern "C" void isr_handler (Registers regs, uint32_t int_number, StackState state);

static inline bool areInterruptsEnabled () {
    unsigned long flags;
    __asm__ volatile ("pushf\n\tpop %0" : "=g"(flags));
    return flags & (1 << 9);
}

#endif