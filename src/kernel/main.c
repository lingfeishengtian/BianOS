#include "../drivers/vga_text.h"

// Testing scrolling
void test(){
	printd("TEST\nttt");
	printd("oof\n");
	for(int i = 0; i < 30; ++i){
		char* str = "ftkynormpgsyghwljsksjtccpbdjasokwkfzjivmnklxhedmjtixywuwtfvvwpplhkmjssyrhmrgseab"; 
		str[0] = i + 48;
		str[79] = i + 49;
		printd(str);
	}
}

// Start here
int main(){
	clr_screen();
	printd("Welcome to BianOS. CURSOR is enabled by default.");

	return 0;
}
