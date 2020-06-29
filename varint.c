#include "varint.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
uint32_t generate_number()
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
size_t encode_varint(uint32_t value, uint8_t* buf)
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
uint32_t decode_varint(const uint8_t** bufp)
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
void match_check(uint32_t* com, uint32_t* uncom) // проверка на совпадения
значений в двух файлах
{
	int count = 0; // счетчик совпадений
	for (size_t i = 0; i < SIZE; i++)
	{
		if (com[i] == uncom[i]) //если значения совпадают
		{
			count++;
		}
	}
	if (count == SIZE) //если количество совпадений равно размеру
	{
		printf("Числа в двух файлах совпадают\n");
		filesize(); // в случае успеха вызываем функцию вывода размеров файлов
	}
	else
	{
		printf("Числа в двух файлах не совпадают\n");
	}
}
size_t generate() // генерирует и записывает числа в 2 бинарных файла (в сжатом и несжатом форматах)
{
	size_t count = 0; // счетчик кол-во байт
	FILE* f;
	FILE* z;
	f = fopen("uncompressed.dat", "w"); // создаем файл для записи чисел в
	несжатом формате
		z = fopen("compressed.dat", "w"); // создаем файл для записи чисел в
	сжатом формате
		for (size_t i = 0; i < SIZE; ++i)
		{
			uint32_t r = generate_number();
			fwrite(&r, sizeof(r), 1, f); // запись в файл
			uint8_t buf;
			size_t t = encode_varint(r, &buf); // кодируем число
			count += t;
			fwrite(&buf, sizeof(buf) * t, 1, z); //запись в файл
		}
	fclose(f);
	fclose(z);
	return count;
}
void filesize() //выводит размер файлов
{
	double size, size_of_file;
	FILE* f;

	f = fopen("uncompressed.dat", "r"); //открываем бинарник на чтение
	fseek(f, 0, SEEK_END); //перемещаем указатель в конец файла
	size_of_file = ftell(f);//считываем местоположение указателя от начала
	файла(возвращается количество байт)
		fseek(f, 0, SEEK_SET); //возвращаем указатель на место
	fclose(f);
	size = size_of_file / 1024 / 1024; //переводим байты в мегабайты
	printf("Размер 'uncompressed file' = %.2f Mbyte\n", size);
	f = fopen("compressed.dat", "r");
	fseek(f, 0, SEEK_END); //происходит то же самое, но для другого
	size_of_file = ftell(f); //файла compressed.dat
	fseek(f, 0, SEEK_SET);
	fclose(f);
	size = size_of_file / 1024 / 1024;
	printf("Размер 'compressed file' = %.2f Mbyte\n", size);
}
void checkopen(FILE * a)
{
	if (a == NULL)
	{
		printf("Произошла ошибка открытия файла, программа закрывается");
		exit(-1);
	}
}