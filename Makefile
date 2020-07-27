# Make file created to simplify building process

# declare our source and output folders
OUTPUT = build
SOURCE = src

# declare filenames before wildcarding in order to add source folder prefix
C_FILES = $(addprefix ${SOURCE}/, drivers/*.c kernel/*.c kernel/gdt/*.c)
C_HEADERS = $(addprefix ${SOURCE}/, drivers/*.h kernel/*.h kernel/gdt/*.h)

# wildcard to find all c source and header files required to build
C_SOURCES = $(wildcard ${C_FILES})
HEADERS = $(wildcard ${C_HEADERS})

# generate a list of all the compiled files
OBJ = ${C_SOURCES:${SOURCE}/%.c=${OUTPUT}/%.o} 

# do not delete build output folders if make is stopped abruptly
.PRECIOUS: $(OUTPUT)/. $(OUTPUT)%/.

# find out if the OS is Mac
uname = $(shell uname -s)
is_darwin = $(filter Darwin,$(uname))

# declare our compiler and debugger depending on the OS
CC = $(if $(is_darwin), i386-elf-gcc, gcc)
GDB = gdb
LD = $(if $(is_darwin), i386-elf-ld, ld)
ISO_MAKER = $(if $(is_darwin), mkisofs, genisoimage)

# a BUNCH of flags required in order for our compiled files to not have unnecessary extra code
# ALSO treat all warnings as errors
# also build with i386 (x32)
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LD_FLAGS = -T link.ld -melf_i386

# default: build the iso file
os.iso: $(OUTPUT)/kernel.elf
	cp -r $(SOURCE)/iso $(OUTPUT)/iso
	cp $^ $(OUTPUT)/iso/boot/kernel.elf
	${ISO_MAKER} -R                                        \
                    -b boot/grub/stage2_eltorito              \
                    -no-emul-boot                             \
                    -boot-load-size 4                         \
                    -A os                                     \
                    -input-charset utf8                       \
                    -quiet                                    \
                    -boot-info-table                          \
                    -o $@                                     \
                    $(OUTPUT)/iso

# a bunch of extra targets to create the build folders
$(OUTPUT)/.: 
	mkdir -p $@

$(OUTPUT)%/.: 
	mkdir -p $@

# kernel
$(OUTPUT)/kernel.elf: $(OUTPUT)/loader.o $(OUTPUT)/kernel/gdt/gdt_flush.o $(OBJ) 
	${LD} ${LD_FLAGS} $^ -o $@

# run target
run: os.iso
	qemu-system-i386 -boot d -cdrom os.iso -m 10240 -serial stdio

# qemu debug to monitor registers, memory, etc. However, there is no serial output to stdio.
qemu-monitor: os.iso
	qemu-system-i386 -boot d -cdrom os.iso -m 10240 -monitor stdio

.SECONDEXPANSION:
# Generic rules for wildcards
$(OUTPUT)/%.o: ${SOURCE}/%.c ${HEADERS} | $$(@D)/.
	${CC} ${CFLAGS} -c $< -o $@

.SECONDEXPANSION:
$(OUTPUT)/%.o: ${SOURCE}/%.s | $$(@D)/.
	nasm $< -f elf -o $@

.SECONDEXPANSION:
$(OUTPUT)/%.bin: check_os ${SOURCE}/%.asm | $$(@D)/.
	nasm $< -f bin -o $@

# remove build folder and iso output
clean:
	rm -rf build os.iso
	#rm -rf *.bin *.dis *.o os-image.bin *.elf
	#rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
