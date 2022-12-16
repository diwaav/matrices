/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA3
* Sparse.c 
* Main function handing matrix operations
**********************************************************************************/
#include "List.h"
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    // There must be an input and output file
    if (!argv[1] || argv[3]) {
        fprintf(stderr, "Error: Wrong number of files given.\n");
        exit(EXIT_FAILURE);
    }

    // open input and output file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Error: no such input file exists.\n");
        exit(EXIT_FAILURE);
    }
    FILE *outfile = fopen(argv[2], "w");

    // read in total number of vertices 
    int num = 0;
    int runA = 0;
    int runB = 0;
    fscanf(infile, "%d %d %d\n", &num, &runA, &runB);

    // num = the size of the matrix
    Matrix A = newMatrix(num);
    Matrix B = newMatrix(num);

    fscanf(infile, "\n");

    // runA == number of lines that contain changes to matrix A
    int i = 0; 
    int j = 0;
    double val = 0;
    for (int time = 0; time < runA; time += 1) {
        fscanf(infile, "%d %d %lf\n", &i, &j, &val);
        changeEntry(A, i, j, val);
    }

    fscanf(infile, "\n");

    // runB == number of lines that contain changes to matrix A
    for (int time = 0; time < runB; time += 1) {
        fscanf(infile, "%d %d %lf\n", &i, &j, &val);
        changeEntry(B, i, j, val);
    }

    // print A
    fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outfile, A);
    fprintf(outfile, "\n");

    // print B
    fprintf(outfile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");

    // print (1.5)A
    fprintf(outfile, "(1.5)*A =\n");
    Matrix N = scalarMult(1.5, A);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // print A+B
    fprintf(outfile, "A+B =\n");
    N = sum(A, B);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // print A+A
    fprintf(outfile, "A+A =\n");
    N = sum(A, A);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // print B-A
    fprintf(outfile, "B-A =\n");
    N = diff(B, A);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // print A-A
    fprintf(outfile, "A-A =\n");
    N = diff(A, A);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // print transpose A
    fprintf(outfile, "Transpose(A) =\n");
    N = transpose(A);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // print A*B
    fprintf(outfile, "A*B =\n");
    N = product(A, B);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // print B*B
    fprintf(outfile, "B*B =\n");
    N = product(B, B);
    printMatrix(outfile, N);
    freeMatrix(&N);
    fprintf(outfile, "\n");

    // clear memory
    freeMatrix(&A);
    freeMatrix(&B);
    fclose(infile);
    fclose(outfile);
    return 0;
}

