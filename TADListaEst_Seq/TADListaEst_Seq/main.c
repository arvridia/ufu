#include <stdio.h>
#include "listaEst_Seq.h"
#define MAXC 10

void imprimir_lista(lista lista1) {
    int cont = 1;
    if (lista_vazia(lista1) == 1) {
        printf("Nao ha elementos\n");
        return;
    }
    for(;;cont++) {
        char frase;
        if (get_frase(lista1,cont, &frase) == 0) {
            break;
        }
        printf("%s\n", &frase);
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
                break;
        }
        if (Num == 1) {
            if(X > 0){
                apaga_lista(&lista1);
                X = 0;
                printf("A antiga lista foi apagada e uma nova sera criada\n");
            }
            lista1 = cria_lista();
            if(lista1 == NULL) {
                printf("Nao foi possivel alocar\n");
                return -1;
            }
            else{
                printf("Lista criada\n");
            }
            X++;
        }
        if(Num == 2){
            char frase[MAXC];
            printf("Digite a string que sera inserida na lista:\n");
            scanf("%s", frase);
            char *p;
            p = &frase;
            if (insere_frase(lista1, p) == 0)
                printf("A capacidade maxima de strings foi atingida, remova alguma caso deseja inserir novas\n");
            else
                printf("Sucesso na insercao\n");
            }
        if(Num == 3){
            char frase[MAXC];
            printf("Digite a frase que deseja remover\n");
            scanf("%s", frase);
            char *p;
            p = &frase;
            if (remove_frase(lista1, p) == 0) {
                if (lista_vazia(lista1) == 1)
                    printf("Nao ha strings na lista");
                else
                    printf("Essa string nao existe\n");
            }
            else
                printf("Sucesso na remocao\n");
        }
        if(Num == 4){
            imprimir_lista(lista1);
            }
    }while(Num != 5);
    apaga_lista(&lista1);
    return 0;
}


