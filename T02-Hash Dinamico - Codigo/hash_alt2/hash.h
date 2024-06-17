#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "registro.h"
#include <stdio.h>
#include <stdint.h>

struct entrada_diretorio {
  uint32_t pl;
  uint32_t bucket;
};

typedef struct entrada_diretorio* directory_t;

struct hash {
  directory_t diretorio;
  uint32_t diretorio_size;
  uint32_t bucket_qty;
  uint32_t bucket_regs;
  uint32_t prof_global;
  FILE *fp;
  char *fname;
};

typedef struct hash *Hash;

int CRT_HASH(Hash* hash_ptr, uint32_t pg_inicial, char* hdir);
int SRCH_HASH(Hash hash, char * chave, Registro reg);
int INST_HASH(Hash hash, Registro reg);
int RMV_HASH(Hash hash, char * chave, Registro reg);
int PRNT_HASH(Hash hash);
int PERSISTE_DIR(Hash hash);
int RECUPERA_DIR(Hash *hash_ptr, uint32_t tam, uint32_t bs, uint32_t bn, uint32_t depth, char* hdir);

#endif

