#include "../drivers/vga_text.h"

// Testing print functions for strings before creating a real print statement
void miniPrint(char * str){
	unsigned int i = 0;
	while(str[i] != 0)
	{
		print_char(i * 2, str[i], LIGHT_GREY, BLACK);
		++i;
	}
}

// Start here
int main(){
	miniPrint("Welcome to BianOS. CURSOR is enabled by default.");	
	
	cursor_move(0x0054);
	return 0;
}
