#ifndef ENTRENADOR_H_
#define ENTRENADOR_H_

#include <stdlib.h>
#include "lista.h"
#include "hash.h"
#include <stdio.h>

typedef struct _entrenador_t entrenador_t;
typedef struct _pokemon_t pokemon_t;

/*Crea un entrenador y lo carga en memoria.
*/
entrenador_t* crear_entrenador(entrenador_t* entrenador, char** str_dividido);

/*Crea un pokemon y lo carga en memoria.
*/
pokemon_t* crear_pokemon(pokemon_t* pokemon, char** str_dividido);

/* Funcion que se utiliza para comparar entrenadores. En la comparacion toma el nombre de cada entrenador.
* Si el primero es mayor devuelve 1, si es menor -1,
* si son iguales devuelve 0.
*/
int comparador_entrenadores(void* entrenador1, void* entrenador2);

/*Agrega un pokemon a el equipo del entrenador solicitado
*/
int agregar_pokemon(entrenador_t* entrenador,pokemon_t* pokemon);

/*Devuelve la cantidad de pokemones del equipo de un entrenador
*/
size_t cantidad_pokemones(entrenador_t* entrenador);

/*Libera los entrenadores
*/
void destructor_entrenadores(void* entrenador);

/*Imprime los entrenadores junto a su pokemones. 
*/
int imprimir_entrenadores(entrenador_t* entrenador, FILE* archivo);

/*Elimina un pokemon de un equipo
*/
int quitar_pokemon(void* entrenador, void* pokemon);

/*Devuelve la cantidad de victorias que tiene un entrenador 
*/
int obtener_victorias(entrenador_t* entrenador);

/*Devuelve el nombre de un entrenador
*/
char* obtener_nombre(entrenador_t* entrenador);

/*Verifica si cierto pokemon se encuentra en el equipo de un entrenador y si lo esta lo devuelve
*/
pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

/*Devuelve el nombre de un pokemon
*/
char* obtener_nombre_pokemon(pokemon_t* pokemon);

/*Devuelve el nivel de un pokemon
*/
int obtener_nivel_pokemon(pokemon_t* pokemon);

/*Devuelve la fuerza de un pokemon
*/
int obtener_fuerza_pokemon(pokemon_t* pokemon);

/*Devuelve la defensa de un pokemon
*/
int obtener_defensa_pokemon(pokemon_t* pokemon);

/*Devuelve la inteligencia de un pokemon
*/
int obtener_inteligencia_pokemon(pokemon_t* pokemon);

/*Devuelve la velocidad de un pokemon
*/
int obtener_velocidad_pokemon(pokemon_t* pokemon);

/*Devuelve la posicion en la que se encuentra un pokemon en un equipo
*/
pokemon_t* obtener_posicion_pokemon(entrenador_t* entrenador, size_t posicion);

#endif // ENTRENADOR_H_