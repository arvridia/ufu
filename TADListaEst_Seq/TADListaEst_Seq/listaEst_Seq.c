#include <stdlib.h>
#include "listaEst_Seq.h"
#define MAX 20
#include <string.h>

struct lista {
    char string[MAX];
    int fim;
};
lista cria_lista() {
    lista lista1 = (lista) malloc(sizeof(struct lista));
    if (lista1 != NULL)
        lista1->fim = 0;
    return lista1;
}
int lista_vazia(lista lista1) {
    if (lista1 == NULL) return -1;
    return (lista1->fim == 0);
}
int lista_cheia(lista lista1) {
    if (lista1 == NULL) return -1;
    return (lista1->fim == MAX);
}
int insere_frase(lista lista1, char *frase) {
    if (lista1 == NULL || lista_cheia(lista1) == 1)
        return 0;
    //strcpy(lista1->string[lista1->fim],*frase);
    lista1->string[lista1->fim] = strdup(*frase);
    lista1->fim++;
    return 1;
}
int remove_frase(lista lista1, char *frase) {
    if (lista1 == NULL || lista_vazia(lista1))
        return 0;
    int cont = 0;
    int interm = 0;
    //while (interm < lista1->fim && strcmp(lista1->string[interm],*frase))
    while (interm < lista1->fim && lista1->string[interm] != *frase) //so comparando se é igual
        interm++;
    if (interm == lista1->fim)
        return 0;
    for (cont = interm+1; cont < lista1->fim; cont++)
        lista1->string[cont-1] = lista1->string[cont];
    lista1->fim--;
    return 1;
}
char get_pos(lista lista1, int pos) {
    if (lista1 == NULL || lista_vazia(lista1) || pos <= 0 || pos > lista1->fim)
        return 0;
    return lista1->string[pos-1];
}
int get_frase(lista lista1, int pos, char *frase) {

    if (lista1 == NULL || lista_vazia(lista1) || pos <= 0 || pos > lista1->fim)
        return 0;

    *frase = lista1->string[pos-1];
    return 1;
}
void apaga_lista (lista *lista1) {
    free (*lista1);
    *lista1 = NULL;
}
