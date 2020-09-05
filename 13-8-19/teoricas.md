## 4) Explique qué se entiende por “compilación condicional”. Ejemplifique mediante código.

La compilacion condicional es una facilidad proporcionada por el preprocesador de C y C++ que permite incluir y excluir
segmentos de codigo en el proceso de compilacion en funcion de alguna condicion.

## 5) ¿Qué significa que una función es blocante?¿Cómo subsanaría esa limitación en término de
## mantener el programa ‘vivo’ ?

Las funciones bloqueantes son aquellas que pueden llegar a detener la ejecucion del programa 
debido a que la solicitud que deben completar puede no ser posible en el momento de hacer una llamada
a la misma (y que por ende no retornan ) 