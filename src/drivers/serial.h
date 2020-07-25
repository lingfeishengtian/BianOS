/* COM Ports */

/* All serial COM ports are calculated relative to the first COM port
 * because all the ports are in order.
 * COM1: 0x3F8
 * COM2: 0x2F8
 * COM3: 0x3E8
 * COM4: 0x2E8
 */

#define SERIAL_COM1_PORT                    0x3F8
#define SERIAL_COM2_PORT                    0x2F8
#define SERIAL_COM3_PORT                    0x3E8
#define SERIAL_COM4_PORT                    0x2E8

#define SERIAL_DATA_PORT(base_com)          (base_com)
#define SERIAL_FIFO_COMMAND_PORT(base_com)  (base_com + 2)
#define SERIAL_LINE_COMMAND_PORT(base_com)  (base_com + 3)
#define SERIAL_MODEM_COMMAND_PORT(base_com) (base_com + 4)
#define SERIAL_LINE_STATUS_PORT(base_com)   (base_com + 5)

/** serial_port_configure_baud_rate:
 * Configures the speed of the data being sent.
 * Serial controllers(UART) have an internal clock with a speed of 115200 bits/s, 
 * though you can set the divisor to change the baud rate. The resulting speed
 * would be (115200 / <divisor>) bits/s.
 * 
 * @param com The COM port address that should be configured.
 * @param divisor The divisor needed to calculate the baud rate.
 */
void serial_port_configure_baud_rate(unsigned short com, unsigned short divisor);

/** serial_port_configure_line_default: 
 * Configures the line for the serial port.
 * The port configuration gives a data length of 8, no parity bits, one stop bit,
 * and no break control.
 * 
 * Chart:       7   8   5 4 3   2   1 0
 * Parameter:   d   bc  parity  s   length 
 * Value:       0   0   0 0 0   0   1 1 (8 bits) = 0x03
 * 
 * @param com The COM port address that should be configured
 */
void serial_port_configure_line_default(unsigned short com);

/** is_serial_port_fifo_transmit_empty:
 * Checks to see if the fifth bit of the serial port status is 1 or 0.
 * Determines if data is ready to be sent to the buffer.
 * 
 * @param com The COM port address
 * @return 0 if the the transmit is not empty
 *         !0 if the transmit is empty
 */
int is_serial_port_fifo_trasmit_empty(unsigned short com);

/** serial_write_char:
 * Checks the status of the output port and ensures the character being written is
 * written successfully.
 * 
 * @param com The COM port address
 * @param c The character to be written
 */
void serial_write_char(unsigned short com, unsigned char c);

/** init_serial_port_default:
 * Initialize the baud rate with a divisor of 3 and configure the current COM port
 * to the default settings.
 * 
 * @param com The COM port address
 */
void init_serial_port_default(unsigned short com);

/** serial_write:
 * Write the specified string to the specified COM port address.
 * 
 * @param com The COM port address
 * @param str The string to be written.
 */
void serial_write(unsigned short com, char* str);

/** serial_writeln:
 * Writes the specified string to the specified COM port address with an additional new line
 * character.
 * 
 * @param com The COM port address
 * @param str The string to be written
 */
void serial_writeln(unsigned short com, char* str);