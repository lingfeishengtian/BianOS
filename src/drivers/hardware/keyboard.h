#define KBD_DATA_PORT   0x60

/** read_scan_code:
 * Reads the scan code from the keyboard data port
 * 
 * @return Returns the scan code found.
 */
unsigned char read_scan_code(void);

/** keyboard_scan_code_to_ascii:
 * Translates keyboard scan codes using the default US keyboard layout.
 * 
 * @param scan_code The scan code received.
 * @return ASCII value
 */
unsigned char keyboard_scan_code_to_ascii(unsigned char scan_code);