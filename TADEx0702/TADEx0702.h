typedef struct deque* Deque;

Deque cria_deque();

int insere_fim(Deque p, int A);

int insere_ini(Deque p, int A);

int remove_ini(Deque p, int *f);

int remove_fim(Deque p, int *f);

int deque_vazio(Deque p);

int deque_cheio(Deque p);

void apaga_deque (Deque *p);

int esvazia_deque(Deque p);

