# BianOS
A simple OS(if you even count it as an OS) to test out os dev.

### TODO
- Build a page frame allocater
- Create kmalloc and kfree
- Write better documentation recent changes
- Improve Bochs support

# Building
Building BianOS is fairly simple, setup your dependencies and execute a single command.

## Dependencies
I do not condone building this OS on Windows or any other non-UNIX based OS system.
Building on Windows is a pain and from personal experience doesn't work well.

**Required**
- gcc: building and compiling c files
- genisoimage/mkisofs: generating the iso image
- ld: linking all the files together
- nasm: building and compiling assembly files
- make: Makefiles

**Optional**
- gdb: debugging
- qemu-system-i386: running the OS in a virtual machine

## Arch
Command for arch users:
```sh
sudo pacman -S qemu qemu-arch-extra gcc base-devel nasm cdrtools gdb
```

## MacOS
Mac users should have brew installed before starting to attempt compiling on mac.
Run these commands to install 32 bit elf compiling utilities.

```shell
brew tap nativeos/i386-elf-toolchain
brew install i386-elf-binutils i386-elf-gcc
```

Then run the following commands to install nasm, mkisofs, and qemu.

```shell
brew install nasm cdrtools qemu
```

## Make
Assuming you understand how to use basic terminal commands, cd into the root directory and just run ```make``` which should create an os.iso file in the root directory and also a build folder.
You can run ```make run``` to automatically build and launch the os from qemu.
Additionally, ```make clean``` can be run to remove the build files and have fresh source code.

# Process of Booting
The ISO uses legacy grub so the OS is backwards-compatible.

GRUB initializes 32 bit protected mode and loads up the kernel from the specified loader label from loader.s.

Loader then initializes basic identity mapped PSE paging to allow for basic initialization of the GDT, IDT, debugging drivers, etc.
