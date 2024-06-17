/*  Este programa apresenta o conteúdo de um arquivo na tela do computador,
	mas, caso haja o caracter 'espaço', ele é trocado por '*'.
	Criado por Arthur Resende Santos, 12011BCC020, em 2020.	*/
	
#include <stdio.h>
#define MAX 100
#define MAX1 1000



int 
main()
{
	FILE *abrir = NULL; /*declaração da variável usada para abertura do arquivo*/
	char arquivo[MAX]; /*array para armazenar o nome do arquivo de escolha do usuário*/
	char letra = 0;/*para armazenamento dos caracteres encontrados no arquivo*/
	printf("Digite o nome do arquivo do qual o conteúdo será mostrado:\n");
	scanf("%s", arquivo);/*armazenamento do nome do arquivo*/
	abrir = fopen(arquivo, "r");/*abrindo o arquivo*/
	if (abrir == NULL)/*caso a abertura apresente erro*/
	{
		fprintf(stderr, "Erro ao abrir o arquivo %s\n", arquivo);
		return 5; /*programa finalizará após a mensagem de erro*/
	}
	while (!feof(abrir))/*esta operação ocorrerá enquanto o programa não detectar 'fim do arquivo'*/
	{
		letra = fgetc(abrir);/*capturando um caracter*/
		if (letra == ' ')
			printf("*");/*caso encontre o 'espaço', substituirá por '*'*/
		else
			printf("%c", letra);/*caso não encontre, apresentará o caracter encontrado*/
	}
	printf("\n");
	fclose(abrir);//fechando o arquivo que foi aberto
	abrir == NULL;
	return 0;
}