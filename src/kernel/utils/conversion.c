#include "conversion.h"
#include "../mem/kheap.h"

char* hex_to_ascii(uint32_t hex){
    uint8_t size = sizeof(hex) * 2;
    char* res = kmalloc(size + 3); //32 bit -> 8 hex pairs + 0x and null end

    for(int i = size - 1; i >= 0; --i){
        char ascii_val = hex & 0xF;
        if(ascii_val < 10) ascii_val += 48;
        else ascii_val += 55;

        res[i + 2] = ascii_val;
        hex = hex >> 4;
    }

    res[0] = '0';
    res[1] = 'x';

    res[size + 2] = 0;
    return res;
}