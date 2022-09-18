#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include "stopwatch.h"

#define DATA_SIZE (12000 * 8000)
#define STAGES (4)

unsigned char * Data[STAGES + 1];

void Exit_with_error(void)
{
  perror(NULL);
  exit(EXIT_FAILURE);
}

void Load_data(void)
{
  FILE * File = fopen("Input.bin", "rb");
  if (File == NULL)
    Exit_with_error();

  if (fread(Data[0], 1, DATA_SIZE, File) != DATA_SIZE)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

void Store_data(const char * Filename, int Stage, unsigned int Size)
{
  FILE * File = fopen(Filename, "wb");
  if (File == NULL)
    Exit_with_error();

  if (fwrite(Data[Stage], 1, Size, File) != Size)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

int main()
{
  for (int i = 0; i <= STAGES; i++)
  {
    // We could strictly allocate less memory for some of these buffers, but
    // that is irrelevant here.
    Data[i] = (unsigned char*)malloc(DATA_SIZE);
    if (Data[i] == NULL)
      Exit_with_error();
  }
  Load_data();

  std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;

  start_time = std::chrono::high_resolution_clock::now();
  Scale(Data[0], Data[1]);
  end_time = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();   
  printf("elapsed time for Scale: %lu ns.\n", elapsed);

  Filter(Data[1], Data[2]);

  start_time = std::chrono::high_resolution_clock::now();
  Differentiate(Data[2], Data[3]);
  end_time = std::chrono::high_resolution_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();   
  printf("elapsed time for Differentiate: %lu ns.\n", elapsed);

  start_time = std::chrono::high_resolution_clock::now();
  int Size = Compress(Data[3], Data[4]);
  end_time = std::chrono::high_resolution_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();   
  printf("elapsed time for Compress: %lu ns.\n", elapsed);
  
  Store_data("Output.bin", 4, Size);

  for (int i = 0; i <= STAGES; i++)
    free(Data[i]);

  puts("Application completed successfully.");

  return EXIT_SUCCESS;
}