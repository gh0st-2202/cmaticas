#include "arbol.h"
#include <stdlib.h>
#include <string.h>

Nodo* crear_nodo(TipoNodo tipo, const char *nombre, int aridad) {
    Nodo *n = malloc(sizeof(Nodo));
    n->tipo = tipo;
    n->nombre = nombre ? strdup(nombre) : NULL;
    n->aridad = aridad;
    n->args = aridad > 0 ? calloc(aridad, sizeof(Nodo*)) : NULL;
    return n;
}

void liberar_nodo(Nodo *n) {
    if (!n) return;
    free(n->nombre);
    for (int i = 0; i < n->aridad; i++) {
        liberar_nodo(n->args[i]);
    }
    free(n->args);
    free(n);
}
