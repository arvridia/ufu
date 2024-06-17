typedef struct deque *Deque;

Deque cria_deque();
int deque_vazio(Deque D);
int deque_cheio(Deque D);
int insere_fim(Deque D, int num);
int insere_ini(Deque D, int num);
int remove_ini(Deque D, int *num);
int remove_fim(Deque D, int *num);
int libera_deque(Deque D);
int esvazia_deque(Deque D);


