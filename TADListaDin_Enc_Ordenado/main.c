#include <stdio.h>
#include "TADListaDin_Enc_Ordenado.h"
void imprimir_lista(lista *lista1) {
    if (lista_vazia(lista1) == 1) {
        printf("Nao ha elementos\n");
        return;
    }
    int cont;
    for(cont = 1;;cont++) {
        int nani = 0;
        if(get_num(lista1,cont,&nani)== 0){
            break;
            printf("Falha na impressao");
        }
        printf("%d\n", nani);
    }
}
    /*if (lista_vazia(lista1) == 1) {
        printf("Nao ha elementos\n");
        return;
    }
    lista aux = lista1;
    while(aux != NULL){
        printf("%d ", aux->prox->num);
        aux = aux->prox;
    }
    printf("\n");
}
while
    nani = lista->prox->num
    i++*/



int main(){
    int Num = 0;
    int X = 0;
    lista lista1;
    do{
        do{
            printf("Digite '1' caso queira criar uma nova lista;\nDigite '2' caso queira inserir um elemento;\nDigite '3' caso queira remover um elemento;\n");
            printf("Digite '4' caso queira imprimir toda os dados da lista;\nDigite '5' caso deseje finalizar o programa.\n");
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
                apaga_lista(&lista1);
                X = 0;
                printf("A antiga lista foi apagada e uma nova sera criada\n");
            }
            lista1 = inicializar_lista();
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
            int num;
            printf("Digite o numero que sera inserido na lista:\n");
            scanf("%d", &num);
            if (insere_ord(&lista1, num) == 0)
                printf("Nao foi possivel inserir o elemento.\n");
            else
                printf("Sucesso na insercao.\n");
            }
        if(Num == 3){
            int nani;
            printf("Deseja remover por posicao (Digite '10') ou a primeira ocorrencia (Digite '11')?\n");
            scanf("%d", &nani);
            if(nani == 11){
                int num = 0;
                scanf("%d", &num);
                if (remove_ord(&lista1, num) == 0) {
                    if (lista_vazia(lista1) == 1)
                        printf("Nao ha elementos na lista");
                    else
                        printf("Esse numero nao existe\n");
                }
                else
                    printf("Sucesso na remocao\n");
            }
            if(nani == 10){
                int pos = 0;
                int retorno = 0;
                scanf("%d", &pos);
                retorno = remove_pos(lista1, pos);
                if (lista_vazia(lista1) == 1)
                    printf("Nao ha elementos na lista");
                if (retorno < pos-2)
                    printf("Essa posicao nao existe\n");
                else
                    printf("Sucesso na remocao\n");
            }

            else
                printf("Nao ha essa opcao");
        }
        if(Num == 4){
            imprimir_lista(lista1);
        }
    }while(Num != 5);
    apaga_lista(&lista1);
    return 0;
}

