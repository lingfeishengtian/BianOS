#include <stdint.h>

#define KBD_DATA_PORT   0x60
#define KEYBOARD_INTERRUPT_CODE 0x21

/** read_scan_code:
 * Reads the scan code from the keyboard data port
 * 
 * @return Returns the scan code found.
 */
uint8_t read_scan_code(void);

/** keyboard_scan_code_to_ascii:
 * Translates keyboard scan codes using the default US keyboard layout.
 * 
 * @param scan_code The scan code received.
 * @return ASCII value
 */
uint8_t keyboard_scan_code_to_ascii(uint8_t scan_code);

/** keyboard_interrupt:
 * The keyboard interrupt handler
 */
void keyboard_interrupt();