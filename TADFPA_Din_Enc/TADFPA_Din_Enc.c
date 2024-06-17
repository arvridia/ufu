#include <stdlib.h>
#include "TADFPA_Din_Enc.h"

struct no{
    int info;
    struct no *prox;
};

typedef struct no *No;
struct fila{
    struct no * ini;
    struct no * fim;
};

Fila cria_fila(){
    Fila f;
    f = (Fila) malloc(sizeof(struct fila));
    if(f != NULL){
        f->ini = NULL;
        f->fim = NULL;
    }
    return f;
}

int fila_vazia(Fila f){
    if(f->ini == NULL)
        return 1;
    else
        return 0;
}

int insere_ord(Fila f, int elem)
{
    if(f == NULL)
        return 0;
    No N = (No)malloc(sizeof(struct no));
    if(N == NULL)
        return 0;
    N->info = elem;
    if(fila_vazia(f) == 1 || elem > f->fim->info)
    {
        if(fila_vazia(f) == 1)
            f->ini = N;
        else
            f->fim->prox = N;
        N->prox = NULL;
        f->fim = N;
        return 1;
    }
    if(elem < f->ini->info)
    {
        N->prox = f->ini;
        f->ini = N;
        return 1;
    }
    No aux = f->ini;
    while(aux->prox != NULL && aux->prox->info <= elem)
        aux = aux->prox;
    N->prox = aux->prox;
    aux->prox = N;
    return 1;
}

int remove_ini(Fila f, int *elem){
    if(fila_vazia(f) == 1)
        return 0;
    struct no *aux = f->ini;
    *elem = aux->info;
    if(f->ini == f->fim)
        f->fim = NULL;
    f->ini = aux->prox;
    free(aux);
    return 1;
}

void apaga_fila(Fila f)
{
    struct no *aux = f->ini;
    while(aux != NULL)
    {
        struct no *aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(f);
}

int esvazia_fila(Fila f)
{
    if(fila_vazia(f) == 1)
        return 0;
    f->ini = NULL;
    f->fim = NULL;
    return 1;
}
