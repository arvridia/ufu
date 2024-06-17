#include <stdlib.h>
#include <string.h>
#include "TADPilha_Din_Enc.h"

struct no
{
    char alfa[30];
    struct no *prox;
};

Pilha cria_pilha()
{
    return NULL;
}

int pilha_vazia(Pilha p)
{
    if(p == NULL)
    {
        return 1;
    }
    else
        return 0;
}

int pilha_push(Pilha *p, char elem[])
{
    Pilha N = (Pilha)malloc(sizeof(struct no));

    if(N == NULL)
        return 0;
    strcpy(N->alfa,elem);
    N->prox = *p;
    *p = N;
    return 1;
}

int pilha_pop(Pilha *p, char *elem[])
{
    if(pilha_vazia(*p)==1)
        return 0;

    Pilha aux = *p;
    strcpy(*elem,aux->alfa);
    *p = aux->prox;
    free(aux);
    return 1;
}

int get_topo(Pilha *p, char *nome[]) //
{
    if(pilha_vazia(*p))
        return 0; // erro

    strcpy(*nome,(*p)->alfa);
    return 1;
}

void esvazia_pilha(Pilha *p)
{
    while(*p != NULL)
    {
        Pilha aux = *p;
        *p = aux->prox;
        free(aux);
    }
    p = NULL;
}

void libera_pilha(Pilha *p)
{
    while(*p != NULL)
    {
        Pilha aux = *p;
        *p = aux->prox;
        free(aux);
    }
}

int tamanho_pilha(Pilha p)
{
    int size = 0;
    while(p != NULL){
        p = p->prox;
        size++;
    }
    return size;
}
