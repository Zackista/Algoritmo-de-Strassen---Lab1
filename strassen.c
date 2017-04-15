#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int n, n0;

int suma(double m1, double m2, int n);
void mostrar (double** m, int n);
void mult(double **m1, double **m2, double **m3, int n);
void strassen(double **m1, double **m2, double **m3, int dim);



int main (int argc, char *argv[])
{

	srand(time(NULL));
	if (argc != 4)
	{
		printf("Ingrese solo tipo de multiplicación, n y n0 \n");
		end(0);
	}
	int opcion, i, j, aux;


	opcion = atoi(argv[1]);	
	n = atoi(argv[2]);
	n0 = atoi(argv[3]);
	aux = n;
	double **m1, **m2, **m3;

	m1 = calloc(n,sizeof(double*));
	m2 = calloc(n,sizeof(double*));
	m3 = calloc(n,sizeof(double*));

	for (i = 0; i < n; i = i + 1)
	{
		m3[i] = calloc(n,sizeof(double*));
		m1[i] = calloc(n,sizeof(double*));
		m2[i] = calloc(n,sizeof(double*)); 
	}

 	for (i = 0; i < aux; i = i + 1)
	{
		for (j = 0; j < aux; j = j + 1)
		{
			int r = rand() % 100;
			m1[i][j] = r;
		}
	}
 	for (i = 0; i < aux; i = i + 1)
	{
		for (j = 0; j < aux; j = j + 1)
		{
			int r = rand() % 100;
			m2[i][j] = r;
		}
	}	

	switch(opcion)
	{
		case 1: 
			mult(m1,m2,m3,aux);
			break;

		case 2:
			strassen(m1,m2,m3,n);
			break;
	}


 	printf("Matriz 1 \n");
 	mostrar (m1, aux);
 	printf("\n");
 	printf("Matriz 2 \n");
 	mostrar (m2, aux);
 	printf("\n\n\n");
 	printf("Matriz resultado \n");
 	mostrar (m3, aux);
}

void mult(double **m1, double ** m2, double **m3, int n)
{
 	int i, j, k;
	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			m3[i][j] = 0;
			for (k = 0; k < n; k = k + 1)
			{
				m3[i][j] = m3[i][j] + m1[i][k] * m2[k][j];
			}
		}
	}
}

void strassen(double **m1, double ** m2, double **m3, int dim)
{
	double **p1, **p2, **p3, **p4, **p5, **p6, **p7;
	double **aux, **aux2;
	int i ,j; 
	if(dim > n0) 
	{ 
		p1 = calloc(dim/2,sizeof(double*));		
		p2 = calloc(dim/2,sizeof(double*)); 
		p3 = calloc(dim/2,sizeof(double*));		
		p4 = calloc(dim/2,sizeof(double*));				//se pide la memoria para las 7 submatrices y 2 matrices que se usaran como auxiliar
		p5 = calloc(dim/2,sizeof(double*));		
		p6 = calloc(dim/2,sizeof(double*));		
		p7 = calloc(dim/2,sizeof(double*));		
		
		aux = calloc(dim/2,sizeof(double*));		
		aux2 = calloc(dim/2,sizeof(double*));	
		for(i = 0; i < dim/2; i = i + 1)
		{
			p1[i] = calloc(dim/2,sizeof(double*));
			p2[i] = calloc(dim/2,sizeof(double*));
			p3[i] = calloc(dim/2,sizeof(double*));
			p4[i] = calloc(dim/2,sizeof(double*));
			p5[i] = calloc(dim/2,sizeof(double*));
			p6[i] = calloc(dim/2,sizeof(double*));
			p7[i] = calloc(dim/2,sizeof(double*));
			aux[i] = calloc(dim/2,sizeof(double*));		
			aux2[i] = calloc(dim/2,sizeof(double*));	
		}

		for(i = 0; i < dim / 2; i = i + 1) 
		{
			for(j = 0; j < dim / 2; j = j + 1) 
				aux[i][j] = m1[i][j] + m1[i + dim / 2][j + dim / 2];
		}
		
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux2[i][j] = m2[i][j] + m2[i + dim / 2][j + dim / 2];
		}
		n = dim / 2;
		strassen(aux, aux2, p1, dim / 2);

		//p2
		for(i = 0; i < n / 2; i = i + 1) {
			for(j = 0; j < n / 2; j = j + 1) 
				aux[i][j] = m1[i + dim / 2][j] + m1[i + dim / 2][j + dim / 2];
		}
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux2[i][j] = m2[i][j];
		}
		n = dim / 2;
		strassen(aux, aux2, p2, dim / 2);

		//p3
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux[i][j] = m1[i][j];
		}

		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux2[i][j] = m2[i][j + dim / 2] - m2[i + dim / 2][j + dim / 2];	
		}
		n = dim / 2;
		strassen(aux, aux2, p3, dim / 2);

		//p4
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux[i][j] = m1[i + dim / 2][j + dim / 2];
		}
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux2[i][j] = m2[i + dim / 2][j] - m2[i][j];
		}
		n = dim / 2;
		strassen(aux, aux2, p4, dim / 2);

		//p5

		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux[i][j] = m1[i][j] + m1[i][j + dim / 2];
		}

		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux2[i][j] = m2[i + dim / 2][j + dim / 2];
		}
		n = dim / 2;
		strassen(aux, aux2, p5, dim / 2);

		//p6

		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux[i][j] = m1[i + dim / 2][j] - m1[i][j];
		}
		n = dim / 2;

		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux2[i][j] = m2[i][j] + m2[i][j + dim / 2];
		}

		n = dim / 2;
		strassen(aux, aux2, p6, dim / 2);

		//p7
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				aux[i][j] = m1[i][j + dim / 2] - m1[i + dim / 2][j + dim / 2];
		}

		for(i = 0; i < dim / 2; i = i + 1)
		{
			for(j = 0; j < dim / 2; j = j + 1) 
				aux2[i][j] = m2[i + dim / 2][j] + m2[i + dim / 2][j + dim / 2];
		}
		n = dim / 2;
		strassen(aux, aux2, p7, dim/ 2);
		
		//c11
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				m3[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
		}

		//c12
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				m3[i][j + dim / 2] = p3[i][j] + p5[i][j];
		}
		//c21
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				m3[i + dim / 2][j] = p2[i][j] + p4[i][j];
		}
		
		//c22
		for(i = 0; i < dim / 2; i = i + 1) {
			for(j = 0; j < dim / 2; j = j + 1) 
				m3[i + dim / 2][j + dim / 2] = p1[i][j] + p3[i][j] - p2[i][j] + p6[i][j];
		}
	}
	else
	{
		if(dim==n0){	//Si hemos llegado a n0 se usa multiplicación clásica
			mult(m1,m2,m3,dim);
		}
	}
}


void mostrar(double **m, int n)
{
	int i, j;
	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			printf("[");
			printf("%lf",m[i][j] );
			printf("]");
		}
	printf("\n");
	}
}	


 //  void mostrar(double** m, int n)
 //  {
 //  	int i,j;
 //  	for (i = 0; i < n; i = i + 1)
	// {
	// 	for (j = 0; j < n; j = j + 1)
	// 	{
	// 		printf("[");
	// 		printf("%lf",m[i][j] );
	// 		printf("]");
	// 	}
	// 	printf("\n \n");
	// }
 //  }