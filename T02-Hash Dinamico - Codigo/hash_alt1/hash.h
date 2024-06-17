#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "registro.h"
#include <stdio.h>

struct directory_entry {
  long int bucket;
  unsigned int pl;
};

typedef struct directory_entry* directory_t;

struct hash {
  directory_t diretorio;
  unsigned int diretorio_size;
  long int bucket_qty;
  unsigned int regs_in_bucket;
  unsigned int pg;
  
  FILE* fp;
  char* fname;
};

typedef struct hash* Hash;

int CRT_HASH(Hash* hash_ptr, unsigned int pg_inicial, char* hdir);
int SRCH_HASH(Hash hash, unsigned int chave, Registro reg);
int INST_HASH(Hash hash, Registro reg);
int RMV_HASH(Hash hash, unsigned int chave, Registro reg);
int PRNT_HASH(Hash hash);
int PERSISTE_DIR(Hash hash);
int RECUPERA_DIR(Hash *hash_ptr, unsigned int tam, unsigned int bs, long int bn, unsigned int depth, char* hdir);

#endif // HASH_H_INCLUDED

