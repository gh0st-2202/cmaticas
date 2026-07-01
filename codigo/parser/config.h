/**
 * @file config.h
 * @brief Configuración del lenguaje formal para el parser de cmaticas.
 * 
 * Este archivo define la estructura Lenguaje y las funciones para
 * cargar y liberar la configuración desde un archivo JSON.
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Estructura que almacena toda la configuración de un lenguaje formal.
 * 
 * Contiene la definición de variables, constantes, relatores, funtores,
 * y los signos lógicos que utiliza el parser.
 */
typedef struct {
    char *nombre;               /**< Nombre del lenguaje */
    char *prefijo_var;          /**< Prefijo de las variables (ej: "x") */
    int num_vars;               /**< Número de variables disponibles */
    char *prefijo_const;        /**< Prefijo de las constantes (ej: "c") */
    int num_consts;             /**< Número de constantes disponibles */
    
    struct {
        char *nombre;           /**< Nombre del relator (ej: "=", "R") */
        int rango;              /**< Número de argumentos del relator */
    } *relatores;               /**< Array de relatores */
    int num_relatores;          /**< Número de relatores */
    
    struct {
        char *nombre;           /**< Nombre del funtor (ej: "f", "g") */
        int rango;              /**< Número de argumentos del funtor */
    } *funtores;                /**< Array de funtores */
    int num_funtores;           /**< Número de funtores */
    
    char *negador;              /**< Símbolo del negador (ej: "¬") */
    char *implicador;           /**< Símbolo del implicador (ej: "→") */
    char *conjuntor;            /**< Símbolo del conjuntor (ej: "∧") */
    char *disyuntor;            /**< Símbolo del disyuntor (ej: "∨") */
    char *bicondicional;        /**< Símbolo del bicondicional (ej: "↔") */
    char *cuantificador;        /**< Símbolo del cuantificador universal (ej: "∀") */
    char *cuantificador_existencial; /**< Símbolo del cuantificador existencial (ej: "∃") */
    char *descriptor;           /**< Símbolo del descriptor (ej: "|") */
} Lenguaje;

/**
 * @brief Lee la configuración desde un archivo JSON.
 * @param ruta Ruta al archivo JSON.
 * @return Puntero a la estructura Lenguaje cargada, o NULL si hay error.
 */
Lenguaje* leer_config(const char *ruta);

/**
 * @brief Libera la memoria utilizada por una estructura Lenguaje.
 * @param L Puntero a la estructura que se desea liberar.
 */
void liberar_config(Lenguaje *L);

#endif
