#include <stdlib.h>
#include "TADDin_Enc_Ord.h"
///////////////////////

struct no{
    int num;
    struct no *prox;
};

typedef struct no *lista;

lista inicializar_lista()
{
    return NULL;
}

int lista_vazia(lista lista1)
{
    if(lista1 == NULL)
        return 1;

    else
        return 0;//nao vazia
}

/*int insere_ord(lista *lista1, int elem)
{
    lista N = (lista)malloc(sizeof(struct no));
    if (N == NULL)
    {
        return 0;//faz papel da funcao lista_cheia
    }

    N->num = elem;

    if(lista_vazia(*lista1) == 1 || elem <= (*lista1)->num)
    {
        (*N).prox = *lista1;
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
*/
/*
int remove_ord(lista *lista1, int elem)
{
    if(lista_vazia(*lista1)== 1 || elem < (*lista1)->num)
        return 0;//FALHA
    lista aux = *lista1;
    if(elem == (*lista1)->num)
    {
        *lista1 = aux->prox;
        free(aux);
        return 1;
    }

    while(aux->prox != NULL && aux->prox->num < elem)
    {
        aux = aux->prox;
    }
    if(aux->prox == NULL|| aux->prox->num > elem)
        return 0;//FALHA

    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);

    return 1;
}
*/
///////////////////////
int apaga_lista(lista *lista1)
{
    if (lista_vazia(*lista1) == 1)
    {
        return 0; // Falha
    }
    else
    {
       free(lista1);
       (*lista1) = NULL;
        return 1;
    }

}


int get_pos(lista *lista1,int pos)
{
    //retorna o conteudo do elemento na posicao indicada
    lista aux = *lista1;
    while(aux->prox != NULL) /*&& aux->prox != pos*/
    {
        aux = aux->prox;
    }
    return aux->prox->num;
}//o de baixo eh uma opcao tambem

int get_num(lista lista1, int pos, int *nani)
{
    if ( lista_vazia(lista1) || pos <= 0 )
        return 0; // FALHA
    lista aux = lista1;

    for(;aux->prox != NULL && pos > 1;pos--)
        aux = aux->prox;

    if(pos > 1)
        return 0;

    *nani = aux->num;
    return 1;
}


int remove_pos(lista *lista1, int pos)
//retorna e remove o elemento por posicao ou ao digitar o numero, 1 ocorrencia
{
    if(lista_vazia((*lista1)))
    {
        return 0;
    }
    lista aux = (*lista1);

  if (pos == 1)
    {
        *lista1 = (*aux).prox; //lista aponta para segundo nó
        free(aux); //libera memória de aux
        return 1;
    }

    for(int i = 2; aux->prox != NULL && i < pos; i++)
    {
        aux = (*aux).prox;
    }

    if(aux->prox == NULL) //fim da lista
        return 0;

    lista aux2 = (*aux).prox;
    (*aux).prox = (*aux2).prox;
    free(aux2);

    return 1;
}

int insere_ord(lista *lista1, int elem){
    if(lista_vazia(*lista1) || elem <= (*lista1)->num){
        lista N = (lista)malloc(sizeof(struct no));
        if(N == NULL)
            return 0;
        N->num = elem;
        N = *lista1; //N->prox
        *lista1 = N;
        return 1;
    }
    else{
        int R = 0;
        R = insere_ord((&(*lista1)->prox), elem);
        return R;
    }
}

int remove_ord(lista *lista1, int elem){
    if(lista_vazia(*lista1)|| elem < (*lista1)->num)
        return 0;
    else{
        if(elem == (*lista1)->num){
            lista aux = *lista1;
            lista1 = aux->prox;
            free(aux);
            return 1;
        }
        else{
            int R = 0;
            R = remove_ord((&(*lista1)->prox), elem);
            return R;
        }
    }
}
int obtem_elem(lista *lista1, int posicao, int *elem)
{
   if(lista_vazia(lista1))
        return 0;

    if(posicao == 0)
    {
        *elem = (*lista1)->num;
        return 1;
    }
    if((*lista1)->prox == NULL)
        return 0;

    return obtem_elem((*lista1)->prox, posicao -1, elem);
}
