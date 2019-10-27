#include "io.hpp"

/* Framebuffer:
    Has 80 columns and 25 rows. The row and column indices start at 0.
    Writing text to the framebuffer is done with memory-mapped I/O (write to that position in memory to edit it.)
    The starting address of the memory-mapped I/O for the frame buffer is 0x000B8000 (0xB8000).
    Divided into 16bit cells. The highest eight bits is the ASCII value of the character, bit 7-4 the background and bit 3-0 the foreground
    Bit:     | 15 - 8 |   7 6 5 4  |   3 2 1 0  |
    Content: | ASCII  | Foreground | Background |

    Colors:
    Black: 0, Blue: 1, Green: 2, Cyan: 3
    Red: 4, Magenta: 5, Brown: 6, Light Grey: 7,
    Dark Grey: 8, Light Blue: 9, Light green: 10
    Light Cyan: 11, Light Red: 12, Light magenta: 13,
    Light brown: 14, White: 15

    Cursor:
    0x3D4 describes the data, while 0x3D5 is for the data.
    The position is 16 bits large, but the out instruction only does 8 bits at a time.
    Thus we have to do the first byte, then the next byte to fully set the position
    ```asm
    ; Tell it we are looking to set 14 (I assume this is to tell it for the first part of the cursor position)
    out 0x3D4, 14
    ; Set value to highest byte of position
    out 0x3D5, 0x00 ; highest byte of 0x0050
    ; Next part
    out 0x3D4, 15
    out 0x3d5, 0x50
    ```
*/

uint16_t FrameBuffer::getArea () {
    return columns * rows;
}

void FrameBuffer::setCursorScan (uint8_t start, uint8_t end) {
    outbyte(command_port, 10);
    outbyte(data_port, (inbyte(data_port) & 0xC0) | start);

    outbyte(command_port, 11);
    outbyte(data_port, (inbyte(data_port) & 0xE0) | end);
}

void FrameBuffer::disableCursor () {
    // 10 = low cursor shape register
    outbyte(command_port, 10);
    // bits 6-7 unused, bit 5 disables cursor, bits 0-4 control the shape
    outbyte(data_port, 0x20);
}

void FrameBuffer::setCursorPosition (uint16_t x, uint16_t y) {
    setAbsoluteCursorPosition(y * columns + x);
}
void FrameBuffer::setCursorPosition (FrameBuffer::Point point) {
    setCursorPosition(point.x, point.y);
}
void FrameBuffer::setAbsoluteCursorPosition (uint16_t absolute_position) {
    if (absolute_position >= getArea()) {
        // Fail silently.
        return;
    }

    outbyte(command_port, high_byte_command);
    outbyte(data_port, ((absolute_position >> 8) & 0x00FF)); // Isolate most significant byte

    outbyte(command_port, low_byte_command);
    outbyte(data_port, absolute_position & 0x00FF);
}

uint16_t FrameBuffer::getAbsoluteCursorPosition () {
    uint16_t pos = 0;

    outbyte(command_port, 15);
    pos |= inbyte(data_port);
    outbyte(command_port, 0x0E);
    pos |= ((uint16_t)inbyte(data_port)) << 8;

    return pos;
}
FrameBuffer::Point FrameBuffer::getCursorPosition () {
    uint16_t pos = getAbsoluteCursorPosition();
    uint16_t y = pos % columns;
    uint16_t x = pos - y;
    // TODO: check this code
    return FrameBuffer::Point(x, y);
}

void FrameBuffer::writeCellAt (uint16_t absolute_position, char chr, FrameBuffer::Foreground foreground, FrameBuffer::Background background) {
    if (absolute_position >= getArea()) {
        // Fail silently.
        return;
    }
    // [chr byte][foreground 4bits][background 4bits]
    ((char*)memory)[absolute_position * 2] = chr; // Set first byte to the character
    ((char*)memory)[absolute_position * 2 + 1] = ((foreground & 0x0F) << 4) | (background & 0x0F);
}
void FrameBuffer::writeCell (char chr, FrameBuffer::Foreground foreground, FrameBuffer::Background background) {
    uint16_t pos = getAbsoluteCursorPosition();

    writeCellAt(pos, chr, foreground, background);

    if (chr == '\n') {
        pos += columns;
    } else {
        pos++;
    }

    setAbsoluteCursorPosition(pos);
}
void FrameBuffer::writeString (const char* str, size_t length) {
    for (size_t i = 0; i < length; i++) {
        writeCell(str[i], 2, 8);
    }
}


/* Serial Port:
    The first data that needs to be sent to the port is configuration data.
    The hardware devices must agree on a couple things to talk to each other:
        Baud/bit rate
        If any error checking is used (parity bit, stop bits, etc)
        The number of bits that represent a unit of data (data bits)

    All of the I/O ports a relative to the data port. All serial ports (COM1, COM2, COM3, COM4) have their ports in the same order
    but they start at different values.
*/

SerialPort::COMPort SerialPort::getDataPort (SerialPort::COMPort com) {
    return com;
}
SerialPort::COMPort SerialPort::getFIFOPort (SerialPort::COMPort com) {
    return com + 2;
}
SerialPort::COMPort SerialPort::getLinePort (SerialPort::COMPort com) {
    return com + 3;
}
SerialPort::COMPort SerialPort::getModemPort (SerialPort::COMPort com) {
    return com + 4;
}
SerialPort::COMPort SerialPort::getLineStatusPort (SerialPort::COMPort com) {
    return com + 5;
}

void SerialPort::configureBaudRate (SerialPort::COMPort com, uint16_t divisor) {
    outbyte(getLinePort(com), SerialPort::LineCommands::enableDLAB);

    outbyte(getDataPort(com), (divisor >> 8) & 0x00FF);
    outbyte(getDataPort(com), divisor & 0x00FF);
}
void SerialPort::configureLine (SerialPort::COMPort com) {
    /*
    | 7 | 6 | 5 4 3 | 2 | 1 0 |
    | d | b | prty  | s | dl  |
    d = DLAB enabled?, b = Break control enabled?
    prty = #Parity Bits, s = #stop bits (0=1, 1=2)
    dl = length
    */
   outbyte(getLinePort(com), 0b00000011);
}
bool SerialPort::isTransmitFifoEmpty (SerialPort::COMPort com) {
    return inbyte(getLineStatusPort(com)) & 0b00100000;
}
void SerialPort::writeChar (SerialPort::COMPort com, char c) {
    while (!isTransmitFifoEmpty(com));
    outbyte(com, c);
}
void SerialPort::writeString (SerialPort::COMPort com, const char* str, size_t length) {
    for (size_t i = 0; i < length; i++) {
        writeChar(com, str[i]);
    }
}

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

// IO Port commands

// Tells the serial port to expect first the highest 8 bits on the data port
// then the lowest 8 bits will follow
#define SERIAL_LINE_ENABLE_DLAB 0x80

/** serial_configure_baud_rate:
 * Sets the speed of the data being sent. The default speed of a serial port is
 * 115,200 bits/s. The argument is a divisor of that number.
 * The resulting speed becomes 115,200/divisor bits/s
 *
 * @param com The COM port to configure
 * @param divisor
 */
void serial_configure_baud_rate (uint16_t com, uint16_t divisor) {
    outbyte(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);

    outbyte(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outbyte(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

/** serial_configure_line:
 * Configures the line of the serial port.
 * The port is set to have a data length of 8 bits, no parity bits,
 * one stop bit and break control disabled.
 *
 * @param com The serial port to configure
 */
void serial_configure_line (uint16_t com) {
    /*
    | 7 | 6 | 5 4 3 | 2 | 1 0 |
    | d | b | prty  | s | dl  |
    d = DLAB enabled?, b = Break control enabled?
    prty = #Parity Bits, s = #stop bits (0=1, 1=2)
    dl = length
    */
   outbyte(SERIAL_LINE_COMMAND_PORT(com), 0b00000011);
}

/** serial_is_transmit_fifo_empty:
 * Checks whether the transmit FIFO queue is empty or not for the given port
 *
 * @param com The COM port
 * @return 0 if the transmit FIFO queue is not epty
 *         1 if the transmit FIFO queue is empty
 */
int serial_transmit_fifo_empty (uint32_t com) {
    return inbyte(SERIAL_LINE_STATUS_PORT(com)) & 0b00100000;
}

int serial_write (uint32_t com, const char* str, size_t length) {
    for (size_t i = 0; i < length; i++) {
        while (!serial_transmit_fifo_empty(com));
        outbyte(SERIAL_COM1_BASE, str[i]);
    }

    return 0;
}