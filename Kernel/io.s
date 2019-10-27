global outbyte ; Make it visible outside the file

; outbyte - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
outbyte:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al ; send the data
    ret


global inbyte

; inbyte - returns a byte from an I/O port
; stack: [esp + 4] The address of the I/O port
;        [esp    ] The return address
inbyte:
    mov dx, [esp + 4]
    in al, dx
    ret