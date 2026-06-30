#include "funtores.h"

int funtor_suma(int a, int b) {
    return a + b;
}

int funtor_resta(int a, int b) {
    return a - b;
}

int funtor_multiplicacion(int a, int b) {
    return a * b;
}

int funtor_division(int a, int b) {
    if (b == 0) {
        return 0;   // Por ahora devolvemos 0
    }
    return a / b;
}

int funtor_doble(int x) {
    return 2 * x;
}

int funtor_cuadrado(int x) {
    return x * x;
}

int funtor_absoluto(int x) {
    return (x < 0) ? -x : x;
}
