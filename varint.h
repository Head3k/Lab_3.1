#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#define SIZE 1000000
uint32_t generate_number();
size_t encode_varint(uint32_t value, uint8_t* buf);
uint32_t decode_varint(const uint8_t** bufp);
void match_check(uint32_t* com, uint32_t* uncom);
size_t generate();
void filesize();
void checkopen(FILE* a);