#include <stdio.h>
#include <stdlib.h>
#include "TADFila_Est_Seq_DesPosVDD.h"
#define MAX 10

void imprimir_fila(Fila p)
{
    Fila X = cria_fila();
    if(fila_vazia(p) == 1)
        printf("\nA lista esta vazia!\n");
    else{
        int cont = 1;
        while(fila_vazia(p) != 1)
        {
            char A[MAX];
            char *pp;
            pp = A;
            remove_ini(p,&pp);
            printf("\n\nString %d: \n", cont);
            printf("%s\n", A);
            cont++;
            insere_fim(X,A); // passagem de elementos para fila X
        }
        while(fila_vazia(X) != 1)
        {
            char B[MAX];
            char *ppp;
            ppp = B;
            remove_ini(X,&ppp);
            insere_fim(p,B); // passagem de elementos para fila p
            //pilha era fim fim agr é insere fim e remove ini
        }
    }
}

int main()
{
    int swi, sinal = 0; // sinal contabiliza a qtde de reinicializacoes da fila
    Fila P;
    char A[MAX];
    do {
        do{
            // Obtem opcao do usuario
            printf("\nOpcoes:\n");
            printf("[1] Criar uma fila\n");
            printf("[2] Inserir um elemento na fila\n");
            printf("[3] Remover um elemento da fila\n");
            printf("[4] Imprimir a fila\n");
            printf("[5] Sair do sistema\n");
            printf("\nQual opcao deseja realizar? ");
            scanf("%d", &swi);
            setbuf(stdin, NULL);
            if (swi < 1 || swi > 5)
                printf("\nOpcao invalida...Somente existem essas opcoes:\n");

        } while (swi < 1 || swi > 5);

        if (swi == 5)
            break;
        else if (swi != 1 && sinal == 0) {
            printf("\nAntes de realizar operacoes, crie uma fila.\n\n");
            continue;
        }

        switch (swi) {
            case 1: {
                if (sinal) { // Verifica se a fila já existe
                    libera_fila(&P);
                }

                P = cria_fila();
                if (P == NULL) {
                    printf("\nFalha na alocacao...\n\n");
                    return -1;
                }

                if (sinal)
                    printf("\nReinicializacao da fila pela %d vez...\n\n", sinal);
                else
                    printf("\nCriacao bem sucessida!\n\n");

                sinal++;

                break;
            }
            case 2: {
                printf("Digite a string a ser inserida na pilha: \n");
                fflush(stdin);
                gets(A);
                if (insere_fim(P, A) == 0)
                    printf("\nA fila esta cheia! A string %s nao foi incluido.\n\n", A);
                else
                    printf("\nA string %s foi incluida com sucesso!\n\n", A);
                break;
            }
            case 3: {
                char *pppp;
                pppp = A;
                if (remove_ini(P,&pppp) == 0) {
                    printf("\nFila vazia!\n\n");
                }
                else
                    printf("\nA string %s foi removido com sucesso!\n\n", A);
                break;
            }
            case 4:{
                imprimir_fila(P);
                break;
            }
        }
    }while (swi != 5);
    printf("\nEncerrando o programa...\n");
    return 0;
}
