#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "registro.h"
#include "lista.h"

// list of offsets
struct indice {
	char key[11];//matricula
	int *rid;
};

typedef struct indice* Indice;

#endif // INDICE_H_INCLUDED

