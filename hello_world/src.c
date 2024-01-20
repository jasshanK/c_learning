#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>

#define NUMBER 3

// struct alignment
struct __attribute__((packed)) new_type {
    double b; // 8 byte
    int c; // 4 bytes
    char a; // size of 1 byte
};

int add(int a, int b) {
    return a+b;
}

int main() {
    volatile int array[5] = {1, 2, 3 ,4, 4};
    uint8_t sd[sizeof(struct new_type)]; // 8 bits = 1 byte
    //printf("Hrll\n");

    printf("size of new_type: %lu\n", sizeof(struct new_type));
    printf("size of char: %lu\n", sizeof(char));
    printf("size of int: %lu\n", sizeof(int));

//    volatile struct new_type *test = (struct new_type*) malloc(sizeof(struct new_type));
//    test->a = 'a';
//    test->b = 4;

    volatile struct new_type test;
    test.a = 'a';
    test.b = 4;

    int result = add(1,2);

    return 0;
}


