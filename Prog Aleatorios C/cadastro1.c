/*  Este programa cadastra e consulta informações de funcionários de uma empresa,
além de apresentá-las na tela
	Criado por Arthur Resende Santos*/
#include <stdio.h>

struct cadastro{
	int matricula;
	char nome[50];
	int idade;
	char cargo[20];
	float salario;
};
typedef struct cadastro cadastro;
struct cadastro cadastro[10];

int NovoCadastro(struct cadastro A, int B){
	if (B = 1)
		exit(1);
	else{
		char letra[5];
		int cont;
		for(cont = 0; cont == 0;cont++){
			printf("Digite o número de matrícula do funcionário:");
			scanf("%d", A->matricula);
			printf("Agora, o nome:");
			scanf("%s", A->nome);
			printf("A idade:");
			scanf("%d", A->idade);
			printf("Digite o cargo:");
			scanf("%s", A->cargo);
			printf("Por fim, o salário:");
			scanf("%f", A->salario);
			printf("Digite 's' para continuar o cadastramento ou 'ZERO' para finalizar");
			scanf("%s", letra);
			if(letra == "zero"||"ZERO")
					cont = 1;
			for(letra != "s"||"S"||"zero"||"ZERO"){
				printf("A letra digitada é inválida. Por favor, digite 's' caso deseje continuar cadastrando ou 'ZERO' caso contrário.\n");
				scanf("%s", letra);
			}
			return cont;
	}
void consulta(struct cadastro A, *p){
	int cont;
	do
		scanf("%s", funcionario);
		if(funcionário == "FIM")
			break;
		for(cont = 0; cont < 10; cont++){
			if(A[cont]->nome == funcionario)
				printf("Essas são as informações deste funcionário:\nMatrícula: %d\nIdade: %d\nCargo: %s\nSalário: R$%f,00");
			else
				printf("Nome inserido inválido ou não há este funcionário na empresa");
			printf("Para consultar informações sobre algum funcionário, digite o nome. Caso contrário, digite'FIM'.");
		}
	while(funcionário != "FIM")
	}
		
}

int main(){
	int cont = 0;
	char funcionario[50];
	char* p;
	p = funcionario;
	int B = 0;
	for(cont = 0;cont < num; cont++)
		gravacao(cadastro[cont], B);
	B = 1;
	gravacao(cadastro[cont], B);
	consulta(cadastro[0]);
	return 0;		
}

		
			
			
			
			
			
		
		
	