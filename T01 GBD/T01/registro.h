#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include <stdint.h>

typedef uint64_t memsize_t;
typedef int32_t nseq_t;
typedef char  text_t;

#define TEXT_SIZE 508

struct REGISTRO {
	nseq_t  NSEQ;
	text_t  TEXT[TEXT_SIZE];
};

typedef struct REGISTRO *REGISTRO_p;

// 1.A)
int32_t CREATE_HEAP_FILE(nseq_t nro_registros);
int32_t READ_RANDOM(FILE *arq, REGISTRO_p reg);
int32_t ISRT_AT_END(FILE *arq);
int32_t UPDATE_RANDOM(FILE *arq, REGISTRO_p reg);
int32_t DELETE_RANDOM(FILE *arq, REGISTRO_p reg);

int32_t READ_REG(FILE *arq, nseq_t nseq, REGISTRO_p reg);
int32_t UPDATE_REG(FILE *arq, REGISTRO_p reg);
int32_t DELETE_REG(FILE *arq, nseq_t nseq, REGISTRO_p reg);

int32_t CALC_SIZE_RAM(int32_t ram_size, int32_t ratio, nseq_t *rnum);
int32_t SEQUENTIAL_SWEEP(FILE *arq, int32_t rnum_by_page, nseq_t *valid_registers, int32_t *num_of_pages);
int32_t RANDOM_SWEEP(FILE *arq, nseq_t qtd_reg, nseq_t *valid_registers);
int32_t PRINT_REG(REGISTRO_p reg);

int32_t FILE_REGS(FILE *arq, nseq_t *rnum);
int32_t FILE_SIZE(FILE *arq, memsize_t *arq_size);
int32_t GENERATE_FIRST_100KB(FILE *arq, nseq_t *rnum);

#endif // REGISTRO_H


