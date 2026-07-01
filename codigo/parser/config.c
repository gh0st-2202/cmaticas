/**
 * @file config.c
 * @brief Lectura de configuración del lenguaje desde un archivo JSON.
 *
 * Este módulo se encarga de abrir el archivo `lenguaje.json`, parsearlo
 * con cJSON y cargar todos los datos en una estructura `Lenguaje`
 * que el parser utilizará para reconocer símbolos y operadores.
 */

#include "config.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------
   Funciones auxiliares (estáticas)
   ------------------------------------------------------------ */

/**
 * @brief Lee un archivo completo y devuelve su contenido como cadena.
 * @param ruta Ruta del archivo a leer.
 * @return char* Contenido del archivo (debe liberarse con free()),
 *         o NULL si falla.
 */
static char* leer_archivo(const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) return NULL;

    fseek(archivo, 0, SEEK_END);
    long tamaño = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char *texto = malloc(tamaño + 1);
    fread(texto, 1, tamaño, archivo);
    texto[tamaño] = '\0';
    fclose(archivo);

    return texto;
}

/**
 * @brief Parsea una cadena JSON y devuelve su raíz.
 * @param texto Cadena con el JSON.
 * @return cJSON* Raíz del árbol JSON, o NULL si falla.
 */
static cJSON* parsear_json(const char *texto) {
    return cJSON_Parse(texto);
}

/**
 * @brief Carga las variables desde el JSON a la estructura Lenguaje.
 * @param raiz Raíz del árbol JSON.
 * @param config Estructura donde se almacenarán los datos.
 */
static void cargar_variables(cJSON *raiz, Lenguaje *config) {
    cJSON *vars = cJSON_GetObjectItem(raiz, "variables");
    config->prefijo_var = strdup(cJSON_GetObjectItem(vars, "prefijo")->valuestring);
    config->num_vars = cJSON_GetObjectItem(vars, "cantidad")->valueint;
}

/**
 * @brief Carga las constantes desde el JSON a la estructura Lenguaje.
 * @param raiz Raíz del árbol JSON.
 * @param config Estructura donde se almacenarán los datos.
 */
static void cargar_constantes(cJSON *raiz, Lenguaje *config) {
    cJSON *consts = cJSON_GetObjectItem(raiz, "constantes");
    config->prefijo_const = strdup(cJSON_GetObjectItem(consts, "prefijo")->valuestring);
    config->num_consts = cJSON_GetObjectItem(consts, "cantidad")->valueint;
}

/**
 * @brief Carga los relatores desde el JSON a la estructura Lenguaje.
 * @param raiz Raíz del árbol JSON.
 * @param config Estructura donde se almacenarán los datos.
 */
static void cargar_relatores(cJSON *raiz, Lenguaje *config) {
    cJSON *lista = cJSON_GetObjectItem(raiz, "relatores");
    int cantidad = cJSON_GetArraySize(lista);
    config->num_relatores = cantidad;
    config->relatores = malloc(cantidad * sizeof(*config->relatores));

    for (int i = 0; i < cantidad; i++) {
        cJSON *actual = cJSON_GetArrayItem(lista, i);
        config->relatores[i].nombre = strdup(cJSON_GetObjectItem(actual, "nombre")->valuestring);
        config->relatores[i].rango = cJSON_GetObjectItem(actual, "rango")->valueint;
    }
}

/**
 * @brief Carga los funtores desde el JSON a la estructura Lenguaje.
 * @param raiz Raíz del árbol JSON.
 * @param config Estructura donde se almacenarán los datos.
 */
static void cargar_funtores(cJSON *raiz, Lenguaje *config) {
    cJSON *lista = cJSON_GetObjectItem(raiz, "funtores");
    int cantidad = cJSON_GetArraySize(lista);
    config->num_funtores = cantidad;
    config->funtores = malloc(cantidad * sizeof(*config->funtores));

    for (int i = 0; i < cantidad; i++) {
        cJSON *actual = cJSON_GetArrayItem(lista, i);
        config->funtores[i].nombre = strdup(cJSON_GetObjectItem(actual, "nombre")->valuestring);
        config->funtores[i].rango = cJSON_GetObjectItem(actual, "rango")->valueint;
    }
}

/**
 * @brief Carga todos los signos lógicos desde el JSON.
 * @param raiz Raíz del árbol JSON.
 * @param config Estructura donde se almacenarán los datos.
 */
static void cargar_signos(cJSON *raiz, Lenguaje *config) {
    config->negador = strdup(cJSON_GetObjectItem(raiz, "negador")->valuestring);
    config->implicador = strdup(cJSON_GetObjectItem(raiz, "implicador")->valuestring);
    config->conjuntor = strdup(cJSON_GetObjectItem(raiz, "conjuntor")->valuestring);
    config->disyuntor = strdup(cJSON_GetObjectItem(raiz, "disyuntor")->valuestring);
    config->bicondicional = strdup(cJSON_GetObjectItem(raiz, "bicondicional")->valuestring);
    config->cuantificador = strdup(cJSON_GetObjectItem(raiz, "cuantificador_universal")->valuestring);
    config->cuantificador_existencial = strdup(cJSON_GetObjectItem(raiz, "cuantificador_existencial")->valuestring);
    config->descriptor = strdup(cJSON_GetObjectItem(raiz, "descriptor")->valuestring);
}

/* ------------------------------------------------------------
   Función principal (pública)
   ------------------------------------------------------------ */

/**
 * @brief Lee el archivo de configuración y devuelve una estructura Lenguaje.
 *
 * Este es el punto de entrada del módulo. Abre el archivo JSON,
 * lo parsea, y carga todos los datos en una estructura que el parser
 * utilizará para reconocer el lenguaje.
 *
 * @param ruta Ruta del archivo JSON (ej. "codigo/config/lenguaje.json").
 * @return Lenguaje* Estructura con la configuración cargada.
 *         Debe liberarse con liberar_config().
 *         Devuelve NULL si falla la apertura o el parseo.
 */
Lenguaje* leer_config(const char *ruta) {
    /* Leer el contenido del archivo */
    char *texto = leer_archivo(ruta);
    if (!texto) return NULL;

    /* Parsear el JSON */
    cJSON *raiz = parsear_json(texto);
    free(texto);
    if (!raiz) return NULL;

    /* Crear la estructura principal */
    Lenguaje *config = malloc(sizeof(Lenguaje));
    memset(config, 0, sizeof(Lenguaje));

    /* Cargar el nombre del lenguaje */
    cJSON *item = cJSON_GetObjectItem(raiz, "nombre");
    config->nombre = strdup(item->valuestring);

    /* Cargar cada sección del JSON */
    cargar_variables(raiz, config);
    cargar_constantes(raiz, config);
    cargar_relatores(raiz, config);
    cargar_funtores(raiz, config);
    cargar_signos(raiz, config);

    /* Limpiar el árbol JSON (ya no lo necesitamos) */
    cJSON_Delete(raiz);

    return config;
}

/* ------------------------------------------------------------
   Liberación de memoria
   ------------------------------------------------------------ */

/**
 * @brief Libera toda la memoria asociada a una estructura Lenguaje.
 * @param config Estructura a liberar. Si es NULL, no hace nada.
 */
void liberar_config(Lenguaje *config) {
    if (!config) return;

    /* Strings simples */
    free(config->nombre);
    free(config->prefijo_var);
    free(config->prefijo_const);

    /* Relatores */
    for (int i = 0; i < config->num_relatores; i++)
        free(config->relatores[i].nombre);
    free(config->relatores);

    /* Funtores */
    for (int i = 0; i < config->num_funtores; i++)
        free(config->funtores[i].nombre);
    free(config->funtores);

    /* Signos lógicos */
    free(config->negador);
    free(config->implicador);
    free(config->conjuntor);
    free(config->disyuntor);
    free(config->bicondicional);
    free(config->cuantificador);
    free(config->cuantificador_existencial);
    free(config->descriptor);

    /* Finalmente, la estructura principal */
    free(config);
}
