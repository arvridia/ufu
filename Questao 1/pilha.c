#include <string.h>
#include <stdlib.h>
#include "pilha.h"

struct pilha
{
    int e;
    int d;
    struct pilha *prox;
};

Pilha cria_pilha()
{
    return NULL;
}

int pilha_vazia(Pilha p)
{
    if(p == NULL)
        return 1;
    else
        return 0;
}

int pilha_push(Pilha *p, int e, int d)
{
    Pilha N = (Pilha)malloc(sizeof(struct pilha));

    if(N == NULL)
        return 0;

    N->e = e;
    N->d = d;
    N->prox = *p;
    *p = N;
    return 1;
}

int pilha_pop(Pilha *p, int *e, int *d)
{
    if(pilha_vazia(*p) == 1)
        return 0;

    Pilha aux = *p;
    *e = (*p)->e;
    *d = (*p)->d;
    *p = aux->prox;
    free(aux);
    return 1;
}

