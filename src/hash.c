#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "hash.h"

#define EXITO 0
#define ACTUALIZACION 1
#define ERROR -1
#define NO_EXISTE 0

const double FACTOR_CARGA=0.7;

typedef struct par{
  void* elemento;
  char* clave;
  bool habia_elemento;
}par_t;

struct hash{
  par_t** tabla;
  size_t cantidad;
  size_t capacidad;
  hash_destruir_dato_t destructor; 
};
/* Copia y guarda el string recibido.
 */
char* copiar_string(const char* clave){
  if(!clave)
    return NULL;

  char* nueva_clave = malloc(strlen(clave)+1);
  if(!nueva_clave){
    return NULL;
  }
  strcpy(nueva_clave,clave);
  return nueva_clave;
}
/* Libera el string.
 */
void destruir_string(void* elemento){
  if(elemento){
    free(elemento);
  }
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  if(capacidad_inicial<=3){
    capacidad_inicial=3;
  }
  hash_t* hash = malloc(sizeof(hash_t));
  if(!hash){
    return NULL;
  }
  hash->capacidad= capacidad_inicial;
  hash->cantidad=0;
  hash->destructor= destruir_elemento;
  hash->tabla= calloc(capacidad_inicial,sizeof(par_t*));
  if(!hash->tabla){
    free(hash);
    return NULL;
  }
  
  return hash;
}
/* Se encarga de crear los pares del hash.
 */
par_t* par_crear(void* elemento, const char* clave){
  par_t* par_nuevo= malloc( sizeof(par_t));
  if(!par_nuevo){
    return NULL;
  }
  char* clave_nueva = copiar_string(clave);
  if(!clave_nueva){
    free(par_nuevo);
    return NULL;
  }
  par_nuevo->clave=clave_nueva;
  par_nuevo->elemento= elemento;
  par_nuevo->habia_elemento=true;
 
  return par_nuevo;
}
/* Convierte el string recibido en una valor numerico y le asigna una posicion dentro de la tabla .
 */
size_t funcion_hash(const char* clave, size_t capacidad){
  long int valor=0;
  while(*clave){
    valor+= strtol((const char*)clave, NULL,(int)valor) ;
    clave++;
  }
  return (size_t)valor  % capacidad;
}
/* Verifica si es necesario hacer un rehash, viendo el grado de ocupacion y el factor de carga.
 */
bool es_necesario_rehashear(size_t capacidad,size_t cantidad_guardada){
  double grado_ocupacion=(double)cantidad_guardada/(double)capacidad;
  return grado_ocupacion>FACTOR_CARGA;
}
/* Se encarga de insertar los pares dentro de la tabla de hash.
 */
int insertar_pares(par_t** tabla,const char* clave, void* elemento, size_t capacidad,hash_destruir_dato_t destructor){
    if(!tabla || !clave){
      return ERROR;
    }
    par_t* par_nuevo = par_crear(elemento, clave);
    if (!par_nuevo){ 
      return ERROR;
    }      
    size_t posicion = funcion_hash(clave,capacidad);
    par_t* par_actual = tabla[posicion];

    while(par_actual){
      if(par_actual->clave){
        if(strcmp(par_actual->clave, par_nuevo->clave) == 0){
          if(destructor){
            destructor(par_actual->elemento);
          }
          destruir_string(par_actual->clave);
          free(tabla[posicion]);
          tabla[posicion]= par_nuevo;
          return ACTUALIZACION; 
          }
          posicion++;
          if(posicion >= capacidad){ 
            posicion = 0;
          }
          par_actual = tabla[posicion];
      }
      else{
          free(tabla[posicion]);
          tabla[posicion] = par_nuevo;
          return EXITO;
          }

    }
  tabla[posicion] = par_nuevo;

  return EXITO;
}
/* Se encarga de liberar los pares de la tabla de hash.
 */
void destruir_tabla(par_t** tabla,size_t capacidad, hash_destruir_dato_t destructor){
  for(int i = 0; i < capacidad;i++){
    par_t* par_actual = tabla[i] ;
    if(par_actual){
      if(destructor){ 
        destructor(par_actual->elemento);
      }  
      destruir_string(par_actual->clave);
      free(par_actual);
    }
  }
  free(tabla);
}
/* Agranda el tamaño de la tabla de hash al doble de la capacidad de la tabla original y reinserta los pares 
 *  en la nueva tabla. Luego libera la tabla original. 
 */
int expandir_tabla(hash_t* hash, size_t nueva_capacidad){
  par_t** tabla_mayor= calloc(nueva_capacidad, sizeof(par_t*));
  if(!tabla_mayor){
    return ERROR;
  }
  for(int i=0; i < hash->capacidad;i++ ){
    par_t* par= hash->tabla[i];
    if(par){
      if(par->clave){
        insertar_pares(tabla_mayor,par->clave,par->elemento,nueva_capacidad,hash->destructor);
      } 
    }
  }
  destruir_tabla(hash->tabla,hash->capacidad,NULL);
  hash->tabla = tabla_mayor;
  hash->capacidad = nueva_capacidad;
  
  return EXITO;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  if(!clave || !hash){
    return ERROR;
  }
  int estado = insertar_pares(hash->tabla,clave,elemento,hash->capacidad,hash->destructor);
  if(estado == ERROR){
    return ERROR;
  }
  if(estado == EXITO){
    hash->cantidad++;
  }
  if(es_necesario_rehashear(hash->capacidad, hash->cantidad)){
    return expandir_tabla(hash, hash->capacidad * 2);
  }        
   
  return EXITO;
}

int hash_quitar(hash_t* hash, const char* clave){
    if(!hash || !clave ){
      return ERROR;
    }
    size_t posicion= funcion_hash(clave, hash->capacidad);
    bool clave_encontrada= false;
    par_t* par_actual= hash->tabla[posicion]; 

    
    while(par_actual && (clave_encontrada==false)){
      if(par_actual->clave){
        if(strcmp(par_actual->clave, clave)==0){
          clave_encontrada= true;
        }else{
          posicion++;  
          if(posicion>=hash->capacidad){
            posicion=0;
          }
          par_actual= hash->tabla[posicion];
        }
      }else{
        posicion++;  
        if(posicion==hash->capacidad){
          posicion=0;
        }
        par_actual= hash->tabla[posicion];
      }
    }
    if(par_actual==NULL){
    return ERROR;
    }else{
      destruir_string(par_actual->clave);
      if(hash->destructor){
      hash->destructor(par_actual->elemento );
      }
      par_actual->clave=NULL;
      par_actual->elemento=NULL;
      hash->cantidad--;
    }
   
  return EXITO;
}

void* hash_obtener(hash_t* hash, const char* clave){
  if(!hash|| !clave){
    return NULL;
  }
  
  size_t posicion= funcion_hash(clave, hash->capacidad); ;
  par_t* par_actual=hash->tabla[posicion];
   
  while(par_actual){
    if(par_actual->clave){
      if(strcmp(par_actual->clave ,clave)==0){
        return par_actual->elemento;
      }
    }
    posicion++ ;
    if(posicion>=hash->capacidad  ){
      posicion=0;
    }
    par_actual=hash->tabla[posicion];
  }
  
  return NULL;
}

size_t hash_cantidad(hash_t* hash){
  if(!hash){
    return (size_t)NO_EXISTE;
  }
  return hash->cantidad;
}

bool hash_contiene(hash_t* hash, const char* clave){
  return hash_obtener(hash, clave)!=NULL;
}

void hash_destruir(hash_t* hash){
  if(!hash){
    return;
  }
  if(hash->tabla){
    destruir_tabla(hash->tabla,hash->capacidad,hash->destructor);
  }
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  if(!hash || !funcion){
    return NO_EXISTE;
  }
        
  size_t cantidad = 0;
  bool resultado_funcion=false;
  
  for(int i = 0; i < hash->capacidad; i++){
    par_t*  par_actual = hash->tabla[i];
    if(par_actual){
      if(par_actual->clave){
        resultado_funcion = funcion(hash,par_actual->clave,aux);
        cantidad++;
        if(resultado_funcion){
          return cantidad;
        }
      }
    }
  }
  return cantidad;
}
