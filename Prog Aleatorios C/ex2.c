/*  Este programa cria cadastro para produtos(bebidas), com nome, volume e preco
	e mostra os dados cadastrados.
	Criado por Arthur Resende Santos 12011BCC020*/

#include <stdio.h>
#include <stdlib.h>

struct cadastro{
    char nome[20];
    int volume;
    float preco; };
typedef struct cadastro cadastro;

int size = 0;
cadastro *cadastro1[20];

void resetar_registros(){
    for(int cont=0; cont < 20; cont++)
    {
        cadastro1[cont]=NULL;
    }
}

void consulta_coleta(){ //solicita dados para preencher as etapas
	
    if(size < 20){
		cadastro1[size] = malloc(sizeof(cadastro));
        printf("Registre os produtos seguindo as perguntas:\n");
        printf("Qual o nome?\n");
        scanf("%s", cadastro1[size]->nome);
        printf("Volume em ml?\n");
        scanf("%d", &cadastro1[size]->volume);
        printf("Qual o preco?\n");
        scanf("%f", &cadastro1[size]->preco);
        size = size + 1;
    }
	else
		printf("Voce ja registrou o maximo de produtos desejados ou possiveis:\n");

}

void tornar_null(){ //esvazia o dado utilizado
    if(size > 0){
        size--;
        free(cadastro1[size]);
        cadastro1[size] = NULL;
    }
}

void mostra_dados(){ //imprime os dados cadastrados na tela
	int cont;
    for(cont=0; cont < size; cont++){
        printf("\nProduto de numero %d:\n", cont+1);
        printf("\nNome:");
        printf("%s\n", cadastro1[cont]->nome);
        printf("\nVolume:");
        printf("%d\n", cadastro1[cont]->volume);
        printf("\nPreco:");
        printf("%f\n", cadastro1[cont]->preco);
   }
}


int main(){ //realiza chamada das funcoes e comunicacao base com o usuario
	char num;
	int num1 = 0;
	resetar_registros();
	do{ // escolha dos processos do programa
	
		printf("Escreva '1' registrar produtos, '2' para apagar registros anteriores, '3' para impressao de dados e '4' para finalizar o programa\n");
		scanf(" %c", &num);
		if(num == '1' || num == '2' || num == '3' || num == '4'){
			if(num == '1'){
				consulta_coleta();
			}
			if(num == '2'){
				tornar_null();
			}
			if(num == '3'){
				mostra_dados();
			}
			if(num == '4'){
				return 0;
			}
		}
		else
			printf("Esta opcao nao existe, o programa sera encerrado.\n");
	}while(num == '1' || num == '2' || num == '3');
	return 0;
}
