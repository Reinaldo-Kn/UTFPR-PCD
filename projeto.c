#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
char nome[28];
int idade;
} registro;

int B;

int main(int argc, char *argv[]){
    //TRATAMENTO DE ERRO
    // if(argc!=3){
    //     printf("Nome de arquivo nao informado \n");
    //     exit(1);
    // }

      // if((original=fopen(argv[1],"rb"))==NULL){
    //     printf("Arquivo fonte nao pode ser aberto");
    //     exit(1);
    // }
    //  if((original=fopen(argv[2],"wb"))==NULL){
    //     printf("Arquivo destinatario nao pode ser escrito");
    //     exit(1);
    // }
            
    FILE *original = fopen(argv[1], "r");
    FILE *ordenado = fopen(argv[2], "w");
    sscanf(argv[3], "%d", &B);
    char copia;
    char data[3][32];
  
    int i=0,j=0,linha=0;
    const size_t total_tamanho = 3*B;
    // char* linha = malloc(total_tamanho);
    // registro *paginaA = (registro *)malloc(B*sizeof(registro));
    // registro *paginaB = (registro *)malloc(B*sizeof(registro));
    // registro *paginaC = (registro *)malloc(B*sizeof(registro));
   
    while(!feof(original) && !ferror(original)){
        if(fgets(data[linha],32,original)!=NULL){
            linha++;
        }
    }
    for(i;i<linha;i++){
        printf("%s",data[i]);
    }

//    while ((copia = fgetc(original)) !=EOF) { 
//       for(i;i<3;i++){   //no maximo 3 paginas
//         for(j;j<B;j++){

//         }
//       }                  
//         fputc(copia,ordenado);
//     // copia = fscanf(original, "%s", nome);
//         // copia = fgetc(original);

// } 
    
    
    
    fclose(original);
    fclose(ordenado);
    return 0;
}
