#ifndef INCLUDE_DESCRIPTOR_TABLES_H
#define INCLUDE_DESCRIPTOR_TABLES_H

#include "../Include/stdint.h"

struct GDTEntry {
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

struct GDTPointer {
    // upper 16 bits of all selector limits
    uint16_t limit;
    // Address of the first GDTEntry
    uint32_t base;
} __attribute__((packed));




struct IDTEntry {
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

struct IDTPointer {
    uint16_t limit;
    // address of fire element in interrupt array
    uint32_t base;
} __attribute__((packed));

extern "C" void isr0 ();
extern "C" void isr1 ();
extern "C" void isr2 ();
extern "C" void isr3 ();
extern "C" void isr4 ();
extern "C" void isr5 ();
extern "C" void isr6 ();
extern "C" void isr7 ();
extern "C" void isr8 ();
extern "C" void isr9 ();
extern "C" void isr10 ();
extern "C" void isr11 ();
extern "C" void isr12 ();
extern "C" void isr13 ();
extern "C" void isr14 ();
extern "C" void isr15 ();
extern "C" void isr16 ();
extern "C" void isr17 ();
extern "C" void isr18 ();
extern "C" void isr19 ();
extern "C" void isr20 ();
extern "C" void isr21 ();
extern "C" void isr22 ();
extern "C" void isr23 ();
extern "C" void isr24 ();
extern "C" void isr25 ();
extern "C" void isr26 ();
extern "C" void isr27 ();
extern "C" void isr28 ();
extern "C" void isr29 ();
extern "C" void isr30 ();
extern "C" void isr31 ();
extern "C" void isr32 ();
extern "C" void isr33 ();
extern "C" void isr34 ();
extern "C" void isr35 ();
extern "C" void isr36 ();
extern "C" void isr37 ();
extern "C" void isr38 ();
extern "C" void isr39 ();
extern "C" void isr40 ();

void init_descriptor_tables ();

#endif