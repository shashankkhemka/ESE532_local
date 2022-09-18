#include <stdlib.h>
#include <stdio.h>
#include "App.h"
#include "stopwatch.h"
#define INPUT_HEIGHT (4000)
#define INPUT_WIDTH (6000)

#define FILTER_LENGTH (7)

#define OUTPUT_HEIGHT (INPUT_HEIGHT - (FILTER_LENGTH - 1))
#define OUTPUT_WIDTH (INPUT_WIDTH - (FILTER_LENGTH - 1))

unsigned Coefficients[] = {2, 15, 62, 98, 62, 15, 2};

void Filter_horizontal(const unsigned char * Input, unsigned char * Output)
{
  LOOP1: for (int Y = 0; Y < INPUT_HEIGHT; Y++)
    LOOP2: for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      LOOP3: for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[Y * INPUT_WIDTH + X + i];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
}

void Filter_vertical(const unsigned char * Input, unsigned char * Output)
{
  LOOP1: for (int Y = 0; Y < OUTPUT_HEIGHT; Y++)
    LOOP2: for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      LOOP3: for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[(Y + i) * OUTPUT_WIDTH + X];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
}

void Filter(const unsigned char * Input, unsigned char * Output)
{
  unsigned char * Temp = (unsigned char*)malloc(INPUT_HEIGHT * OUTPUT_WIDTH);

  std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;

  start_time = std::chrono::high_resolution_clock::now();
  Filter_horizontal(Input, Temp);
  end_time = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();   
  printf("elapsed time for Filter_horizontal: %lu ns.\n", elapsed);

  start_time = std::chrono::high_resolution_clock::now();
  Filter_vertical(Temp, Output);
  end_time = std::chrono::high_resolution_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();   
  printf("elapsed time for Filter_vertical: %lu ns.\n", elapsed);

  free(Temp);
}