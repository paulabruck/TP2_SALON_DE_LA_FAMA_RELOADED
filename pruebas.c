
#include "pa2mm.h"
#include "src/salon.h"
#include <string.h>


void dadoUnString_SiQuieroCrearUnEntrenador_PuedoHacerlo(){
	char* entrenador_prueba[2]={"entrenador1" ,"1"};
	entrenador_t* entrenador=NULL;
	pa2m_afirmar((entrenador=crear_entrenador(entrenador, entrenador_prueba)), "Se creo un entrenador correctamente.");
	destructor_entrenadores(entrenador);

	char* entrenador_prueba1[2]={"entrenador2" ,""};
	pa2m_afirmar((entrenador=crear_entrenador(entrenador, entrenador_prueba1)), "Se creo un entrenador sin victorias correctamente.");
	
	pokemon_t* pokemon=NULL;
	char* pokemon_prueba_[6]={"Pikachu" ,"1", "1", "1", "1", "1"};
	char* pokemon_prueba1[6]={"Charizard" ,"2", "2", "2", "2", "2"};
	char* pokemon_prueba2[6]={"Bulbasaur" ,"3", "3", "3", "3", "3"};
	char* pokemon_prueba3[6]={"Squirtle" ,"4", "4", "4", "4", "4"};

	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba_)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego un pokemon a un entrenador de manera correcta.");
	pa2m_afirmar(cantidad_pokemones(entrenador)==1, "La cantidad de pokemones en el equipo del entrenador es la correcta.");
	
	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba1)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego otro pokemon a un entrenador de manera correcta.");
	pa2m_afirmar(cantidad_pokemones(entrenador)==2, "La cantidad de pokemones en el equipo del entrenador es la correcta.");
	
	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba2)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego otro pokemon a un entrenador de manera correcta.");
	pa2m_afirmar(cantidad_pokemones(entrenador)==3, "La cantidad de pokemones en el equipo del entrenador es la correcta.");
	
	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba3)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego un pokemon a un entrenador de manera correcta.");
	pa2m_afirmar(cantidad_pokemones(entrenador)==4, "La cantidad de pokemones en el equipo del entrenador es la correcta.");
	
	destructor_entrenadores(entrenador);
}

void dadoUnSalonInexistente_SiQuieroLeerlo_NOPuedoHacerlo(){
	salon_t* salon=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"hola.txt"))==NULL, "No se puede leer un archivo que no existe. ");
	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_invalido.txt"))==NULL, "Si un entrenador no tiene pokemones no se puede cargar un salon.");
}
void dadoUnSalon_SiQuieroLeerlo_PuedoHacerlo(){
	salon_t* salon=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"probando2.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	
	salon_destruir(salon);
}
void dadoUnSalonInexistente_SiQuieroGuardarloEnUnArchivo_NoPuedoHacerlo(){
	salon_t* salon=NULL;
	pa2m_afirmar(salon_guardar_archivo(salon, (char*)"nuevo.txt")==-1, "Dado un salon nulo no puedo guardarlo en un archivo.");
	pa2m_afirmar((salon=salon_leer_archivo((char*)"probando2.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	pa2m_afirmar(salon_guardar_archivo(salon, (char*)"")==-1, "Dado un nombre de archivo nulo no puedo guardar el salon.");
	salon_destruir(salon);
}
void dadoUnSalon_SiQuieroGuardarloEnUnArchivo_PuedoHacerlo(){
	salon_t* salon=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"probando2.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	pa2m_afirmar(salon_guardar_archivo(salon, (char*)"nuevo.txt"), "Dado un salon valido puedo guardarlo en un archivo nuevo.");
	salon_destruir(salon);
	salon_t* salon1=NULL;
	pa2m_afirmar((salon1=salon_leer_archivo((char*)"nuevo.txt"))!=NULL, "Se puede leer correctamente el archivo recien escrito.");
	
	salon_destruir(salon1);
} 
void dadoUnSalonInexistente_SiQuieroAgregarUnEntrenador_NoPuedoHacerlo(){
	salon_t* salon=NULL;
	entrenador_t* entrenador=NULL;
	pa2m_afirmar((salon_agregar_entrenador(salon,entrenador))==NULL, "No puedo agregar un entrenador en un salon nulo.");
	pa2m_afirmar((salon=salon_leer_archivo((char*)"probando2.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	pa2m_afirmar((salon_agregar_entrenador(salon,entrenador))==NULL, "No puedo agregar un entrenador nulo.");
	
	char* entrenador_prueba_[2]={"entrenador_nuevo" ,"1"};
	pa2m_afirmar((entrenador=crear_entrenador(entrenador, entrenador_prueba_)), "Se creo un entrenador correctamente.");
	pa2m_afirmar((salon_agregar_entrenador(salon,entrenador))==NULL, "No puedo agregar un entrenador sin pokemones.");

	destructor_entrenadores(entrenador);
	salon_destruir(salon);

}
void dadoUnSalon_SiQuieroAgregarUnEntrenador_PuedoHacerlo(){
	salon_t* salon=NULL;
	entrenador_t* entrenador=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"probando.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* entrenador_prueba_[2]={"entrenador_nuevo" ,"1"};
	pa2m_afirmar((entrenador=crear_entrenador(entrenador, entrenador_prueba_)), "Se creo un entrenador correctamente.");
	pokemon_t* pokemon=NULL;
	char* pokemon_prueba_[6]={"Pikachu" ,"1", "1", "1", "1", "1"};
	char* pokemon_prueba1[6]={"Charizard" ,"2", "2", "2", "2", "2"};
	char* pokemon_prueba2[6]={"Bulbasaur" ,"3", "3", "3", "3", "3"};
	char* pokemon_prueba3[6]={"Squirtle" ,"4", "4", "4", "4", "4"};

	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba_)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego un pokemon a un entrenador de manera correcta.");

	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba1)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego un pokemon a un entrenador de manera correcta.");
	
	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba2)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego un pokemon a un entrenador de manera correcta.");

	pa2m_afirmar((pokemon= crear_pokemon(pokemon, pokemon_prueba3)), "Se creo un pokemon de manera correcta.");
	pa2m_afirmar(agregar_pokemon(entrenador,pokemon)==0, "Se agrego un pokemon a un entrenador de manera correcta.");

	pa2m_afirmar(cantidad_pokemones(entrenador)==4, "La cantidad de pokemones en el equipo del entrenador es la correcta.");
	pa2m_afirmar(salon_agregar_entrenador(salon, entrenador), "Puedo agregar un entrenador con 4 pokemones de manera correcta.");
	pa2m_afirmar(salon_guardar_archivo(salon, "otraprueba.txt"), "Puedo guardar correctamente el salon con el nuevo entrenador.");
	salon_destruir(salon);
}
bool funcion_prueba(entrenador_t* entrenador, void* victorias){
	return true;
}
void DadoUnAbbDeEntrenadores_SiQuieroFiltrar_NoPuedoHacerlo(){
	salon_t* salon=NULL;
	pa2m_afirmar(salon_filtrar_entrenadores(salon, funcion_prueba, NULL)==NULL, "Dado un salon nulo no se pueden filtrar entrenadores.");
	pa2m_afirmar((salon=salon_leer_archivo((char*)"casa.txt"))!=NULL, "Puedo leer el archivo de manera correcta. ");
	pa2m_afirmar(salon_filtrar_entrenadores(salon, NULL, NULL)==NULL, "Dado una funcion nula no se pueden filtrar entrenadores.");
	
	salon_destruir(salon);
}
void DadoUnAbbDeEntrenadores_SiQuieroFiltrar_PuedoHacerlo(){
	salon_t* salon=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"casa.txt"))!=NULL, "Puedo leer el archivo de manera correcta. ");
	lista_t* lista=NULL;
	pa2m_afirmar((lista= salon_filtrar_entrenadores(salon, funcion_prueba, NULL))!=NULL, "Se filtran los entrenadores de manera correcta.");
	pa2m_afirmar(lista_elementos(lista)==3, "La cantidad de entrenadores filtrados es la correcta.");
	pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista,0),"Entrenador1")==0, "El entrenador en la lista es el que corresponde.");
	pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista,1),"Entrenador2")==0, "El entrenador en la lista es el que corresponde.");
	pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista,2),"Entrenador3")==0, "El entrenador en la lista es el que corresponde.");
	
	lista_destruir(lista);
	salon_destruir(salon);
}
void dadoUnSalonInexistente_AlPasarleUnComando_MeDevuelveError(){
	salon_t* salon=NULL;
	pa2m_afirmar(salon_ejecutar_comando(salon, (char*)"ENTRENADORES")==NULL, "Dado un salon nulo no puedo ejecutar comandos.");
	pa2m_afirmar((salon=salon_leer_archivo((char*)"casa.txt"))!=NULL, "Puedo leer el archivo de manera correcta. ");
	pa2m_afirmar(salon_ejecutar_comando(salon, (char*)"")==NULL, "Dado un comando nulo no puedo ejecutar comandos.");

	salon_destruir(salon);
}
void dadoUnSalon_AlPasarleUnComandoENTRENADORES_EjecutaElComando(){
	salon_t* salon=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* string=salon_ejecutar_comando(salon, (char*) "ENTRENADORES");
	pa2m_afirmar(string!=NULL, "Dado el comando ENTRENADORES puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string,"Azul,2\nJuan,1\nYony,3\n")==0, "El string devuelto es el esperado.");
	free(string);
	
	salon_destruir(salon);
}
void DadoUnSalon_AlPAsarleUnComandoENTRENADORESSegunVictorias_EjecutaElCOmando(){
	salon_t* salon=NULL;
	
	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* string=salon_ejecutar_comando(salon, (char*) "ENTRENADORES:victorias,2");
	pa2m_afirmar(string!=NULL, "Dado el comando ENTRENADORES:victorias,2 puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string,"Azul\nYony\n")==0, "El string devuelto es el esperado.");
	free(string);
	char* string2 = salon_ejecutar_comando(salon,"ENTRENADORES:victorias");
    pa2m_afirmar(string2 == NULL,"Al tratar de ejecutar el comando ENTRENADORES:VICTORIAS sin numero de victorias, no se ejecuta");
	
	salon_destruir(salon);
}
void DadoUnSalon_AlPAsarleUnComandoENTRENADORESSegunPokemones_EjecutaElCOmando(){
	salon_t* salon=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* string=salon_ejecutar_comando(salon, (char*) "ENTRENADORES:pokemon,Pikachu");
	pa2m_afirmar(string!=NULL, "Dado el comando ENTRENADORES:pokemon,Pikachu puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string,"Azul\nJuan\nYony\n")==0, "El string devuelto es el esperado.");
	free(string);

	char* string1=salon_ejecutar_comando(salon, (char*) "ENTRENADORES:pokemon,Charizard");
	pa2m_afirmar(string1!=NULL, "Dado el comando ENTRENADORES:pokemon,Charizard puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string1,"Juan\nYony\n")==0, "El string devuelto es el esperado.");
	
	free(string1);
	salon_destruir(salon);
}
void DadoUnSalon_AlPAsarleUnComandoEQUIPO_EjecutaElCOmando(){
	salon_t* salon=NULL;

	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	
	char* string=salon_ejecutar_comando(salon, (char*) "EQUIPO:Azul");
	pa2m_afirmar(string!=NULL, "Dado el comando EQUIPO:Azul puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string,"Pikachu,1,1,1,1,1\nBulbasaur,3,3,3,3,3\n")==0, "El string devuelto es el esperado.");
	free(string);
	
	salon_destruir(salon);
	salon_t* salon1=NULL;
	pa2m_afirmar((salon1=salon_leer_archivo((char*)"salon_2e_2p.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	
	char* string1=salon_ejecutar_comando(salon1, (char*) "EQUIPO:entrenador1");
	pa2m_afirmar(string1!=NULL, "Dado el comando EQUIPO:entrenador1 puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string1,"pokemon1,1,2,3,4,5\npokemon2,5,4,3,2,1\n")==0, "El string devuelto es el esperado.");
	
	free(string1);
	
	char* string2=salon_ejecutar_comando(salon1, (char*) "EQUIPO");
	pa2m_afirmar(string2==NULL, "Dado el comando EQUIPO no  puedo ejecutar el comando.");
	
	salon_destruir(salon1);

}
void DadoUnSalon_AlPAsarleUnComandoREGLAS_EjecutaElCOmando(){
	salon_t* salon=NULL;

	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* string1=salon_ejecutar_comando(salon, (char*) "REGLAS");
	pa2m_afirmar(string1!=NULL, "Dado el comando REGLAS puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string1,"CLASICO, combate clasico\nMODERNO, combate moderno\nPEREZOSO, El ganador sera aquel pokemon con menos fuerza\nPRODUCTIVO, El ganador sera aquel pokemon con mas velocidad\nINTUITIVO, El ganador sera el pokemon mas inteligente\n") == 0,"El string devuelto es el correcto");
	
	free(string1);
	salon_destruir(salon);
}
void DadoUnSalon_AlPAsarleUnComandoCOMPARAR_EjecutaElCOmando(){
	salon_t* salon=NULL;

	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* string1=salon_ejecutar_comando(salon, (char*) "COMPARAR:Juan,Yony,hola");
	pa2m_afirmar(string1==NULL, "Dado el comando COMPARAR:Juan,Yony,hola no puedo ejecutar el comando.");

	char* string2=salon_ejecutar_comando(salon, (char*) "COMPARAR:Juan,Yony,CLASICO");
	pa2m_afirmar(string2!=NULL, "Dado el comando COMPARAR:Juan,Yony,CLASICO puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string2,"1\n2\n1\n2\n1\n") == 0,"El string devuelto es correcto");
	
	free(string2);

	char* string3 = salon_ejecutar_comando(salon,"COMPARAR:Juan,Yony,MODERNO,hola");
	pa2m_afirmar(string3==NULL, "Dado el comando COMPARAR:Juan,Yony,MODERNO,hola no puedo ejecutar el comando.");

	salon_destruir(salon);
}
void DadoUnSalon_AlPAsarleUnComandoAGREGAR_EjecutaElCOmando(){
	salon_t* salon=NULL;
	char* string=salon_ejecutar_comando(salon, (char*) "AGREGAR_POKEMON:Azul,Roman,1,2,3,4,5");
	pa2m_afirmar(string==NULL, "Dado el comando AGREGAR_POKEMON:Azul,Roman,1,2,3,4,5 y un salon nulo no puedo ejecutar el comando.");

	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* string1=salon_ejecutar_comando(salon, (char*) "AGREGAR_POKEMON:hola,chau,1,2,3,4,5");
	pa2m_afirmar(string1==NULL, "Dado el comando AGREGAR_POKEMON:hola,chau,1,2,3,4,5 no puedo ejecutar el comando.");

	char* string2=salon_ejecutar_comando(salon, (char*) "AGREGAR_POKEMON:Azul,Roman,1,2,3,4,5");
	pa2m_afirmar(string2!=NULL, "Dado el comando AGREGAR_POKEMON:Azul,Roman,1,2,3,4,5 puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string2,"OK") == 0,"El string devuelto es correcto");
	
	free(string2);
	
	char* string3=salon_ejecutar_comando(salon, (char*) "EQUIPO:Azul");
	pa2m_afirmar(string3!=NULL, "Dado el comando EQUIPO:Azul puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string3,"Pikachu,1,1,1,1,1\nBulbasaur,3,3,3,3,3\nRoman,1,2,3,4,5\n") == 0,"El string devuelto es correcto");
	
	free(string3);

	salon_destruir(salon);
}
void DadoUnSalon_AlPAsarleUnComandoQUITAR_EjecutaElCOmando(){
	salon_t* salon=NULL;
	char* string=salon_ejecutar_comando(salon, (char*) "QUITAR_POKEMON:hola,como,1,2,3,4,5");
	pa2m_afirmar(string==NULL, "Dado el comando QUITAR_POKEMON:hola,como,1,2,3,4,5 y un salon nulo no puedo ejecutar el comando.");
	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");

	char* string2=salon_ejecutar_comando(salon, (char*) "QUITAR_POKEMON:Azul,Pikachu");
	pa2m_afirmar(string2!=NULL, "Dado el comando QUITAR_POKEMON:Azul,Pikachu puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string2,"OK") == 0,"El string devuelto es correcto");
	
	free(string2);

	char* string3=salon_ejecutar_comando(salon, (char*) "EQUIPO:Azul");
	pa2m_afirmar(string3!=NULL, "Dado el comando EQUIPO:Azul puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string3,"Bulbasaur,3,3,3,3,3\n") == 0,"El string devuelto es correcto");

	free(string3);

	char* string1=salon_ejecutar_comando(salon, (char*) "QUITAR_POKEMON:Azul,Bulbasaur");
	pa2m_afirmar(string1==NULL, "Dado el comando QUITAR_POKEMON:Azul,Bulbasaur no puedo ejecutar el comando.");

	salon_destruir(salon);
}
void DadoUnSalon_AlPAsarleUnComandoGUARDAR_EjecutaElCOmando(){
	salon_t* salon=NULL;
	pa2m_afirmar((salon=salon_leer_archivo((char*)"salon_3e.txt"))!=NULL, "Lee el archivo indicado y lo carga a un salon correctamente. ");
	char* string=salon_ejecutar_comando(salon, (char*) "GUARDAR:pruebacomandos.txt");
	pa2m_afirmar(string!=NULL, "Dado el comando GUARDAR:pruebacomandos.txt puedo ejecutar el comando.");
	pa2m_afirmar(strcmp(string,"OK") == 0,"El string devuelto es correcto");
	free(string);

	char* string1=salon_ejecutar_comando(salon, (char*) "GUARDAR");
	pa2m_afirmar(string1==NULL, "Dado el comando GUARDAR no  puedo ejecutar el comando.");

	salon_destruir(salon);
}

int main(){

	pa2m_nuevo_grupo("Pruebas de entrenadores");
	dadoUnString_SiQuieroCrearUnEntrenador_PuedoHacerlo();

	pa2m_nuevo_grupo("Pruebas de leer salon");
	dadoUnSalonInexistente_SiQuieroLeerlo_NOPuedoHacerlo();
	dadoUnSalon_SiQuieroLeerlo_PuedoHacerlo();

	pa2m_nuevo_grupo("Pruebas de guardar salon");
	dadoUnSalonInexistente_SiQuieroGuardarloEnUnArchivo_NoPuedoHacerlo();
	dadoUnSalon_SiQuieroGuardarloEnUnArchivo_PuedoHacerlo();
	
	pa2m_nuevo_grupo("Pruebas de agregar entrenador");
	dadoUnSalonInexistente_SiQuieroAgregarUnEntrenador_NoPuedoHacerlo();
	dadoUnSalon_SiQuieroAgregarUnEntrenador_PuedoHacerlo();

	pa2m_nuevo_grupo("Pruebas de filtrar entrenadores");
	DadoUnAbbDeEntrenadores_SiQuieroFiltrar_NoPuedoHacerlo();
	DadoUnAbbDeEntrenadores_SiQuieroFiltrar_PuedoHacerlo();

    pa2m_nuevo_grupo("Pruebas de comandos");
	dadoUnSalonInexistente_AlPasarleUnComando_MeDevuelveError();
	dadoUnSalon_AlPasarleUnComandoENTRENADORES_EjecutaElComando();
	DadoUnSalon_AlPAsarleUnComandoENTRENADORESSegunVictorias_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoENTRENADORESSegunPokemones_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoEQUIPO_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoREGLAS_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoCOMPARAR_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoAGREGAR_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoQUITAR_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoGUARDAR_EjecutaElCOmando();
	DadoUnSalon_AlPAsarleUnComandoGUARDAR_EjecutaElCOmando();

    return pa2m_mostrar_reporte();
}
