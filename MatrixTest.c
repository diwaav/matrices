/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA4
* MatrixTest.c 
* A program to test Matrix.c
**********************************************************************************/

#include "List.h"
#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix M = newMatrix(2);
    printf("The matrix has this many nonzero elements: %d.\n", NNZ(M));
    changeEntry(M, 1, 1, 1.0);
    changeEntry(M, 1, 2, 1.0);
    changeEntry(M, 2, 1, 1.0);
    changeEntry(M, 2, 2, 1.0);
    printf("The matrix has this many nonzero elements: %d.\n", NNZ(M));
    freeMatrix(&M);

    printf("\n----------\n");

    printf("\nMATRIX A:\n");
    Matrix A = newMatrix(2);
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 2, 1, 3);
    changeEntry(A, 2, 2, 4);
    printMatrix(stdout, A);
    printf("The matrix A has this many nonzero elements: %d.\n", NNZ(A));

    printf("\nMATRIX B:\n");
    Matrix B = newMatrix(2);
    changeEntry(B, 1, 1, 5);
    changeEntry(B, 1, 2, 6);
    changeEntry(B, 2, 1, 7);
    changeEntry(B, 2, 2, 8);
    printMatrix(stdout, B);
    printf("The matrix B has this many nonzero elements: %d.\n", NNZ(B));

    printf("\nMATRIX C = AxB:\n");
    Matrix C = product(A, B);
    printMatrix(stdout, C);
    printf("The matrix C has this many nonzero elements: %d.\n", NNZ(C));

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);

    return 0;
}

/*
 * The matrix has this many nonzero elements: 0.
 * The matrix has this many nonzero elements: 4.
 *
 * ----------
 *
 *  MATRIX A:
 *  1: (1, 1.0) (2, 2.0) 
 *  2: (1, 3.0) (2, 4.0) 
 *  The matrix A has this many nonzero elements: 4.
 *
 *  MATRIX B:
 *  1: (1, 5.0) (2, 6.0) 
 *  2: (1, 7.0) (2, 8.0) 
 *  The matrix B has this many nonzero elements: 4.
 *
 *  MATRIX C = AxB:
 *  1: (1, 19.0) (2, 22.0) 
 *  2: (1, 43.0) (2, 50.0) 
 *  The matrix C has this many nonzero elements: 4.
*/


