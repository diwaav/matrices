# PA4: MATICES
Diwa Ashwini Vittala    
dashwini

## Assignment details
The program Sparse.c takes in an input file containing instructions to build two matrices, A and B, then computes    
𝐴, 𝐵, 
(1.5)𝐴, 
𝐴 + 𝐵, 𝐴 + 𝐴, 
𝐵 − 𝐴, 𝐴 − 𝐴, 
A transpose, 
AxB, BxB    
along with the number of nonzero elements in A and B.

## Folder details
List.h    
↳ *Contains header file for list ADT*    
List.c    
↳ *Contains list ADT*    
ListTest.c    
↳ *Test file, containing my own test of the list adt*    
Matrix.h    
↳ *Contains header file for matrix ADT*    
Matrix.c    
↳ *Contains matrix ADT*    
MatrixTest.c    
↳ *Test file, containing my own test of the matrix adt*    
Sparse.c    
↳ *Contains the main function*    
Makefile    
↳ *A makefile helps build the executable as well as clean up after use*    

## Running
Make the executable:
```
make
```

Run the program:
```
./Sparse infile outfile
```

Clean up:
```
make clean
```
