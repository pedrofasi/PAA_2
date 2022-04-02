#include <bits/stdc++.h>
using namespace std;

// Aluno: Pedro Henrique Reis Rodrigues
// Professor: Silvio Guimarães
// Matéria: PAA (Projeto e Análise de Algoritmos)
// Problema do Cavalo, utilizando Backtracking

int tab[8][8];

int cavalo(int x, int y, int atual, int tam, int movesX[], int movesY[])
{
    int prox_x, prox_y;
    if (atual == tam * tam)
    {
        return 1; // caso base
    }
    // tenta todas as posicoes do tabuleiro, verificando se há possibilidade (primeiro if)
    for (int i = 0; i < 8; i++)
    {
        prox_x = x + movesX[i];
        prox_y = y + movesY[i];
        if (prox_x >= 0 && prox_x < tam && prox_y >= 0 && y < tam && tab[prox_x][prox_y] == -1)
        { // verificando se a posicao do tabuleiro eh valida
            tab[prox_x][prox_y] = atual;
            if (cavalo(prox_x, prox_y, atual + 1, tam, movesX, movesY) == 1)
            {
                return 1;
            }
            else
            {
                tab[prox_x][prox_y] = -1; // backtracking
            }
        }
    }
}

int main()
{

    int tam = 8; // tamanho do tabuleiro

    int movesX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int movesY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    tab[0][0] = 0;

    if (cavalo(0, 0, 1, tam, movesX, movesY) == 0) // o 0, 0 ali decide qual a posicao inicial do cavalo
    {
        printf("Nao existe solucao");
    }
    else
    {
        for (int i = 0; i < tam; i++)
        {
            for (int j = 0; j < tam; j++)
            {
                printf("%d ", tab[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}