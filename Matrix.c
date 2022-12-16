/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA4
* Matrix.c
* Matrix ADT 
**********************************************************************************/

#include "List.h"
#include "Matrix.h"


/*** Structures for entries and matrix ***/
typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    int size;
    int nonzeros;
    List* matrix;
} MatrixObj;

/*** Create and Destroy structures ***/
// newEntry(): create a new entry
Entry newEntry(int col, double val) {
    Entry E = malloc(sizeof(EntryObj));
    if (E) {
        E->column = col;
        E->value = val;
        return E;
    } else {
        printf("Entry error: unable to allocate memory in newEntry().\n");
        exit(EXIT_FAILURE);
    }
}

// freeEntry(): delete an entry
void freeEntry(Entry* pE) {
    if (pE && *pE) {
        free(*pE);
        *pE = NULL;
    }
    return;
}

// newMatrix(): Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->nonzeros = 0;
    M->matrix = (List *) calloc((n + 1), sizeof(List));
    for (int i = 1; i <= n; i += 1) {
        M->matrix[i] = newList();
    }
    return M;
}

// freeMatrix(): Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM && (*pM)) {
        for (int i = 1; i <= size(*pM); i += 1) {
            while(length((*pM)->matrix[i]) > 0) {
                moveFront((*pM)->matrix[i]);
                Entry E = (Entry)get((*pM)->matrix[i]);
                freeEntry(&E);
                delete((*pM)->matrix[i]);
            }
            freeList(&((*pM)->matrix[i]));
        }
        free((*pM)->matrix);
        free(*pM);
        *pM = NULL;
    }
    return;
}

/*** Access functions ***/
// size(): Return the size of square Matrix M.
int size(Matrix M) {
    if (M) {
        return M->size;
    } else {
        printf("Matrix Error: calling size() on a nonexistent matrix.\n");
        exit(EXIT_FAILURE);
    }
}

// NNZ(): Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    if (M) {
        return M->nonzeros;
    } else {
        printf("Matrix Error: calling NNZ() on a nonexistent matrix.\n");
        exit(EXIT_FAILURE);
    } 
}

// equals(): Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (A && B) {
        if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
            return 0;
        } else {
            for (int i = 1; i <= size(A); i += 1) {
                // for each row in the matrix
                moveFront(A->matrix[i]);
                moveFront(B->matrix[i]);
                if (length(A->matrix[i]) != length(B->matrix[i])) {
                    return 0;
                }
                while (index(A->matrix[i]) != -1) {
                    // for each column in that row
                    Entry Acur = (Entry)get(A->matrix[i]);
                    Entry Bcur = (Entry)get(B->matrix[i]);
                    if ((Acur->column != Bcur->column) || (Acur->value != Bcur->value)) {
                        // cursor is not the same
                        return 0;
                    }
                    moveNext(A->matrix[i]);
                    moveNext(B->matrix[i]);
                }
            }
        }
        return 1;
    } else {
        printf("Matrix error: calling equals() on nonexistent/NULL matrices.\n");
        exit(EXIT_FAILURE);
    }
}

/***  Manipulation procedures ***/
// makeZero(): Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if (M) {
        for (int i = 1; i <= size(M); i += 1) {
            while(length(M->matrix[i]) > 0) {
                moveFront(M->matrix[i]);
                Entry E = (Entry)get(M->matrix[i]);
                freeEntry(&E);
                delete(M->matrix[i]);
            }
            freeList(&(M->matrix[i]));
            M->matrix[i] = newList();
        }
        M->nonzeros = 0;
        return;
    } else {
        printf("Matrix error: calling makeZero() on nonexistent/NULL matrices.\n");
        exit(EXIT_FAILURE);
    }
}

// changeEntry(): Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (M && (i>=1 && i<=size(M)) && (j>=1 && j<=size(M))) {
        List row = M->matrix[i];
        for (moveFront(row); index(row) != -1; moveNext(row)) {
            Entry cursor = (Entry)get(row);
            if (cursor->column == j) {
                if (x != 0) {
                    cursor->value = x;
                } else {
                    delete(row);
                    freeEntry(&cursor);
                    M->nonzeros -= 1;
                }
                return;
            } else if (cursor->column > j) {
                if (x != 0) {
                  insertBefore(row, newEntry(j, x));
                  M->nonzeros += 1;
                }
                return;
            }
        }
        if (x != 0) {
            append(row, newEntry(j, x));
            M->nonzeros += 1;
        }
        return;
    } else {
        printf("Matrix error: calling changeEntry() on nonexistent/NULL matrices, or row/column not in range.\n");
        exit(EXIT_FAILURE);
    }
}

/*** Matrix Arithmetic operations ***/
// copy(): Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    if (A) {
        Matrix B = newMatrix(size(A));
        for (int row = 1; row <= size(A); row += 1) {
            List L = A->matrix[row];
            if (length(L) > 0) {
                for (moveFront(L); index(L) != -1; moveNext(L)) {
                    Entry N = (Entry)get(L);
                    append(B->matrix[row], newEntry(N->column, N->value));
                }
            }
        }
        B->nonzeros = A->nonzeros;
        return B;
    } else {
        printf("Matrix error: calling copy() on nonexistent/NULL matrix\n");
        exit(EXIT_FAILURE);
    }
}

// transpose(): Returns a reference to a new Matrix object representing the transpose of A
Matrix transpose(Matrix A) {
    if (A) {
        Matrix T = newMatrix(size(A));
        for (int row = 1; row <= size(A); row += 1) {
            for (moveFront(A->matrix[row]); index(A->matrix[row]) != -1; moveNext(A->matrix[row])) {
                Entry E = (Entry)get(A->matrix[row]);
                append(T->matrix[E->column], newEntry(row, E->value));
            }
        }
        T->nonzeros = A->nonzeros;
        return T;
    } else {
        printf("Matrix error: calling transpose() on nonexistent/NULL matrix\n");
        exit(EXIT_FAILURE);
    }
}

// scalarMult(): Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    if (A) {
        Matrix B = newMatrix(size(A));
        for (int row = 1; row <= size(A); row += 1) {
            List L = A->matrix[row];
            if (length(L) > 0) {
                for (moveFront(L); index(L) != -1; moveNext(L)) {
                    Entry N = (Entry)get(L);
                    double Bval = N->value * x;
                    append(B->matrix[row], newEntry(N->column, Bval));
                }
            }
        }
        B->nonzeros = A->nonzeros;
        return B;
    } else {
        printf("Matrix error: calling scalarMult() on nonexistent/NULL matrix\n");
        exit(EXIT_FAILURE);
    }
}

// sum(): Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix error: calling sum() on matrices of different sizes.\n");
        exit(EXIT_FAILURE);
    }

    if (A == B) {
        return scalarMult(2, A);
    }

    Matrix sum = newMatrix(size(A));
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(A->matrix[i]);
        moveFront(B->matrix[i]);
        while (index(A->matrix[i]) != -1 || index(B->matrix[i]) != -1) {
            if (index(B->matrix[i]) == -1 && (index(A->matrix[i]) != -1)) {
                int colA = ((Entry)get(A->matrix[i]))->column;
                double valA = ((Entry)get(A->matrix[i]))->value;
                append(sum->matrix[i], newEntry(colA, valA));
                sum->nonzeros += 1;
                moveNext(A->matrix[i]);
            } else if (index(A->matrix[i]) == -1 && (index(B->matrix[i]) != -1)) {
                int colB = ((Entry)get(B->matrix[i]))->column;
                double valB = ((Entry)get(B->matrix[i]))->value;
                append(sum->matrix[i], newEntry(colB, valB));
                sum->nonzeros += 1;
                moveNext(B->matrix[i]);
            } else {
                if (((Entry)get(A->matrix[i]))->column == ((Entry)get(B->matrix[i]))->column) {
                    double valA = ((Entry)get(A->matrix[i]))->value;
                    double valB = ((Entry)get(B->matrix[i]))->value;
                    if (valA + valB != 0) {
                        append(sum->matrix[i], newEntry(((Entry)get(A->matrix[i]))->column, valA + valB));
                        sum->nonzeros += 1;
                    }
                    moveNext(A->matrix[i]);
                    moveNext(B->matrix[i]);
                } else if (((Entry)get(A->matrix[i]))->column >= ((Entry)get(B->matrix[i]))->column) {
                    int colB = ((Entry)get(B->matrix[i]))->column;
                    double valB = ((Entry)get(B->matrix[i]))->value;
                    append(sum->matrix[i], newEntry(colB, valB));
                    sum->nonzeros += 1;
                    moveNext(B->matrix[i]);
                } else if(((Entry)get(A->matrix[i]))->column <= ((Entry)get(B->matrix[i]))->column) {
                    int colA = ((Entry)get(A->matrix[i]))->column;
                    double valA = ((Entry)get(A->matrix[i]))->value;
                    append(sum->matrix[i], newEntry(colA, valA));
                    sum->nonzeros += 1;
                    moveNext(A->matrix[i]);
                }
            }
        }
    }
    return sum;
}


// diff(): Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix error: calling diff() on matrices of different sizes.\n");
        exit(EXIT_FAILURE);
    }

    if (A == B) {
        return newMatrix(size(A));
    }

    Matrix sum = newMatrix(size(A));
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(A->matrix[i]);
        moveFront(B->matrix[i]);
        while (index(A->matrix[i]) != -1 || index(B->matrix[i]) != -1) {
            if (index(B->matrix[i]) == -1 && (index(A->matrix[i]) != -1)) {
                int colA = ((Entry)get(A->matrix[i]))->column;
                double valA = ((Entry)get(A->matrix[i]))->value;
                append(sum->matrix[i], newEntry(colA, valA));
                sum->nonzeros += 1;
                moveNext(A->matrix[i]);
            } else if (index(A->matrix[i]) == -1 && (index(B->matrix[i]) != -1)) {
                int colB = ((Entry)get(B->matrix[i]))->column;
                double valB = ((Entry)get(B->matrix[i]))->value;
                append(sum->matrix[i], newEntry(colB, -valB));
                sum->nonzeros += 1;
                moveNext(B->matrix[i]);
            } else {
                if (((Entry)get(A->matrix[i]))->column == ((Entry)get(B->matrix[i]))->column) {
                    double valA = ((Entry)get(A->matrix[i]))->value;
                    double valB = ((Entry)get(B->matrix[i]))->value;
                    if (valA - valB != 0) {
                        append(sum->matrix[i], newEntry(((Entry)get(A->matrix[i]))->column, valA - valB));
                        sum->nonzeros += 1;
                    }
                    moveNext(A->matrix[i]);
                    moveNext(B->matrix[i]);
                } else if (((Entry)get(A->matrix[i]))->column > ((Entry)get(B->matrix[i]))->column) {
                    int colB = ((Entry)get(B->matrix[i]))->column;
                    double valB = ((Entry)get(B->matrix[i]))->value;
                    append(sum->matrix[i], newEntry(colB, -valB));
                    sum->nonzeros += 1;
                    moveNext(B->matrix[i]);
                } else if (((Entry)get(A->matrix[i]))->column < ((Entry)get(B->matrix[i]))->column) {
                    int colA = ((Entry)get(A->matrix[i]))->column;
                    double valA = ((Entry)get(A->matrix[i]))->value;
                    append(sum->matrix[i], newEntry(colA, valA));
                    sum->nonzeros += 1;
                    moveNext(A->matrix[i]);
                }
            }
        }
    }
    return sum;
}

// vectorDot(): finds dot product of two lists (rows)
double vectorDot(List P, List Q) {
    double prod = 0;
    moveFront(P);
    moveFront(Q);
    while ((index(P) != -1) && (index(Q) != -1)) {
        int col1 = ((Entry)get(P))->column;
        int col2 = ((Entry)get(Q))->column;
        if (col1 == col2) {
            double val1 = ((Entry)get(P))->value;
            double val2 = ((Entry)get(Q))->value;
            prod += (val1 * val2);
            moveNext(P);
            moveNext(Q);
        } else if (col1 > col2) {
            moveNext(Q);
        } else {
            moveNext(P);
        }
    }
    return prod;
}

// product(): Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix Error: calling product() on two matices with different sizes.\n");
        exit(EXIT_FAILURE);
    }

    Matrix P = newMatrix(size(A));
    Matrix BT = transpose(B);
    for (int i = 1; i <= size(A); i += 1) {
        for (int j = 1; j <= size(A); j += 1) {
            double prodval = vectorDot(A->matrix[i], BT->matrix[j]);
            if (prodval != 0) {
                append(P->matrix[i], newEntry(j, prodval));
                P->nonzeros += 1;
            }
        }
    }

    freeMatrix(&BT);
    return P;
}

/*** Printing ***/
// printMatrix(): prints a matrix to outfile with nonzero elements as a tuple of 
// (column, value) and each line is a row
void printMatrix(FILE* out, Matrix M) {
    if (M) {
        for (int i = 1; i <= size(M); i += 1) {
            if (length(M->matrix[i]) > 0) {
                fprintf(out, "%d: ", i);
                for (moveFront(M->matrix[i]); index(M->matrix[i]) != -1; moveNext(M->matrix[i])) {
                    Entry E = (Entry)get(M->matrix[i]);
                    fprintf(out, "(%d, %.1lf) ", E->column, E->value);
                }
                fprintf(out, "\n");
            }
        }
    }
    return;
}




