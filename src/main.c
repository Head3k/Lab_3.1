#include "varint.h"
#include <stdio.h>
int main()
{
    size_t i = 0;
    size_t count = generate();
    uint32_t* uncom;
    uint32_t* com;
    uint8_t* r;
    r = malloc(sizeof(uint8_t) * count);
    com = malloc(sizeof(uint32_t) * size);
    uncom = malloc(sizeof(uint32_t) * size);
    FILE* f = fopen("build/compressed.bin", "r");
    fread(r, sizeof(uint8_t), count, f);
    fclose(f);
    const uint8_t* c = r;
    f = fopen("build/uncompressed.bin", "r");
    fread(uncom, sizeof(uint32_t), size, f);
    fclose(f);
    for (i = 0; i < size; i++) {
        com[i] = decode_varint(&c);
    }
    match(com, uncom);
    free(r);
    free(com);
    free(uncom);
    return 0;
}
