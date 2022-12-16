/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA4 
* ListTest.c 
* A program to test List.c
**********************************************************************************/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // checking constructor of list
    List L = newList();
    printf("Initially:\n");
    printf("List length = %d\n", length(L));

    // put numbers into the list to play with
    printf("\nPutting in numbers from array\n");
    int *arr = malloc(20 * sizeof(int));
    for (int i = 1; i <= 10; i += 1) {
        arr[i] = i;
        append(L, &arr[i]);
        prepend(L, &arr[i]);
    }

    // print out list
    printf("\nWhat's in the list?\n");
    int x;
    for (moveFront(L); index(L) != -1; moveNext(L)) {
        x = *(int *)get(L);
        printf("%d ", x);
    }
    printf("\n");
    printf("Now, list length = %d\n", length(L));

    // changing cursor elements
    printf("I want to change the first 4 elements to 2...\n");
    moveFront(L);
    int num = 2;
    for (int i = 1; i < 5; i += 1) {
        set(L, &num);
        moveNext(L);
    }
    // print out list
    for (moveFront(L); index(L) != -1; moveNext(L)) {
        x = *(int *)get(L);
        printf("%d ", x);
    }
    printf("\n");

    // clear memory
    free(arr);
    freeList(&L);
    return 0;
}

/*
 * Initially:
 * List length = 0
 *
 * Putting in numbers from array
 *
 * What's in the list?
 * 10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10 
 * Now, list length = 20
 * I want to change the first 4 elements to 2...
 * 2 2 2 2 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10 
*/


