#ifndef ARBOL_H
#define ARBOL_H

#include <stdbool.h>

typedef enum {
    NODO_VARIABLE,
    NODO_CONSTANTE,
    NODO_RELATOR,
    NODO_FUNTOR,
    NODO_NEGADOR,
    NODO_IMPLICADOR,
    NODO_CONJUNCION,
    NODO_DISYUNCION,
    NODO_BICONDICIONAL,
    NODO_CUANTIFICADOR,
    NODO_DESCRIPTOR
} TipoNodo;

typedef struct Nodo {
    TipoNodo tipo;
    char *nombre;
    struct Nodo **args;
    int aridad;
} Nodo;

Nodo* crear_nodo(TipoNodo tipo, const char *nombre, int aridad);
void liberar_nodo(Nodo *n);

#endif
