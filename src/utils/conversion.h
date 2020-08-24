#include <stdint.h>

/** 
 * Converts an integer value to a hex ascii value.
 * Uses kmalloc to assist with string creation!
 * 
 * @param hex The value being converted
 * @return A string with the new ascii value
 */
char* hex_to_ascii(uint32_t hex);

/** 
 * Converts an integer value to an ascii value.
 * Uses kmalloc to assist with string creation!
 * 
 * @param integer The value being converted
 * @return A string with the new ascii value
 */
char* int_to_ascii(uint32_t integer);