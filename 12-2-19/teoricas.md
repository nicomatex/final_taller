## 1) ¿Qué es un functor? Ejemplifique.

Un functor es una clase que sobrecarga el operador (), permitiendo que sus instancias sean llamadas 
como si fueran funciones, teniendo algun comportamiento en particular. Por ejemplo:

```C++
class Sumador{
    public:
        int operator()(int a, int b);
        float operator()(float a, float b);
};


int main(){
    Sumador suma;
    int resultado = suma(12,3);
}
```



## 2) Explique qué es cada uno de los siguientes, haciendo referencia a su inicialización, su
## comportamiento y el area de memoria donde residen:

### a) Una variable global static.
Las variables globales static son variables cuyo alcance esta limitado al archivo donde estan definidas, dado que
no es exportada al enlazador. Pueden ser inicializadas con un valor por default por el compilador en tiempo de 
compilacion, de no especificarse un valor de inicializacion. Residen en el Data Segment del programa.

### b) Una variable local.
Las variables locales son aquellas variables locales al scope de una funcion. Si no son inicializadas con un valor
especifico, conteneran basura correspondiente a lo que sea que hubiera en el area de memoria que se reserva para ellas. 
Residen en el Stack Segment (y en particular dentro del stack frame de la funcion a la que pertenecen).

### c) Un atributo de clase static.
Los atributos de clase static pueden ser inicializados de forma inline en la declaracion de la clase, o bien 
en metodos estaticos de la clase  asi como tambien en metodos de instancia de clase. Al igual
que las variables globales static, se pueden inicializar con una constante en tiempo de compilacion. Su 
visibilidad esta restringida a la clase que la define, y en caso de ser publica, es accesible 
desde otros archivos (porque se exporta al enlazador).

## 5) ¿Qué es la compilación condicional? En qué etapa del proceso de transformación de
## código se resuelve. Ejemplifique mediante código C, dando un caso de uso útil.

La compilacion condicional es una utilidad que provee el preprocesador de C, y permite incluir ciertas secciones de codigo
en el proceso del compilador dependiendo de alguna condicion. Esto se resuelve en tiempo de preprocesado. Un ejemplo
posible es:

```C
#ifdef SUMAS_GRANDES
    long suma(long a, long b){
        return a+b;
    }
#else
    int suma(int a, int b){
        return a+b;
    }
#endif
```

## 7) ¿Por qué las librerías que usan Templates se publican con todo el código fuente y no como
## un .h y .o/.obj?.

Porque las templates no se traducen a codigo objeto de forma directa, sino que, en el momento de compilacion, el 
compilador determina para que tipos debe generar clases completas a partir de la template. Para generar estas clases concretas, 
necesita saber la implementacion completa (es decir, las templates se resuelven en tiempo de compilacion y no 
en tiempo de enlazado).


## 8) ¿Qué significa la palabra virtual antepuesta a un método de una clase?¿Qué cambios genera
## a nivel compilación y al momento de ejecución?

La palabra virtual antepuesta a un metodo de un clase significa que, en caso de existir una clase hija que 
sobreescribe ese metodo, a la hora de llamar el metodo de forma polimorfica en una instancia de la clase hija, se 
llamara en efecto a la implementacion de la clase hija y no a la implementacion de la clase padre. 
A nivel compilacion, esto genera en el codigo objeto una tabla de metodos virtuales para cada objeto (VTable) que facilita
el dynamic binding (el proceso mediante el cual se determina en tiempo de ejecucion cual metodo debe ser llamado). Sin 
la keyword virtual, el compilador sabe en tiempo de compilacion que metodo va a ser llamado (static binding). Cuando
se introduce la keyword, el compilador ya no tiene esta informacion, y debe recurrir a la VTable para resolver las
llamadas a este tipo de metodos en tiempo de ejecucion.
