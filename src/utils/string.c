#include "string.h"

uint32_t strlen(char* str){
    uint32_t len;
    while(str[len]){
        len++;
    }
    return len;
}

char* concat(char* str1, char* str2){
    uint32_t str1len = strlen(str1);
    uint32_t str2len = strlen(str2);
    uint32_t size =  str1len + str2len + 1;
    char* str = kmalloc(size);

    memcpy(str, str1, str1len);
    memcpy(str + str1len, str2, str2len);

    str[size - 1] = 0;

    return str;
}