#include <stdint.h>

/**
 * memcpy is a classic c library function that copies a certain section of memory to a destination. The range
 * of values being copied over is from [src -> src + size] -> [dst -> dst + size].
 * 
 * @param dst Destination address
 * @param src Source address
 * @param size The size of the chunk being copied
 */
void * memcpy(void* dst, void* src, uint32_t size);

/**
 * memset is a classic c library function that sets a certain section of memory to a certain specified value.
 * The range of values being set is value -> [dst -> dst + size].
 * 
 * @param dst Destination address
 * @param src Source address
 * @param size The size of the chunk being copied
 */
void * memset(void* dst, uint8_t value, uint32_t size);