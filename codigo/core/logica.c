/*
 * Una vez entendidas los conectores lógicos, 
 * mi siguiente paso es pasarlos a código en C.
 *
 * Mi objetivo es poder crear una base sólida combinando
 * matemáticas y C para tener una visión del conjunto
 * más clara y sólida.
 */

#include "logica.h"
#include <stdio.h>

// Invierte el valor de verdad
bool negacion(bool p) {
    return !p;
}

// Solo se cumple si ambas son verdaderas
bool conjuncion(bool p, bool q) {
    return p && q;
}

// Se cumple siempre que una o ambas sean verdaderas
bool disyuncion(bool p, bool q) {
    return p || q;
}

/* Se incumple unicamente si:
 * 1. El "contrato" (p) es verdadero
 * 2. La "consecuencia" (q) es falsa
 *
 * Como podemos ver, se pueden crear combinando
 * dos de los conectores ya vistos
 */
bool implicacion(bool p, bool q) {
    return disyuncion(negacion(p), q);
}

// Se cumple solo si ambas son iguales
bool bicondicional(bool p, bool q) {
    return p == q;
}

// Solo para ver las tablas de verdad (comprobador)
void tabla_verdad_binaria(const char* nombre, bool (*op)(bool, bool)) {
    printf("Tabla de verdad: %s\n", nombre);
    printf("p\tq\tres\n");
    for (int p = 0; p <= 1; p++) {
        for (int q = 0; q <= 1; q++) {
            printf("%d\t%d\t%d\n", p, q, op(p, q));
        }
    }
}
