#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include "../Include/stdint.h"
/** outbyte:
 * Sends the given data to the given I/O port. Defined in io.s
 *
 * @param port The I/O port to send the data to
 * @param data The data to send to the I/O port
 */
extern "C" void outbyte (uint16_t port, uint8_t data);
/** inbyte:
 * Reads a byte from the given I/O port. Defined in io.s
 *
 * @param port The I/O port to read from
 * @return The read byte
 */
extern "C" uint16_t inbyte (uint16_t port);

// See io_c.c for implementation
class FrameBuffer {
    private:
    FrameBuffer () = delete;

    private:
    // FIXME: This is.. irritating. I can't cast it to a char* if it's static.
    inline static char* memory = (char*)0x000B8000;

    static const uint16_t command_port = 0x3D4;
    static const uint16_t data_port = 0x3D5;

    static const uint8_t high_byte_command = 14;
    static const uint8_t low_byte_command = 15;

    public:
    struct Point {
        uint16_t x;
        uint16_t y;
        Point (uint16_t t_x, uint16_t t_y) : x(t_x), y(t_y) {}
    };
    using Foreground = uint8_t;
    using Background = uint8_t;

    static const uint16_t columns = 80;
    static const uint16_t rows = 80;

    static uint16_t getArea ();

    static void setCursorScan (uint8_t start, uint8_t end);

    static void disableCursor ();

    static void setCursorPosition (uint16_t x, uint16_t y);
    static void setCursorPosition (FrameBuffer::Point point);
    static void setAbsoluteCursorPosition (uint16_t absolute_position);

    static uint16_t getAbsoluteCursorPosition ();
    static FrameBuffer::Point getCursorPosition ();

    static void writeCellAt (uint16_t absolute_position, char chr, FrameBuffer::Foreground foreground, FrameBuffer::Background background);
    static void writeCellBackgroundAt (uint16_t absolute_position, FrameBuffer::Background background);
    static void writeCellForegroundAt (uint16_t absolute_position, FrameBuffer::Foreground foreground);
    static void writeCellCharacterAt (uint16_t absolute_position, char chr);
    static void writeCell (char chr, FrameBuffer::Foreground foreground, FrameBuffer::Background background);
    static void writeString (const char* str, size_t length, FrameBuffer::Foreground foreground, FrameBuffer::Background Background);
};

namespace SerialPort {
    using COMPort = uint16_t;

    const COMPort COM1 = 0x3F8;

    struct LineCommands {
        static const uint8_t enableDLAB = 0x80;
    };

    COMPort getDataPort (COMPort com);
    COMPort getFIFOPort (COMPort com);
    COMPort getLinePort (COMPort com);
    COMPort getModemPort (COMPort com);
    COMPort getLineStatusPort (COMPort com);

    void configureBaudRate (COMPort com, uint16_t divisor);
    // TODO: this should be for more than COM1 (logging)
    void configureLine (COMPort com);
    bool isTransmitFifoEmpty (COMPort com);
    void writeChar (COMPort com, char c);
    void writeString (COMPort com, const char* str, size_t length);
};

namespace PIC {
    // Master PIC
    struct PIC1 {
        // IO Base address
        static const uint16_t address = 0x20;
        static const uint16_t command = address;
        static const uint16_t data = address + 1;

        static const uint16_t start_interrupt = 0x20;
    };
    // Slave pic
    struct PIC2 {
        // IO Base address
        static const uint16_t address = 0xA0;
        static const uint16_t command = address;
        static const uint16_t data = address + 1;

        static const uint16_t start_interrupt = 0x28;
        static const uint16_t end_interrupt = start_interrupt + 7;
    };

    struct Commands {
        static const uint16_t EOI = 0x20;
    };

    extern "C" void sendEOI (uint32_t irq);
};

#endif