#include "isr.hpp"
#include "io.hpp"
#include "../Include/kcstring.hpp"

extern "C" void isr_handler (Registers regs) {
    const char* text = "Unhandled INT ";
    char* text = KCString::toDecimal(regs.int_number);
    SerialPort::writeString(SerialPort::COM1, text, KCString::getLength(text));
}