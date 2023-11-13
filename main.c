#include "matriz.h"
#include <stdio.h>

int main(void) {
    Matriz *A, *B, C, D;
    A = leMatrizes();
    printf("Matriz A:\n");
    imprimeMatriz(*A);
    B = leMatrizes();
    printf("Matriz B:\n");
    imprimeMatriz(*B);
    C = somaMatrizes(*A, *B);
    printf("Matriz soma A + B:\n");
    imprimeMatriz(C);
    D = multiplicaMatrizes(*A, *B);
    printf("Matriz produto A * B:\n");
    imprimeMatriz(D);
    return 0;
}
