# BianOS
A simple OS(if you even count it as an OS) to test out os dev.

# Process of Booting
The ISO uses legacy grub so the OS is backwards-compatible.

GRUB initializes 32 bit protected mode and loads up the kernel from the specified loader label from loader.s.
