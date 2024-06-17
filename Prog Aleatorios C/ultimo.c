/* Este programa recebe um nome de arquivo e um número de alunos que deve ser cadastrado,
faz o cadastro e imprime essas informações em um arquivo
Arthur Resende Santos 12011BCC020*/

#include <stdio.h>
#include <stdlib.h>

struct cadastro{
	int matricula;
	char nome[30];
	float notaFinal;
};

typedef struct cadastro cadastro;


struct cadastro 
leitura(struct cadastro A){
	printf("Digite o número de matrícula do aluno:\n");
	scanf("%d", &A.matricula);
	printf("Agora, o nome:\n");
	scanf("%s", A.nome);
	printf("Por fim, a nota:\n");
	scanf("%f", &A.notaFinal);
	return A;
}

void
gravacao(struct cadastro A, FILE *abrir){
	fprintf(abrir, "%d\n", A.matricula);
	fprintf(abrir, "%s\n", A.nome);
	fprintf(abrir, "%f\n", A.notaFinal);
	fprintf(abrir, "\n");
}

int 
main(int argc, char *argv[])
{
	if (argc == 3){
		FILE *abrir = NULL;
		int cont;
		int num = 0;
		num = atoi(argv[1]);
		struct cadastro cadastro[num];
		struct cadastro cadastroo[num];
		for(cont = 0;cont < num; cont++){
			cadastroo[cont] = leitura(cadastro[cont]);
		}
		
		abrir = fopen(argv[2],"a");
		if (abrir == NULL){ //caso haja falha ao abrir o arquivo
			fprintf(stderr, "Falha ao abrir o arquivo");
			exit(1);
			return 0;
		}
		for(cont = 0;cont < num; cont++){
			gravacao(cadastroo[cont], abrir);
		}
		fclose(abrir);
		abrir == NULL;
		return 0;
	}
    else
		printf("Número de parâmetros inválido.");
}