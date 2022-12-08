#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[28];
    int idade;
} reg;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("%s [arquivo.txt] [arquivo.bin]\n", argv[0]);
        return 1;
    }

    FILE *ftxt = fopen(argv[1], "r");
    FILE *f = fopen(argv[2], "w");
    char nome[28];
    int id;

    while (fscanf(ftxt,"%s %d", nome, &id) != EOF) {
        reg r;
        memcpy(r.nome, nome, 28*sizeof(char));
        r.idade = id;
        fwrite(&r, sizeof(reg), 1, f);
    }
    fclose(f);
    fclose(ftxt);

    return 0;
}
