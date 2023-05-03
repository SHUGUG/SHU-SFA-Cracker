#include <stdio.h>

int main() {
    printf("Size of char: %lu \n", sizeof(char));
    printf("Size of unsigned char: %lu \n", sizeof(unsigned char));
    printf("Size of signed char: %lu \n", sizeof(signed char));
    printf("Size of int: %lu \n", sizeof(int));
    printf("Size of unsigned int: %lu \n", sizeof(unsigned int));
    printf("Size of int: %lu \n", sizeof(int));
    printf("Size of short: %lu \n", sizeof(short));
    printf("Size of unsigned short: %lu \n", sizeof(unsigned short));
    printf("Size of long: %lu \n", sizeof(long));
    printf("Size of unsigned long: %lu \n", sizeof(unsigned long));
    printf("Size of float: %lu \n", sizeof(float));
    printf("Size of double: %lu \n", sizeof(double));
    printf("Size of long double: %lu \n", sizeof(long double));

    return 0;
}
//Size of char: 1
//Size of unsigned char: 1
//Size of signed char: 1
//Size of int: 4
//Size of unsigned int: 4
//Size of int: 4
//Size of short: 2
//Size of unsigned short: 2
//Size of long: 8
//Size of unsigned long: 8
//Size of float: 4
//Size of double: 8
//Size of long double: 16