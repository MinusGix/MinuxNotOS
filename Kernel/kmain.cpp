#include "io.hpp"
#include "general_assembly.hpp"
#include "descriptor_tables.hpp"
#include "context.hpp"
#include "../Include/kcstring.hpp"

extern "C" void kmain () {
    init_descriptor_tables();

    // Enable interrupts again
    __asm__ volatile ("sti");

    // Remap the PIC interrupts to the correct places.
    PIC::remapPIC();
    outbyte(PIC::PIC1::data, 0b11111101);
    outbyte(PIC::PIC2::data, 0b11111111);

    FrameBuffer::setCursorPosition(0, 0);
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

    __asm__ volatile ("int $0x3");
    __asm__ volatile ("int $0x4");
}