#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimeVetor(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%d ",v[i]);
    printf("\n\n");
    }

void insertionSort(int v[], int n){
    int i, j, aux;
    for(i = 1; i < n; i++){
        aux = v[i];
        j = i-1;
        while((j >= 0) && (v[j] > aux)){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = aux;
    }
}

int main(){
    clock_t t;
    int n;
    scanf("%d",&n);
    int vetor[n];
    for(int i = 0; i < n; i++){
        vetor[i] = rand();
    }
    imprimeVetor(vetor, n);
    t = clock();
    insertionSort(vetor,n);
    t = clock() - t;
    printf("Tempo de ordenacao: %f ms\n\n", ((float)t)/CLOCKS_PER_SEC);
    imprimeVetor(vetor, n);
    return 0;
}
