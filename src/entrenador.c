#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lista.h"
#include "entrenador.h"

#define MAX_NOMBRE_POKEMON    10
#define MAX_NOMBRE_ENTRENADOR 30
#define FORMATO_ENTRENADORES "%s;%d\n"
#define FORMATO_POKEMONES "%s;%d;%d;%d;%d;%d\n"
#define ERROR -1
#define EXITO 0

const int ES_MAYOR=1,SON_IGUALES=0,ES_MENOR=-1;

struct _pokemon_t{
    char nombre[MAX_NOMBRE_POKEMON];
    int nivel;
    int fuerza;
    int inteligencia;
    int velocidad;
    int defensa;
};

struct _entrenador_t{
    char nombre[MAX_NOMBRE_ENTRENADOR];
    int victorias;
    lista_t* equipo;
};

entrenador_t* crear_entrenador(entrenador_t* entrenador, char** str_dividido){
    entrenador= calloc(1, sizeof(entrenador_t));
    if(!entrenador){
        free(entrenador);
        return NULL;
    }
    strcpy(entrenador->nombre, str_dividido[0]);
    entrenador->victorias= atoi(str_dividido[1]);
    entrenador->equipo=lista_crear();
    if(!entrenador->equipo){
        free(entrenador);
        return NULL;
    }
    return entrenador;
}

pokemon_t* crear_pokemon( pokemon_t* pokemon, char** str_dividido){
    pokemon= calloc(1, sizeof(pokemon_t));
    if(!pokemon){
        free(pokemon);
        return NULL;
    }
    strcpy(pokemon->nombre, str_dividido[0]);
    pokemon->nivel= atoi(str_dividido[1]);
    pokemon->defensa= atoi(str_dividido[2]);
    pokemon->fuerza= atoi(str_dividido[3]);
    pokemon->inteligencia= atoi(str_dividido[4]);
    pokemon->velocidad= atoi(str_dividido[5]);
    return pokemon;
}

int comparador_entrenadores(void* entrenador1,void* entrenador2){
  	if(strcmp(((entrenador_t*)entrenador1)->nombre,((entrenador_t*)entrenador2)->nombre)>0){
  		return ES_MAYOR;
  	}
  	else if(strcmp(((entrenador_t*)entrenador1)->nombre,((entrenador_t*)entrenador2)->nombre)<0){
  		return ES_MENOR;
  	}
  	else{
  		return SON_IGUALES;
  	}
}

int agregar_pokemon(entrenador_t* entrenador,pokemon_t* pokemon){
    int estado= lista_insertar(entrenador->equipo,pokemon);
    if(estado==ERROR){
        return ERROR;
    }
    return EXITO;
}

char* obtener_nombre(entrenador_t* entrenador){
    if(!entrenador){ 
        return NULL;
    }    
    return entrenador->nombre;
}

int obtener_victorias(entrenador_t* entrenador){
    if(!entrenador){ 
        return ERROR;
    }    
    return entrenador->victorias;
}

pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon){
    if(!entrenador || !nombre_pokemon){ 
        return NULL;
    }    
    if(lista_elementos(entrenador->equipo) == 0){ 
        return NULL;
    }    
    size_t posicion_actual = 0;
    pokemon_t* pokemon_actual = lista_elemento_en_posicion(entrenador->equipo,posicion_actual);
    while(pokemon_actual){
        if(strcmp(pokemon_actual->nombre,nombre_pokemon) == 0){  
            return pokemon_actual;
        }    
        posicion_actual++;
        pokemon_actual = lista_elemento_en_posicion(entrenador->equipo,posicion_actual);
    }
    return NULL;
}

pokemon_t* obtener_posicion_pokemon(entrenador_t* entrenador, size_t posicion){
    return lista_elemento_en_posicion(entrenador->equipo,posicion);
}

char* obtener_nombre_pokemon(pokemon_t* pokemon){
    if(!pokemon){ 
        return NULL;
    }    
    return pokemon->nombre;
}

int obtener_nivel_pokemon(pokemon_t* pokemon){
    if(!pokemon){ 
        return ERROR;
    }    
    return pokemon->nivel;
}

int obtener_fuerza_pokemon(pokemon_t* pokemon){
    if(!pokemon){ 
        return ERROR;
    }
    return pokemon->fuerza;
}

int obtener_inteligencia_pokemon(pokemon_t* pokemon){
    if(!pokemon){ 
        return ERROR;
    }
    return pokemon->inteligencia;
}

int obtener_defensa_pokemon(pokemon_t* pokemon){
    if(!pokemon){ 
        return ERROR;
    }
    return pokemon->defensa;
}

int obtener_velocidad_pokemon(pokemon_t* pokemon){
    if(!pokemon){ 
        return ERROR;
    }
    return pokemon->velocidad;
}
/*Se encarga de imprimir un pokemon con todos sus campos.
*/
int imprimir_pokemones(entrenador_t* entrenador, FILE* archivo){
    size_t cantidad= lista_elementos(entrenador->equipo);
    size_t posicion=0;
    pokemon_t* pokemon=lista_elemento_en_posicion(entrenador->equipo, posicion);
    for(int i=0; i<cantidad;i++){
        fprintf(archivo,FORMATO_POKEMONES, pokemon->nombre, pokemon->nivel, pokemon->defensa, pokemon->fuerza,pokemon->inteligencia, pokemon->velocidad);
        posicion++;
        pokemon= lista_elemento_en_posicion(entrenador->equipo,posicion);
    }
    return EXITO;
}

int imprimir_entrenadores(entrenador_t* entrenador, FILE* archivo){
    fprintf(archivo,FORMATO_ENTRENADORES, entrenador->nombre, entrenador->victorias);
    imprimir_pokemones(entrenador, archivo);
    return EXITO;
}

size_t cantidad_pokemones(entrenador_t* entrenador){
    return lista_elementos(entrenador->equipo);
}

int quitar_pokemon(void* entrenador, void* pokemon){
    if(!entrenador || !pokemon){
        return ERROR;
    }
    size_t cantidad= lista_elementos(((entrenador_t*)entrenador)->equipo);
    if(cantidad<=1){
        return ERROR;
    }
    size_t posicion=0;
    void* pokemon_actual= lista_elemento_en_posicion(((entrenador_t*)entrenador)->equipo, posicion);
    for(int i=0; i<cantidad ;i++){
        if(strcmp(pokemon_actual,(char*)pokemon)==0){
            int estado =lista_borrar_de_posicion(((entrenador_t*)entrenador)->equipo, posicion);
            if(estado==EXITO){
                free(pokemon_actual);
                return EXITO;
            }else{
                return ERROR;
            }  
        }
        posicion++;
        pokemon_actual= lista_elemento_en_posicion(((entrenador_t*)entrenador)->equipo, posicion);
    }
    return ERROR;    
}
/*Sen encarga de liberar la memoria de un pokemon
*/
bool destructor_pokemon(void* pokemon, void* poke){
    free(pokemon);
    return true;
}

void destructor_entrenadores(void* entrenador){
    if(!entrenador){
        return;
    }
    lista_con_cada_elemento(((entrenador_t*)entrenador)->equipo, destructor_pokemon , NULL);
    lista_destruir(((entrenador_t*)entrenador)->equipo);
    free(entrenador);
}

