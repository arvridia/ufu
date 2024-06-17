#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

#define MAXOP 6
typedef uint32_t u32;
void print_menu();

int main()
{
  struct registro reg;
  Hash h;
	int op;
  u32 pg_inicial;
  char *chave = NULL;

  int FLAG = 0;
  FILE *dir;
  dir = fopen("dir", "r+");
  if (dir != NULL) {
    FLAG = 1;

    // fread(ptr, size, nmemb, stream)

    u32 tam;
    fread(&tam, sizeof(u32), 1, dir);

    u32 bn;
    fread(&bn, sizeof(u32), 1, dir);

    u32 bs;
    fread(&bs, sizeof(u32), 1, dir);

    u32 depth;
    fread(&depth, sizeof(u32), 1, dir);

    // directory_t dir_t;
    // fread(&dir_t, sizeof(directory_t), 1, dir);

   FLAG = RECUPERA_DIR(&h, tam, bs, bn, depth, "arquivo_diretorio");
  }

	do {
    print_menu();
    if (FLAG == 1) printf("Hash jah criado!\n");

		scanf("%d", &op);
		setbuf(stdin, NULL);

		switch(op){
			case 1:
				printf("Iniciando profundidade global: ");
        scanf("%u", &pg_inicial);

        if(CRT_HASH(&h, pg_inicial, "arquivo_diretorio")) {
          printf("Hash criado com sucesso!\n\n");
          FLAG = 1;
        }
        else
            printf("Erro na criacao do hash\n\n");
        break;

			case 2:
				printf("KEY: ");
        scanf("%s", chave);
        if(SRCH_HASH(h, chave, &reg))
          printf("Encontrado: <%u, %s>!\n\n", reg.nseq, reg.matricula);
        else
          printf("Nao foi encontrado...\n\n");

	 			break;

      case 3:
        printf("NSEQ: \n");
        scanf("%u", &reg.nseq);
        printf("TEXTO: \n");
        scanf("%s", reg.text);
        printf("MATRICULA: \n");
        scanf("%s", reg.matricula);

        if(INST_HASH(h, &reg))
          printf("Insercao com sucesso!\n\n");
        else
          printf("INnsercao falhou...\n\n");

        break;

			case 4:
				printf("KEY: ");
        scanf("%s", chave);
        if(RMV_HASH(h, chave, &reg))
          printf("Remocao com sucesso: <%u, %s>!\n\n", reg.nseq, reg.matricula);
        else
          printf("Nao foi encontrado...\n\n");

	 			break;

      case 5:
        if(!PRNT_HASH(h)) printf("Erro na impressao\n\n");
        break;

			case MAXOP:
				PERSISTE_DIR(h);
				printf("Sair\n");
				break;

		}

	} while(op != MAXOP);

	return 0;
}

void print_menu() {
  printf("===========MENU============\n\nEscolha:\n");
  printf(" [1] Criar Hash\n");
  printf(" [2] Busca\n");
  printf(" [3] Insercao\n");
  printf(" [4] Remocao\n");
  printf(" [5] Imprimir\n");
  printf(" [6] Sair\n");
  printf("\n");
}
