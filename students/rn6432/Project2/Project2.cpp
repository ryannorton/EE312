/* Project2.cpp
 * Ima Student
 * EE312, Spring 2014
 * Project 2, Matrix Multiplication
 */

#include <stdio.h>
#include <stdint.h>
#include "MatrixMultiply.h"

/*
 * An example routine demonstrating the use of row-major ordering
 *
 * You do not need to use this function in your solution
 * (I didn't use it in mine!)
 *
 * given two matrices a and b, where the number of rows in b is equal
 * to the number of columns in a,
 * and given a row number 'row' and a column number 'col',
 * calculate the dot product of the row'th row from a and the col'th column from b
 *
 * recall the dot product is the sum of the element-by-element product of
 * the two vectors.
 */
double dotProduct(double a[], const uint32_t a_rows, const uint32_t a_cols,
    /* a is a matrix with a_rows rows and a_cols columns */
    double b[], const uint32_t b_cols,
    /* b is also a matrix.  It has a_cols rows and b_cols columns */
    uint32_t row, // an index of a row of a
    uint32_t col) { // an index of a column of b

        double sum = 0.0; // the result of the dot product is stored here
        uint32_t k = 0;
        while (k < a_cols) { // recall: a_cols == b_rows
            /* we need to multiply a[row, k] and b[k, col] and add that to sum */
            sum = sum + a[(row * a_cols) + k] * b[k * b_cols + col];
            /* recall a[i,j] is stored at a[(i * a_cols) + j] and b[i, j] is at b[(i * b_cols) + j] */
            k += 1;
        }

        return sum;
}

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {
	int i, j;
	for (i=0; i < a_rows; i++) { // for each row
		for (j=0; j < b_cols; j++) { // for each col
			c[(i*b_cols) + j] = dotProduct(a, a_rows, a_cols, b, b_cols, i, j);
		}
	}
}

#define READY_FOR_STAGE2
#ifdef READY_FOR_STAGE2

// allocate space for intermediate matrices
#define TOTAL_SPACE 10000
double memory_pool[TOTAL_SPACE];
uint32_t top_of_pool = 0;

PtrDouble allocateSpace(uint32_t size) {
	top_of_pool += size;
	return &(memory_pool[top_of_pool - size]);
}

void multiplyMatrixChain(
    PtrDouble matrix_list[],
    uint32_t rows[],
    uint32_t cols[],
    uint32_t num_matrices,
    double out[],
    uint32_t out_rows,
    uint32_t out_cols) {

	double* a_mat = matrix_list[0];
	uint32_t a_rows = rows[0]; // number of rows in a matrix
	uint32_t a_cols = cols[0]; // number of cols in a matrix
	uint32_t next_src = 1; // index of next matrix to multiply by
	double* b_mat;
	double* c_mat;
	uint32_t b_cols;
	while (next_src < num_matrices) {
		b_mat = matrix_list[next_src];
		b_cols = cols[next_src];
		c_mat = allocateSpace(a_rows * b_cols);
		multiplyMatrices(a_mat, a_rows, a_cols, b_mat, b_cols, c_mat);
		a_mat = c_mat;
		a_cols = b_cols;
		next_src += 1;
	}
	// place c_mat into out matrix
	for (int i=0; i<(out_rows*out_cols); i++) {
		out[i] = c_mat[i];
	}
	// deallocate memory_pool
	top_of_pool = 0;
}

#endif /* READY_FOR_STAGE_2 */