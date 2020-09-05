/*
7) Escriba el .H de una biblioteca de funciones ISO C para números complejos. Incluya, al
menos, 4 funciones.
*/
#ifndef __COMPLEX_H
#define __COMPLEX_H

typedef struct complex{
    float re;
    float im;
}complex_t;


int complex_crear(complex_t* self, float parte_real, float parte_imaginaria);

int complex_destruir(complex_t* self);

float complex_modulo(const complex_t* self);

complex_t* complex_complemento(complex_t* self);

#endif