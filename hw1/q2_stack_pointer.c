#include<stdio.h>
#include<stdlib.h>

int main() {

    int a[2][4] = {{10, 20, 30, 40}, {50, 60, 70, 80}}; //Defining a 2D array

    int *ptr[2]; //Declaring an array of pointers

    ptr[0] = a[0];
    ptr[1] = a[1];

    printf("Printing the array using a array of pointers:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d\t", *(ptr[i]+j));
        }
        printf("\n");
    }

    int **d_ptr = ptr; //Declaring a double pointer

    printf("Printing the array using a double pointer:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d\t", *(*(d_ptr + i) + j));
        }
        printf("\n");
    }

    return 0;
}