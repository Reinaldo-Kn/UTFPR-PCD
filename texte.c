#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pagina 3

typedef struct {
char nome[28];
int idade;
} registro;

void quicksort(registro *v, int esq, int dir);
void mergeSort(registro *paginaA, registro *paginaB, registro *paginaC, int total, FILE *ordenado,FILE *original,int reg);
void sort(registro *paginaA, registro *paginaB, registro *paginaC,int comeco, int fim, FILE *ordenado, FILE *original,int reg);
void merge(registro *paginaA, registro *paginaB, registro *paginaC,int comeco, int meio, int fim, FILE *ordenado, FILE *original,int reg);





int main(int argc, char const *argv[])
{
	int B;
    
	FILE *original = fopen(argv[1], "rb"); //rb para binairo
    FILE *ordenado = fopen(argv[2], "wb"); //wb para binario
	sscanf(argv[3], "%d", &B); // B -> registro por pagina
    int total = B * pagina;
	// if(original==NULL) return 0;															// ex: B = 4 e pagina = 3, total de registro -> B x Pagina = 12
	registro *paginaA = (registro *)malloc(B*sizeof(registro)); // vetor de 0 ate B    							ex: 0 1 2 3     -> 4
	registro *paginaB = (registro *)malloc(B*sizeof(registro)); // vetor de B ate (B x Pagina) - B     			ex: 4 5 6 7	    -> 8		
	registro *paginaC = (registro *)malloc(B*sizeof(registro)); // vetor de (B x Pagina) - B  ate (B x Pagina)	ex: 8 9 10 11   -> 12

	  
        
		for(int i=0; i<B;i++){
			fread(&paginaA[i],sizeof(registro),1,original); //ex: de 0 ate 4 
		};
		for(int i=0; i<B;i++){
			fread(&paginaB[i],sizeof(registro),1,original); //ex: de 4 ate 8 
		};
		for(int i=0; i<B;i++){
			fread(&paginaC[i],sizeof(registro),1,original); //ex: de 8 ate 12 
		};
		quicksort(paginaA,0,B-1);
		quicksort(paginaB,0,B-1);
		quicksort(paginaC,0,B-1);
      
        mergeSort(paginaA,paginaB,paginaC,total,ordenado,original,B);

        free(paginaA);
        free(paginaB);
        free(paginaC);
	
	return 0;
}

void quicksort(registro *v, int esq, int dir) {
int i, j;
registro pivo, aux;
i = esq;
j = dir;
pivo = v[(esq + dir) / 2];
	while(i <= j) {
	 	while(strcmp(v[i].nome, pivo.nome) < 0 && i < dir) {
			i++;
		}
		while(strcmp(v[j].nome, pivo.nome) > 0 && j > esq) {
			j--;
		}
		if(i <= j) {
		aux = v[i];
		v[i] = v[j];
		v[j] = aux;
		i++;
		j--;
		}
	}
	if(j > esq) {
	quicksort(v, esq, j);
	}
	if(i < dir) {
	quicksort(v, i, dir);
	}
}


void mergeSort(registro *paginaA, registro *paginaB, registro *paginaC, int total,FILE *ordenado, FILE *original,int reg) {
   sort(paginaA,paginaB,paginaC,0,total,ordenado,original,reg);
}

void sort(registro *paginaA, registro *paginaB, registro *paginaC,int comeco, int fim,FILE *ordenado, FILE *original,int reg) {
    if(comeco < fim) {
 
        int meio = (comeco + fim) / 2;
        sort(paginaA,paginaB,paginaC,comeco,meio,ordenado,original,reg); //merge do começo ate o meio
        sort(paginaA,paginaB,paginaC,meio+1,fim,ordenado,original,reg); // merge do meio+1 ate o fim
        merge(paginaA,paginaB,paginaC,comeco,meio,fim,ordenado,original,reg);
    }
}
 void merge(registro *paginaA, registro *paginaB, registro *paginaC,int comeco, int meio, int fim,FILE *ordenado, FILE *original,int reg) {
    int i, j, k;
    int total = reg * pagina;
    i = comeco;
    j = meio+1;
    k = comeco;

        for(int z = 0; z< meio; z++){
			fread(&paginaA[z],sizeof(registro),1,original); 
		};
         for(int z = 0; z< meio; z++){
			fread(&paginaB[z],sizeof(registro),1,original); 
		};

    while(i <= meio && j <= fim) {
        if(strcmp(paginaA[i].nome, paginaB[j].nome) < 0 ) {
            paginaC[k] = paginaA[i];
            i++;
            
        }else {
            paginaC[k] = paginaB[j];
            j++;
            
        }
        k++;
    }
    while(i <= meio) {
        paginaC[k] = paginaA[i];
        i++;
        k++;
    }
    while(j <= fim) {
        paginaC[k] = paginaB[j];
        j++;
        k++;
    }
    for(int k = 0; k < fim; k++){
        fwrite(&paginaC[k],sizeof(registro),1,ordenado);
    }
    
 }
