/*Este programa implementa o problema de Josephus utilizando o TAD lista.
  Decidimos pela implementacao dinamica encadeada circular,
  pois os soldados estao agrupados em um circulo e, dentro da logica do problema,
  o sucessor do ultimo soldado sera o primeiro novamente e esta dinamica ocorrera algumas vezes durante a execucao.
  Assim, uma aplicacao que facilite percorrer do ultimo para o primeiro, a circular, eh a melhor

  Desenvolvido por:
  Arthur Resende Santos
  Daniel Gonçalves
  Henrique Braga
  Lorenzo Machado Burgos*/

#include <stdlib.h>
#include <string.h>
#include "TADLista_Enc_Din_Cir_07.h"
#define MAX 30

struct no
{
    char nome[MAX];
    struct no *prox;
};

Lista criar_lista()
{
    return NULL;
}

int lista_vazia(Lista lst)
{
    if(lst == NULL)
        return 1; //vazia
    else
        return 0;
}

int escolha_nome(Lista *lst, char *nome)//esta funcao faz o ponteiro apontar para o nome escolhido, o enunciado pede para comecar a contagem no que o usuario pedir, caso escolha um nome, esta funcao faz isso
{
    if(lista_vazia(*lst) == 1)//a funcao retornara um se estiver vazia
    {
        return 0;
    }
    if(strcmp((*lst)->nome, nome)==0)//se o primeiro elemento ja for o desejado
    {
        return 1; //operacao concluida
    }

    Lista aux=*lst;
    *lst=(*lst)->prox;

    while(*lst != aux && strcmp((*lst)->nome, nome)!= 0)
    {
        *lst=(*lst)->prox;//avanco da lista ate chegar ao elemento desejado ou ate o final da lista
    }
    if(*lst == aux)
    {
        return 0; //"fim" da lista e o elemento nao foi encontrado
    }
    else
    {
        return 1;//operacao concluida
    }
}

int escolha_pos(Lista *lst, int pos, char *nome)//esta funcao faz o ponteiro apontar para a posicao escolhida, o enunciado pede para comecar a contagem no que o usuario pedir, caso escolha uma posicao, esta funcao faz isso
{
    if(lista_vazia(*lst) == 1)
    {
        return 0;
    }

    int i;
    for(i = 1; i < pos ;i++)//avanca ate chegar na posicao escolhida
    {
        *lst = (*lst)->prox;
    }

    strcpy(nome, (*lst)->nome);//para o uso na interface com o usuario, obter o nome do soldado que esta na posicao escolhida eh interessante

    return 1; //operacao concluida
}

int insere_elem(Lista *lst, char *nome)//esta funcao insere no final da lista, visto que os soldados serao agrupados a partir da ordem de insercao
{
    Lista N;
    N = (Lista) malloc (sizeof(struct no));//cria um novo noh para ser inserido
    if(N==NULL)
    {
        return 0; // erro na alocacao
    }

    strcpy(N->nome, nome);//copia o nome recebido para o campo no noh

    if(lista_vazia(*lst) == 1)//caso esteja vazia
    {
        *lst = N;//faz a lisa apontar para o novo no
        N->prox = N;//faz o no apontar para ele mesmo (ja que eh circular e so tem um elemento)
        return 1;
    }
	//caso a lista tenha 1 ou mais elementos
    N->prox = (*lst)->prox;//faz o novo no apontar para o primeiro no
    (*lst)->prox = N;//faz o ultimo noh apontar para o novo noh
    *lst = N;//faz a lista apontar para o novo no(ultimo no)
    return 1;
}

int remove_pos(Lista *lst, int pos, int qnt, char *nome)
{
    if(lista_vazia(*lst) == 1)
    {
        return 0;
    }
    Lista aux=*lst;
    int i;
    for(i=1;i<pos;i++)//percorre ate chegar na posicao desejada
    {
        (*lst)=(*lst)->prox;
    }

    while(aux->prox != *lst)//avanca o auxiliar ate a posicao desejada, uma anterior a da lst
    {
        aux=aux->prox;
    }
    Lista aux2 = *lst;//aux2 guarda o endereco do no que deseja remover

    strcpy(nome, (*lst)->nome);

    aux->prox = aux2->prox;//aux->prox recebe o endereco do proximo elemento
    (*lst) = (*lst)->prox;//a lista, que continha o endereco do elemento que deseja remover avancou
				//portanto a informacao do no foi perdida, o no foi removido da lista


    free(aux2);
    if(qnt == 1)//sinaliza se o elemento removido era o ultimo,se for o caso, ele eh o vencedor
    {
        return -1;
    }
    return 1;
}

int get_nome(Lista lst, int pos, char *nome)
{
    if (pos < 1 || pos > tamanho(lst))//se a posicao pesquisada eh menor que 1 nao faz sentido nem pode ser maior que o tamanho da lista(numero de elementos)
    {
        printf("\nERRO! Consulta invalida.\n");
        return 0;
    }
    for (;pos>0;pos--)
        lst = lst->prox;//avanca a lista ate chegar na posicao desejada
    strcpy(*nome, lst->nome);//copia o nome para a variavel passada
    return 1;
}

int tamanho(Lista lst)
{
    if (lst == NULL)
        return (0);
    else
    {
        Lista aux;
        int cont;
        for (cont = 1, aux = lst->prox; aux != lst; cont++)//avanca a lista e para cada a avanco a variavel cont aumenta em 1, no final da lista ela tera o numero de elementos
            aux = aux->prox;
        return cont;
    }
}

