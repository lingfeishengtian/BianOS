// Colors that are available for text color and background color
enum Colours{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GREY,
	DARK_GREY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_BROWN,
	WHITE
};

// Useful macros to make vga_text.c more readable
#define VIDEO_BUFFER 0x000B8000

#define VGA_INDEX 0x03D4
#define VGA_DATA 0x03D5

#define CURSOR_START_REG 0x0A
#define CURSOR_END_REG 0x0B
#define CURSOR_LOCATION_HIGH 0x0E
#define CURSOR_LOCATION_LOW 0x0F

/** print_char:
 * Writes a single character with specified background and foreground color to specified position cell.
 * 
 * @param i The location in frame buffer. Must be divisible by 2 (first half is character, second half is foreground and background color
 * @param c The character to be printed.
 * @param tc The text color.
 * @param bg Background color.
 */
void print_char(unsigned int i, char c, enum Colours tc, enum Colours bg);

/** cursor_toggle:
 * Toggles whether or not the cursor should be displayed. Takes in a 1 byte of data and uses bitwise and 0x1 to imitate boolean value.
 * Cursor will appear at an unknown location when toggled.
 *
 * @param t Enable or disable. 1 for disable, 0 for enable. Seems counter-intuitive, but that's just how VGA Text Mode works!
 */
void cursor_toggle(unsigned char t);

/** cursor_move:
 * Moves cursor to a specified location.
 *
 * @param pos The position cursor should travel to.
 */
void cursor_move(unsigned short pos);
