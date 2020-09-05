## 2) Explique qué son los métodos virtuales y para qué sirven. De un breve ejemplo donde su uso sea imprescindible.

Los metodos virtuales se utilizan, en un contexto de herencia, para distinguir de forma 
univoca que metodo sera llamado entre un metodo overriden en una clase hija y un 
metodo con el mismo nombre en su clase padre, cuando se hace una llamada polimorfica. 

Un ejemplo de uso de los metodos virtuales podria ser:

```C++
class Vehiculo{
    virtual void abrir_puerta(){
        puerta.abrir();
    }
};

class Bicicleta: public Vehiculo{
    void abrir_puerta() override{
        throw ExcepcionNoTienePuertas();
    }
}

void abrir_puerta(Vehiculo vehiculo){
    vehiculo.abrir_puerta();
}

Bicicleta bici = Bicicleta();
abrir_puerta(bici);
```

Si el metodo ```abrir_puerta``` no fuera virtual, no se lanzaria la excepcion ```ExcepcionNoTienePuertas``` (pues se ejecutaria la implementacion del metodo correspondiente a la clase base Vehiculo), que es el comportamiento esperado para la bicicleta.

## 3) Descrciba con exactitud cada uno de los siguientes:
### a) static int A=7;

Se trata de una variable de tipo entero signado, que ocupa 2 o 4 bytes
dependiendo de la arquitectura. Es de alcance local (porque esta declarada como static), por lo que reside en el Data Segment, y su valor es 7.

### b) extern char *(*B)[7];
Es un puntero a un array de 7 caracteres (es decir, desreferenciarlo 
devuelve la direccion de memoria del primer elemento del array), definido externo (es decir, su 
definicion esta en otro archivo).

### c) float **C;
Es un puntero a puntero a float. Desreferenciarlo devuelve un puntero
a float. 


## 5 ) ¿Cómo se logra que 2 threads accedan (lectura/escritura) a un mismo recurso compartido
## sin que se generen problemas de consistencia? Ejemplifique.

Para lograr que 2 threads accedan a un mismo recurso compartido sin problemas de consistencia, se utilizan mecanismos de sincronizacion de threads
como son los mutexes. Mediante el uso de mutexes, se protegen las llamadas secciones criticas de los recursos compartidos para garantizar que estas
se ejecuten de forma atomica, eliminando los potenciales problemas de consistencia. Por ejemplo:

```C++
void incrementar(int* a){
    static std::mutex m;
    m.lock();
    (*a)++;
    m.unlock();
}

void t_func(int* a){
    for(size_t i = 0;i<1000;i++){
        incrementar(a);
    }
}

int main(){
    int a = new int;
    *a = 0;

    std::thread t1(t_func,a);
    std::thread t2(t_func,a);
    t1.join();
    t2.join();
    std::cout << (*a) << std::endl;
}
```

## 6) Describa el concepto de loop de eventos (events loop) utilizado en programación orientada
## a eventos y, en particular, en entornos de interfaz gráfica (GUIs).

En la programacion orientada a eventos, el programa esta constantemente esperando que se generen nuevos eventos para despacharlos
a sus respectivos manejadores o handlers. El loop de eventos es el proceso de recorrer alguna estructura de eventos (como una cola), determinar
de que tipo de evento se trata, y despachar el evento a su respectivo manejador (de existir este).

En particular, en interfaces graficas, se maneja en el loop de eventos todos los eventos relacionados al input del usuario con la interfaz (clicks, botones
del teclado, ajustes de la ventana, etc). Cada uno de estos eventos tendra un manejador acorde; por ejemplo, presionar "F11" en el teclado podria tener un 
manejador que conmute el modo pantalla completa. Los handlers
para estos eventos son en general cortos y se encargan de proveerle interaccion al usuario. 

## 7) ¿Qué valor arroja sizeof(int)? Justifique .

sizeof(int) arroja un valor de 2 (bytes) o 4(bytes) dependiendo de la arquitectura para la cual se compile el codigo (es dependiente de la implementacion). En
sistemas modernos de 32 y 64 bits en general el resultado es 4 bytes, mientras que en sistemas mas viejos de 16 bits el resultado es 2 bytes.

## 8) ¿Qué significa que una función es blocante?¿Cómo subsanaría esa limitación en término de
## mantener el programa ‘vivo’ ?

Que una funcion sea "blocante" significa que la ejecucion del programa no continua hasta que esa funcion haya podido completarse. En particular, este 
concepto se utiliza en contextos de entrada-salida. Por ejemplo, las lecturas a disco son por defecto bloqueantes. Para subsanar esta limitacion, las 
llamadas a funciones bloqueantes deben hacerse en hilos de ejecucion separados al hilo de ejecucion principal. 