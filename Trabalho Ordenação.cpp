#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Confirmar se os valores de comparacoes e trocas est� correto, principalmente do quicksort

void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int partition(int A[], int inicio, int fim,long long int *comparacoes3,long long int *trocas3) {
    int meio = (inicio + fim) / 2;
    int a = A[inicio];
    int b = A[meio];
    int c = A[fim];
    int medianaIndice; 
    if (a < b) {
        if (b < c) {
            medianaIndice = meio;
        } else {
            if (a < c) {
                medianaIndice = fim;
            } else {
                medianaIndice = inicio;
            }
        }
    } else {
        if (c < b) {
            medianaIndice = meio;
        } else {
            if (c < a) {
                medianaIndice = fim;
            } else {
                medianaIndice = inicio;
            }
        }
    }
    swap(A, medianaIndice, fim);
	*trocas3+=1;   
	int pivo = A[fim];
    int i = inicio - 1;
    int j;
    for (j = inicio; j <= fim - 1; j++) {
    	*comparacoes3 += 1;
        if (A[j] <= pivo) {
        	*trocas3+=1;
            i = i + 1;
            swap(A, i, j);
        }
    }
    *trocas3+=1;
    swap(A, i + 1, fim);
    return i + 1; 
}

void quicksort(int A[], int inicio, int fim,long long int *comparacoes3,long long int *trocas3) {
    if (inicio < fim) {
        int q = partition(A, inicio, fim,comparacoes3,trocas3);
        quicksort(A, inicio, q - 1,comparacoes3,trocas3);
        quicksort(A, q + 1, fim,comparacoes3,trocas3);
    }
}

void insertionSort(int A[ ],int n,long long int *comparacoes1,long long int *trocas1){
	int i;
    for(i = 1; i < n; i++){
        int elemento = A[i];
        int j = i - 1;
        while(j >= 0 && A[j] > elemento){
        	*trocas1 += 1;
            A[j + 1] = A[j]; 
            j = j - 1;
        }
        A[j + 1] = elemento; 
        if(j < 0) j++;
		*comparacoes1 += (i - j);
    }
}





void selectionSort(int a[],int n,long long int *comparacoes2,long long int *trocas2) {
    int i;
    for (i = 0; i < n - 1; i++) {
        int minIndex = i;
        int k;
        for (k = i + 1; k < n; k++) {
        	*comparacoes2 +=1 ;
            if (a[minIndex] > a[k]) {
                minIndex = k;
            }
        }
        *trocas2+=1;
        int temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
}

int main() {
	int n = 1000;
	FILE *ins,*sel,*qui;
    int A[n],B[n],C[n];
    int i;
    clock_t t1,t2,t3 ;
    long long int comparacoes1  = 0,comparacoes2 = 0,comparacoes3 = 0,trocas1 = 0,trocas2 = 0,trocas3 = 0;
    srand (time(NULL));  
    for(i=0;i<n;i++){
    	A[i] = n-i;
    	B[i] = A[i];
    	C[i] = A[i];
	}
	
    ins = fopen("Inserção.txt", "w+");
    fprintf(ins,"Vetor Desordenado:\n\n");
    sel = fopen("Seleção.txt", "w+");
    fprintf(sel,"Vetor Desordenado:\n\n");
    qui = fopen("Quicksort.txt", "w+");
    fprintf(qui,"Vetor Desordenado:\n\n"); 	
	for(i=0;i<n;i++){
    	fprintf(ins,"%d\n",A[i]);
    	fprintf(sel,"%d\n",B[i]);
    	fprintf(qui,"%d\n",C[i]);		
	}
	fclose(ins);
	fclose(sel);
	fclose(qui);
	
	t1 = clock();
    insertionSort(A,n,&comparacoes1,&trocas1);
    t1 = clock() - t1;
    t2 = clock();
    selectionSort(B,n,&comparacoes2,&trocas2);
    t2 = clock() - t2;
    t3 = clock();
    quicksort(C,0,n-1,&comparacoes3,&trocas3);
    t3 = clock() - t3;
    
    
    ins = fopen("Inserção.txt", "a+");
    fprintf(ins,"\n\n\nVetor Ordenado:\n\n");
    sel = fopen("Seleção.txt", "a+");
    fprintf(sel,"\n\n\nVetor Ordenado:\n\n");
    qui = fopen("Quicksort.txt", "a+");
    fprintf(qui,"\n\n\nVetor Ordenado:\n\n");   
    for(i=0;i<n;i++){
    	fprintf(ins,"%d\n",A[i]);
    	fprintf(sel,"%d\n",B[i]);
    	fprintf(qui,"%d\n",C[i]);
	}
	fclose(ins);
	fclose(sel);
	fclose(qui);
    printf("\n\nTempo de Execucao Insert = %lf %lld %lld\n\n",((double)t1)/((CLOCKS_PER_SEC)),comparacoes1,trocas1);
    printf("Tempo de Execucao Select = %lf %lld %lld\n\n",((double)t2)/((CLOCKS_PER_SEC)),comparacoes2,trocas2);
    printf("Tempo de Execucao Quicksort = %lf %lld %lld\n\n",((double)t3)/((CLOCKS_PER_SEC)),comparacoes3,trocas3);
	return 0;
}
