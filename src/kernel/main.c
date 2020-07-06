#include "framebuffer.h"

void miniPrint(char * str){
	unsigned int i = 0;
	while(str[i] != 0)
	{
		print_char(i * 2, str[i], LIGHT_GREY, BLACK);
		++i;
	}
}

int main(){
	miniPrint("Welcome to BianOS");	
	return 0;
}
