OBJECTS = build/Kernel/loader.o build/Kernel/io.o build/Kernel/io_c.o build/Kernel/kmain.o build/Kernel/general_assembly.o build/Kernel/descriptor_tables.o build/Kernel/memory.o build/Kernel/isr.o build/Kernel/interrupt.o build/Include/kcstring.o
CC = clang++
CFLAGS = -H -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -ffreestanding -O2 -mno-sse -fno-exceptions -fno-rtti -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T link.ld -melf_i386 -nostdlib
AS = nasm
ASFLAGS = -f elf
GRUB_IMAGE = boot/grub/stage2_eltorito

# see: https://wiki.osdev.org/Calling_Global_Constructors#GNU_Compiler_Collection_-_System_V_ABI
CRTI_OBJ=build/Kernel/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=build/Kernel/crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJECTS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

all: build/kernel.elf

build/:
	mkdir -p build

build/Kernel/: build/
	mkdir -p build/Kernel

build/Include/: build/
	mkdir -p build/Include


build/kernel.elf: build/Kernel/ $(OBJ_LINK_LIST)
	mkdir -p build/Kernel
	ld $(LDFLAGS) $(OBJ_LINK_LIST) -o build/kernel.elf

build/os.iso: build/kernel.elf
	mkdir -p build
	cp build/kernel.elf iso/boot/kernel.elf
	genisoimage -rock                           \
				-eltorito-boot $(GRUB_IMAGE)    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o build/os.iso                 \
				iso

run: build/os.iso
	bochs -f bochsrc.txt -q

build/Kernel/%.o: build/Kernel/ Kernel/%.cpp
	$(CC) $(CFLAGS) $< -o $@

build/Include/%.o: build/Include/ Include/%.cpp
	$(CC) $(CFLAGS) $< -o $@

build/%.o: %.cpp
	$(CC) $(CFLAGS)  $< -o $@

build/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf build/