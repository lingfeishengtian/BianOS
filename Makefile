# Make file created to simplify building process
OUTPUT = build
SOURCE = src

C_FILES = $(addprefix ${SOURCE}/, kernel/*.c)
C_HEADERS = $(addprefix ${SOURCE}/, kernel/*.h)

C_SOURCES = $(wildcard ${C_FILES})
HEADERS = $(wildcard ${C_HEADERS})

OBJ = ${C_SOURCES:${SOURCE}/%.c=${OUTPUT}/%.o} 

.PRECIOUS: $(OUTPUT)/. $(OUTPUT)%/.


CC = gcc
GDB = gdb

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LD_FLAGS = -T link.ld -melf_i386

os.iso: $(OUTPUT)/kernel.elf
	cp -r $(SOURCE)/iso $(OUTPUT)/iso
	cp $^ $(OUTPUT)/iso/boot/kernel.elf
	genisoimage -R                                        \
                    -b boot/grub/stage2_eltorito             \
                    -no-emul-boot                             \
                    -boot-load-size 4                         \
                    -A os                                     \
                    -input-charset utf8                       \
                    -quiet                                    \
                    -boot-info-table                          \
                    -o $@                                     \
                    $(OUTPUT)/iso
$(OUTPUT)/.: 
	mkdir -p $@

$(OUTPUT)%/.: 
	mkdir -p $@

$(OUTPUT)/kernel.bin: $(OUTPUT)/kernel/kernel_entry.o ${OBJ}
	ld ${LD_FLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
$(OUTPUT)/kernel.elf: $(OUTPUT)/loader.o $(OBJ) 
	ld ${LD_FLAGS} $^ -o $@

run: os.iso
	qemu-system-i386 -boot d -cdrom os.iso -m 10240

qemu-monitor: os.iso
	qemu-system-i386 -boot d -cdrom os.iso -m 10240 -monitor stdio

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

.SECONDEXPANSION:
# Generic rules for wildcards
$(OUTPUT)/%.o: ${SOURCE}/%.c ${HEADERS} | $$(@D)/.
	${CC} ${CFLAGS} -c $< -o $@

.SECONDEXPANSION:
$(OUTPUT)/%.o: ${SOURCE}/%.s | $$(@D)/.
	nasm $< -f elf -o $@

.SECONDEXPANSION:
$(OUTPUT)/%.bin: ${SOURCE}/%.asm | $$(@D)/.
	nasm $< -f bin -o $@

clean:
	rm -rf build os.iso
	#rm -rf *.bin *.dis *.o os-image.bin *.elf
	#rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
