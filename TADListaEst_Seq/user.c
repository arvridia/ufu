#include <stdio.h>
#include "lista.h"

void imprime_lista(Lista);

int main()
{
    int op, FLAG = 0; // FLAG contabiliza a qtde de reinicializacoes da lista
    Lista L;

    do {
        do{
            // Obtem opcao do usuario
            printf("===================================\n");
            printf("[1] Criar uma lista\n");
            printf("[2] Inserir um elemento na lista\n");
            printf("[3] Remover um elemento da lista\n");
            printf("[4] Imprimir a lista\n");
            printf("[5] Sair do sistema\n");
            printf("\nDigite a opcao desejada: ");

            scanf("%d", &op);
            setbuf(stdin, NULL);
            if (op < 1 || op > 5)
                printf("\n*** Opcao digitada nao eh valida! ***\nAs opcoes disponiveis sao:\n");

        } while (op < 1 || op > 5);

        if (op == 5)
            break;
        else if (op != 1 && FLAG == 0) {
            printf("\nAntes de qualquer operacao, a lista precisa ser CRIADA.\n\n");
            continue;
        }

        switch (op) {
            case 1: {
                if (FLAG) { // Verifica se a lista já existe
                    libera_lista(&L);
                }

                L = cria_lista();
                if (L == NULL) {
                    printf("\nFalha na alocacao...\n\n");
                    return -1;
                }

                if (FLAG)
                    printf("\nA lista foi REINICIALIZADA pela %d vez com sucesso!\n\n", FLAG);
                else
                    printf("\nA lista foi CRIADA com sucesso!\n\n");

                FLAG++;

                break;
            }
            case 2: {
                int N;
                printf("Digite o elemento (nro inteiro) a ser inserido na lista: ");
                scanf("%d", &N);
                if (insere_elem(L, N) == 0)
                    printf("\nA lista ja estah cheia! Nao foi possivel incluir o elemento %d.\n\n", N);
                else
                    printf("\nO elemento %d foi incluido com sucesso!\n\n", N);

                break;
            }
            case 3: {
                int N;

                printf("\nDigite o elemento a ser removido da lista: ");
                scanf("%d", &N);

                if (remove_elem(L, N) == 0) {
                    if (lista_vazia(L) == 1)
                        printf("\nA lista estah vazia!\n\n");
                    else
                        printf("\nNao existe o elemento %d na lista.\n\n", N);
                }
                else
                    printf("\nO elemento %d foi removido com sucesso!\n\n", N);

                break;
            }
            case 4: {
                imprime_lista(L);
                break;
            }
        }
    } while (op != 5);

    printf("\nGOOD BYE!\n");
    return 0;
}

void imprime_lista(Lista L) {

    if (lista_vazia(L) == 1) {
        printf("\n*** LISTA VAZIA ***\n\n");
        return;
    }

    printf("\nLista: {");
    int i;
    for (i=1; ; i++) {
        int N;
        if (get_elem(L,i, &N) == 0) {
            break;
        }
        printf(" %d ", N);
//        printf("O %do. elemento da lista eh: %d\n", i, N);
    }
    printf("}\nExistem %d elementos na lista.\n\n", i-1);
}