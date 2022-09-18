#include<stdio.h>
#include<stdlib.h>

struct s2 {
  float a;
  int b;
};

struct s1 {
  int c;
  struct s2 **d;
};

struct s1 x[5];

int main() {

    struct s2 *ptr;
    struct s2 e;
    
    ptr = &e;

    x[2].d = &ptr;

    printf("%p\n", &((*x[2].d)->b));

    return 0;
}