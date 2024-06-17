#include <stdio.h>
#include <stdlib.h>
#include "TADFila_Est_Seq_DesPos.h"

void imprimir_fila(Fila p)
{
    Fila X = cria_fila();
    if(fila_vazia(p) == 1)
        printf("\nA lista esta vazia!\n");
    else{
        int cont = 1;
        while(fila_vazia(p) != 1)
        {
            func f;
            remove_ini(p,&f);
            printf("\nAluno %d: \n", cont);
            printf("Matricula:%d \n", f.mat);
            printf("Nome:%s \n", f.nome);
            printf("Faltas:%c \n", f.faltas);
            printf("Media:%f \n", f.media);
            cont++;
            insere_fim(X,f); // passagem de elementos para fila X
        }
        while(fila_vazia(X) != 1)
        {
            func f;
            remove_ini(X,&f);
            insere_fim(p,f); // passagem de elementos para fila p
            //pilha era fim fim agr é insere fim e remove ini
        }
    }
}

int main()
{
    int swi, sinal = 0; // sinal contabiliza a qtde de reinicializacoes da fila
    Fila P;
    func A;
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
                printf("Digite a matricula do aluno a ser inserido na fila: \n");
                scanf("%d", &A.mat);
                printf("Digite o nome do aluno: \n");
                fflush(stdin);
                gets(A.nome);
                printf("Digite o numero de faltas do aluno: \n");
                scanf("%d", &A.faltas);
                printf("Digite a media do aluno: \n");
                scanf("%f", &A.media);
                if (insere_fim(P, A) == 0)
                    printf("\nA fila esta cheia! O aluno %s nao foi incluido.\n\n", A.nome);
                else
                    printf("\nO aluno %s foi incluido com sucesso!\n\n", A.nome);
                break;
            }
            case 3: {
                if (remove_ini(P,&A) == 0) {
                    printf("\nFila vazia!\n\n");
                }
                else
                    printf("\nO aluno %s foi removido com sucesso!\n\n", A.nome);
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
