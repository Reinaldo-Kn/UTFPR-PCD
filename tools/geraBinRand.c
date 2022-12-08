#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char nome[28];
    int idade;
} reg;

int main(int argc, char *argv[]) {

    srand(time(NULL) + clock());
    if (argc != 3) {
        printf("%s [tamanho aprox. em bytes] [arquivo.bin]\n", argv[0]);
        return 1;
    }

    int tam;
    sscanf(argv[1], "%d", &tam);
    int regs = tam/sizeof(reg);
    reg r;
    FILE *f = fopen(argv[2], "w");
    for (int i=0;i<regs;i++) {
        for (int j=0;j<27;j++)
            r.nome[j] = rand()%26 + 'a';
        r.nome[27] = '\0';
        r.idade = rand();
        fwrite(&r, sizeof(reg), 1, f);
    }
    fclose(f);

    return 0;
}
