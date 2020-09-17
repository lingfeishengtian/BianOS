#include <stdint.h>
#include <stdbool.h>

/** initialize_error_handling:
 * Start error handling from interrupts.
 */
void initialize_error_handling();

/** panic:
 * Halts the OS.
 */
void panic();

/** dump_cpu:
 * Retrieves the current cpu state (registers) and prints them out in the format starting from EAX - EDX
 * then ESP, EBP, and finally EIP and EDI.
 * 
 * To better indicate the start of a CPU dump, the color of the text "CPU DUMP" is light blue and the registers
 * are red to indicate system function.
 */
void dump_cpu();