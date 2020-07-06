#include "../drivers/vga_text.h"

// Testing print functions for strings before creating a real print statement
void miniPrint(char * str){
	unsigned int i = 0;
	while(str[i] != 0)
	{
		print_char(i * 2, str[i], LIGHT_GREY, BLACK);
		++i;
	}
	cursor_move(i);
}

// Start here
int main(){
	//miniPrint("Welcome to BianOS. CURSOR is enabled by default.");	
	miniPrint("ftkynormpgsyghwljsksjtccpbdjasokwkfzjivmnklxhedmjtixywuwtfvvwpplhkmjssyrhmrgseab");
	
	return 0;
}
