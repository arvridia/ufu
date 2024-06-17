struct bebidas
{
    char Nome[20];
    int Volume;
    float Preco;
};
typedef struct bebidas bebidas;

struct lista
{
    bebidas *p;
    int fim;
};
typedef struct lista lista;

lista ordena_lista(lista lista1);
lista criar_lista();
void registro_bebidas();
int lista_vazia(lista lista1);
int lista_cheia(lista lista1);
bebidas get_pos(lista lista1, int pos);
lista insere_elem(lista lista1, bebidas elem);
lista remove_elem(lista lista1, char elem[20]);
void imprimir_lista(lista lista1);
lista limpa_lista(lista lista1);


