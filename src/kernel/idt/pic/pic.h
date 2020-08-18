/** PIC Utilites
 * Because of an IBM design error, the PIC controller interrupts interfere with Intel's,
 * so now we have to remap them to available interrupts. The interrupts I'm using will be
 * using interrupts 0x20 for PIC1 and 0x28 for PIC2. (Intel reserved from 0x00 to 0x1F)
 */
#include <stdint.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		/* ICW4 being sent */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

// PIC has two parts, PIC1 and PIC2. We remap them to the following interrupts
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7
#define PIC_EOI     0x20

/** pic_remap:
 * Remaps the PIC interrupt codes.
 * 
 * @param offset1 The PIC1 offset
 * @param offset2 The PIC2 offset
 */
void pic_remap(uint8_t offset1, uint8_t offset2);

/** pic_eoi:
 * Tell the PIC that we ended the interrupt.
 * 
 * @param interrupt The interrupt code that was recieved to verify if the pic_eoi is needed or which PICs need it
 */
void pic_eoi(uint32_t interrupt);