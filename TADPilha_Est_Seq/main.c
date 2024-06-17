#include <stdio.h>
#include <stdlib.h>
#include "TADPilha_Est_Seq.h"

void imprimir_pilha(Pilha p)
{
    Pilha X = cria_pilha();
    if(pilha_vazia(p) == 1)
        printf("A lista esta vazia!!");
    else{
        int cont = 1;
        while(pilha_vazia(p) != 1)
        {
            func f;
            pilha_pop(p,&f);
            pilha_push(X,f); // passagem de elementos para pilha X

        }
            while(pilha_vazia(X) != 1)
        {
            func f;
            pilha_pop(X,&f);
            printf("\n\nFuncionario %d: \n", cont);
            printf("Matricula:%ld \n", f.mat);
            printf("Nome:%s \n", f.nome);
            printf("Setor:%c \n", f.setor);
            printf("Salario:%f ", f.salario);
            cont++;
            pilha_push(p,f); // passagem de elementos para pilha p

        }
    }
}

int main()
{
    int swi, sinal = 0; // sinal contabiliza a qtde de reinicializacoes da pilha
    Pilha P;
    func A;
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
                if (P == NULL) {
                    printf("\nFalha na alocacao...\n\n");
                    return -1;
                }

                if (sinal)
                    printf("\nReinicializacao da pilha pela %d vez...\n\n", sinal);
                else
                    printf("\nCriacao bem sucessida!\n\n");

                sinal++;

                break;
            }
            case 2: {
                printf("Digite a matricula do funcionario a ser inserido na pilha: \n");
                scanf("%ld", &A.mat);
                printf("Digite o nome do funcionario: \n");
                fflush(stdin);
                gets(A.nome);
                do{
                    printf("Digite o setor em que trabalha o funcionario ('F' se trabalha na fabrica, 'A' no administrativo, 'C' comercial, 'G' na gerencia): \n");
                    A.setor = getchar();
                    if(A.setor!='f' && A.setor!='F' && A.setor!='a' && A.setor!='A' && A.setor!='c' && A.setor!='C' && A.setor!='g' && A.setor!='G')
                        printf("Insira uma opcao valida!\n");
                }while(A.setor!='f' && A.setor!='F' && A.setor!='a' && A.setor!='A' && A.setor!='c' && A.setor!='C' && A.setor!='g' && A.setor!='G');
                printf("Digite o salario do funcionario: \n");
                scanf("%f", &A.salario);
                if (pilha_push(P, A) == 0)
                    printf("\nA pilha esta cheia! O funcionario %s nao foi incluido.\n\n", A.nome);
                else
                    printf("\nO funcionario %s foi incluido com sucesso!\n\n", A.nome);
                break;
            }
            case 3: {
                if (pilha_pop(P,&A) == 0) {
                    printf("\nPilha vazia!\n\n");
                }
                else
                    printf("\nO funcionario %s foi removido com sucesso!\n\n", A.nome);
                break;
            }
            case 4:{
                imprimir_pilha(P);
                break;
            }
            case 5:{
                func B;
                if(get_topo(P, &B) == 0)
                    printf("\nOcorreu um erro...Verifique se a pilha nao esta vazia\n");
                else{
                    printf("\nO funcionario do topo da pilha eh: %s ", B.nome);
                    printf("\nSua matricula eh: %ld ", B.mat);
                    printf("\nSeu setor eh: %c ", B.setor);
                    printf("\nSeu salario eh: %f ", B.salario);
                }
                break;
            }
            case 6:{
                if(esvazia_pilha(P) == 0)
                   printf("\nOcorreu um erro...Verifique se a pilha nao esta vazia ou se foi criada corretamente\n");
                else
                    printf("\nPilha esvaziada com sucesso\n");
                break;
            }
            case 7:{
                libera_pilha(&P);
            }
        }
    }while (swi != 8);
    printf("\nEncerrando o programa...\n");
    return 0;
}
