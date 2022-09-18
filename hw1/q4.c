#include<stdio.h>
#include<stdlib.h>

int main() {
    double a[] = {3.14, 2.71};
    
    unsigned char *ch;

    ch = (unsigned char*)a;

    printf("Printing the bytes: ");
    
    for (int i = 0; i < 16; i++) {
        printf("%x ", *(ch+i));
    }
    
    printf("\n");
}