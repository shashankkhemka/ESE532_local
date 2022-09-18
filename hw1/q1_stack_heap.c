#include<stdio.h>
#include<stdlib.h>

int main() {

    int value = 20; //Declaring an integer on stack
    int *ptr[3]; //Declaring an array of pointers on stack

    ptr[0] = (int*)malloc(3 * sizeof(int));
    ptr[1] = (int*)malloc(sizeof(int));

    ptr[0][0] = 5;
    ptr[0][1] = 6;
    ptr[0][2] = 7;
    *ptr[1] = 50;
    ptr[2] = &value;

    printf("\nAddresses and Contents of Stack:\n");
    printf("%p %d\n%p %p\n%p %p\n%p %p\n", &value, value, &ptr[2], ptr[2], &ptr[1], ptr[1], &ptr[0], ptr[0]);
    
    printf("\nAddresses and Contents of Heap:\n");
    printf("%p %d\n%p %d\n%p %d\n%p %d\n\n", &ptr[0][2], ptr[0][2], &ptr[0][1], ptr[0][1], &ptr[0][0], ptr[0][0], ptr[1], *ptr[1]);

    return 0;
}