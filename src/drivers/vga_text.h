#include <stdint.h>
#include <stdbool.h>

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
#define VIDEO_BUFFER 0xC00B8000

#define VGA_INDEX 0x03D4
#define VGA_DATA 0x03D5

#define CURSOR_START_REG 0x0A
#define CURSOR_END_REG 0x0B
#define CURSOR_LOCATION_HIGH 0x0E
#define CURSOR_LOCATION_LOW 0x0F

#define ROWS 25
#define COLS 80

/** set_char:
 * Writes a single character with specified background and foreground color to specified position cell.
 * 
 * @param i The location in frame buffer. Must be divisible by 2 (first half is character, second half is foreground and background color. If the value given is odd, then you will see funky results.
 * @param c The character to be printed.
 * @param tc The text color.
 * @param bg Background color.
 */
void set_char(uint32_t i, char c, enum Colours tc, enum Colours bg);

/** get_char:
 * Retrieves the character at the specified location.
 * The color and character is not separated, so you can retrieve a character with a number and the color of that character with that number plus 1.
 *
 * @param loc Location to retrieve. You can also retrieve color with this location.
 */
char get_char(uint32_t loc);

/** print:
 * Print a string to the screen and moves the cursor to the location right after the printed string.
 *
 * If the string overflows, then the screen will scroll.
 *
 * @param str The string to be printed
 * @param tc The text color
 * @param bg The background color
 */
void print(char* str, enum Colours tc, enum Colours bg);

//TODO: USE __VA_ARGS__ to create something similar to printf
/** printd:
 * Same thing as the function above exept with default colors: text color is light grey, background color is black.
 *
 * @param str The string to be printed
 */
void printd(char* str);

/** clr_screen:
 * Clears the screen of everything.
 */
void clr_screen();
