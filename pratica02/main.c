//Amanda Rodrigues Leandro 12311EMC029
#include <stdio.h>
#include <stdlib.h>

int main(){
    int num = 0;
    do{
        printf("Insira um numero inteiro maior que zero\n");
        scanf("%d", &num);
        if(num <= 0)
            printf("O numero deve ser maior que zero!\n");
    }while (num <= 0);
    int soma = 0;
    for (int i =1; i < (num/2)+1; i++){
        if(num%i == 0)
            soma = soma + i;
    }
    printf ("Soma eh:%d\n", soma);
    return 0;
}
