#include <stdlib.h>
#include "TADFila_Est_Seq_DesPosVDD.h"
#define N 100
#define N2 10

struct fila
{
    char vetor[N][N2];
    int ini, fim;
};

Fila cria_fila()
{
    Fila p = (Fila) malloc(sizeof(struct fila));
    if(p != NULL){
        p->ini = 0; //
        p->fim = 0; //fila vazia
    }
    return p;
}

int insere_fim(Fila p, char A[]) // inserção
{
    if (fila_cheia(p) == 1)
        return 0;
    else{
        strcpy(p->vetor[p->fim],A);
        p->fim = (p->fim+1)%N;
        return 1;
    }
}

int remove_ini(Fila p, char *f[]) // remoção
{
    if (fila_vazia(p) == 1)
    {
        return 0;
    }
    strcpy(*f,p->vetor[p->ini]);
    p->ini = (p->ini+1)%N;
    return 1;
}

int fila_vazia (Fila p)  // verifica se esta vazia
{
    if(p->ini == p->fim)
        return 1;
    else
        return 0;
}

int fila_cheia(Fila p)
{
    if (p->ini == (p->fim+1)%N)
        return 1;
    else
        return 0;
}

void libera_fila(Fila* p)
{
    free(*p);
}
