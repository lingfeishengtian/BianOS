/** port_byte_in:
 * C wrapper for the assembly function "in"
 *
 * @param port_addr Port address to retrieve a single byte
 */
unsigned char port_byte_in(unsigned short port_addr);
/** port_byte_out:
 * C wrapper for the assembly function "out"
 *
 * @param port_addr Port address
 * @param data Data address to store a single byte into the port
 */
void port_byte_out(unsigned short port_addr, unsigned char data);/** port_word_in:
 * C wrapper for the assembly function "in"
 *
 * @param port_addr Port address to retrieve 2 bytes
 */
unsigned short port_word_in(unsigned short port_addr);
/** port_word_out:
 * C wrapper for the assembly function "out"
 *
 * @param port_addr Port address
 * @param data Data address to store 2 bytes into the port
 */
void port_word_out(unsigned short port_addr, unsigned short data);