#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

Celula *criaCelula(int linha, int coluna, double valor) {
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    if (novaCelula != NULL) {
        novaCelula->linha = linha;
        novaCelula->coluna = coluna;
        novaCelula->valor = valor;
        novaCelula->proxLinha = NULL;
        novaCelula->proxColuna = NULL;
    }
    return novaCelula;
}

void insere(Matriz *mat, int linha, int coluna, double valor) {
    Celula *novaCelula = criaCelula(linha, coluna, valor);
    if (novaCelula == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }

    Celula *anterior = NULL;
    Celula *atual = mat->inicio;

    while (atual != NULL && (atual->linha < linha || (atual->linha == linha && atual->coluna < coluna))) {
        anterior = atual;
        atual = atual->proxLinha;
    }

    if (atual != NULL && atual->linha == linha && atual->coluna == coluna) {
        // Célula já existe, atualize o valor
        atual->valor = valor;
        free(novaCelula); // Libera a memória alocada
    } else {
        novaCelula->proxLinha = atual;
        
        if (anterior != NULL && anterior->linha == linha) {
            novaCelula->proxColuna = anterior->proxColuna;
            anterior->proxColuna = novaCelula;
        } else {
            novaCelula->proxColuna = atual;
            if (atual != NULL && atual->linha == linha) {
                atual->proxColuna = novaCelula;
            }
        }

        if (anterior == NULL) {
            mat->inicio = novaCelula;
        } else {
            anterior->proxLinha = novaCelula;
        }
    }
}







void imprimeMatriz(Matriz A) {
    for (int i = 1; i <= A.linhas; i++) {
        for (int j = 1; j <= A.colunas; j++) {
            Celula *atual = A.inicio;
            int found = 0;

            while (atual != NULL) {
                if (atual->linha == i && atual->coluna == j) {
                    printf("%.2lf\t", atual->valor);
                    found = 1;
                    break;
                }
                atual = atual->proxLinha;
            }

            if (!found) {
                printf("0.00\t");
            }
        }
        printf("\n");
    }
}



Matriz *leMatrizes() {
    FILE *arquivo = fopen("matriz.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: não foi possível abrir o arquivo.\n");
        exit(1);
    }

    Matriz *matrizes = malloc(2 * sizeof(Matriz));
    if (matrizes == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    Matriz matriz;
    int matrizAtual = 0;
    int linha, coluna;
    double valor;

    while (fscanf(arquivo, "%d,%d\n", &matriz.linhas, &matriz.colunas) == 2) {
        matriz.inicio = NULL;

        while (fscanf(arquivo, "%d,%d,%lf", &linha, &coluna, &valor) == 3) {
            insere(&matriz, linha, coluna, valor);
        }

        matrizes[matrizAtual++] = matriz;
    }

    fclose(arquivo);
    return matrizes;
}








Matriz somaMatrizes(Matriz A, Matriz B) {
    if (A.linhas != B.linhas || A.colunas != B.colunas) {
        printf("Erro: As matrizes têm dimensões diferentes.\n");
        exit(1);
    }

    Matriz C;
    C.linhas = A.linhas;
    C.colunas = A.colunas;
    C.inicio = NULL;

    for (int i = 1; i <= A.linhas; i++) {
        for (int j = 1; j <= A.colunas; j++) {
            double valorA = 0, valorB = 0;

            Celula *celulaA = A.inicio;
            Celula *celulaB = B.inicio;

            while (celulaA != NULL) {
                if (celulaA->linha == i && celulaA->coluna == j) {
                    valorA = celulaA->valor;
                    break;
                }
                celulaA = celulaA->proxLinha;
            }

            while (celulaB != NULL) {
                if (celulaB->linha == i && celulaB->coluna == j) {
                    valorB = celulaB->valor;
                    break;
                }
                celulaB = celulaB->proxLinha;
            }

            double soma = valorA + valorB;
            if (soma != 0) {
                insere(&C, i, j, soma);
            }
        }
    }
    return C;
}

Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    if (A.colunas != B.linhas) {
        printf("Erro: As dimensões das matrizes são incompatíveis para multiplicação.\n");
        exit(1);
    }

    Matriz C;
    C.linhas = A.linhas;
    C.colunas = B.colunas;
    C.inicio = NULL;

    for (int i = 1; i <= A.linhas; i++) {
        for (int j = 1; j <= B.colunas; j++) {
            double valor = 0;

            for (int k = 1; k <= A.colunas; k++) {
                double valorA = 0, valorB = 0;

                Celula *celulaA = A.inicio;
                Celula *celulaB = B.inicio;

                while (celulaA != NULL) {
                    if (celulaA->linha == i && celulaA->coluna == k) {
                        valorA = celulaA->valor;
                        break;
                    }
                    celulaA = celulaA->proxLinha;
                }

                while (celulaB != NULL) {
                    if (celulaB->linha == k && celulaB->coluna == j) {
                        valorB = celulaB->valor;
                        break;
                    }
                    celulaB = celulaB->proxLinha;
                }

                valor += valorA * valorB;
            }
            if (valor != 0) {
                insere(&C, i, j, valor);
            }
        }
    }

    return C;
}

