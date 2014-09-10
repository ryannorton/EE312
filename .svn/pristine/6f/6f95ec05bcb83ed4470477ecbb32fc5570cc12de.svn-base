typedef int int32_t;
typedef unsigned uint32_t;

//extern "C" { void putchar(int); }

#include <stdio.h>

void demonstration1(const char fmt[], ...) {
	int32_t k = 0;
    while (fmt[k] != 0) {
        putchar(fmt[k]);
        k = k + 1;
    }
}

/* this code only works on GCC
 * most of the other demonstrations work on either GCC or Visual Studio */
void demonstration2(const char fmt[], ...) {
    int32_t wtf[2];
	int32_t k = 0;
    while (fmt[k] != 0) {
        if (fmt[k] == '%') { // an escape sequence!
            if (fmt[k+1] == 'd') {
                int32_t x = wtf[7];  
                printf("value was %d\n", x);
            } else {
                // WTF?
            }
            k = k + 2;
        } else { // not an escape sequence, just display next charaacter
            putchar(fmt[k]);
            k = k + 1;
        }
    }
}

void displayDecimal(int32_t x) {
    char digits[10];
    uint32_t num_digits = 0;

    if (x == 0) { // special case for zero
        putchar('0');
        return;
    }

    if (x < 0) { // special case for negative
        putchar('-');
        x = -x;
        // fall through to display the abs value
    }

    while (x != 0) {
        char d = x % 10 + '0';
        digits[num_digits] = d;
        num_digits += 1;
        x = x / 10;
    }

    while (num_digits > 0) {
        num_digits -= 1;
        putchar(digits[num_digits]);
    }


}

void myPrintf(const char fmt[], ...) {
    void* blah = &fmt + 1;
    uint32_t k = 0;
    
    while (fmt[k] != 0) {
        if (fmt[k] == '%') { // escape sequence
            if (fmt[k+1] == 'd') { // decimal
                int32_t* p = (int32_t*) blah;
                int32_t x = *p;
                displayDecimal(x);
            } else if (fmt[k+1] == 'c') { // character
            } else if (fmt[k+1] == 's') { // string
            } else if (fmt[k+1] == 'f') { // floating point
            } else if (fmt[k+1] == '%') { // special %% sequence
                putchar('%');
            } else { // ERROR
            }
            k = k + 2;
        } else { // normal character, just print it
            putchar(fmt[k]);
            k = k + 1;
        }
    }
}




int main(void) {
    demonstration1("Hello World\n");
    demonstration2("x is %d\n", 13);
    myPrintf("x is %d\n", 42);
}



