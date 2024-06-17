#include <stdlib.h>
#include "TADListaDin_Enc.h"
#define MAX 20
#include <string.h>

struct no{
    char carac;
    struct no *prox;
};
lista cria_lista(){
    return NULL;

}
int lista_vazia(lista lista1){
    if(lista1 == NULL)
        return 1;
    else
        return 0;
}
int insere_ord(lista *lista1, char elem){
    lista N = (lista) malloc(sizeof(struct no));
    if (N == NULL){
        return 0;//faz papel da funcao lista_cheia
    }
    N->carac = elem;
    if(lista_vazia(*lista1)||elem<= (*lista1)->carac){
        N->prox = *lista1;
        *lista1 = N;
        return 1;
    }
    lista aux = *lista1;
    while(aux->prox != NULL && aux->prox->carac < elem)
        aux = aux->prox;
    N->prox = aux->prox;
    aux->prox = N;
    return 1;
}
int remove_ord(lista *lista1, char elem){
    if(lista_vazia(lista1)==1||elem < (*lista1)->carac)
        return 0;
    lista aux = *lista1;
    if(elem == (*lista1)->carac){
        *lista1 = aux->prox;
        free(aux);
        return 1;
    }
    //percorrimento
    while(aux->prox != NULL && aux->prox->carac != elem){
        aux = aux->prox;
    }
    if(aux->prox == NULL|| aux->prox->carac > elem)
        return 0;
    //remove elemento != 1 no da lista
    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    return 1;
}
void limpa_lista(lista *lista1){
    free(lista1);
}
char obtem_posicao(lista *lista1,int pos){
    lista aux = *lista1;
    while(aux->prox != NULL && aux->prox != pos){
        aux = aux->prox;
    }
    return aux->prox->carac;
}
int get_carac(lista lista1, int pos, char carac) {

    if (lista1 == NULL || lista_vazia(lista1) || pos <= 0 || pos > lista1->carac)
        return 0; // FALHA

    carac = lista1->prox[pos-1].carac;
    return 1; // SUCESSO
}
