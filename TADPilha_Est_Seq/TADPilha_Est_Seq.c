#include <string.h>
#include <stdlib.h>
#include "TADPilha_Est_Seq.h"
#define N 100

struct pilha
{
    int tamanho;
    func vetor[N];
};

Pilha cria_pilha()
{
    Pilha p = (Pilha) malloc(sizeof(struct pilha));
    if(p != NULL)
        p->tamanho = 0; // Inicializa com 0 elementos
    return p;
}

int pilha_push (Pilha p, func A) // inserção
{
    if (pilha_cheia(p) == 0)
    {
        p->vetor[p->tamanho] = A;
        p->tamanho++;
        return 1;
    }
    else
        return 0;
}

int pilha_pop (Pilha p, func *f) // remoção
{
    if (pilha_vazia(p))
    {
        return 0;
    }
    *f = p->vetor[p->tamanho-1];
    p->tamanho--;
    return 1;
}

int pilha_vazia (Pilha p)  // verifica se esta vazia
{
    if( p->tamanho == 0)
        return 1;
    else
        return 0;
}

int pilha_cheia(Pilha p)
{
    return (p->tamanho==N);
}

int get_topo(Pilha p, func *A)
{
    if(pilha_vazia(p)||p == NULL)
        return 0; // erro
    *A = p->vetor[p->tamanho-1];
    return 1;
}

void libera_pilha (Pilha* p)
{
    free(*p);
}

int tamanho (Pilha p)
{
    if (pilha_vazia(p)||p == NULL)
        return 0;
    return (p->tamanho);
}

int esvazia_pilha(Pilha p){
    if (pilha_vazia(p))
    {
        return 0;
    }
    p->tamanho = 0;
    return 1;
}


