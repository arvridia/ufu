#include <stdio.h>
#include <stdlib.h>
#include "TADPilha_Din_Enc.h"
#define MAX 20

void imprimir_pilha(Pilha p)
{
    if(pilha_vazia(p) == 1)
        printf("A lista esta vazia!!");
    else{
    Pilha X = cria_pilha();
        int cont = 1;
        while(pilha_vazia(p) != 1)
        {
            char A[MAX];
            char *pp;
            pp = A;
            pilha_pop(&p,&pp);
            pilha_push(&X,A); // passagem de elementos para pilha X

        }
            while(pilha_vazia(X) != 1)
        {
            char B[MAX];
            char *ppp;
            ppp = B;
            pilha_pop(&X,&ppp);
            printf("\n\nString %d: \n", cont);
            printf("%s\n", B);
            cont++;
            pilha_push(&p,B); // passagem de elementos para pilha p

        }
    }
}

int main()
{
    int swi, sinal = 0; // sinal contabiliza a qtde de reinicializacoes da pilha
    Pilha P;
    char A[MAX];
    do {
        do{
            // Obtem opcao do usuario
            printf("\n\nOpcoes:\n");
            printf("[1] Criar uma pilha\n");
            printf("[2] Inserir um elemento na pilha\n");
            printf("[3] Remover um elemento da pilha\n");
            printf("[4] Imprimir a pilha\n");
            printf("[5] Imprimir o elemento do topo da pilha\n");
            printf("[6] Esvaziar pilha\n");
            printf("[7] Liberar pilha\n");
            printf("[8] Sair do sistema\n");
            printf("\nQual opcao deseja realizar? ");
            scanf("%d", &swi);
            setbuf(stdin, NULL);
            if (swi < 1 || swi > 8)
                printf("\nOpcao invalida...Somente existem essas opcoes:\n");

        } while (swi < 1 || swi > 8);

        if (swi == 8)
            break;
        else if (swi != 1 && sinal == 0) {
            printf("\nAntes de realizar operacoes, crie uma pilha.\n\n");
            continue;
        }

        switch (swi) {
            case 1: {
                if (sinal) { // Verifica se a pilha já existe
                    libera_pilha(&P);
                }

                P = cria_pilha();
                if (sinal)
                    printf("\nReinicializacao da pilha pela %d vez...\n\n", sinal);
                else
                    printf("\nCriacao bem sucessida!\n\n");

                sinal++;

                break;
            }
            case 2: {
                printf("Digite a string a ser inserida na pilha: \n");
                fflush(stdin);
                gets(A);
                if (pilha_push(&P, A) == 0)
                    printf("\nA pilha esta cheia! A string %s nao foi incluida.\n\n", A);
                else
                    printf("\nA string %s foi incluida com sucesso!\n\n", A);
                break;
            }
            case 3: {
                char *pppp;
                pppp = A;
                if (pilha_pop(&P,&pppp) == 0) {
                    printf("\nPilha vazia!\n\n");
                }
                else
                    printf("\nA string %s foi removida com sucesso!\n\n", A);
                break;
            }
            case 4:{
                imprimir_pilha(P);
                break;
            }
            case 5:{
                char B[MAX];
                char *ppppp;
                ppppp = B;
                if(get_topo(&P, &ppppp) == 0)
                    printf("\nOcorreu um erro...Verifique se a pilha nao esta vazia\n");
                else{
                    printf("\nA string do topo da pilha eh: %s ", B);
                }
                break;
            }
            case 6:{
                esvazia_pilha(&P);
                break;
            }
            case 7:{
                libera_pilha(&P);
                break;
            }
        }
    }while (swi != 8);
    printf("\nEncerrando o programa...\n");
    return 0;
}
