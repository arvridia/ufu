/* Este programa cria uma matriz 5x5 a partir dos números informados pelo usuário.
Além disso, apresenta a sua diagonal secundária. 
Criado por Arthur Resende Santos, 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
	float m[5][5]; // matriz
	int i = 0; // usado para determinar o número da linha no momento de coleta de dados inseridos pelo usuário
	int j = 0; // usado para determinar o número da coluna no momento de coleta de dados inseridos pelo usuário
	int z = 0; // usado como contador dos elementos inseridos pelo usuário
	int x = 0; // usado para determinar o número da coluna no momento de apresentação da matriz
	int p = 0; // usado para determinar o número da linha no momento de apresentação da matriz
	int y = 0; // usado para determinar o número da coluna no momento de apresentação da diagonal secundária
	int h = 0; // usado para determinar o número da linha no momento de apresentação da diagonal secundária
	printf ("Digite 25 números para preencher a matriz. Deve-se digitar um número, apertar 'enter' e repetir:\n");
	while ( z < 25 )
	{
		scanf ("%f", &m[i][j]); // para receber os dados do usuário
		j++;
		z++;
		if ( j >= 5) // quando deve-se mudar de linha
		{
			i++;
			j = 0;
		}
	}
	z = 0;
	printf ("A matriz é:\n");
	while ( z < 25)
	{
		printf ("%.0f", m[p][x]); // apresentação da matriz
		x++;
		z++;
		if ( z == 5 || z == 10 || z == 15 || z == 20 || z == 25) // quando deve-se mudar de linha ou finalizar a apresentação
		{
			printf ("\n");
			x = 0;
			p++;
		}
	}
	y = y + 4;
	printf ("A diagonal secundária é:\n");
	while ( h < 5 )
	{
		printf ("%.0f ", m[h][y]); // apresentação da diagonal secundária
		h++;
		y--;
	}
	printf ("\n");
} 