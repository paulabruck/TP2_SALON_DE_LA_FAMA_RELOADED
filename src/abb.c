#include "abb.h"

const int CERO=0;
const int ERROR=-1,EXITO=0;
const size_t NO_EXISTE=0;


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    abb_t* arbol=malloc(sizeof(abb_t));
    if(!arbol){
        return NULL;
    }
    arbol->nodo_raiz=NULL;
    arbol->comparador=comparador;
    arbol->destructor=destructor;

    return arbol;
}
/* Crea un nuevo nodo en el se guarda un elemento.Luego de su creacion es devuelto.
* En caso de  error devuelve NULL al nodo de arriba,
* y guarda el estado en una variable.
*/
nodo_abb_t* crear_nodo(void* elemento,int* estado_creacion){
    nodo_abb_t* nuevo_nodo=malloc(sizeof(nodo_abb_t));
    if(!nuevo_nodo ){
        (*estado_creacion)=ERROR;
        return NULL;
    }
    nuevo_nodo->elemento=elemento;
    nuevo_nodo->izquierda=NULL;
    nuevo_nodo->derecha=NULL;
    (*estado_creacion)=EXITO;
    return nuevo_nodo;
}
/* Recorre el arbol buscando el lugar en el que debe realizar la insercion del elemento. Usa el comparador para saber
* en donde tiene que insertarlo.
*/
nodo_abb_t* insertar_elemento(nodo_abb_t* nodo,abb_comparador comparador,void* elemento,int* estado_insercion){
    if(!nodo){
        return crear_nodo(elemento,estado_insercion);
    }
    int resultado=comparador(elemento,nodo->elemento);
    if(resultado>CERO){
        nodo->derecha=insertar_elemento(nodo->derecha,comparador,elemento,estado_insercion);
    }
    else if(resultado<=CERO ){
        nodo->izquierda=insertar_elemento(nodo->izquierda,comparador,elemento,estado_insercion);
    }
    return nodo;
}
int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol){
        return ERROR;
    }
    int estado_insercion;
    arbol->nodo_raiz=insertar_elemento(arbol->nodo_raiz,arbol->comparador,elemento,&estado_insercion);
    return estado_insercion;
}
/* Devuelve true si el nodo no tiene hijos.
 */
bool es_nodo_hoja(nodo_abb_t* nodo){
	return (nodo->izquierda==NULL && nodo->derecha==NULL);
}
/* Devuelve true si el nodo tiene dos hijos .
 */
bool tiene_dos_hijos(nodo_abb_t* nodo){
	return (nodo->izquierda!=NULL && nodo->derecha!=NULL);
}
/* Busca el predecesor inorden(mayor de los menores). Recibe un puntero usado para actualizar el padre del nodo que va a tomar el lugar del nodo que va a ser eliminado.
 */
nodo_abb_t* buscar_predecesor_inorden(nodo_abb_t* nodo){
	if(nodo->derecha!=NULL){
		return buscar_predecesor_inorden(nodo->derecha);
	}
	return nodo;
}
/* Busca que nodo seria el padre del predecesor inorden (mayor de los menores), en caso de que el predecesor inorden no tenga un 
 * padre(el mayor es el nodo izquierdo),se devuelve NULL. 
 */
nodo_abb_t* buscar_padre(nodo_abb_t* nodo,nodo_abb_t* nodo_hijo){
	if(nodo->derecha==NULL){
		return NULL;
	}
	if(nodo->derecha==nodo_hijo){
		return nodo;
	}
	return buscar_padre(nodo->derecha,nodo_hijo);
}
/* Se liberan los nodos que se encuentran en el arbol.
 */
void destruir_nodo(nodo_abb_t* nodo,abb_liberar_elemento destructor){
    if(destructor!=NULL){
        destructor(nodo->elemento);
    }
    free(nodo);
}
/* Reacomoda cuando se va a borrar un elemento en el arbol. Borra el nodo solicitado ,se encarga de que se mantenga la estructura.
 */
nodo_abb_t* reacomodar_arbol(nodo_abb_t* nodo,abb_liberar_elemento destructor,int* estado){
	nodo_abb_t* nodo_devuelto;
	if(es_nodo_hoja(nodo)){
		nodo_devuelto=NULL;
	}
	else if(tiene_dos_hijos(nodo)){
		nodo_devuelto=buscar_predecesor_inorden(nodo->izquierda);
		nodo_abb_t* padre=buscar_padre(nodo->izquierda,nodo_devuelto);
		if(padre!=NULL){
			padre->derecha=nodo_devuelto->izquierda;
		}
		nodo_devuelto->derecha=nodo->derecha;
		if(nodo_devuelto!=nodo->izquierda){
			nodo_devuelto->izquierda=nodo->izquierda;
		}
	}
	else{
		if(nodo->derecha!=NULL){
			nodo_devuelto=nodo->derecha;
		}
		else{
			nodo_devuelto=nodo->izquierda;
		}
	}
	destruir_nodo(nodo,destructor);
	(*estado)=EXITO;
	return nodo_devuelto;
}
/* Busca el nodo que tiene el elemento que hay que borrar, una vez que lo encuentra lo elimina y reacomoda el arbol.
 */
nodo_abb_t* borrar_elemento(abb_comparador comparador,abb_liberar_elemento destructor,nodo_abb_t* nodo,void* elemento,int* estado){
	if(!nodo){
		(*estado)=ERROR;
		return NULL;
	}
	int resultado=comparador(elemento,nodo->elemento);
	if(resultado==CERO){
		return reacomodar_arbol(nodo,destructor,estado);
	}
	else if(resultado>CERO){
		nodo->derecha=borrar_elemento(comparador,destructor,nodo->derecha,elemento,estado);
	}
	else {
		nodo->izquierda=borrar_elemento(comparador,destructor,nodo->izquierda,elemento,estado);
	}

	return nodo;
}
int arbol_borrar(abb_t* arbol, void* elemento){
    if(!arbol){
		return ERROR;
	}
	int estado;
	arbol->nodo_raiz=borrar_elemento(arbol->comparador,arbol->destructor,arbol->nodo_raiz,elemento,&estado);
	return estado;
}
/* Recorre el arbol buscando  el elemento solicitado. Si no esta devuelve NULL. Usa el comparador del arbol.
 */
void* buscar_elemento(abb_comparador comparador,nodo_abb_t* nodo,void* elemento){
    if(!nodo){
        return NULL;
    }
    int resultado=comparador(elemento,nodo->elemento);
    if(resultado==CERO){
        return nodo->elemento;
    }
    else if(resultado>CERO){
        return buscar_elemento(comparador,nodo->derecha,elemento);
    }
    else{
        return buscar_elemento(comparador,nodo->izquierda,elemento);
    }
}
void* arbol_buscar(abb_t* arbol, void* elemento){
    if(!arbol){
        return NULL;
    }
    return buscar_elemento(arbol->comparador,arbol->nodo_raiz,elemento);
}
void* arbol_raiz(abb_t* arbol){
    if(!arbol || arbol->nodo_raiz==NULL){
        return NULL;
    }
    return arbol->nodo_raiz->elemento;
}
bool arbol_vacio(abb_t* arbol){
    if(!arbol){
        return true;
    }
    return arbol->nodo_raiz==NULL;
}
/* Recorre el arbol de manera inorden(IZQUIERDA-RAIZ-DERECHA).
 * Los elementos se guardan en un array ,se compara con la cantidad de elementos guardados.
 */
void recorrer_inorden(nodo_abb_t* nodo,void** array,size_t tamanio_array,size_t* cantidad_elementos_guardados){
	if(!nodo){
		return;
	}
	recorrer_inorden(nodo->izquierda,array,tamanio_array,cantidad_elementos_guardados);
	if((*cantidad_elementos_guardados)>=tamanio_array){
		return;
	}
	array[*cantidad_elementos_guardados]=nodo->elemento;
	(*cantidad_elementos_guardados)++;
	recorrer_inorden(nodo->derecha,array,tamanio_array,cantidad_elementos_guardados);
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    if(!arbol){
		return NO_EXISTE;
	}
	size_t cantidad_elementos_guardados=0;
	recorrer_inorden(arbol->nodo_raiz,array,tamanio_array,&cantidad_elementos_guardados);
	return cantidad_elementos_guardados;
}

/* Recorre el arbol de maner preorden(RAIZ-IZQUIERDA-DERECHA)
 * Los elementos se  guardan en un array , se compara con la cantidad de elementos guardados.
 */
void recorrer_preorden(nodo_abb_t* nodo,void** array,size_t tamanio_array,size_t* cantidad_elementos_guardados){
	if(!nodo){
		return;
	}
	if((*cantidad_elementos_guardados)>=tamanio_array){
		return;
	}
	array[*cantidad_elementos_guardados]=nodo->elemento;
	(*cantidad_elementos_guardados)++;
	recorrer_preorden(nodo->izquierda,array,tamanio_array,cantidad_elementos_guardados);
	recorrer_preorden(nodo->derecha,array,tamanio_array,cantidad_elementos_guardados);
}
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    if(!arbol){
		return NO_EXISTE;
	}
	size_t cantidad_elementos_guardados=0;
	recorrer_preorden(arbol->nodo_raiz,array,tamanio_array,&cantidad_elementos_guardados);
	return cantidad_elementos_guardados;
}
/* Recorre el arbol de manera postorden(IZQUIERDA-DERECHA-RAIZ).
 * Los elementos se guardan en un array, se compara con la cantidad de elementos guardados.
 */
void recorrer_postorden(nodo_abb_t* nodo,void** array,size_t tamanio_array,size_t* cantidad_elementos_guardados){
	if(!nodo){
		return;
	}
    recorrer_postorden(nodo->izquierda,array,tamanio_array,cantidad_elementos_guardados);
	recorrer_postorden(nodo->derecha,array,tamanio_array,cantidad_elementos_guardados);
	if((*cantidad_elementos_guardados)>=tamanio_array){
		return;
	}
	array[*cantidad_elementos_guardados]=nodo->elemento;
	(*cantidad_elementos_guardados)++;
}
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    if(!arbol){
		return NO_EXISTE;
	}
	size_t cantidad_elementos_guardados=0;
	recorrer_postorden(arbol->nodo_raiz,array,tamanio_array,&cantidad_elementos_guardados);
	return cantidad_elementos_guardados;
}

/* Recorre el arbol entero de manera postorden, va liberando la memoria que tenia cada nodo.
*/
void recorrer_arbol(nodo_abb_t* nodo,abb_liberar_elemento destructor){
    if(!nodo){
        return;
    }
    if(nodo->izquierda!=NULL){
        recorrer_arbol(nodo->izquierda,destructor);
    }
    if(nodo->derecha!=NULL){
        recorrer_arbol(nodo->derecha,destructor);
    }
    destruir_nodo(nodo,destructor);
}
void arbol_destruir(abb_t* arbol){
    if(!arbol){
        return;
    }
    recorrer_arbol(arbol->nodo_raiz,arbol->destructor);
    free(arbol);
}
/* Recorre el arbol de manera inorden hasta recorrerlo entero o que la funcion devuelva true.
 */
void recorrido_inorden_elemento(nodo_abb_t* nodo, bool (funcion)(void*, void*), void* extra,bool* estado, size_t* contador_inorden){
	if(!nodo){
		return;
	}
	if(*estado){
		return;
	}
	recorrido_inorden_elemento(nodo->izquierda,funcion,extra,estado, contador_inorden);
	if(*estado){
		return;
	}
	(*estado)=(*funcion)(nodo->elemento,extra);
	(*contador_inorden)++;
	recorrido_inorden_elemento(nodo->derecha,funcion,extra,estado, contador_inorden);	
}
/* Recorre el arbol de manera preorden hasta recorrerlo entero o que la funcion devuelva true.
 */
void recorrido_preorden_elemento(nodo_abb_t* nodo, bool (funcion)(void*, void*), void* extra,bool* estado, size_t* contador_preorden){
	if(!nodo){
		return;
	}
	if(*estado){
		return;
	}
	(*estado)=(*funcion)(nodo->elemento,extra);
	(*contador_preorden)++;
	recorrido_preorden_elemento(nodo->izquierda,funcion,extra,estado, contador_preorden);
	if(*estado){
		return;
	}
	recorrido_preorden_elemento(nodo->derecha,funcion,extra,estado, contador_preorden);
}
/* Recorre el arbol de manera postorden hasta recorrerlo entero o que la funcion devuelva true.
 */
void recorrido_postorden_elemento(nodo_abb_t* nodo, bool (funcion)(void*, void*), void* extra,bool* estado, size_t* contador_postorden ){
	if(!nodo){
		return;
	}
	if(*estado){
		return;
	}
	recorrido_postorden_elemento(nodo->izquierda,funcion,extra,estado, contador_postorden);
	if(*estado){
		return;
	}
	recorrido_postorden_elemento(nodo->derecha,funcion,extra,estado, contador_postorden);
	if(*estado){
		return;
	}
	(*estado)=(*funcion)(nodo->elemento,extra);
	(*contador_postorden)++;
}
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (funcion)(void*, void*), void* extra){
    if(!arbol || !funcion){
		return NO_EXISTE;
	}
    size_t contador=0;
    size_t contador_inorden=0;
    size_t contador_preorden=0;
    size_t contador_postorden=0;
	bool estado=false;
	if(recorrido==ABB_RECORRER_INORDEN){
		recorrido_inorden_elemento(arbol->nodo_raiz,funcion,extra,&estado, &contador_inorden);
        contador= contador_inorden;
	}
	else if(recorrido==ABB_RECORRER_PREORDEN){
		recorrido_preorden_elemento(arbol->nodo_raiz,funcion,extra,&estado, &contador_preorden);
        contador= contador_preorden;
	}
	else if(recorrido==ABB_RECORRER_POSTORDEN){
		recorrido_postorden_elemento(arbol->nodo_raiz,funcion,extra,&estado,&contador_postorden);
        contador=contador_postorden;
	}
    return contador;
}