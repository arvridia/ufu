#include <stdlib.h>
#include "TADEx0702.h"
#define N 15

struct deque
{
    int vetor[N];
    int ini, fim;
};

Deque cria_deque()
{
    Deque p = (Deque) malloc(sizeof(struct deque));
    if(p != NULL){
        p->ini = 0; //
        p->fim = 0; //inicializacao
    }
    return p;
}

int insere_fim(Deque p, int A) // insercao no fim
{
    if (deque_cheio(p) == 1)
        return 0;
    else{
        p->vetor[p->fim] = A;
        p->fim = (p->fim+1)%N;
        return 1;
    }
}

int insere_ini(Deque p, int A) // insercao no inicio
{
    if(deque_cheio(p) == 1)
        return 0;
    else{
        p->ini = (p->ini-1+N)%N;
        p->vetor[p->ini] = A;
        return 1;
    }
}

int remove_ini(Deque p, int *f) // remocao no inicio
{
    if (deque_vazio(p) == 1)
    {
        return 0;
    }
    *f = p->vetor[p->ini];
    p->ini = (p->ini+1)%N;
    return 1;
}

int remove_fim(Deque p, int *f) // remocao no fim
{
     if (deque_vazio(p) == 1)
    {
        return 0;
    }
    p->fim = (p->fim-1+N)%N;
    *f = p->vetor[p->fim];
    return 1;
}

int deque_vazio (Deque p)  // verifica se esta vazio
{
    if(p->ini == p->fim)
        return 1;
    else
        return 0;
}

int deque_cheio(Deque p) // verifica se esta cheio
{
    if (p->ini == (p->fim+1)%N)
        return 1;
    else
        return 0;
}

int esvazia_deque(Deque p){
    if(p == NULL)
        return 0;
    p->ini = 0;
    p->fim = 0;
    return 1;
}

void apaga_deque(Deque *p)
{
    free(*p);
    p = NULL;
}

