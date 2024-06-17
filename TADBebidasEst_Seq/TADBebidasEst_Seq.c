#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADBebidasEst_Seq.h"
#define MAXC 20

lista criar_lista(){
    lista lista1;
    lista1.fim = 0;
    lista1.p = malloc(MAXC*sizeof(bebidas));
    return lista1;
}
int lista_vazia(lista lista1){
    if(lista1.fim == 0)
        return 1;
    else
        return 0;
}
int lista_cheia(lista lista1){
    if(lista1.fim == MAXC){
        return 1;
    }
    else{
        return 0;
    }
}
bebidas get_pos(lista lista1, int pos){
    return lista1.p[pos];
}
lista insere_elem(lista lista1, bebidas elem){
    if(lista_cheia(lista1)){
        return ;
    }
    lista1.p[lista1.fim] = elem;
    lista1.fim++;
    return ordena_lista(lista1);
}
lista remove_elem(lista lista1, char elem[20]){
    int pos  = -1;
    if(lista_vazia(lista1)){
            return;
    }
    for(int i = 0; i < lista1.fim; i++){
        if(strcmp(lista1.p[i].Nome,elem) == 0){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        printf("Elemento nao existe\n");
        return;
    }

    for(int i = pos; i < lista1.fim; i++){
        bebidas temp = lista1.p[i];
        lista1.p[i] = lista1.p[i+1];
        lista1.p[i+1] = temp;
    }

    lista1.fim--;
    return lista1;
}
lista ordena_lista(lista lista1){
    int terminou = 0;

    while(terminou == 0)
    {
        terminou = 1;

        for(int i = 0; i < lista1.fim - 1; i++)
        {
            int eh_maior = 0;
            int resultado = strcmp(lista1.p[i].Nome,lista1.p[i+1].Nome);

            if(resultado != 0)
            {
                eh_maior = resultado > 0 ? 1 : 0;
            }
            else
            {
                eh_maior = lista1.p[i].Volume > lista1.p[i+1].Volume ? 1 : 0;
            }

            if(eh_maior == 1)
            {
                bebidas temp = lista1.p[i];
                lista1.p[i] = lista1.p[i+1];
                lista1.p[i+1] = temp;
                terminou = 0;
            }
        }
    }

    return lista1;
}
lista limpa_lista(lista lista1){
    if(lista_vazia(lista1)){
        return;
    }
    lista1.fim = 0;
    return lista1;
}

