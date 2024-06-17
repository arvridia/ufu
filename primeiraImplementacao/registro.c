#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

#include "size.h"
#include "registro.h"
#include "mtwister/mtwister.h"

int SEED_SET;
MTRand r;

void SET_SEED() {
	srand(time(NULL));
	SEED_SET = rand() + 1;
	r = seedRand(SEED_SET);
}

void RANDOM_REG(char* reg_text) {
	char diff = 'Z' - 'A';
	for(int i = 0; i < TEXT_SIZE; i++)
		reg_text[i] = 'A' + rand() % diff;
}

int CREATE_HEAP_FILE(nseq_t nro_registros) {
	FILE *fp;
	fp = fopen("arquivo", "wb");
	if(fp == NULL)
    return 0;

	if(!SEED_SET)
    SET_SEED();

	struct REGISTRO reg;
	for(nseq_t i = 0; i < nro_registros; i++) {
		reg.NSEQ = i;
		RANDOM_REG(reg.TEXT);

		if(!fwrite(&reg, sizeof(struct REGISTRO), 1, fp)) {
			fclose(fp);
			remove("arquivo");
			return 0;
		}
	}

	fclose(fp);

	return 1;
}

int READ_REG(FILE *arq, nseq_t nseq, REGISTRO_p reg) {
	if(arq == NULL) return 0;

	// Acha a quantidade de registro no momento
	nseq_t rqtd;
	FILE_REGS(arq, &rqtd);

	// Se o numero sequencial for maior ou
	// igual a qtd acima, nseq invalidso
	if(nseq >= rqtd) return 0;

	// Seta o Stream para uma posição nseq
	fseek(arq, nseq * sizeof(struct REGISTRO), SEEK_SET);

	// le o registro
	struct REGISTRO registro;
	if(!fread(&registro, sizeof(struct REGISTRO), 1, arq)) return 0;

	*reg = registro;

	rewind(arq);

	return 1;
}

int READ_RANDOM(FILE *arq, REGISTRO_p reg) {

if(arq == NULL) return 0;

	nseq_t rnum;
	FILE_REGS(arq, &rnum);

	if(!SEED_SET)
    SET_SEED();

  double rn = genRand(&r);
	nseq_t nseq = (rnum - 1) * rn;

	return READ_REG(arq, nseq, reg);
}

int ISRT_AT_END(FILE *arq) {
if(arq == NULL) return 0;

	// Seta stream para o ultimo registro
	fseek(arq, -(long int)sizeof(struct REGISTRO), SEEK_END);

	// le o ultimo registro
	struct REGISTRO reg;
	fread(&reg, sizeof(struct REGISTRO), 1, arq);

	// Escreve o registro
	reg.NSEQ++;
	RANDOM_REG(reg.TEXT);
	if(!fwrite(&reg, sizeof(struct REGISTRO), 1, arq)) return 0;

	rewind(arq);
	return 1;
}

int UPDATE_REG(FILE *arq, REGISTRO_p reg) {
	if(arq == NULL || reg == NULL) return 0;

	// Acha a quantidade de registro no momento
	nseq_t rqtd;
	FILE_REGS(arq, &rqtd);

	// Se nseq eh maior ou igual a rqtd, invalidso
	if(reg->NSEQ >= rqtd) return 0;

	fseek(arq, reg->NSEQ * sizeof(struct REGISTRO), SEEK_SET);
	if(!fwrite(reg, sizeof(struct REGISTRO), 1, arq)) return 0;

	rewind(arq);

	return 1;
}

int UPDATE_RANDOM(FILE *arq, REGISTRO_p reg) {
	if(arq == NULL || reg == NULL) return 0;

	// Acha a quantidade de registro no momento
	nseq_t rqtd;
	FILE_REGS(arq, &rqtd);

	if(!SEED_SET) SET_SEED();

	// Pega um aleatorio em [0..1] (MersenneTwister)
	double rn = genRand(&r);

	// Acha nseq aleatorio
	nseq_t nseq = (rqtd - 1) * rn;

	// Registro aleatorio
	reg->NSEQ = nseq;
	RANDOM_REG(reg->TEXT);

	// Update um registro aleatorio
	return UPDATE_REG(arq, reg);
}

int DELETE_REG(FILE *arq, nseq_t nseq, REGISTRO_p reg) {
	if(arq == NULL || reg == NULL) return 0;

	// Acha a quantidade de registro no momento
	nseq_t rqtd;
	FILE_REGS(arq, &rqtd);

	// Se nseq eh maior ou igual a rqtd, invalidso
	if(nseq >= rqtd) return 0;

	// Seta stream para o registro nseq
	fseek(arq, nseq * sizeof(struct REGISTRO), SEEK_SET);

	struct REGISTRO registro;
	if(!fread(&registro, sizeof(struct REGISTRO), 1, arq)) return 0;

	// Faz uma copia do registro retirado
	*reg = registro;

	registro.NSEQ = UINT_MAX;

	fseek(arq, nseq * sizeof(struct REGISTRO), SEEK_SET);

	fwrite(&registro, sizeof(struct REGISTRO), 1, arq);

	rewind(arq);

	return 1;
}

int DELETE_RANDOM(FILE *arq, REGISTRO_p reg) {
	if(arq == NULL || reg == NULL) return 0;

	// Acha a quantidade de registro no momento
	nseq_t rqtd;
	FILE_REGS(arq, &rqtd);

	if(!SEED_SET) SET_SEED();

	// Pega um aleatorio em [0..1] (MersenneTwister)
	double rn = genRand(&r);

	// Acha nseq aleatorio
	nseq_t nseq = (rqtd - 1) * rn;

	// Delete um registro aleatorio
	return DELETE_REG(arq, nseq, reg);
}

int FILE_REGS(FILE *arq, nseq_t* rnum) {
	if(arq == NULL || rnum == NULL)
    return 0;

	nseq_t seek = ftell(arq);

	fseek(arq, 0, SEEK_END);
	*rnum = ftell(arq) / sizeof(struct REGISTRO);
	fseek(arq, 0, seek);

	return 1;
}

int FILE_SIZE(FILE *arq, memsize_t *arq_size) {
	if(arq == NULL || arq_size == NULL) return 0;

	nseq_t rnum;
	FILE_REGS(arq, &rnum);
	*arq_size = rnum * sizeof(struct REGISTRO);

	return 1;
}

int SEQUENTIAL_SWEEP(FILE *arq, int rnum_by_page, nseq_t *nvalids, int *num_of_pages) {
	if(arq == NULL || rnum_by_page <= 0)
    return 0;

	rewind(arq);

	*num_of_pages = -1;
	*nvalids = 0;

	REGISTRO_p buffer = (REGISTRO_p) malloc(rnum_by_page * sizeof(struct REGISTRO));

	int read = 0;
	do {
		for(int i = 0; i < read; i++)
			if(buffer[i].NSEQ >= 0)
				(*nvalids)++;

		(*num_of_pages)++;

		read = fread(buffer, sizeof(struct REGISTRO), rnum_by_page, arq);
	} while(read);

	return 1;
}

int RANDOM_SWEEP(FILE *arq, nseq_t qtd_reg, nseq_t *nvalids) {
	if(arq == NULL || nvalids == NULL || qtd_reg <= 0)
    return 0;

	struct REGISTRO reg;
	*nvalids = 0;

	for(int i = 0; i < qtd_reg; i++)
		if(READ_RANDOM(arq, &reg))
			if(reg.NSEQ >= 0)
				(*nvalids)++;

	return 1;
}

int PRINT_REG(REGISTRO_p reg) {
	if(reg == NULL)
		return 0;

	printf("NSEQ: %u\n", reg->NSEQ);
	printf("TEXT: %s\n", reg->TEXT);

	return 1;
}


