#include "isr.hpp"
#include "io.hpp"
#include "../Include/kcstring.hpp"

uint8_t toIRQLine (uint32_t int_number) {
    return int_number - 13;
}

extern "C" void isr_handler (Registers regs, uint32_t int_number, StackState state) {
    const char* text = "Unhandled INT ";

    SerialPort::writeString(SerialPort::COM1, text, KCString::getLength(text));
    FrameBuffer::writeString(text, KCString::getLength(text), 2, 4);

    char num_text[3] = {0, 0, 0};
    uint8_t num = int_number;

    num_text[2] = (num % 10) + 48;
    num_text[1] = ((num % 100) / 10) + 48;
    num_text[0] = ((num % 1000) / 100) + 48;

    FrameBuffer::writeCell(num_text[0], 2, 4);
    FrameBuffer::writeCell(num_text[1], 2, 4);
    FrameBuffer::writeCell(num_text[2], 2, 4);
    SerialPort::writeDecimal<3, uint8_t>(SerialPort::COM1, num);

    if (int_number == 33) {
        FrameBuffer::writeCell('-', 2, 4);
        SerialPort::writeChar(SerialPort::COM1, '-');
        uint8_t v = Keyboard::readScanCode();
        PIC::sendEOI(int_number);

        num_text[2] = (v % 10) + 48;
        num_text[1] = ((v % 100) / 10) + 48;
        num_text[0] = ((v % 1000) / 100) + 48;

        FrameBuffer::writeCell(num_text[0], 2, 4);
        FrameBuffer::writeCell(num_text[1], 2, 4);
        FrameBuffer::writeCell(num_text[2], 2, 4);
        SerialPort::writeDecimal<3, uint8_t>(SerialPort::COM1, v);
    }

    FrameBuffer::writeCell('\n', 2, 4);
    SerialPort::writeChar(SerialPort::COM1, '\n');
}