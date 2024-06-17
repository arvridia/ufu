/*Arthur Resende Santos 12011BCC020
*/

#include <stdio.h>
#include <stdlib.h>
#define size 20

struct lista{

    float *v1;
    int numero;
};

typedef struct lista lista;

lista cria_lista();
int lista_vazia(lista A1);
int lista_cheia(lista A1);
lista insere_elem(lista A1, float dado);
lista remove_elem(lista A1, float dado);
void imprimir_lista(lista A1);
lista limpa_lista(lista A1);
float get_cont(lista A1, int cont);

int main(){
    lista A = cria_lista();

    imprimir_lista(A);

    A = insere_elem(A,4);
    A = insere_elem(A,8.5);
    A = insere_elem(A,-1.1);
    A = insere_elem(A,19);
    A = insere_elem(A,2.5);
    A = insere_elem(A,7);
    A = insere_elem(A,8.45);
    A = insere_elem(A,7);
    A = insere_elem(A,-9);
    A = insere_elem(A,22);
    A = insere_elem(A,45.7);

    imprimir_lista(A);
    A = remove_elem(A,7);
    imprimir_lista(A);

    A = remove_elem(A,8.55);
    imprimir_lista(A);

    A = limpa_lista(A);
    imprimir_lista(A);
}
lista cria_lista(){
    lista A1;
    A1.numero = 0;
    A1.v1 = malloc(size*sizeof(float));
    return A1;
}
int lista_vazia(lista A1){
    if(A1.numero == 0)
        return 1;
    else
        return 0;
}
int lista_cheia(lista A1){
    if(A1.numero == size)
        return 1;
    else
        return 0;
}
lista insere_elem(lista A1, float dado){
    if(lista_cheia(A1))
        exit(1);

    A1.v1[A1.numero] = dado;
    A1.numero++;
    return A1;
}
lista remove_elem(lista A1, float dado){
    int cont  = -1;
    if(lista_vazia(A1))
        exit(1);
    for(int i = 0; i < A1.numero; i++){
        if(A1.v1[i] == dado){
            cont = i;
            break;
        }
    }
    if(cont == -1){
        printf("Elemento nao existe\n");
        exit(1);
    }
    A1.v1[cont] = 0;
    for(int i = cont; i < A1.numero; i++){
        int temp = A1.v1[i];
        A1.v1[i] = A1.v1[i+1];
        A1.v1[i+1] = temp;
    }
    A1.numero--;
    return A1;
}
void imprimir_lista(lista A1){
    if(lista_vazia(A1)){
        printf("lista vazia\n");
        exit(1);
    }

    for(int i = 0; i < A1.numero; i++)
        printf("%.2f,", A1.v1[i]);
    printf("\n");
}
lista limpa_lista(lista A1){
    if(lista_vazia(A1))
        exit(1);
    for(int i = 0; i<A1.numero; i++)
        A1.v1[i] = 0;
    A1.numero = 0;
    return A1;
}
float get_cont(lista A1, int cont){
    if(cont >= A1.numero)
        return -9999999;
    return A1.v1[cont];
}
get_pos(){
    //retorna o valor do elemento na posicao solicida, se existente
}

apaga_lista(){
    //libera espaço de memoria alocado para uma lista
}

