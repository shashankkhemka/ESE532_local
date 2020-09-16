#include "App.h"

void Scale(const unsigned char *Input, unsigned char *Output, int Y_Start_Idx, int Y_End_Idx)
{
  for (int Y = Y_Start_Idx; Y < Y_End_Idx; Y += 2)
  {
    for (int X = 0; X < WIDTH; X += 2)
    {
      Output[(Y / 2) * WIDTH / 2 + (X / 2)] = Input[Y * WIDTH + X];
    }
  }
}
