#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[28];
    int idade;
} reg;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("%s [arquivo.bin]\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    int ok=1;
    reg rega, regb;
    fread(&rega, sizeof(reg), 1, f);
    while (fread(&regb, sizeof(reg), 1, f)) {
        if (strcmp(regb.nome,rega.nome) < 0 ||
        (strcmp(regb.nome,rega.nome)==0 && regb.idade < rega.idade)) {
            ok=0;
            break;
        }

        memcpy(&rega, &regb, sizeof(reg));
    }
    fclose(f);

    printf("Arquivo %sordenado\n", ok?"":"nao ");

    return 0;
}
