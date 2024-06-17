#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REG 1024

unsigned int _CALC_N(unsigned int p) {
  unsigned int np = 1;

  for(unsigned int i = 0; i < p; i++)
    np *= 2;

  return np;
}

unsigned int _HASH_FUNCTION(unsigned int chave, unsigned int N) {
  return chave % N;
}

int CRT_HASH(Hash* hash_ptr, unsigned int pg_inicial, char* hdir) {
  if(hash_ptr == NULL || pg_inicial <= 0 || hdir == NULL) return 0;

  *hash_ptr = malloc(sizeof(struct hash));
  if(*hash_ptr == NULL) return 0;

  Hash hash = *hash_ptr;

  unsigned int diretorio_size = _CALC_N(pg_inicial);

  hash->diretorio_size = diretorio_size;
  hash->bucket_qty = diretorio_size;
  hash->regs_in_bucket = diretorio_size;
  hash->pg = pg_inicial;

  hash->diretorio = malloc(hash->diretorio_size * sizeof(struct directory_entry));
  if(hash->diretorio == NULL) {
    free(hash);
    hash = NULL;
    return 0;
  }

  hash->fname = malloc(MAX_REG * sizeof(char));
  if(hash->fname == NULL) {
    free(hash);
    hash = NULL;
    return 0;
  }

  strcpy(hash->fname, hdir);
  hash->fp = fopen(hash->fname, "w+");
  if(hash->fp == NULL) {
    free(hash->diretorio);
    free(hash);
    hash = NULL;
    return 0;
  }

  rewind(hash->fp);
  long int fp_pointer;

  struct registro reg;
  reg.nseq = 0;

  for(unsigned int i = 0; i < hash->diretorio_size; i++) {
    fp_pointer = ftell(hash->fp);
    for(unsigned int j = 0; j < hash->bucket_qty; j++) {
      if(!fwrite(&reg, sizeof(struct registro), 1, hash->fp)) {
        fclose(hash->fp);
        free(hash->diretorio);
        free(hash);
        hash = NULL;
        return 0;
      }
    }
    hash->diretorio[i].pl = hash->pg;
    hash->diretorio[i].bucket = fp_pointer;
  }

  fclose(hash->fp);
  PERSISTE_DIR(hash);

  return 1;
}

int _NVLD_HASH(Hash hash) {
  return(hash == NULL || hash->diretorio == NULL || hash->pg <= 0 || hash->fname == NULL);
}

int SRCH_HASH(Hash hash, unsigned int chave, Registro reg) {
  if(_NVLD_HASH(hash) || chave == 0 || reg == NULL) return 0;

  hash->fp = fopen(hash->fname, "r");
  if(hash->fp == NULL) return 0;

  unsigned int bucket = _HASH_FUNCTION(chave, hash->diretorio_size);

  fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);

  for(unsigned int i = 0; i < hash->bucket_qty; i++) {
    if(!fread(reg, sizeof(struct registro), 1, hash->fp)) return 0;
    if(reg->nseq == chave) return 1;
  }
  
  fclose(hash->fp);
  return 0;
}

int INST_HASH(Hash hash, Registro reg) {
  if(_NVLD_HASH(hash) || reg == NULL) return 0;

  hash->fp = fopen(hash->fname, "r+");
  if(hash->fp == NULL) return 0;

  unsigned int bucket = _HASH_FUNCTION(reg->nseq, hash->diretorio_size);
  fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);    

  struct registro aux;

  unsigned int original;
  for(original = 0; original < hash->bucket_qty; original++) {
    fread(&aux, sizeof(struct registro), 1, hash->fp);
    if(aux.nseq == 0) break;
  }

  if(original != hash->bucket_qty) {
    fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
    fwrite(reg, sizeof(struct registro), 1, hash->fp);
  } else {

    struct registro buffer[hash->bucket_qty];
    aux.nseq = 0;

    if(hash->pg == hash->diretorio[bucket].pl) {
      hash->diretorio_size *= 2;
      hash->pg++;

      hash->diretorio = (directory_t) realloc(hash->diretorio, hash->diretorio_size * sizeof(struct directory_entry));
      if(hash->diretorio == NULL) return 0;
        
      for(unsigned int i = 0; i < hash->diretorio_size / 2; i++) {
        hash->diretorio[hash->diretorio_size / 2 + i].pl = hash->diretorio[i].pl;
        hash->diretorio[hash->diretorio_size / 2 + i].bucket = hash->diretorio[i].bucket;
      }
    }
    
    // duplica diretorio
    long int bucket_duplicado = bucket + hash->diretorio_size / 2;
    hash->diretorio[bucket].pl++;

    hash->diretorio[bucket_duplicado].pl++;
    fseek(hash->fp, 0, SEEK_END);
    hash->diretorio[bucket_duplicado].bucket = ftell(hash->fp);
    hash->regs_in_bucket ++;

    fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);

    for(unsigned int j = 0; j < hash->bucket_qty; j++) {
      fread(&buffer[j], sizeof(struct registro), 1, hash->fp);
      if(hash->diretorio[_HASH_FUNCTION(buffer[j].nseq, hash->diretorio_size)].bucket == hash->diretorio[bucket].bucket) buffer[j].nseq = 0;
      else {
        fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
        fwrite(&aux, sizeof(struct registro), 1, hash->fp);
      }
    }

    fseek(hash->fp, hash->diretorio[bucket_duplicado].bucket, SEEK_SET);

    unsigned int qtd = 0;
    for(unsigned int j = 0; j < hash->bucket_qty; j++) {
      fwrite(&buffer[j], sizeof(struct registro), 1, hash->fp);
      qtd++;
    }
    
    if(_HASH_FUNCTION(reg->nseq, hash->diretorio_size) == bucket) {
      fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);
      for(original = 0; original < hash->bucket_qty; original++) {
        fread(&aux, sizeof(struct registro), 1, hash->fp);
        if(aux.nseq == 0) break;
      }

      if(original != hash->bucket_qty) {
        fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
        fwrite(reg, sizeof(struct registro), 1, hash->fp);
      }
    }
    // reg in new bucket
    else {
      fseek(hash->fp, hash->diretorio[bucket_duplicado].bucket, SEEK_SET);
      for(original = 0; original < hash->bucket_qty; original++) {
        fread(&aux, sizeof(struct registro), 1, hash->fp);
        if(aux.nseq == 0) break;
      }

      if(original != hash->bucket_qty) {
        fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
        fwrite(reg, sizeof(struct registro), 1, hash->fp);
        qtd++;
      }
    }

    hash->regs_in_bucket++;
  }

  fclose(hash->fp);
  return 1;
}

int RMV_HASH(Hash hash, unsigned int chave, Registro reg) {
  if(_NVLD_HASH(hash) || reg == NULL) return 0;

  hash->fp = fopen(hash->fname, "r+");
  if(hash->fp == NULL) return 0;

  long int bucket = _HASH_FUNCTION(chave, hash->diretorio_size);

  fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);

  struct registro aux;
  aux.nseq = 0;

  for(unsigned int i = 0; i < hash->bucket_qty; i++) {
    if(!fread(reg, sizeof(struct registro), 1, hash->fp))  {
      fclose(hash->fp);
    return 0;
    }

    if(reg->nseq == chave) {
      fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
      fwrite(&aux, sizeof(struct registro), 1, hash->fp);
      fclose(hash->fp);
      return 1;
    }
  }
  
  fclose(hash->fp);
  return 0;
}

int PRNT_HASH(Hash hash) {
  if(_NVLD_HASH(hash)) return 0;

  hash->fp = fopen(hash->fname, "r");
  if(hash->fp == NULL) return 0;

  printf("dir size = %u\n", hash->diretorio_size);
  printf("regs in bucket = %u\n", hash->regs_in_bucket);
  printf("buckets quantity = %ld\n", hash->bucket_qty);
  printf("global depth = %u\n", hash->pg);

  printf("\ndir content:\n\n");    

  struct registro aux;

  for(unsigned int i = 0; i < hash->diretorio_size; i++) {
    printf("(B%ld, %u):", hash->diretorio[i].bucket, hash->diretorio[i].pl);

    fseek(hash->fp, hash->diretorio[i].bucket, SEEK_SET);

    for(unsigned int j = 0; j < hash->bucket_qty; j++) {
      fread(&aux, sizeof(struct registro), 1, hash->fp);

      if(aux.nseq != 0) printf(" <%u, %s> |", aux.nseq, aux.text);
      else printf(" <%u> |", aux.nseq);
    }

    printf("\n\n");
  }

  fclose(hash->fp);

  return 1;
}

int PERSISTE_DIR(Hash hash)  {
  FILE *dir = fopen("arquivo_diretorio", "w+");
  if (!dir) return 0;

  fwrite(&hash->diretorio_size, sizeof(unsigned int), 1, dir); 
  fwrite(&hash->regs_in_bucket, sizeof(long int), 1, dir);
  fwrite(&hash->bucket_qty, sizeof(unsigned int), 1, dir); 
  fwrite(&hash->pg, sizeof(unsigned int), 1, dir);
  fwrite(&hash->diretorio, sizeof(directory_t) * hash->diretorio_size, 1, dir);
  

  fclose(dir);
  return 1;
}

int RECUPERA_DIR(Hash *hash_ptr, unsigned int tam, unsigned int bs, long int bn, unsigned int depth, char* hdir) {
  *hash_ptr = malloc(sizeof(struct hash));
  if(*hash_ptr == NULL) return 0;

  Hash hash = *hash_ptr;

  hash->diretorio_size = tam;
  hash->bucket_qty = bs;
  hash->regs_in_bucket = bn;
  hash->pg = depth;
  hash->diretorio = malloc(hash->diretorio_size * sizeof(struct directory_entry));
  if (hash->diretorio == NULL)  {
    free(hash->diretorio);
    return 0;
  }

  hash->fname = malloc(MAX_REG * sizeof(char));
  if (hash->fname == NULL)  {
    free(hash->fname);
    return 0;
  }
 
  strcpy(hash->fname, hdir);
  hash->fp = fopen(hash->fname, "r");
  if(hash->fp == NULL) {
    free(hash->diretorio);
    free(hash);
    hash = NULL;
    return 0;
  }

  rewind(hash->fp);
  long int fp_pointer;
  for(unsigned int i = 0; i < hash->diretorio_size; i++) {
    fp_pointer = ftell(hash->fp);
    for(unsigned int j = 0; j < hash->bucket_qty; j++) {
      fseek(hash->fp, sizeof(struct registro), SEEK_CUR);
    }
    hash->diretorio[i].pl = hash->pg;
    hash->diretorio[i].bucket = fp_pointer;
  }

  fclose(hash->fp);
  return 1;
}

