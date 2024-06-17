#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dicionario.h"
#define MAX 50

int main()
{
    FILE *abrir = NULL;
    char arquivo[MAX];
    char A[MAX];
    char frase[MAX][MAX];
    lista lista1;
    VOCAB voc;
    ArvAVL arv = NULL, b;
    int swi, sinal = 0; // sinal contabiliza se é para atualizar ou somente abrir um arquivo
    do {
        do{
            // Obtem opcao do usuario
            printf("\n\nOpcoes:\n");
            printf("[1] Carregar ou atualizar um arquivo\n");
            printf("[2] Buscar uma palavra no dicionario\n");
            printf("[3] Inserir uma nova entrada no dicionario\n");
            printf("[4] Remover uma entrada do dicionario\n");
            printf("[5] Relatorio do dicionario\n");
            printf("[6] Salvar o dicionario em um arquivo texto\n");
            printf("[7] Sair do sistema\n");
            printf("\nQual opcao deseja realizar? ");
            scanf("%d", &swi);
            setbuf(stdin, NULL);
            if (swi < 1 || swi > 7)
                printf("\nOpcao invalida...Somente existem essas opcoes:\n");

        } while (swi < 1 || swi > 8);

        if (swi == 7)
            break;
        else if (swi != 1 && sinal == 0) {
            printf("\nAntes de realizar operacoes, carregue um arquivo.\n\n");
            continue;
        }

        switch (swi) {
            case 1: {
                char continua='s';
                char item[100];
                int f1=0,f2=0,f3=0;
                int i = 0;
                if (sinal) { // Verifica se ja carregou arquivo
                    fclose(abrir);
                    abrir = NULL;
                }
                printf("Digite o nome do arquivo que sera carregado:\n");
                scanf("%s", arquivo);
                fflush(stdin);
                abrir = fopen(arquivo, "r");
                if (abrir == NULL)/*caso a abertura apresente erro*/
                {
                    fprintf(stderr, "Erro ao abrir o arquivo %s\n", arquivo);
                    return 5; /*programa finalizará após a mensagem de erro*/
                }
                if (sinal)
                    printf("\nAtualizacao do dicionario pela %d vez...\n\n", sinal);
                else
                    printf("\nCarregamento concluido!\n\n");


                printf("\nLeitura do arquivo");
                while (!feof(abrir)){
                    continua=fgetc(abrir);
                    if(continua != EOF){
                        i=0;
                        while(continua!='\n'){
                            if (continua!='#'){
                                item[i]=continua; i++;
                            }
                            continua=fgetc(abrir);
                        }
                        item[i]='\0';

                        if (f1==0){
                            strcpy(voc.palavra,item); f1=1;
                        }
                        else if(f2==0){
                            strcpy(voc.classe_gramatical,item);
                            f2=1;
                        }
                        else if(f3==0){
                            strcpy(voc.definicao,item);
                            f3=1;
                        }
                        if((f1==1)&&(f2==1)&&(f3==1)) {
                            printf("\n\nVocabulo: %s \nClassificacao Gramatical: %s \nDefinicao: %s",voc.palavra,voc.classe_gramatical,voc.definicao);
                            arv=insere(arv,voc);
                            f1=0;
                            f2=0;
                            f3=0;
                            insere_ord(lista1, voc.palavra, voc.classe_gramatical, voc.definicao);
                        }
                    }
                    else{
                        printf("\n\n--------------Fim da leitura do arquivo");
                        break;
                    }
                }

                sinal++;
                fclose(abrir);
                abrir = NULL;
                break;
            }
            case 2: {
                VOCAB med;
                printf("Digite a palavra para ser pesquisada: \n");
                gets(voc.palavra);
                fflush(stdin);
                med = consulta_ArvAVL(&arv, voc.palavra);
                if(med == NULL)
                    printf("Arvore vazia ou elemento nao encontrado\n");
                else{
                    Exibir_NO(med);
                    Comparar_Tempos(lista1, arv, voc.palavra);
                }
                break;
            }
            case 3: {
                VOCAB med;
                printf("Digite a palavra a ser inserida no dicionario: \n");
                gets(voc.palavra);
                fflush(stdin);
                printf("Digite a sua classe gramatical: \n");
                gets(voc.classe_gramatical);
                fflush(stdin);
                printf("Digite a definicao: \n");
                gets(voc.definicao);
                fflush(stdin);
                med = consulta_ArvAVL(&arv, voc.palavra);
                if(med != NULL)
                    printf("Este elemento ja existe no dicionario!!\n");
                else{
                    insere_ord(lista1, voc.palavra, voc.classe_gramatical, voc.definicao);
                    insere_ArvAVL(&arv, voc.palavra, voc.classe_gramatical, voc.definicao);
                }
                break;
            }
            case 4:{
                printf("Digite a palavra a ser removida do dicionario: \n");
                gets(voc.palavra);
                fflush(stdin);
                remove_ArvAVL(&arv, voc.palavra);
                remover(lista1, voc.palavra);
                break;
            }
            case 5:{
                Gerar_Relatorio(arv);
                break;
            }
            case 6:{
                int numer = 0;
                do{
                    printf("Deseja salvar o dicionario em pre-ordem(1), em ordem(2) ou em pos-ordem(3)?\n");
                    numer = getchar();
                    setbuf(stdin, NULL);
                    if (numer < 1 || numer > 3)
                        printf("\nOpcao invalida...Digite '1' para escolher o percurso pre-ordem, '2' para o em ordem e '3' para o pos-ordem:\n");
                }while(numer < 1 || numer > 3);
                printf("Digite um nome para a criacao do arquivo em que sera salvo o dicionario (arquivos existentes com o nome digitado serão apagados)\n");
                scanf("%s", arquivo);
                fflush(stdin);
                abrir = fopen(arquivo, "w");
                if (abrir == NULL)/*caso a abertura apresente erro*/
                {
                    fprintf(stderr, "Erro ao abrir o arquivo %s\n", arquivo);
                    return 5; /*programa finalizará após a mensagem de erro*/
                }
                if(numer == 1)
                    preorder(arv, abrir);
                if(numer == 2)
                    inorder(arv, abrir);
                if(numer == 3)
                    posorder(arv, abrir);

                fclose(abrir);
                abrir = NULL;
                break;
            }
        }
    }while (swi != 7);
    printf("\nEncerrando o programa...\n");
    return 0;
}
