#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

const size_t size = 10;

size_t encode_varint(uint32_t value, uint8_t *buf)
{
assert(buf != NULL);
uint8_t *cur = buf;
while (value >= 0x80)
{

const uint8_t byte = (value & 0x7f) | 0x80;
*cur = byte;
value >>= 7;
++cur;
}
*cur = value;
++cur;
return cur - buf;
}

uint32_t decode_varint(const uint8_t **bufp)
{
const uint8_t *cur = *bufp;
uint8_t byte = *cur++;
uint32_t value = byte & 0x7f;
size_t shift = 7;
while (byte >= 0x80)
{
byte = *cur++;
value += (byte & 0x7f) << shift;
shift += 7;
}
*bufp = cur;
return value;
}

uint32_t generate_number()
{
const int r = rand();
const int p = r % 100;
if (p < 90)
{
return r % 128;
}
if (p < 95)
{
return r % 16384;
}
if (p < 99)
{
return r % 2097152;
}
return r % 268435455;
}

size_t generate()
{
size_t i=0;
size_t count = 0;
FILE *f = fopen("build/uncompressed.dat", "w");
fclose(f);
f = fopen("build/compressed.dat", "w");
fclose(f); 
for (i = 0; i < size; ++i)
{
uint32_t r = generate_number(); 
f = fopen("build/uncompressed.dat", "a"); 
fwrite(&r, sizeof(r), 1, f); 
fclose(f);
f = fopen("build/compressed.dat", "a"); 

uint8_t buf;
size_t t = encode_varint(r, &buf); 
count += t; 

fwrite(&buf, sizeof(buf) * t, 1, f); 
fclose(f);
}
return count;
}
void match(uint32_t *com, uint32_t *uncom)
{
int cnt = 0;
size_t i=0;
for (i = 0; i < size; i++)
{
if (com[i] == uncom[i])
{
cnt++;
}
}
if (cnt == size)
{
printf("OK\n");
}
else printf("Pizda");
}
