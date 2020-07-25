/** debugger.h
 * Kernel utility to assist with debugging on virtual machines.
 * Uses serial COM1 port to debug for virtual machines.
 */

/** initialize_serial_debugging:
 * The debugger requires you MUST initialize the serial COM port before writing to it.
 * Sets the baud, break control, parity, and stop bits and configures the line.
 */
void initialize_serial_debugging();

/** debug_write:
 * Writes to the serial COM1 port, in QEMU, this can be routed to the console. (Which is what my makefile does)
 * 
 * @param str The string to be written
 */
void debug_write(char* str);

/** debug_writeln:
 * Writes to the serial COM1 port with an additional new line character.
 * 
 * @param str The string to be written
 */
void debug_writeln(char* str);