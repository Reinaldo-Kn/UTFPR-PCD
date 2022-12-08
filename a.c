#include <stdio.h>
#include <stdlib.h>
#define N 5000
#define segments 10

void swap (int *x, int *y) {
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

// void QuickSort(int vetor[],int inicio,int fim){
//     if (inicio >= fim) return;
//     int pivo = vetor[inicio];
//     int m = inicio;
//     for (int i =inicio+1 ; i<fim;i++){
//         if (vetor[i]<=pivo){
//             swap(&vetor[i], &vetor[m+1]);
//             m++;
//         }
//         swap(&vetor[inicio],&vetor[m]);
//         QuickSort(vetor,inicio,m-1);
//         QuickSort(vetor,m+1,fim);
//     }
// }

void QuickSort(int a[], int l, int r) {
	int i,j;
	
	if (l>=r) return;
	i = l+1; //razvrstavanje elemenata s obzirom na stozer
	j = r;
	while ((i<=j) && (i<=r) && (j>l)) {
		while ((a[i] <= a[l]) && (i<=r)) i++;
		while((a[j] >= a[l]) && (j>l)) j--;
		if (i<j)
			swap(&a[i], &a[j]);
	}
	if (i>r) { // stozer je najveci u polju
		swap(&a[r], &a[l]);
		QuickSort(a, l, r-1);
	}
	else if (j<=l) { // stozer je najmanji u polju
		QuickSort(a, l+1, r);
	}
	else { //stozer je negdje u sredini
		swap(&a[j], &a[l]);
		QuickSort(a, l, j-1);
		QuickSort(a, j+1, r);
	}
} 

void merge (FILE *pomocni, FILE *output, int puta) {
	int i=0, j=0, broj, jedan, dva; FILE *aux;
	aux=fopen("aux.txt", "w+");
	fscanf(pomocni, "%d", &jedan);
	fscanf(output, "%d", &dva);
	while (i<(N/segments) && j<(N/segments*puta)) {
		if (jedan<=dva) {
			fprintf(aux, "%d\n", jedan);
			fscanf(pomocni, "%d", &jedan);
			i++;
		} else {
			fprintf(aux, "%d\n", dva);
			fscanf(output, "%d", &dva);
			j++;
		}
	}
	if (i<(N/segments)) fprintf(aux, "%d\n", jedan);
	if (j<(N/segments*puta)) fprintf(aux, "%d\n", dva);
	while (i<(N/segments)) {
		fscanf(pomocni, "%d", &broj);
		fprintf(aux, "%d\n", broj);
		i++;
	}
	while (j<(N/segments*puta)) {
		fscanf(output, "%d", &broj);
		fprintf(aux, "%d\n", broj);
		j++;	
	} 
	// aux pretacemo u output
	fclose(aux); aux=fopen("aux.txt", "r+"); // rewind valjda ne radi kad je u w mode-u	
	fclose(output); output=fopen("output.txt", "w+"); // reset outputa
	for (i=0; i<(N/segments*(puta+1)); i++) {
		fscanf(aux, "%d", &broj);
		fprintf(output, "%d\n", broj);
	}
	fclose(output);
	fclose(aux); remove("aux.txt");
}

int main (void) {

	char ime[20];
	int i,j, broj, niz[N/segments];
	FILE *pocetni, *pomocni, *output;

	// 1) generiranje pocetnog file-a
	pocetni=fopen("pocetni.txt","w");
	for (i=0; i < N; i++) {
		fprintf(pocetni, "%d\n", rand());
	}
	fclose(pocetni);

	// 2) cijepanje pocetnog file-a
	pocetni=fopen("pocetni.txt","r");
	for(j=0; j<segments; j++) {
		sprintf(ime, "%d.txt", j+1);
		pomocni = fopen(ime, "w");
		for(i=j*(N/segments); i<(j+1)*(N/segments); i++) {
			fscanf(pocetni, "%d", &broj);
			fprintf(pomocni, "%d\n", broj);
		}
		fclose(pomocni);

		//ucitavanje male datoteke u gl mem
		pomocni = fopen(ime, "r+"); 
		for (i=0; i<(N/segments); i++) {
			fscanf(pomocni, "%d", &broj);
			niz[i]=broj;
		}

		// 3) quicksort male datoteke, tj. malog niza
		QuickSort(niz, 0, (N/segments)-1);

		rewind(pomocni);
		//ponovno ispisivanje male datoteke na disk
		for (i=0; i<(N/segments); i++) {
			fprintf(pomocni, "%d\n", niz[i]);
		}

		fclose(pomocni);
	}
	
	// kreiranje output file-a (sigurno ima jedna mala datoteka)
	output=fopen("output.txt","w");
	pomocni=fopen("1.txt", "r");
	for(i=0; i<(N/segments); i++) { //while !feof ne radi jer ima \n na kraju svakog filea
		fscanf(pomocni, "%d", &broj);
		fprintf(output, "%d\n", broj);
	}
	fclose(output); fclose(pomocni); remove("1.txt");

	// 4) merge-anje s preostalim datotekama (ako ih ima :))

	for(j=1; j<segments; j++) {
		output = fopen("output.txt","r+"); 
		sprintf(ime, "%d.txt", j+1);
		pomocni = fopen(ime, "r+");
		merge(pomocni, output, j);
		fclose(pomocni);
		remove(ime);
	}
	
	fclose(pocetni);
	remove("pocetni.txt");
	return 0;
}
