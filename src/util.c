#include "util.h"
#include <string.h>
#include <stdbool.h>
const char BARRA_CERO= '\0';

size_t vtrlen(void* ptr){
    void** auxiliar= ptr;
    size_t contador=0;    
    if(auxiliar==NULL){
         return 0;
    }
    while(auxiliar[contador]!=NULL){
        contador++;   
    }
    return contador;  
}
void* vtradd(void* ptr, void* item){
    size_t tamanio= vtrlen(ptr);
    void** auxiliar = realloc(ptr, sizeof(item)*(tamanio+2));
    if(auxiliar==NULL){
        return NULL;
    }
    auxiliar[tamanio]=item;
    tamanio++;
    auxiliar[tamanio]=NULL;
    return auxiliar; 
}
void vtrfree(void* ptr){
    size_t tamanio= vtrlen(ptr);
    void** auxiliar=ptr;
    if(ptr==NULL){
        return ;
    }
    for(int i=0; i<tamanio;i++){
        if(auxiliar[i]!=NULL){
           free(auxiliar[i]);
        }  
    }
   free(auxiliar);
}
char** split(const char* str, char separador){
   size_t tamanio_str=0;
   size_t i=0;
   size_t j=0;
   size_t k=0;
   size_t posicion_separador=0;
   size_t tamanio_substr=0;
   size_t posicion_inicial=0;
   char* auxiliar=NULL;
   char** ptr=NULL;
   bool es_null= false ;
    if(str== NULL){
        return NULL;
    }
    tamanio_str= strlen(str);
    if(tamanio_str<=0){
        return NULL;
    }  
    while(i<= tamanio_str && !(es_null)){
        if((str[i]== separador) || i == tamanio_str ){
            posicion_separador=i;
            tamanio_substr= posicion_separador -posicion_inicial +1;
            auxiliar = calloc(  tamanio_substr, (sizeof(char)));
            if(!auxiliar){
                es_null= true;
            } 
            j=0;
            k= posicion_inicial;
        while(k<tamanio_str && str[k]!=separador && !(es_null)){
                auxiliar[j]=str[k];
                k++;
                j++;          
        }   
        if(auxiliar!=NULL){
            ptr=vtradd(ptr, auxiliar);
        }
        posicion_inicial=posicion_separador+1;  
        }      
        i++;
    }  
    return ptr;
}
char* fgets_alloc(FILE* archivo){
    size_t bytes_leidos=0;
    size_t tamanio= 512;
    char* buffer = malloc(tamanio);
    if(!buffer){
        return NULL;
    }
    while(fgets(buffer+bytes_leidos, 512  , archivo)){
        size_t leido= strlen(buffer+bytes_leidos);
        if(leido>0 && *(buffer+bytes_leidos+leido-1)== '\n'){
            return buffer;
        }else{
            char* auxiliar= realloc(buffer, tamanio*2);
            if(!auxiliar){
                return NULL;
            }
            buffer= auxiliar;
            tamanio*=2;
        }
        bytes_leidos+=leido;
    }
    if(bytes_leidos==0){
        free(buffer);
        return NULL;
    }
    return buffer; 
}
void fclosen(FILE* archivo){
    if(archivo){
        fclose(archivo);
    }
}