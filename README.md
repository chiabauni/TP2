# Taller de Programación I [75.42] - TP2

---

Nombre: BAUNI Chiara

Padron: 102981

Cuatrimestre: 2C 2020

Link al repositorio: [https://github.com/chiabauni/TP2](https://github.com/chiabauni/TP2)

---

# Indice

1. Presentación del trabajo
    - Introducción
    - Descripción
2. Especificaciones provistas
    - Programa eBPF
    - Threads
    - Restricciones
    - Formato de Linea de Comandos
    - Salida
3. Modelo propuesto
    - Implementacion
    - Diseño final

---

# Presentación del trabajo

## Introducción

Este trabajo practico consiste en implementar una versión simplificada del verificador de programas eBPF el cual solo verificará la existencia o no de bucles de código y/o instrucciones sin ejecutar. Ademas el verificador deberá procesar archivos en paralelo implementando una serie de threads definidos por linea de comando.

## Descripción

Para implementar la detección de bucles e instrucciones sin ejecutar es necesario modelar el programa eBPF en un grafo. Para lograr esto la clave esta en detectar únicamente loas instrucciones *jumps*, los *ret* y las *etiquetas*. También se debe implementar un objeto como repositorio de los archivos a ser procesados y otro como repositorio de los resultados obtenidos, obligando así a que los hilos compartan estos dos objetos.

---

# Especificaciones provistas

## Programas eBPF

Los programas eBPF se componen de lineas en donde cada linea consta de una unica instruccion que puede o no ser prefijada por una etiqueta. En este caso en particular que vamos a implementar, solo nos vamos a concentrar en identificar las instrucciones que son jumps o ret y las lineas que tienen etiquetas. 

Una etiqueta es una palabra que puede tener letras y/o números y siempre van seguidas de un dos puntos ":". Asimismo habrá siempre un espacio entre la etiqueta, si existiese, y el resto de la instrucción.

Cada instrucción tiene un único comando u opcode al que le siguen cero o más argumentos. En el caso de haber más argumentos estos se separan por comas "," y un espacio. Ademas siempre hay al menos un espacio entre el comando y los argumentos y entre los argumentos.

Los opcodes correspondientes a los jumps o saltos son: *jmp, ja, jeq, jneq, jne, jlt, jle, jgt, jge, jset*. Hay tres modos de operación o formas de salto:

1. `<jmp-opcode> <etiqueta>` : el programa al ejecutar dicha instrucción salta a la instrucción etiquetada.
2. `<jmp-opcode> <arg>, <etiqueta>` : el programa evalúa el primer argumento. Si la evaluación es true saltan a la instrucción cuya etiqueta es el segundo argumento y si la evaluación es false no hay un salto y el programa continúa con la siguiente instrucción al jump.
3. `<jmp-opcode> <arg>, <etiqueta>, <etiqueta>` :  el programa evalúa el primer argumento. Si la evaluación es true saltan a la instrucción etiquetada con la primera etiqueta mientras que si es false
saltan a la segunda. 

El opcode correspondiente a la instrucción ret es: *ret*. Las instrucciones "ret" pueden tener cero o más argumentos y marcan el fin de un programa.

## Threads

El verificador deberá procesar los archivos en paralelo con una serie de threads definidos por línea de comandos.

Se debe implementar un objeto compartido que servirá de repositorio de los archivos a ser procesados. Cada hilo deberá pedir un archivo a este objeto, parsearlo, modelarlo y analizarlo para luego volver a pedir otro archivo y repetir la operación.

Por el otro lado, los hilos deberán guardar los resultados a medida que los vayan obteniendo en un único
objeto compartido. Cuando todos los archivos hayan sido procesados se imprimirán los resultados.

## Restricciones

La siguiente es una lista de restricciones técnicas exigidas:

- El sistema debe desarrollarse en ISO C++11.
- Está prohibido el uso de variables globales.
- Se garantiza que todos los programas eBPF serán siempre válidos sintácticamente para simplificar la implementación.
- Se garantiza que todas las etiquetas que aparezcan en una instrucción de salto estará definida. Esto es, existirá una única instrucción que tendrá dicha etiqueta.
- Se garantiza que si la linea no es un jump, ret o linea vacía si o si salta a la siguiente linea.
- Deberá haber un único objeto compartido que tenga los archivos y serán los hilos de procesamiento que le irán pidiendo un archivo a la vez para procesarlos.
- Deberá haber un único objeto compartido que guarde los resultados a medida que los hilos los
vayan generando. Al terminar todos los archivos, se imprimen de ahí los resultados por pantalla.

## Formato de Línea de Comandos

El programa se ejecutará pasando por línea de comandos recibiendo la cantidad de hilos y luego uno o más
archivos: `./tp <num hilos> <archivo> [<archivo>...]`

## Salida

El verificador deberá imprimir por pantalla el nombre de cada archivo procesado y un mensaje indicando los resultados
linea a linea, con la salida ordenada alfabéticamente.

1. **GOOD** → en el caso de no haberse encontrado ciclos ni instrucciones sin uso.
2. **FAIL: cycle detected** → en el caso de haberse detectado un ciclo
3. **FAIL: unused instructions detected** → en el caso de instrucciones sin uso. 

Si un programa eBPF tuviese ciclos e instrucciones sin uso, el verificador deberá imprimir solo el mensaje correspondiente al de los ciclos.

---

# Modelo propuesto

## Implementación

A la hora de la resolución del trabajo planteado, primero comencé a diseñar una solución para el problema pero sin implementar los threads. Es decir, crear un programa que parsee el texto, modele el grafo y finalmente obtenga los resultados esperados. Con este primer objetivo en mente cree las siguientes clases:

- **Reader**: contiene las funciones para parsear el texto. Primero hay una función findLabels que se encarga de recorrer todo el archivo en busca de las etiquetas y las guarda en un diccionario con su correspondiente numero de linea. Luego esta la función parseText que recorre nuevamente el archivo esta vez en busca de instrucciones jump y ret y se encarga de agregar las aristas correspondientes del grafo.
- **Graph**: contiene las funciones para crear y recorrer el grafo. Tiene la funcion addEdge() que permite crear una arista de un nodo hacia otro. Ademas tiene la función isCyclic() con la cual la detección de ciclos se reduce tan solo a una búsqueda DFS. Finalmente la función unusedInstruction() verifica si quedo algún nodo sin visitar, detectando así una instrucción no utilizada.

![imagen1.png]

Una vez que esta primera parte funciono correctamente, comencé con la implementación de los hilos. Para esto fue necesario crear las siguientes clases:

- **FilesToProcess**: esta clase cuenta con una Critical Section la cual se debe proteger ya que se trata de un recurso compartido por los hilos. Por este motivo el mecanismo utilizado para la protección en este TP son los mutex. En esta clase "monitor" la Critical Section esta compuesta por la función getFileNameIfEmpty() se encarga de primero chequear si la lista de nombres de archivos esta vacía y en caso de que no lo este le asigna a la variable fileName el nombre del archivo a procesar.
- **ProcessedFiles**: esta clase al igual que la anterior es otro "monitor", pero en este caso la Critical Section esta compuesta por dos funciones. La función addResult() recibe un resultado  y lo guarda en el vector de resultados. La función getResult(), es únicamente de lectura (igualmente esta protegida) y devuelve el vector de resultados.
- **Thread**: para lograr encapsulamiento y mayor legibilidad, generamos la clase Thread que se encarga de lanzar el método run() en un hilo, y de proporcionar la interfaz necesaria para la interacción con el hilo (poder hacer start al un hilo, o poder hacerle join).
- **Lock**:  para lograr encapsulamiento y mayor legibilidad, generamos la clase Lock, que se encarga de bloquear o desbloquear según corresponda un mutex.

Ademas una modificación importante hecha fue hacer que el objeto Reader sea un objeto activo. Los objetos activos son aquellos que corren en su propio hilo de ejecución. Esto se logra haciendo que su clase lance un thread, con un método al que llamaremos run() que se ejecutará en el hilo. Diremos entonces que todas las clases que hereden de Thread serán objetos activos.

## Modelo final

El diseño final consta de 6 clases con responsabilidades claras y un acoplamiento razonable. Los mismos se muestran a continuación:

![imagen2.png]
