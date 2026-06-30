#include "descriptor.h"
#include <stddef.h>

/*
 * Busca manualmente si hay mas de un elemento
 * en un conjunto que sea capaz de cumplir la
 * condición...
 * 
 * En caso de que no haya un elemento (ya sea por
 * que no hay o porque hay varios) se considera
 * como una descripcion impropia
 */
int descriptor(const Conjunto* c, bool (*pred)(int), bool* ok) {
    int encontrado = 0;
    int valor = DESCRIPCION_IMPROPIA;

    // Recorremos el conjunto
    for (int i = 0; i < c->size; i++) {
        if (pred(c->elementos[i])) {
            encontrado++;
            valor = c->elementos[i];
            // Si ya encontramos más de uno, podemos salir temprano
            if (encontrado > 1) {
                break;
            }
        }
    }

    // Decidimos si es propia o impropia
    if (encontrado == 1) {
        if (ok != NULL) *ok = true;
        return valor;
    } else {
        if (ok != NULL) *ok = false;
        return DESCRIPCION_IMPROPIA;
    }
}
