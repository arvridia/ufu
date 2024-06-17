#include <stdlib.h>
#include "lista.h"

#define MAX 20

struct lista {
    int no[MAX];
    int Fim;
};

Lista cria_lista() {

    Lista lst = (Lista) malloc(sizeof(struct lista));

    if (lst != NULL)
        lst->Fim = 0;

    return lst;
}

int lista_vazia(Lista lst) {
    if (lst == NULL) return -1;
    return (lst->Fim == 0);
}

int lista_cheia(Lista lst) {
    if (lst == NULL) return -1;
    return (lst->Fim == MAX);
}

int insere_elem(Lista lst, int elem) {
    if (lst == NULL || lista_cheia(lst) == 1)
        return 0;

    lst->no[lst->Fim] = elem; // Insere elemento
    lst->Fim++; // Avança o Fim

    return 1;
}

int remove_elem(Lista lst, int elem) {
    if (lst == NULL || lista_vazia(lst))
        return 0; // FALHA

    int i, Aux = 0;

    // Percorrimento até achar o elem ou final de lista
    while (Aux < lst->Fim && lst->no[Aux] != elem)
        Aux++;

    if (Aux == lst->Fim) // Final de lista (elem nao existe)
        return 0; // Falha

    // Deslocamento à esq. do sucessor até o final da lista
    for (i = Aux+1; i < lst->Fim; i++)
        lst->no[i-1] = lst->no[i];

    lst->Fim--; // Decremento do campo Fim
    return 1; // Sucesso
}

void libera_lista (Lista *lst) {
    free (*lst);
    *lst = NULL;
}

void inicializa_lista(Lista lst) {
    lst->Fim = 0;
}

int get_elem(Lista lst, int pos, int *elem) {

    if (lst == NULL || lista_vazia(lst) || pos <= 0 || pos > lst->Fim)
        return 0; // FALHA

    *elem = lst->no[pos-1];
    return 1; // SUCESSO
}