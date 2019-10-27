; A file for general assembly functions that are exported. They might get their own files... someday

global gdt_flush
gdt_flush:
    mov eax, [esp + 4] ; Get the pointer to GDT
    lgdt [eax]

    mov ax, 0x10 ; Offset in the GDT to our data segment (2*sizeof(gdtentry))
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ; Each GDT entry is 8 bytes, kernel code descriptor is the second segment, so it's offset is 0x08
    ; Changes cs implicitly
    jmp 0x08:.flush ; 8 is offset to code segment, it is a far jump
.flush:
    ret

global idt_flush
idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
    ret