/**
 * @file parser.h
 * @brief Analizador sintáctico para fórmulas en notación prefija.
 *
 * Este módulo proporciona la función principal `parsear()` que recibe una
 * cadena de texto y, usando la configuración del lenguaje cargada en `config.h`,
 * construye un árbol sintáctico (estructura `Nodo`) que representa la fórmula.
 *
 * El parseo es recursivo descendente y sigue las reglas de formación de
 * términos y fórmulas de la lógica de primer orden (Capítulo 1 de Ivorra).
 */

#ifndef PARSER_H
#define PARSER_H

#include "config.h"
#include "arbol.h"

/**
 * @brief Inicializa el parser con la configuración del lenguaje.
 * @param L Estructura con la configuración (leída de lenguaje.conf).
 *
 * Debe llamarse antes de cualquier llamada a `parsear()`.
 */
void inicializar_parser(Lenguaje *L);

/**
 * @brief Analiza una cadena de texto y devuelve el árbol sintáctico.
 * @param cadena Fórmula en notación prefija (ej: "∀x0 → = x0 c1 R x0").
 * @return Nodo* Raíz del árbol, o NULL si la fórmula es inválida.
 *
 * La cadena debe contener únicamente los símbolos definidos en la configuración
 * y seguir la gramática de la lógica de primer orden.
 * El árbol devuelto debe ser liberado con `liberar_nodo()`.
 */
Nodo* parsear(const char *cadena);

#endif
