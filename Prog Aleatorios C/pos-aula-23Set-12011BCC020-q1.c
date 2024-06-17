/* Este programa gera números aleatórios, até 20, e os armazena em uma matriz,
 que é apresentada. Além disso, o programa apresenta a sua diagonal principal também.
 Criado por Arthur Resende Santos, em 2020*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>




/*----Funções----*/
void loadA (int n, float m[n][n]);//carrega os valores aleatórios
void showArrayBi (int n, float m[n][n]);//apresenta os valores
void dp (int n, float m[n][n]);//apresenta a diagonal principal

int 
main()
{
    int n = 4;//ordem da matriz
	float m[n][n];//matriz
	//chamadas das funções
	loadA(n, m);
	showArrayBi (n, m);
	dp (n, m);
	
	printf ("\n");
    return 0;
}
void
loadA(int n, float m[n][n])
{
	int i, j;
	srand(time(NULL));
	printf("Gerando valores aleatórios para a matriz...\n");
	for (i = 0; i < n; i++)
	{
        for (j = 0; j < n; j++)
            m[i][j] = rand() % 21;
	
    } 
}
void 
showArrayBi(int n, float m[n][n])
{
	int i, j;
	printf ("Os valores gerados são:\n\n");
	for ( i = 0; i < n; i++)                    /*impressão da matriz*/
    {
        for ( j = 0; j < n; j++)
            printf("%.0lf ", m[i][j]);    
        printf("\n");
    }
	printf("\n");
}
void 
dp(int n, float m[n][n])
{
	int i, j;
	printf ("E sua diagonal principal é:\n");
	for(i = 0, j = 0; i < n; i++, j++)
		printf ("%.0lf ", m[i][j]); // apresentação da diagonal principal
}