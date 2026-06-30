#include "logica.h" 
#include "cuantificadores.h"

/*
 * Para un conjunto c (array) se establece que
 * al menos 1 cumpla la condición (pred) que
 * es establecida previamente como una función.
 *
 * Un ejemplo de pred puede ser comprobar que el
 * resto de una división sea 0 (encontrar divisor).
 * En ese caso, devolvería verdadero, si no, falso
 */
bool existe(const Conjunto* c, bool (*pred)(int)) {
    for (int i = 0; i < c->size; i++) {
        if (pred(c->elementos[i])) {
            return true;
        }
    }
    return false;
}

/*
 * Para un conjunto c (array) se establece que
 * si alguno de los elementos NO CUMPLE la
 * función (pred), diga que no se cumple para
 * todos los elementos del conjunto.
 *
 * Un ejemplo de pred puede ser comprobar que
 * el resto de una división NO sea 0.
 * En el caso de encontrar 0, pred sería falso
 * su negación verdadera y por lo tanto, tendriamos
 * un caso que no se cumple, haciendo que ese
 * "para_todo" sea falso
 */
bool para_todo(const Conjunto* c, bool (*pred)(int)) {
    for (int i = 0; i < c->size; i++) {
        if (negacion(pred(c->elementos[i]))) {
            return false;
        }
    }
    return true;
}
