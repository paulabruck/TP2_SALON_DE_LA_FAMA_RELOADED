
*Un Readme.txt donde se expliquen todas las decisiones de diseño. Tenga en cuenta que la finalidad de este
TP es evaluar los conocimientos adquiridos durante la materia y como tal, debe explicar qué estructuras usa
para cada problema y por qué, como mı́nimo.

Bueno en este segundo trabajo practico como era una reforma del primer trabajo practico pude reutilizar funciones y archivos que 
junto con los TDA implementados sirvieron para el desarrollo de el mismo. Del tp 1 use los archivos de util.c y salon.c que me 
sirvio de referencia para las funciones de leer, agregar , guardar y destruir. Como estructura de este trabajo elegi usar un 
arbol para los entrenadores para asi al momento de insertarlos poder ordenarlos por nombre y poder mantenenrlos ordenados y ya que la complejidad de busqueda es menor. A 
su vez para cada uno de estos entrenadores elegi para almacenar el equipo de pokemones una lista. Una vez definida la estructura
comence a reformar leer salon , cambiando que luego de dividir la linea leida la insercion se produzca para los entrenadores en 
el arbol  para lo que cree una funcion de comparacion entre nombres para poder asi determinar como seria el orden y para 
insertar los pokemones una lista dentro de cada uno de los entrenadores. A su vez esta vez al momento de pensar en insertar 
teniamos que tener en consideracion que no se insertaran 2 entrenadores con el mismo nombre y que ningun entrenador tenga menos 
de 1 pokemon en su equipo. Para ello tuve que agregar las verificaciones correspondientes para que luego al momento de realizar
las pruebas estas funcionaran. En este proceso cree varias funciones definidas en entrenador.h para poder ir realizando cada 
una de las nuevas cuestiones a tener en cuenta y poder probar mejor las funciones.Una vez que logre que pasaran las pruebas
de leer realice la funcion de guardar archivo en la cual utilice funciones de entrenador.c . Luego una vez que probe esta funcion 
segui con agregar entrenador , en la cual lo unico que tuve que modificar fue que se insertara el entrenador en el arbol. 
Despues ya pase a las dos funciones nuevas del trabajo, en la de filtrar entrenadores lo que hice fue usar abb_recorrido_inorden
para poder asi recorrer el arbol y guardarme un array con estos para luego ir comparando si cada uno cumple con las caracteristicas
solicitadas por la funcion y en base a eso devolver la lista con los enternadores que corresponde. Una vez terminada esa funcion
pase a la ultima parte del trabajo que fue la ejecutar comandos. Para los comandos lo que hice fue crear una estructura comando
e inclui en mi estructura salon una tabla de hash para asi almacenar cada uno de los posibles comando con su funcion a realizar.
Me parecio que un hash era lo mas adecuado por su complejidad de busqueda de O(1) y porque no iba a estar realizando insercciones , borrando,
sino que la incialicaba en salon leer y listo . Cada comando como lo dice su estructura tiene un nombre de comando
y una funcion a ejecutar. Cada una de estas funciones devolvia un string a liberar por el usuario y en ese string lo que habia 
eran registros segun el comando. Tambien cree uan funcion auxiliar que se encargar de procesar el comando recibido en salon ejecutar
, es decir que divida el comando recibido para poder asi ver a que comando corresponde y ver sus argumentos para saber que subtipo
de comando es. Para el comando ENTRENADORES hice la funcion listar_entrenadores que tenia 3 posibilidades. Una era que le manden 
el comando ENTRENADORES solo, sin argumentos, y en ese caso lo que hacia era devolver un string con todos los entrenadores y sus victorias separados
cada entrenador por un \n . Otra de las opciones era mandarle el comando ENTRENADORES:victorias,<algun_numero> en ese caso lo 
que hacia la funcion era devolver todos los entrenadores que tenian esa cantidad de victorias. Y la tercera opcion era que 
reciba el comando ENTRENADORES:pokemones,<nombre> que al pasarle el nombre de un pokemon te decia que entrenadores lo tenian en
su equipo. Despues estaba el comando REGLAS que devolvia 5 reglas de combate de las cuales dos venian en la consigna del tp y 
las otras 3 las teniamos que crear nosotros. Yo elegi crear las reglas de INTUITIVO ( el ganador era aquel que poseia mayor 
inteligencia ), PRODUCTIVO(el ganador era el que tenia mayor velocidad ) y la ultima regla la de combate PEREZOSO(el ganador 
era el pokemon con menos fuerza). Despues teniamos comando de AGREGAR y de QUITAR para agregar o quitar pokemones de un equipo
estos comando devolvian OK si se habia podido relizar la operacion. Otro comando era el de GUARDAR que lo que hacia era usar la
funcion de salon_guardar que habiamos hecho y nos permitia guardar un salon en nuevo archivo- Y el ultimo comando que era el
mas importante de todos era el de COMPARAR que lo que hacia era que tomba lo dos nombres de entrenadores que uno le pasaba y 
la regla de combate elegida y devolvia un string con el resultado de batalla segun la regla y la formula que hay detras de esta.
Para todo esto realice varias pruebas pero tambien probe mucho con el server que nos pasaron, para ver si iba funcionando bien 
sobretodo la parte de los comandos.
