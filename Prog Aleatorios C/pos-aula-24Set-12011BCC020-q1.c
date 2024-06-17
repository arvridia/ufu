/* Este programa captura uma frase digitada pelo usuário 
   e apresenta seu número de letras, o inverso do inserido e
   multiplica o primeiro caracter pelo do meio e último, apresentando o resultado.
   Criado por Arthur Resende Santos, 2020 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

int X = 0;
void loadA(char nani[MAX]);
void inv(char nani[MAX]);
int prod(char a, char b, char c);
int
main()
{
	int X = 0;
	int r = 0;
	char a[MAX];
	loadA(a);
	X = strlen(a);
	inv(a);
	r = prod(a[0], a[(X % 2 == 0)? (X / 2) - 1:X / 2], a[X - 1]);
	printf("%d", r);
	if ( X == MAX)
		fprintf(stderr, "Número máximo de caracteres foi atingido. Consequentemente, o programa pode não funcionar como esperado");
	printf("\n");
	return 0;
	
	

}
	
void
loadA(char nani[MAX])
{
	int y = 0; //contador de posições dentro do array
	int count = 0; //tamanho da string já colocada
	
	for (;y < MAX; y++)
	{
		nani[y] = getchar(); //guarda a frase do usuário
		if(nani[y] == '\n')
		{
			break;
		}
		count++;
	}
	int X = strlen(nani);
	printf("A quantidade de caracteres digitados é igual a %d", X);
}
void
inv(char nani[MAX])
{
	int count = 0;
	count = strlen(nani);
	while(count >= 0)
	{
		putchar(nani[count]); //apresenta a frase inversa
		count--;
	}	
	printf ("\n");
}
int
prod(char a, char b, char c)
{
	
	int r = 0;
	int x, y, z = 0;
	x = a;
	y = b;
	z = b;
	r = x*y*z;
	return r ;
}












