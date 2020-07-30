/** PIC Utilites
 * Because of an IBM design error, the PIC controller interrupts interfere with Intel's,
 * so now we have to remap them to available interrupts. The interrupts I'm using will be
 * using interrupts 0x20 for PIC1 and 0x28 for PIC2. (Intel reserved from 0x00 to 0x1F)
 */

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

/** pic_remap:
 * Remaps the PIC interrupt codes.
 * 
 * @param offset1 The PIC1 offset
 * @param offset2 The PIC2 offset
 */
void pic_remap(unsigned char offset1, unsigned char offset2);