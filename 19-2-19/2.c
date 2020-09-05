/*
2) Escriba una función ISO C llamada Replicar que reciba 1 cadena (S), dos índices (I1 e I2) y
una cantidad (Q). La función debe retornar una copia de S salvo los caracteres que se
encuentran entre los índices I1 e I2 que serán duplicados Q veces.
Ej. replicar(“Hola”, 1, 2, 3) retorna “Hololola”.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* replicar(char* s, size_t i1, size_t i2, size_t q){
    size_t final_size = strlen(s) + 1;
    final_size += (q - 1) * (i2 - i1 + 1);

    char* output = malloc(final_size * sizeof(char));
    memset(output,0,final_size*sizeof(char));
    for(size_t i = 0;i<i1;i++){
        output[i] = s[i];
    }

    size_t output_i;
    for(size_t i = 0;i < q;i++){
        for(size_t j = i1;j <= i2;j++){
            output_i = (i2 - i1 + 1)*i + j;
            output[output_i] = s[j];
        }
    }

    size_t original_size = strlen(s);
    for(size_t i = i2 + 1;i<original_size;i++){
        output[++output_i] = s[i];
    }
    return output;
}

int main(void){
    char str[] = "hola";
    char* output = replicar(str,1,2,3);
    printf("%s\n",output);
    return 0;
}