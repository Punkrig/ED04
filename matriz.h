#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Celula {
    int linha;
    int coluna;
    double valor;
    struct Celula *proxLinha;
    struct Celula *proxColuna;
} Celula;

typedef struct {
    int linhas;
    int colunas;
    Celula *inicio;
} Matriz;

void insere(Matriz *mat, int linha, int coluna, double valor);
void imprimeMatriz(Matriz A);
Matriz* leMatrizes();  // Corrigido o tipo de retorno
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);

#endif // MATRIZ_H
