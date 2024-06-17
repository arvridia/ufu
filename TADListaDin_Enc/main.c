#include <stdio.h>
#include "TADListaDin_Enc.h"


void imprimir_lista(lista lista1) {
    int cont = 1;
    if (lista_vazia(lista1) == 1) {
        printf("Nao ha elementos\n");
        return;
    }
    for(;;cont++) {
        char carac;
        if (carac = get_carac(lista1,cont,carac) == 0) {
            break;
        }
        printf("%c\n", carac);
    }
}
int main(){
    int Num = 0;
    int X = 0;
    lista lista1;
    do{
        do{
            printf("Digite '1' caso queira criar uma nova lista;\nDigite '2' caso queira inserir um elemento;\nDigite '3' caso queira remover um elemento;\nDigite '4' caso queira imprimir toda os dados da lista;\nDigite '5' caso deseje finalizar o programa.\n");
            scanf("%d", &Num);
            if(Num < 1 || Num > 5){
                printf("O numero digitado deve ser >= 1 e <= 5\nO programa foi finalizado.");
                return 0;
            }
            continue;
        }while (Num < 1 || Num > 5);
        if (Num == 5){
            return 0;
        }
        if (Num != 1 && X == 0) {
                printf("Primeiramente deve se criar a lista\n");
        }
        if (Num == 1) {
            if(X > 0){
                limpa_lista(&lista1);
                X = 0;
                printf("A antiga lista foi apagada e uma nova sera criada\n");
            }
            lista1 = cria_lista();
            if(lista1 == NULL) {
                printf("Lista criada\n");
            }
            else{
                printf("Erro ao alocar");
                return -1;
            }
            X++;
        }
        if(Num == 2){
            char carac;
            printf("Digite o caracter que sera inserida na lista:\n");
            scanf("%c", carac);
            if (insere_ord(lista1, carac) == 0)
                printf("Nao foi possivel inserir o elemento.\n");
            else
                printf("Sucesso na insercao.\n");
            }
        if(Num == 3){
            char carac;
            printf("Digite o caracter que deseja remover\n");
            scanf("%s", carac);
            if (remove_ord(lista1, carac) == 0) {
                if (lista_vazia(lista1) == 1)
                    printf("Nao ha caracteres na lista");
                else
                    printf("Esse caracter nao existe\n");
            }
            else
                printf("Sucesso na remocao\n");
        }
        if(Num == 4){
            imprimir_lista(lista1);
            }
    }while(Num != 5);
    limpa_lista(&lista1);
    return 0;
}
