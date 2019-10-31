#include "isr.hpp"
#include "io.hpp"
#include "../Include/kcstring.hpp"

Function<void(ISR::Registers, ISR::Interrupt, ISR::StackState)> ISR::interrupt_handlers[ISR::interrupt_handler_count];

void initialiseInterrupts () {}

extern "C" void ISR::isr_handler (ISR::Registers regs, ISR::Interrupt int_number, ISR::StackState state) {
    if (int_number < ISR::interrupt_handler_count && ISR::interrupt_handlers[int_number].hasFunction()) {
        interrupt_handlers[int_number](regs, int_number, state);
        return;
    }

    const char* text = "Unhandled INT ";

    SerialPort::writeString(SerialPort::LOG, text, KCString::getLength(text));
    FrameBuffer::writeString(text, KCString::getLength(text), 2, 4);

    char num_text[3] = {0, 0, 0};
    uint8_t num = int_number;

    num_text[2] = (num % 10) + 48;
    num_text[1] = ((num % 100) / 10) + 48;
    num_text[0] = ((num % 1000) / 100) + 48;

    FrameBuffer::writeCell(num_text[0], 2, 4);
    FrameBuffer::writeCell(num_text[1], 2, 4);
    FrameBuffer::writeCell(num_text[2], 2, 4);
    SerialPort::writeDecimal<3, ISR::Interrupt>(SerialPort::LOG, num);
    FrameBuffer::writeCell('\n', 2, 4);
    SerialPort::writeChar(SerialPort::LOG, '\n');
}