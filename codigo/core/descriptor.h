#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <stdbool.h>
#include "cuantificadores.h"

// Valor que devolvemos cuando la descripción es impropia
#define DESCRIPCION_IMPROPIA 0

int descriptor(const Conjunto* c, bool (*pred)(int), bool* ok);

#endif
