#ifndef CONECTORES_LOGICOS_H
#define CONECTORES_LOGICOS_H

#include <stdbool.h>

bool negacion(bool p);
bool conjuncion(bool p, bool q);
bool disyuncion(bool p, bool q);
bool implicacion(bool p, bool q);
bool bicondicional(bool p, bool q);

void tabla_verdad_binaria(const char* nombre, bool (*op)(bool, bool));

#endif
