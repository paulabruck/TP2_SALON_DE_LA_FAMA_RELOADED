#include "lista.h"
#include <stdlib.h>
#include <string.h>

lista_t* lista_crear(){
    lista_t* lista=malloc(sizeof(lista_t));
	if(!lista){
		return NULL;
	}
	lista->nodo_inicio=NULL;
	lista->nodo_fin=NULL;
    lista->cantidad=0;

	return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
    if(!lista){
        return -1;
    }
    nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo){
		return -1;
	}
	nuevo_nodo->siguiente=NULL;
    if(lista_vacia(lista)){
		lista->nodo_inicio=nuevo_nodo;
		lista->nodo_fin=nuevo_nodo;
	}
	else{
		lista->nodo_fin->siguiente=nuevo_nodo;
		lista->nodo_fin=nuevo_nodo;
	}
    lista->cantidad++;
    nuevo_nodo->elemento= elemento;

    return 0;
}

void ir_posicion_anterior(nodo_t** aux,size_t posicion){
	for(int i=0;i<posicion-1;i++){
		if((*aux)!=NULL){
			(*aux)=(*aux)->siguiente;
		}
	}
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista){
        return -1;
    }
    if(lista->cantidad<=posicion || lista->cantidad==0){
		return lista_insertar(lista,elemento);
	}
    nodo_t* nuevo_nodo=malloc(sizeof(nodo_t));
	if(! nuevo_nodo){
		return -1;
	}
	if(posicion==0){
		nuevo_nodo->siguiente=lista->nodo_inicio;
		lista->nodo_inicio=nuevo_nodo;
	}
	else{
		nodo_t* aux=lista->nodo_inicio;
		ir_posicion_anterior(&aux,posicion);
		nuevo_nodo->siguiente=aux->siguiente;
		aux->siguiente=nuevo_nodo;
	}
	(lista->cantidad)++;
	nuevo_nodo->elemento=elemento;

    return 0;
}

int lista_borrar(lista_t* lista){
    if(!lista){
		return -1;
	}
	if(lista->cantidad==0 || lista->nodo_inicio==NULL){
		return -1;
	}
	else if(lista->cantidad==1){
		free(lista->nodo_inicio);
		lista->nodo_inicio=NULL;
		lista->nodo_fin=NULL;
	}
	else{
		nodo_t* auxiliar=lista->nodo_inicio;
		ir_posicion_anterior(&auxiliar,lista->cantidad-1);
		free(auxiliar->siguiente);
		lista->nodo_fin=auxiliar;
		lista->nodo_fin->siguiente=NULL;
	}
	(lista->cantidad)--;

    return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista){
		return -1;
	}
	if((lista->cantidad-1)<=posicion || lista->cantidad<=1){
		return lista_borrar(lista);
	}
	if(posicion==0){
		nodo_t* auxiliar=lista->nodo_inicio;
		lista->nodo_inicio=lista->nodo_inicio->siguiente;
		free(auxiliar);
	}
	else{
		nodo_t* iterador=lista->nodo_inicio;
		ir_posicion_anterior(&iterador,posicion);
		nodo_t* auxiliar=iterador;
		iterador=iterador->siguiente;
		auxiliar->siguiente=iterador->siguiente;
		free(iterador);
	}
	(lista->cantidad)--;
	
    return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if(lista==NULL){
		return NULL;
	}
	if(lista->cantidad<=posicion || lista->nodo_inicio==NULL){
		return NULL;
	}
	if(posicion==0){
		return lista->nodo_inicio->elemento;
	}
	nodo_t* iterador=lista->nodo_inicio;
	ir_posicion_anterior(&iterador,posicion+1);

	return iterador->elemento;
}

void* lista_ultimo(lista_t* lista){
    if(!lista){
		return NULL;
	}
	if(lista->cantidad==0|| lista->nodo_fin==NULL){
		return NULL;
	}

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
    if(!lista || lista->cantidad==0){
		return true;
	}

    return false;
}

size_t lista_elementos(lista_t* lista){
    if(!lista){
		return 0;
	}

	return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
    if(!lista){
        return -1;
    }
    lista_insertar_en_posicion(lista,elemento,0 );

    return 0;
}

int lista_desapilar(lista_t* lista){
    if(!lista){
        return -1;
    }
    if(lista->cantidad==0 || lista->nodo_inicio==NULL){
		return -1;
	}
    lista_borrar_de_posicion(lista,0);
    return 0;
}

void* lista_tope(lista_t* lista){
    if(!lista||lista->cantidad==0){
        return NULL;
    }

    return lista->nodo_inicio->elemento;
}

int lista_encolar(lista_t* lista, void* elemento){
    if(!lista){
        return -1;
    }
    lista_insertar(lista, elemento);

    return 0;
}

int lista_desencolar(lista_t* lista){
    if(!lista){
	    return -1;
	}
    if( lista->cantidad==0){
		return -1;
	}
    lista_borrar_de_posicion(lista,0);

    return 0;
}

void* lista_primero(lista_t* lista){
    if(!lista || lista->nodo_inicio==0){
        return NULL;
    }
	
    return lista->nodo_inicio->elemento;
}

void lista_destruir(lista_t* lista){
     while(!lista_vacia(lista)){
		lista_borrar_de_posicion(lista, 0);
	}
    free(lista);	
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista){
		return NULL;
	}
	lista_iterador_t* iterador=malloc(sizeof(lista_iterador_t));
	if(!iterador){
		return NULL;
	}
	iterador->lista=lista;
	iterador->corriente= lista->nodo_inicio;   
    
	return iterador;   
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador ){
		return false;
	}
	
	return iterador->corriente!=NULL;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if(!lista_iterador_tiene_siguiente(iterador)){
		return false;
	}
	iterador->corriente=iterador->corriente->siguiente;
	 
	return iterador->corriente!=NULL;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!iterador){
        return NULL;
    }
	if(!iterador->corriente){
		return NULL;
	}

    return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (funcion)(void*, void*), void *contexto){
    if(!lista|| !funcion){
        return 0;
    }
	size_t cantidad_=0;
	nodo_t* iterador=lista->nodo_inicio;
	for(int i=0;i<lista->cantidad;i++){
		(*funcion)(iterador->elemento, contexto);
		iterador=iterador->siguiente;
		cantidad_++;
	}

	return cantidad_ ;
}