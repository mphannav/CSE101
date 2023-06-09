/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA4 
* MatrixTest.c 
* Main test harness for the Matrix ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Matrix.h"

int main(){
   int n=10;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, T, S;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
   changeEntry(A, 3,3,0); changeEntry(B, 3,3,0);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");
   
   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = copy(A);
   T = transpose(A);
   S = scalarMult(2, C);

   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   printf("%d\n", NNZ(T));
   printMatrix(stdout, T);
   printf("\n");

   printf("%d\n", NNZ(S));
   printMatrix(stdout, S);
   printf("\n");

   Matrix D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   Matrix E = diff(A, B);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   Matrix P = product(A, B);
   printf("%d\n", NNZ(P));
   printMatrix(stdout, P);
   printf("\n");

   Matrix X = product(B, A);
   printf("%d\n", NNZ(P));
   printMatrix(stdout, P);
   printf("\n");

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&T);
   freeMatrix(&S);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&P);
   freeMatrix(&X);

   return EXIT_SUCCESS;
}