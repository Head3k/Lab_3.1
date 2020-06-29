#include "varint.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
uint32_t generate_number() // rand digit
{
	const int r = rand();
	const int p = r % 100;
	if (p < 90) {
		return r % 128;
	}
	if (p < 95) {
		return r % 16384;
	}
	if (p < 99) {
		return r % 2097152;
	}
	return r % 268435455;
}
size_t encode_varint(uint32_t value, uint8_t* buf) // encode
{
	assert(buf != NULL);
	uint8_t * cur = buf;
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
uint32_t decode_varint(const uint8_t** bufp) // decode 
{
	const uint8_t* cur = *bufp;
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
void match_check(uint32_t* com, uint32_t* uncom) // check compressed && uncompressed
{
	int count = 0; // count
	for (size_t i = 0; i < SIZE; i++)
	{
		if (com[i] == uncom[i]) // if compress == uncompress
		{
			count++;
		}
	}
	if (count == SIZE) // if full ==
	{
		printf("Digit match\n");
	}
	else
	{
		printf("Digit no match\n");
	}
}
size_t generate() // work with .dat
{
	size_t count = 0; // count bite
	FILE* f;
	FILE* z;
	f = fopen("uncompressed.dat", "w"); // create or read uncompress
		z = fopen("compressed.dat", "w"); // create or read compress
		for (size_t i = 0; i < SIZE; ++i)
		{
			uint32_t r = generate_number();
			fwrite(&r, sizeof(r), 1, f); // write in file
			uint8_t buf;
			size_t t = encode_varint(r, &buf); // encode digit
			count += t;
			fwrite(&buf, sizeof(buf) * t, 1, z); // write in file
		}
	fclose(f); // close
	fclose(z);
	return count;
}

void checkopen(FILE * a) //check open file
{
	if (a == NULL)
	{
		printf("Error open file");
		exit(-1);
	}
}
