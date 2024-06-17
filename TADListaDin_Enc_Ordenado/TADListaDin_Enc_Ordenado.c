#include <stdlib.h>
#include "TADListaDin_Enc_Ordenado.h"
///////////////////////

struct no{
    int num;
    struct no *prox;
};

typedef struct no *lista;

lista inicializar_lista(){
    return NULL;
}

int lista_vazia(lista lista1){
    if(lista1 == NULL)
        return 1;
    else
        return 0;//nao vazia
}

int insere_ord(lista *lista1, int elem){
    lista N = (lista)malloc(sizeof(struct no));
    if (N == NULL){
        return 0;//faz papel da funcao lista_cheia
    }
    N->num = elem;
    if(lista_vazia(*lista1)||elem<= (*lista1)->num){
        N->prox = *lista1;
        *lista1 = N;
        return 1;
    }
    lista aux = *lista1;
    while(aux->prox != NULL && aux->prox->num < elem)
        aux = aux->prox;
    N->prox = aux->prox;
    aux->prox = N;
    return 1;
}

int remove_ord(lista *lista1, int elem){
    if(lista_vazia(*lista1)== 1 || elem < (*lista1)->num)
        return 0;//FALHA
    lista aux = *lista1;
    if(elem == (*lista1)->num){
        *lista1 = aux->prox;
        free(aux);
        return 1;
    }
    //percorrimento
    while(aux->prox != NULL && aux->prox->num < elem){
        aux = aux->prox;
    }
    if(aux->prox == NULL|| aux->prox->num > elem)
        return 0;//FALHA
    //remove elemento != 1 no da lista
    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    return 1;
}

///////////////////////
void apaga_lista(lista *lista1){
    free(lista1);
}

int get_pos(lista *lista1,int pos){
    //retorna o conteudo do elemento na posicao indicada
    lista aux = *lista1;
    while(aux->prox != NULL /*&& aux->prox != pos*/){
        aux = aux->prox;
    }
    return aux->prox->num;
}//o de baixo eh uma opcao tambem
int get_num(lista lista1, int pos, int *nani) {
    if (lista1->prox == NULL || lista_vazia(lista1) || pos <= 0 || lista1->prox == NULL)
        return 0; // FALHA
    lista aux = lista1;
    /*while(aux->prox != NULL /*&& aux->prox != pos){
        aux = aux->prox;
    }*/
    for(;pos > 0;pos--)
        aux = aux->prox;
    *nani = aux->prox->num;
    return 1;
}


int remove_pos(lista lista1, int pos)
//retorna e remove o elemento por posicao ou ao digitar o numero, 1 ocorrencia
{
    int nani  = -1;
    int i;
    if(lista_vazia(lista1)){
            return 0;
    }
    //if pos verifica se a pos existe dentro da lista


    /*for(int i = 0; i < lista1.fim; i++){
        if(strcmp(lista1.p[i].Nome,elem) == 0){
            pos = i;
            break;
        }
    }*/


    //percorrimento
    lista aux = lista1;
    //talvez seja null msm
    for(i = 0; aux->prox != NULL && i < pos; i++){
        aux = aux->prox;
    }
    nani = aux->prox->num;
    //if(aux->prox == NULL|| aux->prox->num > pos)
        //return 0;//FALHA
    //remove elemento != 1 no da lista
    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    return nani;
}
