#include <stdio.h>
#include <string.h>
#define MAX 100

/* Este programa inverte a frase digitada eplo usuário.
	Criado por Arthur Resende Santos, 2020. */

int
main ()
{
	char nani[MAX]; //frase do usuário
	int y = 0; //contador de posições dentro do array
	int count = 0; //tamanho da string já colocada
	int x = 0;
	
	for (;y < MAX; y++)
	{
		nani[y] = getchar(); //guarda a frase do usuário
		if(nani[y] == '\n')
		{
			break;
		}
		count++;
	}
	x = strlen(nani);
	printf("%d", x);
	while(count >= 0)
	{
		putchar(nani[count]); //apresenta a frase inversa
		count--;
	}	
	printf ("\n");
}