#ifndef CUANTIFICADORES_H
#define CUANTIFICADORES_H

#include <stdbool.h>

// Representación de un conjunto finito de enteros
typedef struct {
    int* elementos;   // Array de enteros
    int size;         // Número de elementos
} Conjunto;

// ∃: Devuelve true si existe algún elemento que cumpla el predicado
bool existe(const Conjunto* c, bool (*pred)(int));

// ∀: Devuelve true si todos los elementos cumplen el predicado
bool para_todo(const Conjunto* c, bool (*pred)(int));

#endif
