#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#define SIZE 1000000 // size need generate
uint32_t generate_number(); // random digit 
size_t encode_varint(uint32_t value, uint8_t* buf); // encode
uint32_t decode_varint(const uint8_t** bufp); // decode
void match_check(uint32_t* com, uint32_t* uncom); // match digit
size_t generate(); // generate file
void checkopen(FILE* a); // check open file