#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

#define MAXOP 6

void menu();
int FLAG = 0;

int main() {
  struct registro reg;
  Hash h;
  int op;
  unsigned int pg_inicial;
  unsigned int chave;

  FILE *dir;
  dir = fopen("arq_diretorio", "r+");
  if (dir != NULL) {
    FLAG = 1;

    unsigned int tam;
    long int bn;
    unsigned int bs;
    unsigned int depth;

    fread(&tam, sizeof(unsigned int), 1, dir);
    fread(&bn, sizeof(long int), 1, dir);
    fread(&bs, sizeof(unsigned int), 1, dir);
    fread(&depth, sizeof(unsigned int), 1, dir);

    FLAG = RECUPERA_DIR(&h, tam, bs, bn, depth, "arq_dados");
  }

  do {
    menu();
    scanf("%d", &op);
    setbuf(stdin, NULL);

    switch(op) {
      case 1:
        printf("pg_inicial: ");
        scanf("%u", &pg_inicial);

        if(CRT_HASH(&h, pg_inicial, "arquivo_dados")) {
          printf("Hash criado com sucesso!\n\n");
          FLAG = 1;
        } else
          printf("Erro na criacao do hash\n\n");
      break;

      case 2:
        printf("Chave: ");
        scanf("%u", &chave);
        if(SRCH_HASH(h, chave, &reg))
          printf("Encontrado: <%u, %s>\n\n", reg.nseq, reg.text);
        else
          printf("Nao foi encontrado...\n\n");
      break;

      case 3:
        printf("Registro: \n");
        printf("Chave: ");
        scanf("%u", &reg.nseq);
        printf("text: ");
        scanf("%s", reg.text);

        if(INST_HASH(h, &reg))
          printf("Insercao com sucesso\n\n");
        else
          printf("Erro no registro\n\n");
      break;

      case 4:
        printf("Chave: ");
        scanf("%u", &chave);
        if(RMV_HASH(h, chave, &reg))
          printf("Removido: <%u, %s>!\n\n", reg.nseq, reg.text);
        else
          printf("Nao foi encontrado...\n\n");

      break;

      case 5:
        if(!PRNT_HASH(h)) printf("Erro na impressao\n\n");
      break;

      case MAXOP:
        PERSISTE_DIR(h);
        printf("QUIT\n");
      break;
    }
	} while(op != MAXOP);

	return 0;
}

void menu() {
  printf("==============MENU==============\n");
  if (FLAG == 1) printf("\n[!] Hash jah existe!\n\n");
  printf(" (1) Criar hash\n");
  printf(" (2) Busca hash\n");
  printf(" (3) Insercao de registros\n");
  printf(" (4) Remocao de registros\n");
  printf(" (5) Imprimir hash\n");
  printf(" (6) Sair\n");
  printf("\n Escolha: \n");
}

