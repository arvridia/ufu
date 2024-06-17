#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define N 10000

struct cliente{
    char nome[MAX];
    int agencia;
    int conta;
    float cpf;
};
typedef struct cliente Cliente;

void troca(Cliente v[], int i, int j){
     Cliente temp;
     temp = v[i];
     v[i] = v[j];
     v[j] = temp;
}

void InsertionSort(Cliente *v, int n) {
int i, j, aux;
  for(i = 1; i < n; i++) {
    aux = v[i].agencia;
    for (j=i-1; j>=0 && v[j].agencia>aux; j--){
         v[j+1].agencia = v[j].agencia;
    }
    v[j+1].agencia = aux;
  }
}

void intercala (Cliente v[], int e, int m, int d){
    Cliente *r; //vetor auxiliar para armazenar a mistura
    int i,j,k;
    r = (Cliente *) malloc (((d+1)-e)*sizeof(Cliente));
    i=e;
    j=m+1;
    k=0;
    while ((i<=m)&&(j<=d)){ // intercala enquanto nenhuma das partes do vetor
        if(v[i].agencia <= v[j].agencia){ // foi consumida totalmente
            r[k]=v[i];
            i++;
        }
        else{
            r[k] = v[j];
            j++;
        }
        k++;
    }
    while (i<=m) {
            r[k] =v[i];
            i++;
            k++;
    } //termina de intercalar se sobrou à esquerda
    while (j<=d) {
        r[k] = v[j];
        j++;
        k++;
    } //termina de intercalar se sobrou à direita
    //Cópia do vetor auxiliar (contendo os dados ordenados) sobre o vetor original
    j=0;
    for(i=e;i<=d;i++){
        v[i] = r[j];
        j++;
    }
    free(r);
}

void mergesort (Cliente v[], int e, int d){
    int m;
    if (e<d){
        m = (e+d)/2;
        mergesort(v,e,m);
        mergesort(v,m+1,d);
        intercala(v,e,m,d);
    }
}

int main()
{
    int swi = 0;
    int count = 0; //count contabiliza quantos elementos ha no vetor
    Cliente Client[N]; //vetor de clientes
    do {
        do{
            // Obtem opcao do usuario
            printf("\n\nOpcoes:\n");
            printf("[1] Inserir um elemento no vetor\n");
            printf("[2] Remover um elemento do vetor\n");
            printf("[3] Imprimir o vetor\n");
            printf("[4] Esvaziar o vetor\n");
            printf("[5] Ordenar o vetor\n");
            printf("[6] Sair do sistema\n");
            printf("\nQual opcao deseja realizar? ");
            scanf("%d", &swi);
            setbuf(stdin, NULL);
            if (swi < 1 || swi > 6)
                printf("\nOpcao invalida...Somente existem essas opcoes:\n");

        } while (swi < 1 || swi > 6);

        if (swi == 6)
            break;
        else if (swi != 1 && count == 0) {
            printf("\nAntes de realizar operacoes, crie um vetor.\n\n");
            continue;
        }

        switch (swi) {
            case 1: {
                Cliente A;
                printf("Digite o nome do cliente a ser inserido no vetor: \n");
                gets(A.nome);
                fflush(stdin);
                printf("Digite a agencia do cliente a ser inserido no vetor: \n");
                scanf("%d", &A.agencia);
                printf("Digite o numero da conta do cliente a ser inserido no vetor: \n");
                scanf("%d", &A.conta);
                printf("Digite o CPF do cliente a ser inserido no vetor: \n");
                scanf("%f", &A.cpf);
                if (count == N)
                    printf("\nO vetor esta cheio! O cliente %s nao foi incluido.\n\n", A.nome);
                else{
                    Client[count] = A;
                    printf("\nO cliente %s foi incluido com sucesso!\n\n", A.nome);
                    count++;
                }
                break;
            }
            case 2: {
                if (count == 0)
                        printf("\nVetor vazio!\n\n");
                else{
                    char A[MAX];
                    printf("Digite o nome do cliente a ser removido do vetor: \n");
                    gets(A);
                    fflush(stdin);
                    int Aux = 0;
                    int i = 0;
                    while (Aux < count && strcmp(Client[Aux].nome,A) != 0)
                        Aux++;
                    if (Aux != count){ // Final do vetor (cliente nao existe)
                        for (i = Aux+1; i < count; i++)
                            Client[i-1] = Client[i];
                        printf("\nO cliente %s foi removido com sucesso!\n\n", A);
                        count--;
                    }
                }
                break;
            }
            case 3: {
                for(int i=0;i<count;i++){
                    printf("\nCliente %d\n", i+1);
                    printf("Nome:\n");
                    printf("\t%s\n", Client[i].nome);
                    printf("Agencia:\n");
                    printf("\t%d\n", Client[i].agencia);
                    printf("Conta:\n");
                    printf("\t%d\n", Client[i].conta);
                    printf("CPF:\n");
                    printf("\t%.f\n", Client[i].cpf);
                }
                break;
            }
            case 4:{
                count = 0;
                break;
            }
            case 5:{
                InsertionSort(&Client, count-1);
                printf("\nOrdenacoes por nome e por agencia completas!\n");
                break;
            }

        }
    }while (swi != 6);
    printf("\nEncerrando o programa...\n");
    return 0;
}
