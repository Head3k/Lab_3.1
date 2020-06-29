#include "varint.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	uint8_t* r;
	uint32_t* uncom, * com; // for check to match
	size_t count = generate(); // work with file
	r = malloc(sizeof(uint8_t) * count);
	com = malloc(sizeof(uint32_t) * SIZE); // memory for array for check
	uncom = malloc(sizeof(uint32_t) * SIZE); // memory for array for check
	FILE* a = fopen("compressed.dat", "r"); // open file for read
	checkopen(a); // check open file
		fread(r, sizeof(uint8_t), count, a); // scan data
	fclose(a); // close
	const uint8_t* c = r;
	a = fopen("uncompressed.dat", "r"); // open file for read
	checkopen(a); // check open file
		fread(uncom, sizeof(uint32_t), SIZE, a); // scan data
	fclose(a); //close 
	for (size_t i = 0; i < SIZE; i++)
	{
		com[i] = decode_varint(&c); // decode compressed.dat for check
	}
	match_check(com, uncom); // check data to match
	free(r);
	free(com);
	free(uncom);
	return 0;
}