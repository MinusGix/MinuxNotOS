#include "io.hpp"
#include "general_assembly.hpp"
#include "descriptor_tables.hpp"

extern "C" void kmain () {
    init_descriptor_tables();

    FrameBuffer::setCursorPosition(0, 0);
    char* alpha = "Starting up";
    FrameBuffer::writeString(alpha, 5);

    SerialPort::configureBaudRate(SerialPort::COM1, 0x0006);
    SerialPort::configureLine(SerialPort::COM1);
    SerialPort::writeString(SerialPort::COM1, alpha, 6);

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
}