/* Este programa apresenta as iniciais das palavras inseridas pelo usuário
	Criado por Arthur Resende Santos, 2020*/


#include <stdio.h>
#include <string.h>
#define MAX 100

int
main()
{
	char nome[MAX]; //array utilizado para armazenar a palavra inserida pelo usuário
	int i = 0; // essa variável representa a posição de um determinado carácter dentro do array
	int x = 0; // variável utilizada para armazenar o valor do tamanho do array utilizado pelo usuário
	scanf ("%[^\n]c", nome); //captura dados
	printf("%c", nome[0]); // apresenta dados
	x = strlen(nome);
	while( i < x) //enquanto essa expressão for verdadeira, o laço ocorre
	{
		if(nome[i] == ' ') // se essa expressão for igual a zero, ela é ignorada
			printf("%c", nome[i + 1]); //apresenta dados
		i++;
	}
	printf ("\n"); // apresenta dados, no caso, um salto de linha
}
