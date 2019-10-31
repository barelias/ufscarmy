/*
Nome: Ricardo Augusto Lopes de Faria
R.A.: 758598
Curso: Engenharia de Computacao
Trabalho 2 de AED1: O Problema de Josephus
Universidade Federal de Sâo Carlos
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//variaveis globais
typedef struct pessoa Pessoa;
struct pessoa
{
    int posicao;
    Pessoa *prox;
};
Pessoa *final;
Pessoa *inicio = NULL;

//Prototipos das Funcoes
void insereLista(int pos);
void removeLista(Pessoa *p);
void imprimeLista();
int resolveJosephus(int n, int m);

int main()
{

    int nroexecs;

    scanf("%d", &nroexecs);
    int *n = malloc(nroexecs * sizeof(int));
    int *m = malloc(nroexecs * sizeof(int));
    for (int i = 0; i < nroexecs; i++)
    {
        scanf("%d", &n[i]);
        scanf("%d", &m[i]);
    }

    for (int i = 0; i < nroexecs; i++)
    {
        printf(" Usando n=%d, m=%d, resultado =%d\n", n[i], m[i], resolveJosephus(n[i], m[i]));
    }

    free(n);
    free(m);

    return 0;
}

void insereLista(int pos)
{
    Pessoa *novaPessoa;
    novaPessoa = malloc(sizeof(Pessoa));
    novaPessoa->posicao = pos;
    //Caso o inicio for nulo precisa criar um no
    if (inicio == NULL)
    {
        inicio = novaPessoa;
        novaPessoa->prox = inicio;
    }

    if (final != NULL) {
        final->prox = novaPessoa;
    }
    
    novaPessoa->prox = inicio;
    final = novaPessoa;
    free(novaPessoa);
}

void removeLista(Pessoa *p)
{
    Pessoa *fora = inicio;
    fora = malloc(sizeof(Pessoa));
    // Caso a celula que deseja-se ser tirada for a primeira
    if (fora == inicio)
    {
        inicio = fora->prox;
    }
    fora = p->prox;
    p->prox = fora->prox;
    free(fora);
}
void imprimeLista()
{
    Pessoa *impressao;
    impressao = inicio;
    while (impressao != final->prox)
    {
        printf("%d", impressao->posicao);
        impressao = impressao->prox;
    }
}

int resolveJosephus(int n, int m)
{
    int i;
    for (i = 0; i < n; i++)
    {
        insereLista(i);
    }

    Pessoa *sobrevivente = inicio;
    // Pessoa *auxiliar = inicio;

    while (sobrevivente != sobrevivente->prox)
    {
        for (i = 0; i < m - 1; i++)
        {
            sobrevivente = sobrevivente->prox;
            // auxiliar->posicao = (sobrevivente->prox)->posicao;
        }
        if (sobrevivente->posicao == (sobrevivente->prox)->posicao)
        {
            sobrevivente = sobrevivente->prox;
        }
        removeLista(sobrevivente);
        sobrevivente = sobrevivente->prox;
    }
    return sobrevivente->posicao;
}