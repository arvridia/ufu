/*  Este programa calcula o arranjo simples de N elementos por P, números inteiros coletados do usuário
	Criado por Arthur Resende Santos 12011BCC020*/
#include <stdio.h>

unsigned long int arranjo(int *N, int *P){
	unsigned long int resultado = 1;
	unsigned long int resultado2 = 1;
	int fatorial;
	int sub = 0;
	sub = *N - *P;
	for(fatorial = 1; fatorial <= sub; fatorial++)
		resultado = resultado * fatorial;
	for(fatorial = 1; fatorial <= *N; fatorial++)
		resultado2 = resultado2 * fatorial;
	return resultado = resultado2/resultado;
}


int 
main()
{
	int N = 0;
	int P = 0;
	unsigned long int resultado = 0;
	printf("Digite um número inteiro positivo para calcular seu arranjo simples:\n");
	scanf("%d", &N);
	if (N < 0){
		printf("O número inserido não é válido. O programa foi encerrado.\n");
		return 0;
	}
	printf("Agora digite de quantos em quantos elementos será tomado:\n");
	scanf("%d", &P);
	if (P > N){
		printf("O número de elementos a se agrupar deve ser menor que o total de elementos. O programa foi encerrado.\n");
		return 0;
	}
	resultado = arranjo(&N, &P);
	printf("O resultado do arranjo simples de %d por %d é igual a %lu.\n", N, P, resultado);
	return 0;
}

