#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "stopwatch.h"

#define WIN_SIZE 16
#define PRIME 3
#define MODULUS 256
#define TARGET 0

uint64_t hash_func(unsigned char *input, unsigned int pos)
{
	// put your hash function implementation here
	uint64_t hash = 0;

	for (unsigned int i = 0; i < WIN_SIZE; i++) {
		hash += int(input[pos + WIN_SIZE - 1 - i]) * pow(PRIME, i + 1);
	}
	return hash;
}

void cdc(unsigned char *buff, unsigned int buff_size)
{
	// put your cdc implementation here
	uint64_t hash = hash_func(buff, WIN_SIZE);
	unsigned int a, b;

	if((hash % MODULUS) == TARGET)
			printf("%u\n", WIN_SIZE);

	for (unsigned int i = WIN_SIZE + 1; i < (buff_size - WIN_SIZE); i++) {
		
		a = (int) buff[i - 1] * pow(PRIME, WIN_SIZE+1);
		b = (int) buff[i - 1 + WIN_SIZE] * PRIME;

		hash = (hash * PRIME - a + b);

		if(hash % MODULUS == TARGET) {
			printf("%u\n", i);
		}
	}
}

void test_cdc( const char* file )
{
	FILE* fp = fopen(file,"r" );
	if(fp == NULL ){
		perror("fopen error");
		return;
	}

	fseek(fp, 0, SEEK_END); // seek to end of file
	int file_size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file

	unsigned char* buff = (unsigned char *)malloc((sizeof(unsigned char) * file_size ));	
	if(buff == NULL)
	{
		perror("not enough space");
		fclose(fp);
		return;
	}

	int bytes_read = fread(&buff[0],sizeof(unsigned char),file_size,fp);

	cdc(buff, file_size);

    free(buff);
    return;
}

int main()
{
	stopwatch timer;

	timer.start();
	test_cdc("prince.txt");	
	timer.stop();

	printf("Latency of cdc improved function: %lf ns.\n", timer.latency());
	
	return 0;
}