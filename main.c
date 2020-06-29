#include "varint.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	uint8_t* r;
	uint32_t* uncom, * com;
	size_t count = generate();
	r = malloc(sizeof(uint8_t) * count);
	com = malloc(sizeof(uint32_t) * SIZE);
	uncom = malloc(sizeof(uint32_t) * SIZE);
	FILE* a = fopen("compressed.dat", "r"); // открыли файл для чтения
	checkopen(a); // проверили что открытие
	прошло успешно
		fread(r, sizeof(uint8_t), count, a); // считываем данные из файла
	fclose(a);
	const uint8_t* c = r;
	a = fopen("uncompressed.dat", "r"); // открыл файл для чтения
	checkopen(a); // проверили что открытие прошло
	успешно
		fread(uncom, sizeof(uint32_t), SIZE, a); // считываем данные из файла
	fclose(a);
	for (size_t i = 0; i < SIZE; i++)
	{
		com[i] = decode_varint(&c); // декодируем данные, полученные из
		файла compressed.dat
	}
	match_check(com, uncom); // проверка что значения одинаковые в двух
	файлах
		free(r);
	free(com);
	free(uncom);
	return 0;
}