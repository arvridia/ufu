#include <stdio.h>
#include "TADListaDin_Enc_NaoOrd_Alunos.h"
#define MAX 20
void imprimir_lista(lista *lista1)
{
    if (lista_vazia(lista1) == 1)
    {
        printf("Nao ha elementos\n");
        return;
    }
    int cont = 1;
    while(1)
    {
        printf("sumadre");
        unsigned int mat = 0;
        char nome[MAX];
        float media = 0;
        int faltas = 0;
        if(get_pos(lista1,cont,&mat, &nome, &media, &faltas)== 0)
        {
            break;
        }
        printf("suamae");
        printf("\nMatricula:%d\nNome:%s\nMedia:%f\nFaltas:%d", mat, nome, media, faltas);
        cont ++;
    }
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
            printf("\nDigite '1' caso queira criar uma nova lista;\nDigite '2' caso queira realizar o cadastro de um aluno;\nDigite '3' caso queira remover um cadastro;\n");
            printf("Digite '4' caso queira imprimir todos dados da lista;\nDigite '5' caso deseje obter a quantidade de alunos cadastrados;\nDigite '6' caso deseje finalizar o programa.\n\n");
            fflush(stdin);
            scanf("%d", &Num);
            if(Num < 1 || Num > 6)
            {
                printf("O numero digitado deve ser >= 1 e <= 6\nO programa foi finalizado.");
                return 0;
            }
            continue;
        }
        while (Num < 1 || Num > 6);
        if (Num == 6){
            return 0;
        }
        if (Num != 1 && X == 0) {
                printf("Primeiramente deve se criar a lista\nSistema encerrado");
                break;
        }
        if (Num == 1) {
            if(X > 0){
                apaga_lista(&lista1);
                X = 0;
                printf("A antiga lista foi apagada e uma nova sera criada\n");
            }
            lista1 = inicializar_lista();
            if(lista1 == NULL) {
                printf("Lista criada\n");
            }
            else{
                printf("Erro ao alocar");
                return -1;
            }
            X++;
        }
        if(Num == 2){
            int num = 0;
            char nome[MAX];
            float media = 0;
            int faltas = 0;
            printf("Digite o numero de matricula do aluno que sera cadastrado na lista:\n");
            scanf("%d", &num);
            printf("Digite o nome:\n");
            scanf("%s", nome);
            printf("Digite a media:\n");
            scanf("%f", &media);
            printf("Digite o numero de faltas do aluno:\n");
            scanf("%d", &faltas);
            if (insere_elem(&lista1, num, nome, media, faltas) == 0)
                printf("Nao foi possivel inserir o elemento.\n");
            else
                printf("Sucesso na insercao.\n");
            }
        if(Num == 3)
        {
            int nani;
            printf("Deseja remover por posicao na lista(Digite '10') ou por matricula(Digite '11')?\n");
            scanf("%d", &nani);
            if(nani == 11)
            {
                int num = 0;
                printf("Digite a matricula:\n");
                scanf("%d", &num);
                if (remove_elem(&lista1, num) == 0)
                {
                    if (lista_vazia(lista1) == 1)
                        printf("Nao ha elementos na lista");
                    else
                        printf("Essa matricula nao existe\n");
                }
                else
                    printf("Sucesso na remocao\n");
            }
            if(nani == 10)
            {
                int pos = 0;
                int retorno = 0;
                printf("Digite a posicao que se encontra o aluno:\n");
                scanf("%d", &pos);

                retorno = remove_pos(&lista1, pos);

                if (retorno == 0)
                {
                    if (lista_vazia(lista1) == 1)
                        printf("Nao ha elementos na lista");

                    else
                        printf("Essa posicao nao existe\n");
                }
                else
                    printf("Sucesso na remocao\n");
            }

            else
                if(nani != 10 && nani != 11)
                    printf("Nao ha essa opcao");
        }

        if(Num == 4)
        {
            imprimir_lista(lista1);
        }
        if(Num == 5)
        {
            int tamanho = 0;
            tamanho = size_lista(&lista1);
            if (tamanho == -1)
                printf("Ainda nao ha cadastro de alunos");
            printf("A quantidade de alunos cadastrados eh %d", tamanho);
        }
    }
    while(Num != 6);
    apaga_lista(&lista1);
    return 0;
}



