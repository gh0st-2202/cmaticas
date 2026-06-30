#include <stdio.h>
#include "core/cuantificadores.h"
#include "core/descriptor.h"

// Predicados de ejemplo
bool es_par(int x) { return x % 2 == 0; }
bool es_impar(int x) { return x % 2 != 0; }
bool es_divisor_de_12(int x) { return x != 1 && 12 % x == 0; }

int main() {
    // --- Prueba 1: Conjunto con un único par ---
    int numeros1[] = {1, 3, 5, 7, 8};   // Solo el 8 es par
    Conjunto c1 = {numeros1, 5};
    bool ok1;
    int unico = descriptor(&c1, es_par, &ok1);
    if (ok1) {
        printf("El único par es: %d\n", unico);
    } else {
        printf("No hay un único par (descripción impropia).\n");
    }

    // --- Prueba 2: Conjunto con varios pares ---
    int numeros2[] = {2, 4, 6, 8, 10};
    Conjunto c2 = {numeros2, 5};
    bool ok2;
    unico = descriptor(&c2, es_par, &ok2);
    if (ok2) {
        printf("El único par es: %d\n", unico);
    } else {
        printf("No hay un único par (descripción impropia).\n");
    }

    // --- Prueba 3: Conjunto con divisores de 12 (varios) ---
    int numeros3[] = {2, 3, 4, 6, 12};
    Conjunto c3 = {numeros3, 5};
    bool ok3;
    unico = descriptor(&c3, es_divisor_de_12, &ok3);
    if (ok3) {
        printf("El único divisor de 12 distinto de 1 es: %d\n", unico);
    } else {
        printf("No hay un único divisor (descripción impropia).\n");
    }

    // --- Prueba 4: Conjunto con un solo divisor (primo) ---
    int numeros4[] = {1, 7, 14, 21};   // Divisores de 7: solo 7
    Conjunto c4 = {numeros4, 4};
    bool ok4;
    unico = descriptor(&c4, es_divisor_de_12, &ok4);   // 7 no es divisor de 12
    if (ok4) {
        printf("El único divisor de 12 es: %d\n", unico);
    } else {
        printf("No hay un único divisor (descripción impropia).\n");
    }

    return 0;
}
