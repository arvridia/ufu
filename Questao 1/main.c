#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#define N 10

void troca(int v[], int i, int j){
 int temp;
 temp=v[i];
 v[i]=v[j];
 v[j]=temp;
}

int particao(int v[],int esq,int dir){
 int i, fim;
 printf("\n Subvetor:\n");
 for(i=esq; i<=dir; i++) printf("%d ",v[i]); printf("\n");
 fim=esq;
 for(i=esq+1;i<=dir;i++)
 if(v[i]<v[esq]) {
 fim=fim+1;
 troca(v,fim,i);
 }
 troca(v,esq,fim);
 for(i=esq; i<=fim; i++) printf("%d ",v[i]); printf("\n");
 for(i=fim+1; i<=dir; i++) printf("%d ",v[i]); printf("\n");
 return fim;
}

void quicksort(int v[]){
 Pilha p=cria_pilha();
 pilha_push(&p,0,N-1);
 while(pilha_vazia(p)!=1){
 int dir;
 int esq;
 pilha_pop(&p,&esq,&dir);
 if(esq>=dir)
 continue;
 if(esq==dir -1){
 if(v[esq]>v[dir])
 troca(v,esq,dir);}
 else{
 int i=particao(v,esq,dir);
 pilha_push(&p,esq,i-1);
 pilha_push(&p,i+1,dir);}}}


int pivo_aleatorio(int esq, int dir) {
double r;
r = (double) rand()/RAND_MAX; // valor entre 0.01 e 0.99
return (int)(esq + r*(dir-esq));
}
/* A função rand() gera um número pseudo-aleatório entre 0 e a
constante RAND_MAX. A constante RAND_MAX é 32762. */
void quicksort_aleatorizado(int *v, int esq, int dir) {
int i;
if (dir <= esq) return;
troca(v, pivo_aleatorio(esq,dir), esq);
i = particao(v, esq, dir);
quicksort_aleatorizado(v, esq, i-1);
quicksort_aleatorizado(v, i+1, dir);
}
void quicksort_mediana_tres(int v[], int esq, int dir) {
int i;
if(dir <= esq) return;
troca(v, (esq+dir)/2, esq+1);
if(v[esq] > v[esq+1])
troca(v, esq, esq+1);
if(v[esq] > v[dir])
troca(v, esq, dir);
if(v[esq+1] > v[dir])
troca(v, esq+1, dir);
i = particao(v, esq+1, dir-1);
quicksort_mediana_tres(v, esq, i-1);
quicksort_mediana_tres(v, i+1, dir);
}



main(){
 int i,a[N];
 for(i=0; i<N; i++) a[i]=rand()%100;
 for(i=0; i<N; i++) printf("%d ",a[i]);
 quicksort_mediana_tres(a, 0, N-1);
 printf("\n Ordenado:\n");
 for(i=0; i<N; i++) printf("%d ",a[i]);
}

