#ifndef SRC_APP_H_
#define SRC_APP_H_

#define INPUT_HEIGHT_SCALE (540)
#define INPUT_WIDTH_SCALE (960)

void Scale(const unsigned char *Input, unsigned char *Output);
void Filter_core_1(const unsigned char *Input, unsigned char *Output);
void Filter_core_0(const unsigned char *Input, unsigned char *Output);
void Differentiate(const unsigned char *Input, unsigned char *Output);
int Compress(const unsigned char *Input, unsigned char *Output);

#endif