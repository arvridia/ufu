#include <stdlib.h>
#include <string.h>
#include "TADListaDin_Enc_NaoOrd_Alunos.h"
#define MAX 20


struct no{
    unsigned int mat;
    char nome[MAX];
    float media;
    int faltas;
    struct no *prox;
};

typedef struct no *lista;

int size_lista(lista *lista1){
    int i;
    lista aux = *lista1;
    for(i = 0; aux->prox != NULL ; i++)
        aux = aux->prox;
    if(i == 0)
        return -1;
    return i;
}
/*get_pos(lista lista1, int pos){
    int i;
    lista aux = *lista1;
    for(i = 0;i < pos;i)
        aux = aux->prox;
    aux->prox
}*/

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
int insere_elem(lista *lista1, unsigned int mat, char nome, float media, int faltas){

    lista N = (lista) malloc(sizeof(struct no));
    if (N == NULL){
        return 0;//faz papel da funcao lista_cheia
    }
    N->mat = mat;
    strcpy(N->nome, nome);
    N->media = media;
    N->faltas = faltas;
    N->prox = *lista1;
    *lista1 = N;
    return 1;
}

int remove_elem(lista *lista1, int mat)
{
    if(lista_vazia(*lista1)== 1 || mat < (*lista1)->mat)
        return 0;//FALHA
    lista aux = *lista1;
    if(mat == (*lista1)->mat)
    {
        *lista1 = aux->prox;
        free(aux);
        return 1;
    }

    while(aux->prox != NULL && aux->prox->mat < mat)
    {
        aux = aux->prox;
    }
    if(aux->prox == NULL|| aux->prox->mat > mat)
        return 0;//FALHA

    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);

    return 1;
}

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




int get_pos(lista lista1, int pos, unsigned int *mat, char *nome, float *media, int *faltas)
{
    if ( lista_vazia(lista1) || pos <= 0 )
        return 0; // FALHA
    lista aux = lista1;

    for(;aux->prox != NULL && pos > 1;pos--)
        aux = aux->prox;

    if(pos > 1)
        return 0;

    *mat = aux->mat;
    strcpy(*nome, aux->nome);
    *media = aux->media;
    *faltas = aux->faltas;
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





