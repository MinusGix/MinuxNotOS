#include "io.hpp"
#include "general_assembly.hpp"
#include "descriptor_tables.hpp"
#include "../Include/kcstring.hpp"
#include "isr.hpp"
/* To remind myself how the stack is structured until I retain the knowledge:
struct Alpha {
    uint32_t a;
    uint32_t b;
    uint32_t c;
};

extern "C" uint32_t test_func (Alpha a, Alpha b);

asm:
global test_func
; stack: 
;        [esp + 24] b.c
;        [esp + 20] b.b
;        [esp + 16] b.a

;        [esp + 12] a.c
;        [esp + 8 ] a.b
;        [esp + 4 ] a.a
;        [esp     ] return pointer
test_func:
    mov eax, [esp + 16]
    ret


*/

extern "C" void kmain (uint32_t stack_position, uint32_t stack_size) {
    init_descriptor_tables();

    // Enable interrupts again
    __asm__ volatile ("sti");

    // Remap the PIC interrupts to the correct places.
    PIC::remapPIC();
    outbyte(PIC::PIC1::data, 0b11111101);
    outbyte(PIC::PIC2::data, 0b11111111);

    FrameBuffer::setCursorPosition(0, 0);

    Keyboard::initialise();


    char* alpha = "Starting up";
    FrameBuffer::writeString(alpha, KCString::getLength(alpha), 2, 8);

    if (areInterruptsEnabled()) {
        FrameBuffer::writeCell('1', 3, 8);
    } else {
        FrameBuffer::writeCell('0', 3, 8);
    }

    SerialPort::configureBaudRate(SerialPort::COM1, 0x0006);
    SerialPort::configureLine(SerialPort::COM1);
    SerialPort::writeString(SerialPort::COM1, alpha, 6);

    SerialPort::writeChar(SerialPort::COM1, '\n');
    SerialPort::writeDecimal<10, uint32_t>(SerialPort::COM1, stack_position);
    SerialPort::writeChar(SerialPort::COM1, '-');
    SerialPort::writeDecimal<10, uint32_t>(SerialPort::COM1, stack_size);
    SerialPort::writeChar(SerialPort::COM1, '\n');

    __asm__ volatile ("int $0x3");
    __asm__ volatile ("int $0x4");
}