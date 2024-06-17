/*Este programa cria e coleta dados para uma struct aluno de N posicoes desejadas pelo usuario,
 * ordena os alunos pela nota media e os apresenta
 * Criado por Arthur Resende Santos 12011BCC020*/

#include <stdio.h>
#include <stdlib.h>

struct aluno{
    char nome[30];
    double media;
    int faltas;
};
typedef struct aluno aluno;

//essa funcao aloca dinamicamente um vetor struct e o preenche com dados do stdin
aluno *aloc_coleta(int alunos){
    int i;
    aluno *vetor = (aluno *) malloc(alunos*sizeof(aluno));
    if(vetor == NULL){
        fprintf(stderr, "Falha ao alocar\n");
        exit(1);
    }
    for(i = 0; i < alunos; i++){
        printf("Digite o nome do aluno:\n");
        //fgets(vetor[i] -> nome, 29, stdin);
        scanf("%s", vetor[i].nome);
        printf("Digite a media:\n");
        scanf("%lf", &vetor[i].media);
        while(&vetor[i].media < 0){
            printf("A media deve ser maior ou igual a zero.\nDigite novamente a media:\n");
            scanf("%lf", &vetor[i].media);
        }
        printf("Digite numero de faltas:\n");
        scanf("%d", &vetor[i].faltas);
        while(&vetor[i].faltas < 0){
            printf("O número de faltas deve ser maior ou igual a zero.\nDigite novamente o número de faltas:\n");
            scanf("%d", &vetor[i].faltas);
        }
    }
    return vetor;
}

//essa funcao realiza o ordenamento selection sort decrescente
void selection_sort(aluno *vetor, int alunos){
    int i, j;
    aluno intermedio;
    for(i = 0;i < alunos; i++){
        for(j = i+1;j < alunos; j++){
            if((vetor[i].media) <= (vetor[j].media)){
                intermedio = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = intermedio;
            }
        }
    }
}

//essa funcao imprime os dados ordenados do vetor na tela
void impressao_de_dados(aluno *vetor, int alunos){
    int i;
    printf("\nEm ordem decrescente pela media, esses sao os alunos cadastrados:\n");
    for(i=0;i < alunos;i++) {
        printf("\nAluno:%s\nMedia:", vetor[i].nome);
        printf("%lf\nFaltas:", vetor[i].media);
        printf("%d\n", vetor[i].faltas);
    }
}

int main(){
    aluno *vetor;
    int alunos = 0;
    printf("Quantos alunos ha na turma?\n");
    scanf("%d", &alunos);
    if(alunos <= 0) {
        printf("O número de alunos deve ser maior que zero!\n");
        return 0;
    }
    vetor = aloc_coleta(alunos);
    selection_sort(vetor, alunos);
    impressao_de_dados(vetor, alunos);
    free(vetor);
    vetor = NULL;
    return 0;
}