/*  Este programa cria e apresenta uma matriz
	de números aleatórios, de 0 a 10 e
	com base na hora de execução do programa,
	de ordem especificada pelo usuário. Além disso,
	cria e apresenta a sua respectiva matriz transposta
	e as comparam, apresentando se são simétricas
	ou assimétricas.
	Criado por Arthur Resende,
	Carlos Augusto Gomes,
	Henrique Braga e
	Pedro Guarnieri,
	no ano de 2020.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX1 10
#define MAX2 100

//------Protótipo funções------
int loadA (float a[MAX1][MAX1], FILE *arquivo, int m, int n);
void transp( float a[MAX1][MAX1], float at[MAX1][MAX1], int m, int n);
int simetr( float a[MAX1][MAX1], float at[MAX1][MAX1], int m, int n);
void showA( float a[MAX1][MAX1], float at[MAX1][MAX1], int m, int n);


int
main()
{
    FILE *abrir = NULL;                     //variavel do tipo file
	float a[MAX1][MAX1];                  //representa a matriz
    float at[MAX1][MAX1];                 //representa a matriz transposta
    char arquivo[MAX2];             //string que guarda o nome do arquivo digitado
    int m = 0;                          //índice 1 da matriz
    int n = 0;                          //índice 2 da matriz
    

    printf("Digite o nome do arquivo:");
    scanf("%s", arquivo);
    abrir = fopen(arquivo,"r");
	fscanf(abrir, "%d %d", &m, &n);

    loadA ( a, abrir, m, n);        /*chamada a função loadA  */
    transp( a, at, m, n);       /*chamada a função transp */
    showA( a, at, m, n);        /*chamada a função showA  */
    simetr( a, at, m, n);       /*chamada a função simetr */
    fclose(abrir);
	abrir == NULL;
	return 0;
}
int
loadA(float a[MAX1][MAX1], FILE *abrir, int m, int n)
{
	int u, o = 0;
	int i, j = 0; //número de linhas e colunas
	if(abrir == NULL) //caso haja falha ao abrir o arquivo
	{
		fprintf(stderr, "Falha ao abrir o arquivo");
		exit(1);
		return 0;
	}
	for (i = 0, j = 0;!feof(abrir);i++, j = 0) /*laço para mudança de linha e para manter o próximo laço funcionando até que o arquivo seja completamente lido*/
	{
		for (;j < n;j++)//para mudar de coluna
			fscanf(abrir, "%f", &a[i][j]);//carregamento da matriz
		fscanf(abrir, " ");	//para evitar que o programa leia o fim do arquivo e dê erros
	}
	return 1;
}
void 
transp ( float a[MAX1][MAX1], float at[MAX1][MAX1], int m, int n)      /*funcao que elabora da matriz transposta*/
{
    int i = 0;              //contador de laço 1
    int j = 0;              //contador de laço 2

    for ( i = 0; i < m; i++)
        {
            for ( j = 0; j < n; j++)
                at[j][i]=a[i][j];           //transformando linha de uma matriz em coluna de outra
        }
}
int 
simetr ( float a[MAX1][MAX1], float at[MAX1][MAX1], int m, int n)        //função que verifica se há simetria entre as matrizes
{
    int i = 0;              // contador de laço 1
    int j = 0;              // contador de laço 2
    int soma = 0;           //variável auxiliar para achar simetria

    for ( i = 0; i < m; i++) 		        //verificando se os valores da matriz original são iguais aos da transposta
        {
            for ( j = 0; j < n; j++)
            {
                if ( a[i][j]==at[i][j])
                    soma++;                 //se os elementos for igual, soma++
            }
        }
    if ( soma == (m*n))  			        // verificando se a quantidade de itens iguais é igual a quantidade de elementos que existem na matriz
    {
        printf("Esta matriz é simétrica");
        return 1;
    }
    else
    {
        printf("Esta matriz é assimétrica");
        return 0;
    }
}
void showA( float a[MAX1][MAX1], float at[MAX1][MAX1], int m, int n)        //Função que vai imprimir a e at
{
    int i = 0;              //contador de laço 1
    int j = 0;              //contador de laço 2

    printf("\nA matriz é: \n");
        for ( i = 0; i < m; i++)                    //impressão da matriz
        {
            for ( j = 0; j < n; j++)
                printf("%f ", a[i][j]);
            printf("\n");
        }
    printf("\nE sua transposta é: \n");      //impressão da matriz transposta
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < m; j++)
                printf("%f ", at[i][j]);
            printf("\n");
        }
}
