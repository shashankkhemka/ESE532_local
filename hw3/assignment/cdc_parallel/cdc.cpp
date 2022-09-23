#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "App.h"


#define WIN_SIZE 16
#define PRIME 3
#define MODULUS 256
#define TARGET 0
#define NUM_THREADS 4

uint64_t hash_func(unsigned char *input, unsigned int pos)
{
	// put your hash function implementation here
	uint64_t hash = 0;

	for (unsigned int i = 0; i < WIN_SIZE; i++) {
		hash += int(input[pos + WIN_SIZE - 1 - i]) * pow(PRIME, i + 1);
	}
	return hash;
}

void cdc(unsigned char *buff, unsigned int I_Start_Idx, unsigned int I_End_Idx, std::vector<int> &values)
{
	// put your cdc implementation here
	uint64_t hash = hash_func(buff, I_Start_Idx);
	unsigned int a, b;

	if((hash % MODULUS) == TARGET)
			printf("%u\n", WIN_SIZE);

	for (unsigned int i = I_Start_Idx + 1; i < (I_End_Idx); i++) {
		
		a = (int) buff[i - 1] * pow(PRIME, WIN_SIZE+1);
		b = (int) buff[i - 1 + WIN_SIZE] * PRIME;

		hash = (hash * PRIME - a + b);

		if(hash % MODULUS == TARGET) {
			// printf("%u\n", i);
			values.push_back(i);
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

	// cdc(buff, file_size);

	// parallelize cdc over 4 threads here
	std::vector<std::thread> ths, thx;

	std::vector<std::vector<int>> values(4);

    ths.push_back(std::thread(&cdc, buff, WIN_SIZE, file_size / 4, std::ref(values[0])));
    ths.push_back(std::thread(&cdc, buff, file_size / 4, file_size / 2, std::ref(values[1])));
	ths.push_back(std::thread(&cdc, buff, file_size / 2, (3 * file_size) / 4, std::ref(values[2])));
    ths.push_back(std::thread(&cdc, buff, (3 * file_size) / 4, file_size - WIN_SIZE, std::ref(values[3])));

    pin_thread_to_cpu(ths[0], 0);
    pin_thread_to_cpu(ths[1], 1);
	pin_thread_to_cpu(ths[2], 2);
    pin_thread_to_cpu(ths[3], 3);

    for (auto &th : ths)
    {
      th.join();
    }

	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < values[i].size(); j++) {
			printf("%u\n", values[i][j]);
		}

    free(buff);
    return;
}

int main()
{
	test_cdc("../data/prince.txt");
	return 0;
}