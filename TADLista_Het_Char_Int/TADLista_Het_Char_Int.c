#include <stdlib.h>
#include "TADlista_Het_Char_Int.h"

struct no
{
    int type;
    union
    {
        int num;
        char elem;
    } info;

    struct no * prox;
};


lista cria_lista()
{
    return NULL;
}

int lista_vazia(lista lst)
{
    if (lst == NULL)
        return 1;
    else
        return 0;
}

void limpa_lista(lista *lst){
    while(*lst != NULL){
        lista aux = *lst;
        *lst = aux->prox;
        free(aux);
    }
}

int insere_elem (lista *lst, int num, char elem, int type)
{
    lista N = (lista) malloc(sizeof(struct no));
    if (N == NULL)
        return 0;
    if(type == 0)
        N->info.num = num;
    else if(type == 1)
        N->info.elem = elem;
    else
        return 0;
    N->prox = *lst;
    *lst = N;
    return 1;
}

int remove_elem (lista *lst, int num, char elem, int type)
{
    if (lista_vazia(*lst) == 1)
        return 0;
    lista aux = *lst;
    if(type == 0){
        if (num == (*lst)->info.num){
            *lst = aux->prox;
            free(aux);
            return 1;
        }
        while (aux->prox != NULL && aux->prox->info.num != num)
            aux = aux->prox;
        if (aux->prox == NULL)
            return 0;
    }
    else{
        if(type == 1){
            if (elem == (*lst)->info.elem){
                *lst = aux->prox;
                free(aux);
                return 1;
            }
        }
        while (aux->prox != NULL && aux->prox->info.elem != elem)
            aux = aux->prox;
        if (aux->prox == NULL)
            return 0;
        else
            return 0;
    }
    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    return 1;
}



int get_elem(lista lst, int position, int *num, char *elem, int *type)
{
    lista aux = lst;
    int pos = 0;
    while (aux->prox != NULL && pos < position){
        if(pos < position && aux->prox == NULL)
            return 0;
        aux = aux->prox;
        pos++;
    }
    *num = aux->info.num;
    *elem = aux->info.elem;
    *type = aux->type;
    return 1;
}




