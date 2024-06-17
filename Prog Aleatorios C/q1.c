/*  Este programa apresenta o conteúdo de um arquivo da escolha do usuário
	Criado por Arthur Resende Santos, 12011BCC020, em 2020. */

#include <stdio.h>
#define MAX 100

int 
main()
{
	FILE *abrir = NULL; /*declaração da variável usada para abertura do arquivo*/
	char arquivo[MAX]; /*array para armazenar o nome do arquivo de escolha do usuário*/
	char letras;/*variável para armazenar cada caracter do arquivo, que será apresentado na tela*/
	printf("Digite o nome do arquivo:\n");
	scanf("%s", arquivo);/*armazenamento do nome do arquivo*/
	abrir = fopen(arquivo, "r");/*abrindo o arquivo*/
	if (abrir == NULL)/*caso a abertura apresente erro*/
	{
		fprintf(stderr, "Erro ao abrir o arquivo %s\n", arquivo);
		return 5; /*programa finalizará após a mensagem de erro*/
	}
	while( (letras = fgetc(abrir) )!=EOF)/*a variável armazenará um caracter do arquivo, apresentará e repetirá isso até que seja o fim do arquivo*/
		putchar(letras);//apresentando o caracter
	printf("\n");
	fclose(abrir);//fechando o arquivo que foi aberto
	abrir == NULL;
	return 0;
}
	