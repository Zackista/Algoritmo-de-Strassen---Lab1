#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int n, n0;

void mostrar(double **m, int n);
void multi_clasica(double **m1, double **m2, double **m3, int n);
void strassen(double** m1, double** m2, double**m3, int dim);
int padding(int n);	


int main(int argc, char *argv[]){
	int i, j, aux, modo;
	FILE *file;
	srand(time(NULL));
	if (argc != 3)
	{
		printf("Ingrese solo tipo de multiplicación, n y n0 \n");
		end(0);
	}
	float tiempo = 0;
 	clock_t inicio1, fin1; // Se crea variable 'clock_t' para calcular el tiempo de ejecúción del programa.
	inicio1 = clock();		

 	
	n=atoi(argv[1]);		//tamaño de matriz
	n0=atoi(argv[2]);		// Punto en el cual se deja de usar la técnica de strassen o divide y conquistm1, y se comienza a utilizar la multiplicación clásica
	aux = n;

	if(n <= 0)

		return 0;
	n0 = padding(n0);
	n = padding(n);//Para asegurarnos de tener una matriz cuadrada.
	
	double**m1, **m2, **m3;
	m1 = calloc(n,sizeof(double*));		
	m2 = calloc(n,sizeof(double*));	
	m3 = calloc(n,sizeof(double*));
	for(i=0;i<n;i++){
		m3[i] = calloc(n,sizeof(double));
		m1[i] = calloc(n,sizeof(double));		
		m2[i] = calloc(n,sizeof(double));	
		
	}
	for(i=0;i<aux;i++){		// se generan números aleatorios entre 0 y sqrt(tamañomatriz)
		for(j=0;j<aux;j++){
			m1[i][j]=((int)rand())%(100);
		}
	}
	for(i=0;i<aux;i++){
		for(j=0;j<aux;j++){
			m2[i][j]=((int)rand())%(100);
		}
	}

	for(i = aux; i < n; i++)//En caso de que la matriz no sea cuadrada se rellena el resto de la matriz con ceros
		for(j = 0; j < n; j++)
			m1[i][j] = 0;

	for(i = aux; i < n; i++)
		for(j = 0; j < n; j++)
			m2[i][j] = 0;
	
	multi_clasica(m1,m2,m3,aux);
	// mostrar(m1,aux);		//se muestran matrices generadas y el resultado de la multiplicación de estas.
	// mostrar(m2,aux);
	// mostrar(m3,aux);

	fin1=clock();
	tiempo = (fin1-inicio1)/(double)CLOCKS_PER_SEC;
	printf("El tiempo de ejecución fue de: %f \n",tiempo); // %f es porque es un flotante!!!
 	file = fopen("expstrassen.txt", "a");
 	fprintf(file, "Multiplicacion clasica N: %d, n0: %d, tiempo: %F  \t ", n, n0, tiempo);


 	clock_t inicio2, fin2;
 	inicio2 = clock();

	strassen(m1,m2,m3,n);		
	// mostrar(m1,aux);		//se muestran matrices generadas y el resultado de la multiplicación de estas.
	// mostrar(m2,aux);
	// mostrar(m3,aux);

	fin2=clock();
	tiempo = (fin2-inicio2)/(double)CLOCKS_PER_SEC;
	printf("El tiempo de ejecución fue de: %f \n",tiempo); // %f es porque es un flotante!!!
	fprintf(file, "Multiplicacion Strassen N: %d, n0: %d, tiempo: %F  \n", n, n0, tiempo);

	return 0;
	
}

void mostrar(double **m, int n){ 		//Muestra los elementos de la matriz resultados
	int i,j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++)
		{ 
			printf("%lf\t",m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void multi_clasica(double **m1, double **m2, double **m3, int n){	//realiza la multiplicación clásica con n³
	int i, j, k;
	for(i=0; i<n; ++i){
    	for(j=0; j<n; ++j){
			m3[i][j]=0;
		    for(k=0; k<n; ++k)
		    {
		        m3[i][j]+=m1[i][k]*m2[k][j];
		    }
		}
	}
	
}


void strassen(double** m1, double** m2, double**m3, int dim) {		//Realiza la multiplicación haciendo uso de 7 multiplicaciones y varias sumas

	
	double **p1 , **p2 , **p3 , **p4, **p5 , **p6 , **p7;
	double **aux1 , **aux2;
	int i ,j; 
	if(dim > n0) { 
		p1 = calloc(dim/2,sizeof(double*));		
		p2 = calloc(dim/2,sizeof(double*)); 
		p3 = calloc(dim/2,sizeof(double*));		
		p4 = calloc(dim/2,sizeof(double*));				//se pide la memoria para las 7 submatrices y 2 matrices que se usaran como auxiliar
		p5 = calloc(dim/2,sizeof(double*));		
		p6 = calloc(dim/2,sizeof(double*));		
		p7 = calloc(dim/2,sizeof(double*));		
		
		aux1 = calloc(dim/2,sizeof(double*));		
		aux2 = calloc(dim/2,sizeof(double*));	
		for(i=0;i<dim/2;i++){
			p1[i] = calloc(dim/2,sizeof(double));
			p2[i] = calloc(dim/2,sizeof(double));
			p3[i] = calloc(dim/2,sizeof(double));
			p4[i] = calloc(dim/2,sizeof(double));
			p5[i] = calloc(dim/2,sizeof(double));
			p6[i] = calloc(dim/2,sizeof(double));
			p7[i] = calloc(dim/2,sizeof(double));
			aux1[i] = calloc(dim/2,sizeof(double));		
			aux2[i] = calloc(dim/2,sizeof(double));	
		}
		//p1								SE REALIZAN LAS 7 MULTIPLICACIONES GENERANDO SUB MATRICES

		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux1[i][j] = m1[i][j] + m1[i + dim / 2][j + dim / 2];
		}
		
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux2[i][j] = m2[i][j] + m2[i + dim / 2][j + dim / 2];
		}
		n = dim / 2;
		strassen(aux1, aux2, p1, dim / 2);

		//p2
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux1[i][j] = m1[i + dim / 2][j] + m1[i + dim / 2][j + dim / 2];
		}
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux2[i][j] = m2[i][j];
		}
		n = dim / 2;
		strassen(aux1, aux2, p2, dim / 2);

		//p3
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux1[i][j] = m1[i][j];
		}

		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux2[i][j] = m2[i][j + dim / 2] - m2[i + dim / 2][j + dim / 2];	
		}
		n = dim / 2;
		strassen(aux1, aux2, p3, dim / 2);

		//p4
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux1[i][j] = m1[i + dim / 2][j + dim / 2];
		}
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux2[i][j] = m2[i + dim / 2][j] - m2[i][j];
		}
		n = dim / 2;
		strassen(aux1, aux2, p4, dim / 2);

		//p5

		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux1[i][j] = m1[i][j] + m1[i][j + dim / 2];
		}

		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux2[i][j] = m2[i + dim / 2][j + dim / 2];
		}
		n = dim / 2;
		strassen(aux1, aux2, p5, dim / 2);

		//p6

		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux1[i][j] = m1[i + dim / 2][j] - m1[i][j];
		}
		n = dim / 2;

		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux2[i][j] = m2[i][j] + m2[i][j + dim / 2];
		}

		n = dim / 2;
		strassen(aux1, aux2, p6, dim / 2);

		//p7
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux1[i][j] = m1[i][j + dim / 2] - m1[i + dim / 2][j + dim / 2];
		}

		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				aux2[i][j] = m2[i + dim / 2][j] + m2[i + dim / 2][j + dim / 2];
		}
		n = dim / 2;
		strassen(aux1, aux2, p7, dim / 2);
		
		//c11
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				m3[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
		}

		//c12
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				m3[i][j + dim / 2] = p3[i][j] + p5[i][j];
		}
		//c21
		for(i = 0; i < dim / 2; i++) {

			for(j = 0; j < dim / 2; j++) 
				m3[i + dim / 2][j] = p2[i][j] + p4[i][j];
		}
		
		//c22
		for(i = 0; i < dim / 2; i++) {
			for(j = 0; j < dim / 2; j++) 
				m3[i + dim / 2][j + dim / 2] = p1[i][j] + p3[i][j] - p2[i][j] + p6[i][j];
		}
	}else{
		if(dim==n0){	//Si hemos llegado a n0 se usa multiplicación clásica
			multi_clasica(m1,m2,m3,dim);
		}
	}

}

int padding(int n) {  // Busca la potencia de dos más cercana por arriba del número para segurar una matriz cuadrada
	int original_n = n, pot_menor = 0, i, act_n = 1;

	if(n == 1)
		return 1;

	while(n > 1) {
		pot_menor++;
		n /= 2;
	}

	for(i = 0; i < pot_menor; i++) {
		act_n *= 2;
	}

	if(act_n == original_n)
		return original_n;
	else
		return act_n * 2;

}
