#include<stdio.h>
#include<stdlib.h>

void temp(int i) {
  int a[2];
  int b[3];
  int *c;
  int *d;
  c = (int *)malloc(sizeof(int) * 4);
  d = (int *)malloc(sizeof(int) * 5);

  printf("Printing addresses for array a: %p %p\n", a, a + 1);
  printf("Printing addresses for array b: %p %p %p\n", b, b + 1, b + 2);
  printf("Printing addresses for array c: %p %p %p %p\n", c, c + 1, c + 2, c + 3);
  printf("Printing addresses for array d: %p %p %p %p %p\n", d, d + 1, d + 2, d + 3, d + 4);

  return;
}

int main() {
    temp(0);
    return 0;
}