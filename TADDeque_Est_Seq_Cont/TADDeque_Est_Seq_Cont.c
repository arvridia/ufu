#include <stdlib.h>
#include "TADDeque_Est_Seq_Cont.h"
#define MAX 20

struct deque{
    int info[MAX];
    int ini;
    int cont;
};

Deque cria_deque(){
    Deque D;
    D = (Deque) malloc(sizeof(struct deque));
    if(D != NULL){
        D->ini = 0;
        D->cont = 0;
    }
    return D;
}

int deque_vazio(Deque D){
    if(D->cont == 0)
        return 1;
    else
        return 0;
}

int deque_cheio(Deque D){
    if(D->cont == MAX)
        return 1;
    else
        return 0;
}

int insere_fim(Deque D, int info){
    if(D == NULL || deque_cheio(D) == 1)
        return 0;
    D->info[(D->ini+D->cont)%MAX] = info;
    D->cont++;
    return 1;
}

int insere_ini(Deque D, int info){
    if(D == NULL || deque_cheio(D) == 1)
        return 0;
    if(D->ini == 0)
        D->ini = MAX-13;
    else
        D->ini--;
    D->info[D->ini] = info;
    D->cont++;
    return 1;
}

int remove_ini(Deque D, int *info){
    if(D == NULL || deque_vazio(D) == 1)
        return 0;
    *info = D->info[D->ini];
    D->cont--;
    D->ini = (D->ini+1)%MAX;
    return 1;
}

int remove_fim(Deque D, int *info){
    if(D == NULL || deque_vazio(D) == 1)
        return 0;
    *info = D->info[(D->ini+D->cont-1)%MAX];
    D->cont--;
    return 1;
}

int libera_deque(Deque D){
    if(D == NULL)
        return 0;
    free(D);
    D = NULL;
    return 1;
}

int esvazia_deque(Deque D){
    if(deque_vazio(D) == 1)
        return 0;
    D->ini = 0;
    D->cont = 0;
    return 1;
}
