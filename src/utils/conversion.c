#include "conversion.h"
#include "../kernel/mem/kheap.h"
#include "../kernel/debugger.h"

char* hex_to_ascii(uint32_t hex){
    uint8_t size = sizeof(hex) * 2;
    char* res = kmalloc(size + 3); //32 bit -> 8 hex pairs + 0x and null end

    for(int i = size - 1; i >= 0; --i){
        char ascii_val = hex & 0x0000000F;
        if(ascii_val < 10) ascii_val += 48;
        else ascii_val += 55;

        res[i + 2] = ascii_val;
        hex >>= 4;
    }

    res[0] = '0';
    res[1] = 'x';

    res[size + 2] = 0;
    return res;
}

char* int_to_ascii(uint32_t integer){
    uint8_t size = 0;

    uint32_t int_copy = integer;
    while (int_copy / 10 != 0)
    {
        int_copy /= 10;
        ++size;
    }
    ++size;
    
    char* res = kmalloc(size + 1);

    int i;
    for(i = size - 1; i >= 0; --i){
        char ascii_val = integer % 10;
        ascii_val += 48;

        res[i] = ascii_val;
        integer /= 10;
    }

    res[size] = 0;

    return res;
}