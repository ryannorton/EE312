/* Project0.c 
 * Ryan Norton
 * EE312 Summer 2014 
 * Exercise 0 
 *
 * Run the program and restate each of the following three facts
 * The program below indicates....
 *	that 16777216 is the largest number in the universe of 32-bit floating point numbers,
 *	that -2147483648 is the largest (or smallest) integer in the universe of 32-bit ints, 
 *	and that one tenth is not exactly equal to 0.1 because fractions cannot be represented exact 
 */

#include <stdio.h>

void fpWeirdness(void) {
	float x = 0.0;
	float x_plus_1 = 1.0;

	while (x < x_plus_1) { // repeat as long as x < x_plus_1 (i.e., forever???)
		x = x + 1; // make x bigger by 1
		x_plus_1 = x + 1; // and restore x_plus_1 so that it is (once again) equal to x plus 1
	}
	printf("The largest number in the universe is %f\n", x);
}

void intWeirdness(void) {
	int x = 1;
	while (x > 0) {
		x = x + 1;
	}
	printf("The largest integer in the universe is %d\n", x);
}

void fractionalWeirdness(void) {
	double tenth = 0.1; 
	int tenths_count = 0;
	double sum = 0;

	while (sum != 1.0) {
		sum = sum + tenth;
		tenths_count = tenths_count + 1;
	}

	printf("it takes %d tenths to equal a whole\n", tenths_count);
}

int main(void) {

	fpWeirdness();
	intWeirdness();
	fractionalWeirdness();

	printf("all done, hit ctrl-c to stop this program\n");
	while (1);
}
