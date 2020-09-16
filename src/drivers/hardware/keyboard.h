#include <stdint.h>
#include <stdbool.h>

#define KBD_DATA_PORT   0x60
#define L_SHIFT_KEY_DOWN         0x2A
#define R_SHIFT_KEY_DOWN         0x36
#define L_SHIFT_KEY_UP           (L_SHIFT_KEY_DOWN + 0x80)
#define R_SHIFT_KEY_UP           (R_SHIFT_KEY_DOWN + 0x80)
#define DELETE                   0x0E

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
void keyboard_interrupt(int interrupt );