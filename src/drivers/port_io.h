#include <stdint.h>

/** port_byte_in:
 * C wrapper for the assembly function "in"
 *
 * @param port_addr Port address to retrieve a single byte
 */
uint8_t port_byte_in(uint16_t port_addr);
/** port_byte_out:
 * C wrapper for the assembly function "out"
 *
 * @param port_addr Port address
 * @param data Data address to store a single byte into the port
 */
void port_byte_out(uint16_t port_addr, uint8_t data);/** port_word_in:
 * C wrapper for the assembly function "in"
 *
 * @param port_addr Port address to retrieve 2 bytes
 */
uint16_t port_word_in(uint16_t port_addr);
/** port_word_out:
 * C wrapper for the assembly function "out"
 *
 * @param port_addr Port address
 * @param data Data address to store 2 bytes into the port
 */
void port_word_out(uint16_t port_addr, uint16_t data);