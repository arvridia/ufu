#include <stdio.h>
#include "TADdin_enc_ord_fre.h"

void imprimir_lista(lista *lista1)
{
    if (lista_vazia(lista1) == 1)
    {
        printf("Nao ha elementos\n");
        return;
    }
    fflush(stdin);
    printf("\n");
    int cont = 1;
    while(1)
    {
        int nani = 0;
        if(get_num(lista1,cont,&nani)== 0)
        {
            break;
        }
        fflush(stdin);
        printf("%d\n", nani);
        cont ++;
    }
    printf("\n");
}

int main()
{
    int Num = 0;
    int X = 0;
    lista lista1;

    do
    {
        do
        {
            printf("\nDigite '1' caso queira criar uma nova lista;\nDigite '2' caso queira inserir um elemento;\nDigite '3' caso queira remover um elemento;\n");
            printf("Digite '4' caso queira imprimir toda os dados da lista;\nDigite '5' caso deseje finalizar o programa.\n");
            fflush(stdin);
            scanf("%d", &Num);
            if(Num < 1 || Num > 5)
            {
                printf("\nO numero digitado deve ser >= 1 e <= 5\nO programa foi finalizado.\n");
                return 0;
            }
            continue;
        }
        while (Num < 1 || Num > 5);
        if (Num == 5){
            return 0;
        }
        if (Num != 1 && X == 0) {
                printf("\n");
                printf("Primeiramente deve se criar a lista\nSistema encerrado");
                break;
        }
        if (Num == 1) {
            printf("\n");
            if(X > 0){
                apaga_lista(&lista1);
                X = 0;
                printf("A antiga lista foi apagada e uma nova sera criada\n");
            }
            lista1 = inicializar_lista();
            if(lista1 != NULL) {
                printf("Lista criada\n");
            }
            else{
                printf("Erro ao alocar");
                return -1;
            }
            X++;
        }
        if(Num == 2){
            printf("\n");
            int num;
            printf("Digite o numero que sera inserido na lista:\n");
            scanf("%d", &num);
            if (insere_ord(lista1, num) == 0)
                printf("Nao foi possivel inserir o elemento.\n");
            else
                printf("\nSucesso na insercao.\n");
            }
        if(Num == 3)
        {
            printf("\n");
            int num = 0;
            printf("Insera o elemento:\n");
            scanf("%d", &num);
            if (remove_ord(lista1, num) == 0)
            {
                if (lista_vazia(lista1) == 1)
                    printf("Nao ha elementos na lista");
                else
                    printf("Esse numero nao existe\n");
            }
            else
                printf("Sucesso na remocao\n");
        }
        if(Num == 4)
        {
            imprimir_lista(lista1);
        }
    }while(Num != 5);

    apaga_lista(&lista1);

    return 0;
}


