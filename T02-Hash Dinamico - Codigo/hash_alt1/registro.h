#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#define TEXT_SIZE 85
#define MATRICULA_SIZE 11
#define ENTRY_MAX 1024

struct registro {
	unsigned int nseq;
	char text[TEXT_SIZE];
	char matricula[MATRICULA_SIZE];
};

typedef struct registro *Registro;

#endif // REGISTRO_H_INCLUDED

