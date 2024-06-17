#include <stdlib.h>
#include "tadex2.h"
#include <math.h>
#define MAX 20

struct lista {
    float no[MAX];
    int Fim;
};

Lista cria_lista() {

    Lista lst = (Lista) malloc(sizeof(struct lista));

    if (lst != NULL)
        lst->Fim = 0;

    return lst;
}

int lista_vazia(Lista lst) {
    if (lst == NULL) return -1;//caso a lista nao foi criada com sucesso
    return (lst->Fim == 0);//return 1 caso a lista esteja vazia (fim == 0)
}

int lista_cheia(Lista lst) {
    if (lst == NULL) return -1;
    return (lst->Fim == MAX);//return 1 caso a lista esteja cheia (fim == MAX)
}

int insere_elem(Lista lst, float elem) {
    if (lst == NULL || lista_cheia(lst) == 1)//verifica se a lista foi criada com sucesso e se esta cheia
        return 0;

    lst->no[lst->Fim] = elem; // Insere elemento
    lst->Fim++; // Avança o Fim

    return 1;
}

int remove_elem(Lista lst, float elem) {
    if (lst == NULL || lista_vazia(lst))//verifica se a lista foi criada com sucesso e se esta vazia
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
    lst->Fim = 0;//para inicializar uma lista, basta tornar o fim 0, que sinaliza estar vazia
}

int get_elem(Lista lst, int pos, float *elem) {

    if (lst == NULL || lista_vazia(lst) || pos <= 0 || pos > lst->Fim)//uma posicao menor que 0 nao faz sentido, nem uma maior que a quantidade de elementos da lista
        return 0; // FALHA

    *elem = lst->no[pos-1];//como a posicao eh inserida por quantidade de elementos e um array comeca no 0, a pos eh decrementada em 1
    return 1; // SUCESSO
}
int remove_impar(Lista lst){
    if (lst == NULL || lista_vazia(lst))
        return 0; // FALHA

    int i, Aux = 0;

    // Percorrimento até achar o elem ou final de lista
    while(1){
        while (Aux < lst->Fim && fmod(lst->no[Aux], 2) == 0)//enquanto o elemento for par, a lista avanca, quando for impar o laco para ou quado chega o fim da lista
            Aux++;

        if (Aux == lst->Fim){ // Final de lista
            break;;
        }

        // Deslocamento à esq. do sucessor até o final da lista
        for (i = Aux+1; i < lst->Fim; i++)//removendo o numero impar
            lst->no[i-1] = lst->no[i];

        lst->Fim--; // Decremento do campo Fim
    }
    return 1; // Sucesso
}
int tamanho(Lista lst){
    return lst->Fim;//para saber o tamnho de uma lista basta saber o tamanho do fim ja que adotamos o fim como sendo a quantidade de elementos na lista
}
int esvaziar(Lista lst){
    if (lst == NULL || lista_vazia(lst))
        return 0; // FALHA
    else
        lst->Fim = 0;//para esvaziar basta tornar o fim = 0
    return 1;
}
int retorna_maior(Lista lst, float *num){
    if (lst == NULL || lista_vazia(lst))
        return 0; // FALHA
    int aux = 0;
    int cont;
    int i;
    for(cont = 0, i = 0; cont <= lst->Fim; cont++, i++){//o laco ocorrera enquanto a variavel contadora for diferente do fim, ou seja, percorrera todos os elementos da lista
        if(lst->no[i] > aux){//caso ache um elemento maior que o valor que esta armazenado na variavel, a variavel passa a guardar ele e esse processo se repete ate o fim da lista
            aux = lst->no[i];
        }
    }
    *num = aux;
    return 1;//sucesso
}
Lista inverter(Lista lst){
    Lista L2 = (Lista) malloc(sizeof(struct lista));
    if (L2 != NULL)
        L2->Fim = 0;
    else
        return L2;
    int i;
    int cont = 0;
    cont = lst->Fim-1;//como fim sinaliza a quantidade de elementos e um array comeca no 0 e nao no 1, o ultimo elemento esta na posicao fim-1
    for(i = 0; cont >= 0; cont --, i++, L2->Fim++)//este laco percorre a nova lista que sera retornada do comeco, inserindo os elementos de tras pra frente da lista primaria, comecando no ultimo ate o primeiro, ou seja, a lista sera invertida
        L2->no[i] = lst->no[cont];
    return L2;
}
Lista concatenar(Lista lst, Lista L2){
//retorna uma lista l3 que contem os elementos de L1 seguidos dos de L2
    int cont = 0;
    int i;
    Lista L3;
    L3 = cria_lista();
    for (i = 0; i < lst->Fim; i++, L3->Fim++)//insere os elementos da primeira lista na que sera a concatenacao, o laco acaba quando a variavel contadora for igual ao fim da lista, ou seja, todos os elementos foram inseridos
        L3->no[i] = lst->no[i];
    for (; i < lst->Fim + L2->Fim; i++, L3->Fim++)//enquanto a variavel contadora (que no momento esta com o tamanho da primeira lista) for menor que a soma do tamanho das duas listas, o laco ocorrera
    {
        if(lista_cheia(L3) == 1){
            return NULL;//falha se o numero maximo de elementos foi atingido
        }
        else{
            L3->no[i] = L2->no[cont];//insere elementos agora da segunda lista na que sera a concatenacao
            cont++;
        }
    }
    return L3;//retorna a concatenacao
}
