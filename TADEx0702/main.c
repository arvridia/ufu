#include <stdio.h>
#include <stdlib.h>
#include "TADEx0702.h"

void imprimir_deque(Deque p)
{
    Deque X = cria_deque();
    if(deque_vazio(p) == 1)
        printf("\nO deque esta vazio!\n");
    else{
        printf("\n");
        while(deque_vazio(p) != 1)
        {
            int f;
            remove_ini(p,&f);
            printf("Numero:%d \n", f);
            insere_fim(X,f); // passagem de elementos para deque X
        }
        while(deque_vazio(X) != 1)
        {
            int f;
            remove_ini(X,&f);
            insere_fim(p,f); // passagem de elementos para deque p
        }
    }
}

int main()
{
    int swi, sinal = 0; // sinal contabiliza a qtde de reinicializacoes do deque
    Deque P;
    int A;
    do {
        do{
            // Obtem opcao do usuario
            printf("\nOpcoes:\n");
            printf("[1] Criar um deque\n");
            printf("[2] Inserir um elemento no deque\n");
            printf("[3] Remover um elemento do deque\n");
            printf("[4] Imprimir o deque\n");
            printf("[5] Esvaziar deque\n");
            printf("[6] Apagar deque\n");
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
            printf("\nAntes de realizar operacoes, crie um deque.\n\n");
            continue;
        }

        switch (swi) {
            case 1: {
                if (sinal > 0) { // Verifica se o deque já existe
                    apaga_deque(&P);
                }

                P = cria_deque();
                if (P == NULL) {
                    printf("\nFalha na alocacao...\n\n");
                    return -1;
                }

                if (sinal)
                    printf("\nReinicializacao do deque pela %d vez...\n\n", sinal);
                else
                    printf("\nCriacao bem sucessida!\n\n");

                sinal++;

                break;
            }
            case 2: {
                int esc = 0;
                do{
                    printf("\nDeseja inserir um numero no inicio (1) ou no fim do deque (2)?");
                    scanf("%d", &esc);
                    fflush(stdin);
                    if(esc != 1 && esc != 2)
                        printf("\nEscolha invalida! ('1' para inserir no inicio ou '2' para inserir no fim)\n");
                }while(esc != 1 && esc != 2);
                if(esc == 2){
                    printf("Digite o numero: \n");
                    scanf("%d", &A);
                    if (insere_fim(P, A) == 0)
                        printf("\nO deque esta cheio! O numero %d nao foi incluido.\n\n", A);
                    else
                        printf("\nO numero %d foi incluido com sucesso!\n\n", A);
                    break;
                }
                if(esc == 1){
                    printf("\nDigite o numero: \n");
                    scanf("%d", &A);
                    if (insere_ini(P, A) == 0)
                        printf("\nO deque esta cheio! O numero %d nao foi incluido.\n\n", A);
                    else
                        printf("\nO numero %d foi incluido com sucesso!\n\n", A);
                    break;
                }
            }
            case 3: {
                int esc = 0;
                do{
                    printf("\nDeseja remover um numero do inicio (1) ou do fim do deque (2)?");
                    scanf("%d", &esc);
                    fflush(stdin);
                    if(esc != 1 && esc != 2)
                        printf("\nEscolha invalida! ('1' para inserir no inicio ou '2' para inserir no fim)\n");
                }while(esc != 1 && esc != 2);
                if(esc == 1){
                    if (remove_ini(P,&A) == 0) {
                        printf("\nDeque vazio!\n\n");
                    }
                    else
                        printf("\nO numero %d foi removido com sucesso!\n\n", A);
                    break;
                }
                if(esc == 2){
                    if (remove_fim(P,&A) == 0) {
                        printf("\nDeque vazio!\n\n");
                    }
                    else
                        printf("\nO numero %d foi removido com sucesso!\n\n", A);
                    break;
                }
            }
            case 4:{
                imprimir_deque(P);
                break;
            }
            case 5:{
                if(esvazia_deque(P) == 0)
                    printf("\nErro!");
                printf("\nO deque foi esvaziado!\n");
                break;
            }
            case 6:{
                apaga_deque(&P);
                printf("\nO deque foi apagado!\n");
                sinal = 0;
                break;
            }
        }
    }while (swi != 7);
    printf("\nEncerrando o programa...\n");
    return 0;
}
