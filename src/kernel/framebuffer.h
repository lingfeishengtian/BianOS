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

#define VIDEO_BUFFER 0x000B8000

/** print_char:
 * Writes a single character with specified background and foreground color to specified position cell.
 * 
 * @param i The location in framebuffer. Must be divisible by 2 (first half is character, second half is foreground and background color
 * @param c The character to be printed.
 * @param tc The text color.
 * @param bg Background color.
 */
void print_char(unsigned int i, char c, enum Colours tc, enum Colours bg);
