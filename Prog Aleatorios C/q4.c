/*  Este programa coleta os dados de um arquivo da escolha do usuário 
	e forma uma matriz a partir deles. A matriz é apresentada logo a seguir.
	Depois, o programa apresenta opções sobre o que apresentar referente a matriz,
	essas opções são: diagonal principal, secundária, a soma dos elementos
	de uma linha escolhida pelo usuário ou sair. O programa somente termina 
	caso a opção 'sair' tenha sido escolhida(digitada)
	Criado por Arthur Resende Santos, 12011BCC020, em 2020.*/
	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXXX 11
#define MAXX 10
#define MAX 100

/*----Funções/Protótipos----*/
void loadA (FILE *abrir, int n, float m[n][n]);//carrega os valores aleatórios
void showArrayBi (int n, float m[n][n]);//apresenta os valores
void dp (int n, float m[n][n]);//apresenta a diagonal principal
void ds (int n, float m[n][n]);
float tl (int numero, int n, float m[n][n]);

int 
main()
{
    FILE *abrir = NULL; /*declaração da variável usada para abertura do arquivo*/
	char arquivo[MAX]; /*array para armazenar o nome do arquivo de escolha do usuário*/
	int n, numero = 0; /*para armazenarordem da matriz e número da linha que o usuário quer somar, respectivamente*/
	float soma = 0;/*armazenamento da soma de uma linha escolhida pelo usuário*/
	char escolha[MAXXX];/*armazenamento do que o usuário escolher dentre as opções apresentadas após a impressão da matriz contida no arquivo*/
	float m[MAXX][MAXX];/*matriz*/
	printf("Digite o nome do arquivo do qual o conteúdo será mostrado:\n");
	scanf("%s", arquivo); /*armazenamento do nome do arquivo*/
	abrir = fopen(arquivo, "r");/*abrindo o arquivo*/
	if (abrir == NULL) /*caso a abertura apresente erro*/
	{
		fprintf(stderr, "Erro ao abrir o arquivo '%s'\n", arquivo);
		return 5; /*programa finalizará após a mensagem de erro*/
	}
	fscanf(abrir, "%d", &n);
	/*chamadas das funções de carregamento e apresentação da matriz*/
	loadA(abrir, n, m);
	showArrayBi (n, m);
	do
	{
		printf("\nO que você deseja visualizar a seguir: a diagonal principal da matriz(digite DP), a secundária(DS), a soma dos elementos de uma linha de sua escolha(TotalLinha), ou deseja sair do programa(Sair)?\n");
		scanf("%s", escolha);/*armazenamento do que o usuário escolher, dentre as opções*/
		if (strcmp (escolha, "DP") == 0)
			dp (n, m); /*chamada da função da diagonal principal caso o usuário a escolha*/
		else if (strcmp (escolha, "DS") == 0)
			ds (n, m);/*chamada da função da diagonal secundária caso o usuário a escolha*/
		else if (strcmp (escolha, "TotalLinha") == 0)
		{
			printf("\nDigite o número da linha que você deseja somar\n");
			scanf("%d", &numero);/*armazenamento do número da linha que o usuário escolher*/
			soma = tl (numero, n, m);/*chamada da função de soma da linha caso o usuário a escolha*/
			printf("%.f\n", soma);
		}
	}
	while (strcmp (escolha, "Sair") != 0);/*enquanto o usuário não digitar 'Sair' o programa não finalizará normalmente*/
	fclose(abrir);/*fechamento do arquivo*/
	abrir == NULL;
    return 0;
}
void
loadA(FILE *abrir, int n, float m[n][n]) /* esta função carrega os valores contidos no arquivo para a matriz*/
{
	int i, j;
	for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(abrir, "%f", &m[i][j]);/*coleta da matriz*/
}
void 
showArrayBi(int n, float m[n][n])/*esta função imprime na tela os valores contidos na matriz capturada pela função anterior a partir de um arquivo*/
{
	int i, j;
	printf ("\nOs valores do arquivo são:\n\n");
	for ( i = 0; i < n; i++)                    /*impressão da matriz*/
    {
        for ( j = 0; j < n; j++)
            printf("%.f ", m[i][j]);    
        printf("\n");
    }
}
void 
dp(int n, float m[n][n])/* esta função apresenta a diagonal principal caso o usuário a escolha*/
{
	int i, j;
	printf ("\nA diagonal principal dessa matriz é:\n");
	for(i = 0, j = 0; i < n; i++, j++)
		printf ("%.f\n", m[i][j]); /* apresentação da diagonal principal*/
}
void
ds(int n, float m[n][n])/*esta função apresenta a diagonal secundária caso o usuário a escolha*/
{
	int i, j;
	printf("\nA diagonal secundária dessa matriz é:\n");
	for(i = 0, j = n-1; i < n; i++, j--)
		printf("%.f\n", m[i][j]); /*apresentação da diagonal secundária*/
}
float
tl(int numero, int n, float m[n][n])/* esta função apresenta a soma dos valores contidos na linha escolhida pelo usuário, da matriz*/
{
	float soma = 0;
	int j;
	numero--;
	printf("\nA soma da linha é:\n");
	for(j = 0; j < n; j++)
		soma = soma + m[numero][j];
	return soma;/*retornará o valor da soma de todos os elementos da linha escolhida pelo usuário*/
}
