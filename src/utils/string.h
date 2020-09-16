#include "../kernel/mem/mem.h"
#include "../kernel/mem/kheap.h"

/**
 * Retrieve the length of a string up to the next null terminator.
 * 
 * @param str The string to retrieve the length of
 * @return The length of the string
 */
uint32_t strlen(char* str);
char* concat(char* str1, char* str2);