/*  Este programa copia o que o usuário digitar e insere este conteúdo em um arquivo pré-existente,
	escolhido pelo usuário, sobrescrevendo o conteúdo contido nele ou,caso o usuário digite o nome 
	de um arquivo que não exista, o programa criará um e colocará o que foi inserido dentro dele.
	Criado por Arthur Resende Santos, 12011BCC020, em 2020. */

#include <stdio.h>
#include <string.h>
#define MAX 100
#define MAX1 100

int 
main()
{
	FILE *abrir = NULL; /*declaração da variável usada para abertura do arquivo*/
	char arquivo[MAX]; /*array para armazenar o nome do arquivo de escolha do usuário*/
	char digitado[MAX1];/*armazenamento do conteúdo que o usuário quer inserir no arquivo*/
	int i;/*para determinar as posições do array*/
	int x = 0;/*para armazenar o tamanho do array, que será necessário para um controle de laço*/
	printf("Digite o nome do arquivo que você quer adicionar o conteúdo que digitará:\n");
	scanf("%s", arquivo);/*armazenamento do nome do arquivo*/
	while ( getchar() != '\n' )/*para retirar o '\n' "que sobrou", para evitar problemas na próxima captura*/
	;
	abrir = fopen(arquivo, "w");/*abrindo o arquivo*/
	if (abrir == NULL)/*caso a abertura apresente erro*/
	{
		fprintf(stderr, "Erro ao abrir o arquivo %s\n", arquivo);
		return 5; /*programa finalizará após a mensagem de erro*/
	}
	printf("Escreva o que quer que seja transferido para o arquivo '%s'\n", arquivo);
	scanf("%[^\n]", digitado);/*armazenamento do conteúdo que o usuário quer transferir para o arquivo*/
	x = strlen(digitado);/*armazenamento do tamanho do array, usado para o controle do laço a seguir*/
	for(i = 0; i < x; i++)/*laço para inserir o conteúdo digitado para o arquivo*/
		fputc(digitado[i], abrir);/*inserindo o caracter dentro do arquivo*/
	printf("O conteúdo foi adicionado com sucesso!\n");
	fclose(abrir);//fechando o arquivo que foi aberto
	abrir == NULL;
	return 0;
}