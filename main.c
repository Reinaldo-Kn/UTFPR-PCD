#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pagina 3

typedef struct {
char nome[28];
int idade;
} registro;


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


// void mergeSort(registro *paginaA, registro *paginaB, registro *paginaC, FILE *ordenado) {
// int i, j, k;
// i = 0;
// j = 0;
// k = 0;
// 	while(i < pagina && j < pagina) {
// 		if(strcmp(paginaA[i].nome, paginaB[j].nome) < 0) {
// 			paginaC[k] = paginaA[i];
// 			i++;
// 		} else {
// 			paginaC[k] = paginaB[j];
// 			j++;
// 		}
// 		k++;
// 	}
// 	while(i < pagina) {
// 		paginaC[k] = paginaA[i];
// 		i++;
// 		k++;
// 	}
// 	while(j < pagina) {
// 		paginaC[k] = paginaB[j];
// 		j++;
// 		k++;
// 	}
// 	while(k < pagina) {
// 	fwrite(&paginaC[k], sizeof(registro), 1, ordenado);
// 	k++;
// 	}
		
// }

void merge(registro *paginaA, registro *paginaB, registro *paginaC,int reg,FILE *ordenado) {
int i, j, k, totalRegistros;
totalRegistros = pagina * reg;
printf("Total de registros: %d \n", totalRegistros);
i = 0;
j = 0;
k = 0;
while(i < reg && j < reg && k < reg) {  // Permutação dos registros 
	if(strcmp(paginaA[i].nome, paginaB[j].nome) < 0 || strcmp(paginaA[i].nome, paginaC[k].nome) < 0) {     // -1 se a < b, 0 se a == b, 1 se a > b
		fwrite(&paginaA[i], sizeof(registro), 1, ordenado);
		i++;
	} else if (strcmp(paginaB[j].nome, paginaA[i].nome) < 0  || strcmp(paginaB[j].nome, paginaC[k].nome) < 0){
		fwrite(&paginaB[j], sizeof(registro), 1, ordenado);
		j++;
	} else if (strcmp(paginaC[k].nome, paginaA[i].nome) < 0 || strcmp(paginaC[k].nome, paginaB[j].nome) < 0) {
		fwrite(&paginaC[k], sizeof(registro), 1, ordenado);
		k++;
	}
}
while(i < pagina) {
	fwrite(&paginaA[i], sizeof(registro), 1, ordenado);
	i++;
}
while(j < pagina) {
	fwrite(&paginaB[j], sizeof(registro), 1, ordenado);
	j++;
}
while(k < pagina) {
	fwrite(&paginaC[k], sizeof(registro), 1, ordenado);
	k++;
}
}


int main(int argc, char const *argv[])
{
	int B;
	FILE *original = fopen(argv[1], "rb"); //rb para binairo
    FILE *ordenado = fopen(argv[2], "wb"); //wb para binario
	sscanf(argv[3], "%d", &B); // B -> registro por pagina
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
		
		mergeSort(paginaA, paginaB, paginaC,ordenado);
		fclose(original);
		fclose(ordenado);
		free(paginaA);
		free(paginaB);
		free(paginaC);
		
	

	
	return 0;
}
