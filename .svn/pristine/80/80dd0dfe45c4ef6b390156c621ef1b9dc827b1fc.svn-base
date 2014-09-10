#include <stdio.h>
#include <stdint.h>

void doit(int xp[10]) {
    xp = xp + 1;
    *xp = 42;

    printf("size of xp is %d\n", sizeof(int*));
}


int main(void) {
    int x[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    doit(x);

    printf("%d %d\n", x[0], x[1]);

    printf("size of x is %d\n", sizeof(int [10]));

}

