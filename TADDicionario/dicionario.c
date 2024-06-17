#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dicionario.h"
#include <ctype.h> // letra -> igualar a

/*

*/
////////////////////////////////////////////////////////////////////////
struct vocabulo
{
    char palavra[40];
    char classe_gramatical[10];
    char definicao[100];
};

struct no{
    VOCAB A;
    struct no *prox; // LISTA
};



struct NO{
    VOCAB info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

lista Cria_lista()
{
    lista cab;
    cab = (lista) malloc (sizeof(struct no));
    if(cab != NULL){
        cab->prox = NULL;//o no aponta pra null
    }
    return cab;//retorna null se falhar
}

int Apaga_lista(lista *lista1)
{
    free(*lista1);
    (*lista1) = NULL;
    return 1;
}

int insere_ord(lista lista1, char palavra[40], char classe_gramatical[10], char definicao[100]) //////
{
    lista N = (lista)malloc(sizeof(struct no));
    if (N == NULL)
    {
        return 0;//faz papel da funcao lista_cheia
    }

    palavra = Str_tolower(palavra);
    VOCAB B;

    strcpy(B.palavra,palavra);
    strcpy(B.classe_gramatical,classe_gramatical);
    strcpy(B.definicao,definicao);

    N->A = B;
    lista aux = lista1;
    while(aux->prox != NULL && strcmp(palavra, aux->prox->A.palavra) < 0)
        aux = aux->prox;

    N->prox = aux->prox;
    aux->prox = N;
    return 1;
}

int remover(lista lista1, char palavra[40]) /////
{
    if(lista_vazia(lista1)== 1)
        return 0;//FALHA
    lista aux = lista1;

    while(aux->prox != NULL && strcmp(palavra, aux->prox->A.palavra) < 0)
    {
        aux = aux->prox;
    }
    if(aux->prox == NULL || strcmp(palavra, aux->prox->A.palavra) > 0)
        return 0;//FALHA

    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    return 1;
}


//////////////////////////////////////////////////////////////

void Gerar_Relatorio(ArvAVL arvore)
{
    ArvAVL nos[1000000];
    int ocorrencias[26];
    int nos_a_olhar = 1;

    nos[0] = arvore;

    for(int i=0;i<26;i++)
        ocorrencias[i] = 0;

    while(nos_a_olhar > 0)
    {
        nos_a_olhar--;
        no_atual = nos[nos_a_olhar];

        if(no_atual->esq != NULL)
            nos[nos_a_olhar++] = no_atual->esq;

        if(no_atual->dir != NULL)
            nos[nos_a_olhar++] = no_atual->dir;

        ocorrencias[no_atual->info.palavra[0] - 'a']++;
    }

    printf("Relatorio sobre o Dicionario:\n");
    for(int i=0;i<26;i++)
    {
        print("Ocorrencias de palavras comecadas com %c : %d.\n",(char) (i + 'a'),ocorrencias[i]); // TABELA ASCCI 97
    }
    printf("\n");
}


void Comparar_Tempos(lista l, ArvAVL A, char palavra[])
{
    palavra = Str_tolower(palavra);

    clock_t begin = clock();

    lista aux = l;
    while(strcmp(aux->A,palavra) != 0)
    {
        aux =  aux->prox;
        if(aux == NULL)
            break;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(" %.2lf , Tempo da busca na lista em ms.", time_spent*1000);

    begin = clock();

    consulta_ArvAVL(*A, palavra);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(" %.2lf , Tempo da busca na arvore AVL em ms.", time_spent*1000);
}

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc (sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

void Exibir_NO(VOCAB V)
{
    printf("\n Palavra: %s - classe_gramatical: %s - Definicao: %s \n",V.palavra, V.gramtical, V.definicao);
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        Exibir_NO;
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}



///////////////
char* Str_tolower(char s[])
{
    int = 0;
    while(s[i] != '\0')
    {
        s[i] = tolower(s[i]);
        i++;
    }
    return s;
}


VOCAB consulta_ArvAVL(ArvAVL *raiz, char palavra[]){
    if(raiz == NULL)
        return NULL;

    palavra = Str_tolower(palavra);
    struct NO* atual = *raiz;
    while(atual != NULL)
    {
        if(strcmp(palavra, atual->info.palavra) == 0){
            return atual->info;
        }
        if(strcmp(palavra, atual->info.palavra) > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}
// retorna a tripla

void Exibir_Ocorrencias_ArvAVL(ArvAVL *raiz, char frase[])
{
    if(raiz == NULL)
        return;

    if(strcmp((*raiz)->info.palavra,Str_tolower(frase)) == 0)
        Exibir_NO((*raiz)->info);

    else if(strstr(Str_tolower((*raiz)->info.definicao),Str_tolower(frase)) != NULL)
        Exibir_NO((*raiz)->info);

    Exibir_Ocorrencias_ArvAVL(&((*raiz)->esq));
    Exibir_Ocorrencias_ArvAVL(&((*raiz)->dir));
}




//=================================
int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void RotacaoDireita(ArvAVL *A){//LL
    printf("\nRotacao Direita");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoEsquerda(ArvAVL *A){//RR
    printf("\nRotacao Esquerda");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoDuplaDireita(ArvAVL *A){//LR
    printf("\nRotacao Dupla Direita");
    RotacaoEsquerda(&(*A)->esq);
    RotacaoDireita(A);
}

void RotacaoDuplaEsquerda(ArvAVL *A){//RL
    printf("\nRotacao Dupla Esquerda");
    RotacaoDireita(&(*A)->dir);
    RotacaoEsquerda(A);
}


int insere_ArvAVL(ArvAVL *raiz, char palavra[40], char classe_gramatical[10], char definicao[100])
{
    int r;
    palavra = Str_tolower(palavra)
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        VOCAB V;
        strcpy(V.palavra,palavra);
        strcpy(V.classe_gramatical, gramatical);
        strcpy(V. definicao,definicao);
        novo->info = V;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(strcmp(palavra, atual->info.palavra) < 0){
        r = insere_ArvAVL(&(atual->esq), palavra);
        if(r == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(strcmp(palavra,(*raiz)->esq->info.palavra) < 0){
                    RotacaoDireita(raiz);
                }else{
                    RotacaoDuplaDireita(raiz);
                }
            }
        }
    }else{
        if(strcmp(palavra, atual->info.palavra) > 0){
            r = insere_ArvAVL(&(atual->dir), palavra);
            if(r == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(strcmp(palavra,(*raiz)->dir->info.palavra) < 0){
                        RotacaoEsquerda(raiz);
                    }else{
                        RotacaoDuplaEsquerda(raiz);
                    }
                }
            }
        }else{
            printf("palavra duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return r;
}


int remove_ArvAVL(ArvAVL *raiz, char palavra[]){

    int r;
    palavra = Str_tolower(palavra);
	if(*raiz == NULL)
    {// palavra não existe
	    printf("palavra não encontrada!!\n");
	    return 0;
	}

	if(strcmp(palavra, atual->info.palavra) < 0){
      r = remove_ArvAVL(&(*raiz)->esq,palavra);
	    if(r == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoEsquerda(raiz);
                else
                    RotacaoDuplaEsquerda(raiz);
            }
	    }
	}

    if(strcmp(palavra, atual->info.palavra) > 0){
      r = remove_ArvAVL(&(*raiz)->dir, palavra);
	    if(r == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoDireita(raiz);
                else
                    RotacaoDuplaDireita(raiz);
            }
	    }
	}

	if(strcmp(palavra, atual->info.palavra) == 0){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			    struct NO *raizAntiga = (*raiz);
			    if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
          else
                *raiz = (*raiz)->dir;
			    free(raizAntiga);
	    }
      else {                                               // nó tem 2 filhos
			   struct NO* temp = procuraMenor((*raiz)->dir);
			   (*raiz)->info = temp->info;
			   remove_ArvAVL(&(*raiz)->dir, (*raiz)->info.palavra);
         if(fatorBalanceamento_NO(*raiz) >= 2){
  	         if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
				         RotacaoDireita(raiz);
	           else
				         RotacaoDuplaDireita(raiz);
	       }
	   }
	   if (*raiz != NULL)
        (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
	   return 1;
	 }

   (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
   return r;
}


//////////////////////////////////////////////////////////////////////////////
//Função para percorrer a arvore binária com critério pre-ordem
void preorder (ArvAVL a, FILE *arquivo)
{
    if (! EMPTY(a) )
    {
        fprintf(arquivo,"%s ",a->info.palavra);
        preorder(a->esq, arquivo);
        preorder(a->dir, arquivo);
    }
}

//Função para percorrer a arvore binária com critério em-ordem
void inorder (ArvAVL a, FILE *arquivo)
{
    if (! EMPTY(a) )
    {
        inorder(a->esq, arquivo);
        fflush(stdin);
        fprintf(arquivo,"%s ",a->info.palavra);
        inorder(a->dir, arquivo);
    }
}

//Função para percorrer a arvore binária com critério pós-ordem
void posorder (ArvAVL a, FILE *arquivo)
{
    if (! EMPTY(a) )
    {
        posorder(a->esq, arquivo);
        posorder(a->dir, arquivo);
        fprintf(arquivo,"%s ",a->info.palavra);
    }
}

