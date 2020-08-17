#include "conversion.h"
#include "../mem/mem.h"

char* hex_to_ascii(unsigned int hex){
    unsigned char size = sizeof(hex) * 2;
    char* res = (char*) kmalloc(size + 1); //32 bit -> 8 hex pairs

    for(int i = size - 1; i >= 0; --i){
        unsigned char ascii_val = hex & 0xF;
        if(ascii_val < 10) ascii_val += 48;
        else ascii_val += 55;

        res[i] = ascii_val;
        hex = hex >> 4;
    }

    res[size] = 0;
    return res;
}