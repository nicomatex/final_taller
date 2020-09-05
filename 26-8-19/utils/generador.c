// includes
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escribir un programa ISO C que procese el archivo "nros_2bytes_bigendian.dat"
 * sobre sí mismo, eliminando los número múltiplos de 7. */

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "no se pudo crear el archivo\n");
        exit(1);
    }

    uint16_t val;
    val = htons(1);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(14);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(5);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(7);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(8);
    fwrite(&val, sizeof(val), 1, fp);

    fclose(fp);
}

int main(int argc, char* argv[]) {
    const char* filename = "nros_2bytes_bigendian.dat";
    armar_archivo(filename);

    return 0;
}