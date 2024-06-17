#include <stdio.h>
#include <stdlib.h>
#include "TADFPA_Din_Enc.h"

void imprimir_fila(Fila p)
{
    Fila X = cria_fila();
    if(fila_vazia(p) == 1)
        printf("\nA lista esta vazia!\n");
    else{
        printf("\n");
        while(fila_vazia(p) != 1)
        {
            int f;
            remove_ini(p,&f);
            printf("Numero:%d \n", f);
            insere_ord(X,f); // passagem de elementos para fila X
        }
        while(fila_vazia(X) != 1)
        {
            int f;
            remove_ini(X,&f);
            insere_ord(p,f); // passagem de elementos para fila p
        }
    }
}

int main()
{
    int swi, sinal = 0; // sinal contabiliza a qtde de reinicializacoes da fila
    Fila P;
    int A;
    do {
        do{
            // Obtem opcao do usuario
            printf("\nOpcoes:\n");
            printf("[1] Criar uma fila\n");
            printf("[2] Inserir um elemento na fila\n");
            printf("[3] Remover um elemento da fila\n");
            printf("[4] Imprimir a fila\n");
            printf("[5] Esvaziar fila\n");
            printf("[6] Apagar fila\n");
            printf("[7] Sair do sistema\n");
            printf("\nQual opcao deseja realizar? ");
            scanf("%d", &swi);
            setbuf(stdin, NULL);
            if (swi < 1 || swi > 7)
                printf("\nOpcao invalida...Somente existem essas opcoes:\n");

        } while (swi < 1 || swi > 7);

        if (swi == 7)
            break;
        else if (swi != 1 && sinal == 0) {
            printf("\nAntes de realizar operacoes, crie uma fila.\n\n");
            continue;
        }

        switch (swi) {
            case 1: {
                if (sinal) { // Verifica se a fila já existe
                    apaga_fila(P);
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
                printf("Digite o numero: \n");
                scanf("%d", &A);
                if (insere_ord(P, A) == 0)
                    printf("\nA fila esta cheia! A numero %d nao foi incluido.\n\n", A);
                else
                    printf("\nO numero %d foi incluido com sucesso!\n\n", A);
                break;
            }
            case 3: {
                if (remove_ini(P,&A) == 0) {
                    printf("\nFila vazia!\n\n");
                }
                else
                    printf("\nO numero %d foi removido com sucesso!\n\n", A);
                break;
            }
            case 4:{
                imprimir_fila(P);
                break;
            }
            case 5:{
                if(esvazia_fila(P) == 0)
                    printf("A fila ja esta vazia!");
                printf("A fila foi esvaziada!\n");
                break;
            }
            case 6:{
                apaga_fila(P);
                printf("A fila foi apagada!\n");
                sinal--;
                break;
            }
        }
    }while (swi != 7);
    printf("\nEncerrando o programa...\n");
    return 0;
}
