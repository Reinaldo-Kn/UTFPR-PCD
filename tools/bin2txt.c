#include <stdio.h>

typedef struct {
    char nome[28];
    int idade;
} reg;

int B;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("%s [arquivo.bin] [B]\n", argv[0]);
        return 1;
    }

    sscanf(argv[2], "%d", &B);
    FILE *f = fopen(argv[1], "r");
    char nome[28];
    int id;
    reg r;
    int i=0;
    while (fread(&r, sizeof(reg), 1, f)) {
        
    }
    fclose(f);

    return 0;
}
