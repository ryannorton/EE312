#include <stdio.h>
#include <stdint.h>


void swap(int* x, int* y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void test1(void) {
    int a = 1;
    int b = 2;

    swap(&a, &b);

    printf("after swapping a is %d and b is %d\n", a, b);
}

int main(void) {
    char s[] = "Hello World";
    char* p = s;
    char** q = &p;

    *q = *q + 1;
    *p = *p + 1;

    printf("and the string is %s\n", s);
}


