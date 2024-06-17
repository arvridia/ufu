#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#define MAX 50
#define MAX_PATH 256

int main(void) {
  Grafo g;
  g = criaGrafo();
  int swi = 0;
  int sinal = 0; // sinal contabiliza se ja ha insercoes
  do {
      do{
           // Obtem opcao do usuario
          printf("\n------------------------------");
          printf("\nSetor de Produtos Quimicos");
          printf("\n------------------------------");
          if(sinal != 0)  
            imprimirListaAdj(g);
          printf("\n\n[1]Catalogar restricoes utilizando informacoes de arquivo\n");
          printf("[2]Catalogar restricoes manualmente\n");
          printf("[3]Organizar e apresentar solucao\n");
          printf("[4]Sair do sistema\n");
          printf("\nQual opcao deseja realizar?\n");
          scanf("%d", &swi);
          setbuf(stdin, NULL);
          if (swi < 1 || swi > 4)
              printf("\nOpcao invalida...Somente existem essas opcoes:\n");

      } while (swi < 1 || swi > 4);
      if (swi == 3)
          break;
      else if (swi != 1 && sinal == 0) {
          printf("\nPrimeiramente insira restricoes!\n\n");
          continue;
       }
      switch (swi) {
          case 1:{
            char produto[MAX];
            char produto2[MAX];
            FILE *abrir = NULL;
            char arquivo[MAX_PATH];
            printf("\nDigite o nome do arquivo:");
            scanf("%s", arquivo);
            abrir = fopen(arquivo, "r"); /*abrindo arquivo*/
            if(abrir == NULL){ /*caso haja erro na abertura do arquivo*/
              fprintf(stderr,"\nHouve um erro ao abrir o arquivo %s!\n", arquivo);
              return 1;
            }
            while(!feof(abrir)){
              fscanf(abrir, "%s %s", produto, produto2); /* lendo de dois em dois*/
              fscanf(abrir, " "); /* para evitar que o programa leia o fim do arquivo, que nao tem nada */
              inserindoArco(g, produto, produto2); /*insere restricao de dois em dois*/
            }
            printf("\n");
            fclose(abrir); /*fechando arquivo*/
            abrir = NULL;
            printf("\nInsercao com sucesso!\n");
            break;
          }
          case 2:{
            char produto[MAX];
            char produto2[MAX];
            printf("\nInsira produtos incompativeis");
            printf("\nPrimeiro produto:\n");
            scanf("%s", produto);
            setbuf(stdin, NULL);
            printf("\nSegundo produto:\n");
            scanf("%s", produto2);
            setbuf(stdin, NULL);
            inserindoArco(g, produto, produto2);
            sinal++;
            break;
          }
          case 3:{
            int d = 0;
            printf("\nHa diferentes formas de calcular as combinacoes de compartimentos:");
            do{
            printf("\n[1]Opcao eficaz (tempo de resposta demorado)");
            printf("\n[2]Opcao rapida (nem sempre entrega o melhor resultado)\n");
            printf("O que prefere?\n");
            scanf("%d", &d);
            setbuf(stdin, NULL);
            if(d < 1 || d > 2)
              printf("\nDigite um numero valido!\n");
            }while (d < 1 || d > 2);
            if(d == 1)
              backtracking(g);
            else
              coloracao_gulosa(g);
            break;
          }
      }
    }while (swi != 4);
    printf("\nEncerrando o sistema...\n");
    return 0;
}