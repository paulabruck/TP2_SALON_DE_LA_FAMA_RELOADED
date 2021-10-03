#include "salon.h"
#include "abb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "hash.h"

const char SEPARADOR =';';
#define ERROR -1
#define EXITO 0

#define CAMPOS_ENTRENADOR 2
#define CAMPOS_POKEMON 6
#define MAX_VICTORIAS 100

typedef struct comando{
    const char* nombre;
    char* (*ejecutar)(char*[],salon_t*);
}comando_t;

struct _salon_t{
    abb_t* entrenadores;
    size_t cantidad_entrenadores;
    hash_t* comandos;
};
/*Crea un comando reservando memoria.
*/
comando_t* crear_comando(comando_t* comando ){
    comando= calloc(1,sizeof(comando_t));
    if(!comando){
        return NULL;
    }
    return comando;
} 
/*Crea una copia de un string
*/
char* copiar_string_(const char* string){
  if(!string)
    return NULL;

  char* copia_string = malloc(strlen(string)+1);
  if(!copia_string){
      return NULL;
  }
  strcpy(copia_string,string);
  return copia_string;
}
/*Devuelve los registros correspondientes al comando ENTRENADORES
*/
char* listar_entrenadores(char** argumentos, salon_t* salon){
    int victorias_entrenador;
    int victorias_solicitadas = 0;
    char* pokemon_solicitado = NULL;
    char string[500] = "";
    char victorias_string[256];
    
    if(vtrlen(argumentos) != 0){
        if(vtrlen(argumentos) != 2){
            return NULL;
        }
        if(strcmp(argumentos[0],"victorias") == 0){
            victorias_solicitadas = atoi(argumentos[1]);
        }
        else if(strcmp(argumentos[0],"pokemon")){
            pokemon_solicitado = argumentos[1];
        }
    }
    size_t cantidad= salon->cantidad_entrenadores;
    entrenador_t* array[cantidad];
    arbol_recorrido_inorden(salon->entrenadores, (void**)array, cantidad);
    for (int i = 0; i < cantidad; i++){
        if(vtrlen(argumentos) == 0){
            victorias_entrenador = obtener_victorias(array[i]);
            strcat(string,obtener_nombre(array[i]));
            strcat(string,",");
            sprintf(victorias_string,"%i",victorias_entrenador);
            strcat(string,victorias_string);
            strcat(string,"\n");
        }
        else if(strcmp(argumentos[0],"victorias") == 0){
            victorias_entrenador = obtener_victorias(array[i]);
            if(victorias_entrenador >= victorias_solicitadas){
                strcat(string,obtener_nombre(array[i]));
                strcat(string,"\n");
            }
        }
        else{
            pokemon_solicitado = argumentos[1];
            if(obtener_pokemon(array[i],pokemon_solicitado) != NULL){
                strcat(string,obtener_nombre(array[i]));
                strcat(string,"\n");
            }
        } 
    }
    char* respuesta_definitiva = copiar_string_(string);
    return respuesta_definitiva;
}
/*Devuelve los registros correspondientes al comando EQUIPO
*/
char* listar_equipo(char** argumento, salon_t* salon){
    if(!argumento || !salon){
        return NULL;
    }
    char* respuesta=calloc(1024, sizeof(char));
    if(!respuesta){
        return NULL;
    }
    strcpy(respuesta,"");
    entrenador_t* entrenador=NULL;
    size_t cantidad= salon->cantidad_entrenadores;
    entrenador_t* array[cantidad];
    arbol_recorrido_inorden(salon->entrenadores, (void**)array, cantidad);
    for(int i=0; i<cantidad;i++){
        if(strcmp((char*)array[i], argumento[0])==0){
            entrenador= array[i];
        }
    }  
    if(!entrenador){
        free(respuesta);
        return NULL;
    }
    size_t posicion=0;
    char nivel_pokemon_actual_string[256];
    char fuerza_pokemon_actual_string[256];
    char inteligencia_pokemon_actual_string[256];
    char velocidad_pokemon_actual_string[256];
    char defensa_pokemon_actual_string[256];
    pokemon_t* pokemon= obtener_posicion_pokemon(entrenador,posicion);
    for(int i=0; i < cantidad_pokemones(entrenador); i++){
        strcat(respuesta, obtener_nombre_pokemon(pokemon));
        strcat(respuesta, "," );
        sprintf(nivel_pokemon_actual_string,"%i",obtener_nivel_pokemon(pokemon));
        strcat(respuesta,nivel_pokemon_actual_string);
        strcat(respuesta,",");
        sprintf(defensa_pokemon_actual_string,"%i",obtener_defensa_pokemon(pokemon));
        strcat(respuesta,defensa_pokemon_actual_string);
        strcat(respuesta,",");
        sprintf(fuerza_pokemon_actual_string,"%i",obtener_fuerza_pokemon(pokemon));
        strcat(respuesta,fuerza_pokemon_actual_string);
        strcat(respuesta,",");
        sprintf(inteligencia_pokemon_actual_string,"%i",obtener_inteligencia_pokemon(pokemon));
        strcat(respuesta,inteligencia_pokemon_actual_string);
        strcat(respuesta,",");
        sprintf(velocidad_pokemon_actual_string,"%i",obtener_velocidad_pokemon(pokemon));
        strcat(respuesta,velocidad_pokemon_actual_string);
        strcat(respuesta,"\n");
        posicion++;
        pokemon= obtener_posicion_pokemon(entrenador,posicion);      
    } 
    return respuesta;
}
/*Devuelve los registros correspondientes al comando REGLAS
*/
char* listar_reglas(char** argumento, salon_t* salon){
    if(!salon || argumento!=0){
        return NULL;
    }
    char* respuesta= calloc(4096, sizeof(char));
    if(!respuesta){
        return NULL;
    }
    char* regla_clasica="CLASICO, combate clasico";
    char* regla_moderna="MODERNO, combate moderno" ;
    char* regla_perezoso="PEREZOSO, El ganador sera aquel pokemon con menos fuerza" ;
    char* regla_productivo="PRODUCTIVO, El ganador sera aquel pokemon con mas velocidad" ;
    char* regla_intuitivo="INTUITIVO, El ganador sera el pokemon mas inteligente" ;
    strcat(respuesta,regla_clasica );
    strcat(respuesta,"\n");
    strcat(respuesta,regla_moderna) ;
    strcat(respuesta,"\n");
    strcat(respuesta,regla_perezoso) ;
    strcat(respuesta,"\n");
    strcat(respuesta,regla_productivo) ;
    strcat(respuesta,"\n");
    strcat(respuesta,regla_intuitivo) ;
    strcat(respuesta,"\n");
    
    return respuesta;
}
/*Devuelve los registros correspondientes al comando COMPARAR
*/
char* comparar_entrenadores_segun_regla(char** argumento, salon_t* salon){
    if(vtrlen(argumento)!=3){
        return NULL;
    }
    char* respuesta = calloc(1024, sizeof(char));
    if(!respuesta){
        return NULL;
    }
    entrenador_t* entrenador1=NULL;
    entrenador_t* entrenador2=NULL;
    size_t cantidad= salon->cantidad_entrenadores;
    entrenador_t* array[cantidad];
    arbol_recorrido_inorden(salon->entrenadores, (void**)array, cantidad);
    for(int i=0; i<cantidad;i++){
        if(strcmp((char*)array[i], argumento[0])==0){
            entrenador1= array[i];
        }
    } 
    for(int i=0; i<cantidad;i++){
        if(strcmp((char*)array[i], argumento[1])==0){
            entrenador2= array[i];
        }
    }    
    if(!entrenador1 || !entrenador2){
        free(respuesta);
        return NULL;
    }
    size_t posicion1 = 0;
    size_t posicion2 = 0;
    pokemon_t* pokemon_actual_1 = obtener_posicion_pokemon(entrenador1,posicion1);
    pokemon_t* pokemon_actual_2 = obtener_posicion_pokemon(entrenador2,posicion2);
    int cantidad1=0;
    int cantidad2=0;
    while(cantidad1< cantidad_pokemones(entrenador1) && cantidad2< cantidad_pokemones(entrenador2)){
        if(strcmp(argumento[2], "CLASICO")==0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 8 + 10 * obtener_fuerza_pokemon(pokemon_actual_1) + 20 * obtener_velocidad_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 8 + 10 * obtener_fuerza_pokemon(pokemon_actual_2) + 20 * obtener_velocidad_pokemon(pokemon_actual_2)){
                strcat(respuesta,"1");
                posicion2++;
                cantidad2++;
            }
            else{
                posicion1++;
                cantidad1++;
                strcat(respuesta,"2");
            }
        }else if(strcmp(argumento[2],"MODERNO") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 5 + 9 * obtener_defensa_pokemon(pokemon_actual_1) + 30 * obtener_inteligencia_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 5 + 9 * obtener_defensa_pokemon(pokemon_actual_2) + 30 * obtener_inteligencia_pokemon(pokemon_actual_2)){
                strcat(respuesta,"1");
                posicion2++;
                cantidad2++;
            }
            else{
                posicion1++;
                cantidad1++;
                strcat(respuesta,"2");
            }
        }else if(strcmp(argumento[2],"PRODUCTIVO") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 4 + 30 * obtener_defensa_pokemon(pokemon_actual_1) + 20 * obtener_fuerza_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 4 + 30 * obtener_defensa_pokemon(pokemon_actual_2) + 20 * obtener_fuerza_pokemon(pokemon_actual_2)){
                strcat(respuesta,"1");
                posicion2++;
                cantidad2++;
            }
            else{
                posicion1++;
                cantidad1++;
                strcat(respuesta,"2");
            }
        }else if(strcmp(argumento[2],"INTUITIVO") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 4 + 10 * obtener_inteligencia_pokemon(pokemon_actual_1) + 20 * obtener_velocidad_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 4 + 10 * obtener_inteligencia_pokemon(pokemon_actual_2) + 20 * obtener_velocidad_pokemon(pokemon_actual_2)){
                strcat(respuesta,"1");
                posicion2++;
                cantidad2++;
            }
            else{
                posicion1++;
                cantidad1++;
                strcat(respuesta,"2");
            }
        }else if(strcmp(argumento[2],"PEREZOSO") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 5 + 25 * obtener_velocidad_pokemon(pokemon_actual_1) + 60 * obtener_fuerza_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 5 + 25 * obtener_velocidad_pokemon(pokemon_actual_2) + 60 * obtener_fuerza_pokemon(pokemon_actual_2)){
                strcat(respuesta,"1");
                posicion2++;
                cantidad2++;
            }
            else{
                posicion1++;
                cantidad1++;
                strcat(respuesta,"2");
            }
        }else{
            free(respuesta);
            return NULL;
        }
        pokemon_actual_1 = obtener_posicion_pokemon(entrenador1,posicion1);
        pokemon_actual_2 = obtener_posicion_pokemon(entrenador2,posicion2);
        strcat(respuesta,"\n");
    }
    return respuesta;
}
/*Devuelve los registros correspondientes al comando AGREGAR
*/
char* agregar_pokemon_a_equipo(char** argumento, salon_t* salon){
    if(!salon || !argumento){
        return NULL;
    }
    if(vtrlen(argumento)!=7){
        return NULL;
    }
    char* respuesta= calloc(5, sizeof(char));
    if(!respuesta){
        return NULL;
    }
    pokemon_t* pokemon=NULL;
    char* nuevo_argumento[6]={argumento[1],argumento[2], argumento[3],argumento[4], argumento[5], argumento[6] } ;
    size_t cantidad= salon->cantidad_entrenadores;
    entrenador_t* array[cantidad];
    arbol_recorrido_inorden(salon->entrenadores, (void**)array, cantidad);
    for(int i=0; i<cantidad;i++){
        if(strcmp((char*)array[i], argumento[0])==0){
            pokemon=crear_pokemon(pokemon, nuevo_argumento);
            if(!pokemon){
                free(respuesta);
                return NULL;
            }
            int estado=agregar_pokemon( (entrenador_t*)array[i],pokemon);
            if(estado==-1){
                free(respuesta);
                return NULL;
            }
            strcpy(respuesta, "OK");
            return respuesta;
        }
    }
    free(respuesta);
    return NULL;
}
/*Devuelve los registros correspondientes al comando QUITAR
*/
char* quitar_pokemon_de_equipo(char** argumento, salon_t* salon){
    if(!salon){
        return NULL;
    }
    if(vtrlen(argumento)!=2){
        return NULL;
    }
    char* respuesta= calloc(5, sizeof(char));
    if(!respuesta){
        return NULL;
    }
    size_t cantidad= salon->cantidad_entrenadores;
    entrenador_t* array[cantidad];
    arbol_recorrido_inorden(salon->entrenadores, (void**)array, cantidad);
    for(int i=0; i<cantidad;i++){
        if(strcmp((char*)array[i], argumento[0])==0){
            if((cantidad_pokemones(array[i])>1)){ 
                int estado=quitar_pokemon(array[i], argumento[1]);
                if(estado==-1){   
                    free(respuesta);
                    return NULL;
                }
                strcpy(respuesta, "OK");
                return respuesta;
            }
        }
    }
    free(respuesta);
    return NULL;
}
/*Devuelve los registros correspondientes al comando GUARDAR
*/
char* guardar_en_nuevo_archivo(char** argumento, salon_t* salon){
    if(!argumento || !salon){
        return NULL;
    }
    char* archivo= argumento[0];
    if(salon_guardar_archivo(salon, archivo)==-1){
        return NULL;
    }
    char* respuesta=calloc(5, sizeof(char));
    strcpy(respuesta, "OK");
    return respuesta;
}
/*Inicializa los comandos en un hash
*/
hash_t* inicializar_hash_comandos(){
    hash_t* comandos = hash_crear(NULL, 20);
    if(!comandos){
        return NULL;
    }
    int estado=0;
    estado=hash_insertar(comandos, "ENTRENADORES", listar_entrenadores);
    if(estado==ERROR){
        hash_destruir(comandos);
        return NULL;
    }
    estado=hash_insertar(comandos, "EQUIPO", listar_equipo );
    if(estado==ERROR){
        hash_destruir(comandos);
        return NULL;
    }
    estado=hash_insertar(comandos, "REGLAS", listar_reglas);
    if(estado==ERROR){
        hash_destruir(comandos);
        return NULL;
    }
    estado=hash_insertar(comandos, "COMPARAR", comparar_entrenadores_segun_regla);
    if(estado==ERROR){
        hash_destruir(comandos);
        return NULL;
    }
    estado=hash_insertar(comandos, "AGREGAR_POKEMON", agregar_pokemon_a_equipo);
    if(estado==ERROR){
        hash_destruir(comandos);
        return NULL;
    }
    estado=hash_insertar(comandos, "QUITAR_POKEMON", quitar_pokemon_de_equipo);
    if(estado==ERROR){
        hash_destruir(comandos);
        return NULL;
    }
    estado=hash_insertar(comandos, "GUARDAR", guardar_en_nuevo_archivo);
    if(estado== ERROR){
        hash_destruir(comandos);
        return NULL;
    }
    return comandos;
}
/*Devuelve true si la cantidadde pokemones es 0
*/
bool recorrer(void* entrenador ,void* aux){
    if(cantidad_pokemones(entrenador)==0){
        return true;
    }
    return false;
}
/*Recorre el arbol verificando si algun entrenador no tiene pokemones en su equipo
*/
salon_t* verificar_pokemones_en_entrenador(salon_t* salon){
    size_t cantidad= abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, recorrer,NULL);
    if(cantidad<salon->cantidad_entrenadores){
        return NULL;
    }
    return salon;
}

salon_t* salon_leer_archivo(const char* nombre_archivo){
    if(!nombre_archivo){
        return NULL;
    }
    salon_t* salon= calloc(1, sizeof(salon_t));
    if(!salon){ 
        return NULL;
    }    
    hash_t* hash = inicializar_hash_comandos();
    if(!hash){
        free(salon);
        return NULL;
    }
    salon->comandos= hash;
    FILE* archivo = fopen(nombre_archivo, "r");
    if(!archivo){
        free(salon);
        hash_destruir(hash);
        return NULL;
    }    
    salon->entrenadores=arbol_crear(comparador_entrenadores, destructor_entrenadores);
    if(!salon->entrenadores){
        salon_destruir(salon);
        fclosen(archivo);
        return NULL;
    }
    char* str= fgets_alloc(archivo);
    char** str_divido=NULL;
    entrenador_t* entrenador=NULL;
    entrenador_t* entrenador_aux=NULL;
    pokemon_t* pokemon=NULL;
    pokemon_t* pokemon_aux=NULL;
    int i= -1;
    int estado=-1;
    while(str){
        str_divido=split(str, SEPARADOR);
        if(vtrlen(str_divido)== CAMPOS_ENTRENADOR){
            i++;
            size_t cantidad= salon->cantidad_entrenadores;
            if(cantidad>=1){
                entrenador_t* array[cantidad];
                arbol_recorrido_inorden(salon->entrenadores, (void**)array, cantidad);
                for(int i=0; i<cantidad;i++){
                    if(strcmp((char*)array[i], (char*)str_divido[0])==0){
                        salon_destruir(salon);
                        vtrfree(str_divido);
                        free(str);
                        fclosen(archivo);
                        return NULL;        
                    }    
                }
                entrenador_aux= crear_entrenador(entrenador, str_divido);
                if(!entrenador_aux){
                    salon_destruir(salon);
                    vtrfree(str_divido);
                    free(str);
                    fclosen(archivo);
                    return NULL;
                }
                estado= arbol_insertar(salon->entrenadores, entrenador_aux);
                if(estado==0){
                    salon->cantidad_entrenadores++;
                }else{
                    destructor_entrenadores(entrenador_aux);
                    salon_destruir(salon);
                    vtrfree(str_divido);
                    free(str);
                    fclosen(archivo);
                    return NULL;
                } 
            }else{
                entrenador_aux= crear_entrenador(entrenador, str_divido);
                if(!entrenador_aux){
                    salon_destruir(salon);
                    vtrfree(str_divido);
                    free(str);
                    fclosen(archivo);
                    return NULL;
                }
                estado= arbol_insertar(salon->entrenadores, entrenador_aux);
                if(estado==0){
                    salon->cantidad_entrenadores++;
                }else{
                    destructor_entrenadores(entrenador_aux);
                    salon_destruir(salon);
                    vtrfree(str_divido);
                    free(str);
                    fclosen(archivo);
                    return NULL;
                } 
            }             
        }else if(vtrlen(str_divido)==CAMPOS_POKEMON){
            pokemon_aux= crear_pokemon(pokemon,str_divido);
            if(!pokemon_aux){
                salon_destruir(salon);
                    vtrfree(str_divido);
                    fclosen(archivo);
                    free(str);
                    return NULL;
            }
            agregar_pokemon(entrenador_aux, pokemon_aux);  
        }else{
            vtrfree(str_divido);
            salon_destruir(salon);
            free(str); 
            fclosen(archivo);
            return NULL;
        } 
        free(str);
        vtrfree(str_divido);
        str= fgets_alloc(archivo);
    }
    if(verificar_pokemones_en_entrenador(salon)==NULL){
        salon_destruir(salon);
        free(str); 
        fclosen(archivo);
        return NULL;
    }    
    free(str); 
    fclosen(archivo);
    return salon;  
}
/*Imprime los entrenadores junto a sus pokemones
*/
bool recorrer_e_imprimir(void* entrenador, void* archivo){
    imprimir_entrenadores(entrenador, archivo);
    return false;
}
/*Recorre el arbol e imprime los entrenadores junto a sus pokemones
*/
int entrenadores(salon_t* salon, FILE* archivo){
    abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, recorrer_e_imprimir, archivo);
    return 0;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* nuevo_archivo = fopen(nombre_archivo, "w");
    if(!nuevo_archivo){
        return ERROR;
    }   
    if(!salon ){
        fclosen(nuevo_archivo);
        return ERROR;
    }
    size_t cantidad_entrenadores= salon->cantidad_entrenadores;
    if(cantidad_entrenadores<=0){
        fclosen(nuevo_archivo);
        return ERROR;
    }
    entrenadores(salon, nuevo_archivo);
    fclosen(nuevo_archivo);
    return (int)cantidad_entrenadores;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon || !entrenador){
        return NULL;
    }
    if(cantidad_pokemones(entrenador)==0){
        return NULL;
    }else{
        int estado= arbol_insertar(salon->entrenadores, entrenador);
        if(estado==ERROR){
            return NULL;
        }
    }
    return salon;
}

lista_t* salon_filtrar_entrenadores(salon_t* salon , bool (f)(entrenador_t*, void*), void* extra){
    if(!f || !salon){
        return NULL;
    }
    lista_t* lista= lista_crear();
    bool resultado=false;
    size_t cantidad= salon->cantidad_entrenadores;
    entrenador_t* array[cantidad];
    arbol_recorrido_inorden(salon->entrenadores, (void**)array, cantidad);
    for(int i=0; i<cantidad; i++){
        resultado=(*f)((entrenador_t*)array[i], extra);
        if(resultado){
            lista_insertar(lista, (entrenador_t*)array[i]);
        }
    }
    return lista;
}
/*Divide el comando recibido y ejecuta los comandos.
*/
char* procesar_opcion(salon_t* salon,const char* comando_recibido){
    if(!salon || !comando_recibido){
        return NULL;
    }
    char* respuesta=NULL;
    char** separacion= split(comando_recibido,':');
    if(!separacion){
        return NULL;
    }
    char** argumentos= split(separacion[1],',');
    if(!argumentos){
        argumentos= NULL;
    }
    comando_t* comando= crear_comando(comando);
    if(!comando){
        vtrfree(separacion);
        vtrfree(argumentos);
        return NULL;
    }
    if(hash_contiene(salon->comandos, separacion[0])){
        comando->ejecutar = hash_obtener(salon->comandos,separacion[0]);
        if(comando->ejecutar){
          respuesta= comando->ejecutar(argumentos, salon);
        }
    }
    free((comando_t*)comando); 
    vtrfree(separacion);
    vtrfree(argumentos);   
    return respuesta;
}

char* salon_ejecutar_comando(salon_t* salon, const char* comando){
    if(!salon || !comando){
        return NULL;
    }
    char* respuesta=NULL;
    respuesta= procesar_opcion(salon, comando);
    if(!respuesta){
        return NULL;
    }
    return respuesta;
}
/*Destruye los comandos creados
*/
bool destruir_comando(hash_t* comando, const char* clave, void* aux ){
    if(!comando|| !clave){
        return true;
    }
    hash_quitar(comando, clave );
    return false;
}

void salon_destruir(salon_t* salon){
    if(!salon){
        return ;
    }
    for(int i=0; i<salon->cantidad_entrenadores;i++){
       arbol_borrar(salon->entrenadores, salon->entrenadores->nodo_raiz->elemento);
    }
    hash_con_cada_clave(salon->comandos, destruir_comando, NULL);
    hash_destruir(salon->comandos);
    arbol_destruir(salon->entrenadores);
    free(salon);
}