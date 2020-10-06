#define MATRIX_WIDTH (1024)

typedef float matrix_type;

void Multiply_HW(const matrix_type Input_1[MATRIX_WIDTH * MATRIX_WIDTH],
                 const matrix_type Input_2[MATRIX_WIDTH * MATRIX_WIDTH],
		         matrix_type Output[MATRIX_WIDTH * MATRIX_WIDTH])
{
  matrix_type Buffer_1[MATRIX_WIDTH][MATRIX_WIDTH];
  matrix_type Buffer_2[MATRIX_WIDTH][MATRIX_WIDTH];

  Init_loop_i: for(int i = 0; i < MATRIX_WIDTH; i++)
    Init_loop_j: for(int j = 0; j < MATRIX_WIDTH; j++)
    {
      Buffer_1[i][j] = Input_1[i * MATRIX_WIDTH + j];
      Buffer_2[i][j] = Input_2[i * MATRIX_WIDTH + j];
    }

  Main_loop_i: for (int i = 0; i < MATRIX_WIDTH; i++)
    Main_loop_j: for (int j = 0; j < MATRIX_WIDTH; j++)
    {
      matrix_type Result = 0;
      Main_loop_k: for (int k = 0; k < MATRIX_WIDTH; k++)
      {
        Result += Buffer_1[i][k] * Buffer_2[k][j];
      }
      Output[i * MATRIX_WIDTH + j] = Result;
    }
}




