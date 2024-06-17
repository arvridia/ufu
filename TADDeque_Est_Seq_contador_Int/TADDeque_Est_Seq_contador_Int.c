#include <stdlib.h>
#include "TADDeque_Est_Seq_contador_Int.h"
#define N 100

struct fila
{
    func vetor[N];
    int ini, cont;
};

Fila cria_fila()
{
    Fila p = (Fila) malloc(sizeof(struct fila));
    if(p != NULL){
        p->ini = 0; //
        p->cont = 0; //fila vazia
    }
    return p;
}

int insere_fim(Fila p, func A) // inser��o
{
    if (fila_cheia(p) == 1)
        return 0;
    else{
        p->vetor[(p->ini+p->cont)%N] = A;
        p->cont++;
        return 1;
    }
}
int insere_ini(Fila p, func A){
    if (fila_cheia(p) == 1)
        return 0;
    else{
        p->ini-1;
        p->vetor[(p->ini)%N] = A;
        p->cont++;
        return 1;
    }
}
int remove_ini(Fila p, func *f) // remo��o
{
    if (fila_vazia(p) == 1)
        return 0;
    *f = p->vetor[p->ini];
    p->ini = (p->ini+1)%N;
    p->cont--;
    return 1;
}
int remove_fim(Fila p, func *f){
    if(fila_vazia(p) == 1)
        return 0;
    *f = p->vetor[p->cont];
    p->cont = (p->cont+1)%N;
    p->cont--;
    return 1;
}
int fila_vazia (Fila p)  // verifica se esta vazia
{
    if( p->cont == 0)
        return 1;
    else
        return 0;
}

int fila_cheia(Fila p)
{
    if (p->cont == N)
        return 1;
    else
        return 0;
}

void libera_fila(Fila* p)
{
    free(*p);
}
