#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "indice.h"
#include "registro.h"

#define MAX_REG 1024
typedef uint32_t u32;

u32 MurmurOAAT_32(const char* str, uint32_t h)
{
  // One-byte-at-a-time hash based on Murmur's mix
  // Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp
  for (; *str; ++str) {
    h ^= *str;
    h *= 0x5bd1e995;
    h ^= h >> 15;
  }
  return h;
}

u32 _CALC_N(u32 p){
  u32 np = 1;

  for(u32 i = 0; i < p; i++)
    np *= 2;

  return np;
}

int CRT_HASH(Hash* hash_ptr, u32 prof_global_inicial, char* hdir){
    if(hash_ptr == NULL || prof_global_inicial <= 0 || hdir == NULL) return 0;

    *hash_ptr = malloc(sizeof(struct hash));
    if(*hash_ptr == NULL) return 0;

    Hash hash = *hash_ptr;

    u32 diretorio_size = _CALC_N(prof_global_inicial);

    hash->diretorio_size = diretorio_size;
    hash->bucket_qty = diretorio_size;
    hash->bucket_regs = diretorio_size;
    hash->prof_global = prof_global_inicial;

    hash->diretorio = malloc(hash->diretorio_size * sizeof(struct entrada_diretorio));
    if(!hash->diretorio){
        free(hash);
        hash = NULL;
        return 0;
    }

    hash->fname = malloc(MAX_REG * sizeof(char));
    if(hash->fname == NULL){
        free(hash);
        hash = NULL;
        return 0;
    }

    strcpy(hash->fname, hdir);
    hash->fp = fopen(hash->fname, "w+");
    if(hash->fp == NULL){
        free(hash->diretorio);
        free(hash);
        hash = NULL;
        return 0;
    }

    rewind(hash->fp);
    long int fp_pointer;

    struct indice reg;
  	strcpy(reg.key, "");

    for(u32 i = 0; i < hash->diretorio_size; i++){
        fp_pointer = ftell(hash->fp);
        for(u32 j = 0; j < hash->bucket_qty; j++){
            if(!fwrite(&reg, sizeof(struct indice), 1, hash->fp)){
                fclose(hash->fp);
                free(hash->diretorio);
                free(hash);
                hash = NULL;
                return 0;
            }
        }
        hash->diretorio[i].pl = hash->prof_global;
        hash->diretorio[i].bucket = fp_pointer;
    }

    fclose(hash->fp);
    PERSISTE_DIR(hash);

    return 1;
}

int _NVLD_HASH(Hash hash){
    return(hash == NULL || hash->diretorio == NULL || hash->prof_global <= 0 || hash->fname == NULL);
}

int SRCH_HASH(Hash hash, char * chave, Registro reg){
    if(_NVLD_HASH(hash) || chave == 0 || reg == NULL) return 0;

    struct indice idx;

    hash->fp = fopen(hash->fname, "r");
    if(hash->fp == NULL) return 0;

    u32 bucket = MurmurOAAT_32(chave, hash->diretorio_size);
    fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);

    for(u32 i = 0; i < hash->bucket_qty; i++){
        if(!fread(&idx, sizeof(struct indice), 1, hash->fp)) return 0;
        if(!strcmp(idx.key, chave)) {
        	printf("ERROR SRCH_HASH\n");
        	return 1;
        }
    }

    fclose(hash->fp);

    return 0;
}

char *my_utoa(unsigned int num, char *str) {
  if(str == NULL)
    return NULL;
  sprintf(str, "%d", num);
  return str;
}

int INST_HASH(Hash hash, Registro reg){
  if(_NVLD_HASH(hash) || reg == NULL) return 0;

  hash->fp = fopen(hash->fname, "r+");
  if(hash->fp == NULL) return 0;

  u32 bucket = MurmurOAAT_32(reg->matricula, hash->diretorio_size) % hash->diretorio_size;
  fseek(hash->fp, hash->diretorio[bucket].bucket , SEEK_SET);

  struct registro aux;

  u32 original;
  for(original = 0; original < hash->bucket_qty; original++){
      fread(&aux, sizeof(struct indice), 1, hash->fp);
      if(aux.nseq != 0) break;
  }

  // original bucket has space
  if(original != hash->bucket_qty) {
      fseek(hash->fp, -(long int)sizeof(struct indice), SEEK_CUR);
      Indice ind = NULL;
      strcpy(ind->key, reg->matricula);
      ind->rid = (int *) malloc (sizeof(int));
  } else {
    // original bucket is full
    struct registro buffer[hash->bucket_qty];
    aux.nseq = 0;

    // full bucket, duplicate directory
    if(hash->prof_global == hash->diretorio[bucket].pl){
      hash->diretorio_size *= 2;
      hash->prof_global++;

      hash->diretorio = (directory_t) realloc(hash->diretorio, hash->diretorio_size * sizeof(struct entrada_diretorio));
      if(hash->diretorio == NULL) return 0;

      // copying halves
      for(u32 i = 0; i < hash->diretorio_size / 2; i++){
        hash->diretorio[hash->diretorio_size / 2 + i].pl = hash->diretorio[i].pl;
        hash->diretorio[hash->diretorio_size / 2 + i].bucket = hash->diretorio[i].bucket;
      }
    }

    // tidying up directory
    u32 bucket_duplicado = bucket + hash->diretorio_size / 2;
    hash->diretorio[bucket].pl++;

    // tidying up new duplicated bucket (at the end of the file)
    hash->diretorio[bucket_duplicado].pl++;
    fseek(hash->fp, 0, SEEK_END);
    hash->diretorio[bucket_duplicado].bucket = ftell(hash->fp);
    hash->bucket_regs ++;

    // back to original bucket
    fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);

    // moving stuff around
    for(u32 j = 0; j < hash->bucket_qty; j++){
        fread(&buffer[j], sizeof(struct registro), 1, hash->fp);
        // `Registro` still in original bucket
        char tmp_buf[11];
        my_utoa(buffer[j].nseq,tmp_buf);
        if(hash->diretorio[MurmurOAAT_32(tmp_buf, hash->diretorio_size)].bucket == hash->diretorio[bucket].bucket) buffer[j].nseq = 0;
        else{
            // registro in duplicated bucket (remove from the original)
            fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
            fwrite(&aux, sizeof(struct registro), 1, hash->fp);
        }
    }

    // go to duplicated bucket
    fseek(hash->fp, hash->diretorio[bucket_duplicado].bucket, SEEK_SET);
    u32 qtd = 0;
    for(u32 j = 0; j < hash->bucket_qty; j++){
        fwrite(&buffer[j], sizeof(struct registro), 1, hash->fp);
        qtd++;
    }

    // original
    char buffer_str_to_be_hashed[11];
    // gambiarra firme
    my_utoa(reg->nseq, buffer_str_to_be_hashed);
    if(MurmurOAAT_32(buffer_str_to_be_hashed, hash->diretorio_size) == bucket){
        fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);
        for(original = 0; original < hash->bucket_qty; original++){
            fread(&aux, sizeof(struct registro), 1, hash->fp);
            if(aux.nseq == 0) break;
        }

        if(original != hash->bucket_qty){
            fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
            fwrite(reg, sizeof(struct registro), 1, hash->fp);
        }
    }
    else{
      fseek(hash->fp, hash->diretorio[bucket_duplicado].bucket, SEEK_SET);
      for(original = 0; original < hash->bucket_qty; original++){
        fread(&aux, sizeof(struct registro), 1, hash->fp);
        if(aux.nseq == 0) break;
      }

      if(original != hash->bucket_qty){
        fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
        fwrite(reg, sizeof(struct registro), 1, hash->fp);
        qtd++;
      }
    }

    hash->bucket_regs++;
  }

  fclose(hash->fp);
  return 1;
}

int RMV_HASH(Hash hash, char *chave, Registro reg){
    if(_NVLD_HASH(hash) || reg == NULL) return 0;

    hash->fp = fopen(hash->fname, "r+");
    if(hash->fp == NULL) return 0;

    u32 bucket = MurmurOAAT_32(chave, hash->diretorio_size);

    fseek(hash->fp, hash->diretorio[bucket].bucket, SEEK_SET);

    struct registro aux;
    aux.nseq = 0;

    for(u32 i = 0; i < hash->bucket_qty; i++){
      if(!fread(reg, sizeof(struct registro), 1, hash->fp)) {
        fclose(hash->fp);
      return 0;
      }

      if((int)reg->nseq == atoi(chave)) {
        fseek(hash->fp, -(long int)sizeof(struct registro), SEEK_CUR);
        fwrite(&aux, sizeof(struct registro), 1, hash->fp);
        fclose(hash->fp);
        return 1;
      }
    }

    fclose(hash->fp);
    return 0;
}

int PRNT_HASH(Hash hash){
  if(_NVLD_HASH(hash)) return 0;

  hash->fp = fopen(hash->fname, "r");
  if(hash->fp == NULL) return 0;

  printf("DIR SIZE: %u\n", hash->diretorio_size);
  printf("RS_BUCKET: %ud\n", hash->bucket_regs);
  printf("BUCKETS: %u\n", hash->bucket_qty);
  printf("G_DEPTH: %u\n", hash->prof_global);

  printf("DIR CONTENT:\n\n");

  struct registro aux;

  for(u32 i = 0; i < hash->diretorio_size; i++){
    printf("(BUCKET %ud, L_DEPTH %u):", hash->diretorio[i].bucket, hash->diretorio[i].pl);

    fseek(hash->fp, hash->diretorio[i].bucket, SEEK_SET);

    for(u32 j = 0; j < hash->bucket_qty; j++){
      fread(&aux, sizeof(struct registro), 1, hash->fp);

      if(aux.nseq != 0) printf(" <%u, %s> |", aux.nseq, aux.matricula);
      else printf(" <%u> |", aux.nseq);
    }

    printf("\n\n");
  }

  fclose(hash->fp);

  return 1;
}

int PERSISTE_DIR(Hash hash) {
  FILE *dir = fopen("dir", "w+");
  if (dir == NULL) return 0;

  fwrite(&hash->diretorio_size, sizeof(u32), 1, dir);
  fwrite(&hash->bucket_regs, sizeof(u32), 1, dir);
  fwrite(&hash->bucket_qty, sizeof(u32), 1, dir);
  fwrite(&hash->prof_global, sizeof(u32), 1, dir);
  fwrite(&hash->diretorio, sizeof(directory_t), 1, dir);

  fclose(dir);
  return 1;
}

int RECUPERA_DIR(Hash *hash_ptr, u32 tam, u32 bs, u32 bn, u32 depth, char* hdir) {
  *hash_ptr = malloc(sizeof(struct hash));
  if(*hash_ptr == NULL) return 0;

  Hash hash = *hash_ptr;

  hash->diretorio_size = tam;
  hash->bucket_qty = bs;
  hash->bucket_regs = bn;
  hash->prof_global = depth;
  hash->diretorio = malloc(hash->diretorio_size * sizeof(struct entrada_diretorio));
  if (hash->diretorio == NULL) {
    free(hash->diretorio);
    return 0;
  }

  hash->fname = malloc(MAX_REG * sizeof(char));
  if (hash->fname == NULL) {
    free(hash->fname);
    return 0;
  }

  strcpy(hash->fname, hdir);
  hash->fp = fopen(hash->fname, "r");
  if(hash->fp == NULL){
    free(hash->diretorio);
    free(hash);
    hash = NULL;
    return 0;
  }

  rewind(hash->fp);
  long int fp_pointer;
  for(u32 i = 0; i < hash->diretorio_size; i++){
    fp_pointer = ftell(hash->fp);
    for(u32 j = 0; j < hash->bucket_qty; j++){
      fseek(hash->fp, sizeof(struct registro), SEEK_CUR);
    }
    hash->diretorio[i].pl = hash->prof_global;
    hash->diretorio[i].bucket = fp_pointer;
  }

  fclose(hash->fp);
  return 1;
}

