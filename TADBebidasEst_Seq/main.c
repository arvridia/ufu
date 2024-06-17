#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADBebidasEst_Seq.h"

void imprimir_lista(lista lista1){
    int count;
    if(lista_vazia(lista1)){
            printf("Lista vazia\n");
            return;
    }
    for(count = 0; count < lista1.fim; count++){
        printf("%d bebida cadastrada:", count+1);
        printf("%s\n",lista1.p[count].Nome);
        printf("%d\n",lista1.p[count].Volume);
        printf("%f\n",lista1.p[count].Preco);
    }
    printf("\n");
}

int main()
{
lista lista1 = criar_lista();
while(1)
	{
        int num = 0;
		printf("\nDigite 1 para cadastrar uma bebida, 2 para remover um cadastro feito, 3 para mostrar os cadastros realizados e 4 para encerrar o programa.\n");
		scanf("%d", &num);
		printf("\n");
		if(num >= 1 && num <= 4)
		{
            if(num == 1){
                if(lista_cheia(lista1))//so a chamada
                    printf("A lista esta cheia.\n");
                else{
                    bebidas bebida_1;
                    printf("\nDigite o nome da bebida:\n");
                    scanf("%s", bebida_1.Nome);
                    printf("Digite o volume da bebida:\n");
                    scanf("%d", &bebida_1.Volume);
                    printf("Digite o preco da bebida:\n");
                    scanf("%f", &bebida_1.Preco);
                    lista1 = insere_elem(lista1,bebida_1);
                }
            }
            if(num == 2){
                char entrada[20];
                printf("\nDigite o nome do elemento que deseja remover:\n");
                scanf("%s", entrada );
                lista1 = remove_elem(lista1,entrada);
            }
			if(num == 3){
                imprimir_lista(lista1);
			}
			if(num == 4){
                return 0;
			}
		}
		else
			printf("\nEsta opcao nao existe, o programa sera encerrado.\n");
	}
	return 0;
}
