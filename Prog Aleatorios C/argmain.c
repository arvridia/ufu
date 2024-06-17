/*  Este programa cria um vetor de tamanho informado pelo usuário pela linha de comando, coleta e 
armazena inteiros dentro do vetor e os apresenta
	Criado por Arthur Resende Santos 12011BCC020*/
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
	if (argc == 2){
		int num = 0;
		num = atoi(argv[1]);
		int vetorInt[num];
		if (num < 30){
			int count;
			printf("Digite %d números:\n", num);
			for(count = 0; count < num; count++){
				scanf("%d", &vetorInt[count]);
			}
			printf("Os números armazenados são:\n");
			for(count = 0; count < num; count++)
				printf("%d\n", vetorInt[count]);
		}
		else
			printf("O número deve ser menor que 30.\n");
	}
	else
		printf("Somente deve ser escrito o tamanho do vetor.\n");
}