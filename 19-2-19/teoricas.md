## 1) Explique qué es y para qué sirve un constructor de copia en C++. a) Indique cómo se
## comporta el sistema si éste no es definido por el desarrollador; b) Explique al menos una
## estrategia para evitar que una clase particular sea copiable; c) Indique qué diferencia existe
## entre un constructor de copia y uno move.

Un constructor por copia es un constructor especial, que toma por argumento otra instancia de la clase que se 
esta construyendo, y que construye una copia de dicha instancia tomada por argumento. 

Si no se define un constructor por copia, se utiliza un constructor por copia default, que consiste en hacer una
shallow copy (es decir, copia byte a byte cada uno de los campos). 

Para evitar que una clase sea copiable, se puede anular su constructor por copia y su asignador por copia, mediante
la sintaxis 

```C++
clase(const clase& other) = delete;

clase& operator=(const clase& other) = delete;
```

Los constructores por movimiento, a diferencia de los constructores por copia, en lugar de realizar una copia 
de la informacion de una clase, toman posesion de los valores de la clase como propios (esto es, copian los punteros 
manteniendo lo apuntado intacto, y dejan la instancia a partir de la cual se hizo el movimiento inutilizable).

## 3) Describa con exactitud las siguientes declaraciones/definiciones globales:
### 1. void (*F)(int i);
Se trata de un puntero a funcion cuyo tipo de valor de retorno es void, y que recibe un unico argumento de tipo int.

---
### 2. static void B(float a, float b){}
Se trata de una funcion de tipo void, cuyo alcance esta limitado al archivo donde esta declarada, y que recibe dos argumentos
de tipo float.

---
### 3. int *(*C)[5];
Se trata de un puntero a un array de 5 punteros a int (es decir, desreferenciarlo devuelve la direccion de memoria 
donde se encuentra el primer puntero.)


## 6) ¿Qué es una macro de C? Describa las buenas prácticas para su definición y ejemplifique.

Una macro de C es un segmento de codigo que es resuelta por el preprocesador en tiempo de compilacion (y que resulta en 
una constante, o en un fragmento de codigo compilable). Es en general buena practica utilizar macros para 
aritmetica de constantes, especialmente si esta se repite mucho en el codigo. Por ejemplo, digamos que se requiere 
obtener los 12 bits mas significativos en enteros de 4 bytes. En lugar de hacer ```entero >> 20``` cada vez que 
se lo necesita, se puede definir una macro ```#define MSB(integer) (integer >> 20)```, y luego realizar las llamadas
```MSB(entero)``` cada vez que se lo necesita.


## 8) Describa el proceso de transformación de código fuente a un ejecutable. Precise las etapas,
## las tareas desarrolladas y los tipos de error generados en cada una de ellas.

El proceso de transformacion de codigo fuente a un ejecutable, tambien conocido como proceso de compilacion, consta de las siguientes etapas: 

1) Preprocesamiento y expansion de macros. En esta etapa, se expanden los archivos incluidos mediante #include, y se expanden los macros por sus
expresiones resultantes. Tambien se reemplazan las constantes por sus respectivos valores en el codigo. 

2) Compilado. En esta etapa, se convierte el codigo C a codigo Assembly adecuado para la arquitectura hacia la cual se esta compilando. Es en esta etapa 
donde surgen la mayoria de los errores comunes: Errores de sintaxis, simbolos no encontrados. 

3) Ensamblado. En este proceso, se convierten una por una las instrucciones assembly generadas en la etapa anterior en codigo de maquina. 

4) Linkeado (o enlazado). En esta etapa finalmente se enlazan los codigos objeto de cada uno de los modulos compilados en nuestro programa. En el caso del 
linkeado estatico, todo el codigo maquina es vinculado en un mismo archivo ejecutable. En caso de linkeado dinamico, simplemente se agrega el nombre
del modulo que se desea linkear en la tabla de simbolos del ejecutable. Este proceso puede fallar si uno de los modulos que se desea linkear no se encuentra 
en el directorio donde se lo busca. 

## 9) ¿Qué ventaja ofrece un lock raii frente al tradicional lock/unlock ?

La ventaja de un lock RAII, ademas de las ventajas generales de RAII (es decir, que los recursos se liberan automaticamente al salirse de scope), es que no es 
necesario explicitar el unlock. Este sucede de forma automatica al salirse de scope el lock (en su destructor), lo cual salva muchos errores que pueden producirse
al olvidarse un unlock.