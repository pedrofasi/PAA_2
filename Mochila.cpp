#include <bits/stdc++.h>
using namespace std;

// Aluno: Pedro Henrique Reis Rodrigues
// Professor: Silvio Guimarães
// Matéria: PAA (Projeto e Análise de Algoritmos)
// Problema da Mochila, utilizando Branch and Bound

typedef struct Item
{
    float peso;
    int quantidade;
} Item;

typedef struct No
{
    int nivel;
    int max;
    int bound;
    float peso;
} No;

bool cmp(Item a, Item b)
{
    double r1 = (double)a.quantidade / a.peso;
    double r2 = (double)b.quantidade / b.peso;
    return r1 > r2;
}

int bound(No u, int items, int peso, Item K[])
{
    if (u.peso >= peso)
    { // se ultrapassar o proprio peso, retorna 0, n vai entrar
        return 0;
    }
    int lucro = u.max;   // pega o max q aguenta, que seria o lucro
    int j = u.nivel + 1; // começa o index no atual + 1
    int peso_aux = u.peso;

    while ((j < items) && (peso_aux + K[j].peso <= peso))
    { // condicoes de peso e capacidade
        peso_aux += K[j].peso;
        lucro += K[j].quantidade;
        j++;
    }
    if (j < items)
    { // se k for diferente de n, então inclua o ultimo item
        lucro += (peso - peso_aux) * K[j].quantidade / K[j].peso;
    }
    return lucro;
}
// retorna a capacidade maxima de itens K, q suprota a mochila com capacidade "peso"
int mochila(int peso, Item K[], int items)
{
    queue<No> Fila;
    No u, v;
    u.nivel = -1;
    u.max = 0; // inicialização das auxiliares da arvore
    u.peso = 0;

    Fila.push(u); // adiciona na fila
    int max = 0;

    while (!Fila.empty())
    {
        // tira um no
        u = Fila.front();
        Fila.pop();
        if (u.nivel == -1)
        { // no inicial = 0
            v.nivel = 0;
        }
        if (u.nivel == items - 1)
        { // se n tiver next no = continua
            continue;
        }
        v.nivel = u.nivel + 1;
        v.peso = u.peso + K[v.nivel].peso; // adiciona no nó v, todos os itens e valores de u
        v.max = u.max + K[v.nivel].quantidade;

        if (v.peso <= peso && v.max > max) // se o peso acumlado for menor q o peso já calculado anteriormente, atualiza
        {
            max = v.max;
        }
        v.bound = bound(v, items, peso, K); // recorrencia upper bound para verificar se vale apena adicionar v na fila oou não

        if (v.bound > max)
        {
            Fila.push(v);
        }
        v.peso = u.peso;
        v.max = v.max;                      // repete açao so q sem tirar o item da mochila
        v.bound = bound(v, items, peso, K); // recorrencia upper bound para verificar se vale apena adicionar v na fila oou não

        if (v.bound > max)
        {
            Fila.push(v);
        }
    }
    return max;
}

int main()
{

    int peso; // peso da mochila
    scanf("%d", &peso);
    int items;
    scanf("%d", &items); // numero de itens
    Item K[items];
    for (int i = 0; i < items; i++)
    {
        scanf("%d %f", &K[i].quantidade, &K[i].peso); // pega quantidade e peso
    }

    sort(K, K + items, cmp);

    int resultado = mochila(peso, K, items);
    printf("Resultado >%d<", resultado);
}