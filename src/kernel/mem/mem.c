#include "mem.h"

void * memcpy(void* dst, void* src, uint32_t size){
    for(uint32_t i = 0; i < size; ++i){
        *((uint8_t*) (dst + i)) = *((uint8_t*) (src + i));
    }

    return dst;
}

void * memset(void* dst, uint8_t value, uint32_t size){
    for(uint32_t i = 0; i < size; ++i){
        *((uint8_t*) (dst + i)) = value;
    }

    return dst;
}

