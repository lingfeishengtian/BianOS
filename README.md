# BianOS
A simple OS(if you even count it as an OS) to test out os dev.

# Building
Building BianOS is fairly simple, setup your dependencies and execute a single command.

## Dependencies
Please do not use any OS other than linux or mac for building. Building ELF files on Windows is a pain in the booty.

**Required**
- gcc: building and compiling c files
- genisoimage: generating the iso image
- ld: linking all the files together
- nasm: building and compiling assembly files
- make: Makefiles

**Optional**
- gdb: debugging
- qemu-system-i386: running the OS in a virtual machine

Command for arch users:
```sh
sudo pacman -S qemu qemu-arch-extra gcc base-devel nasm cdrtools gdb
```
## Make
Assuming you understand how to use basic terminal commands, cd into the root directory and just run ```make``` which should create an os.iso file in the root directory and also a build folder.
You can run ```make run``` to automatically build and launch the os from qemu.
Additionally, ```make clean``` can be run to remove the build files and have fresh source code.

# Process of Booting
The ISO uses legacy grub so the OS is backwards-compatible.

GRUB initializes 32 bit protected mode and loads up the kernel from the specified loader label from loader.s.
