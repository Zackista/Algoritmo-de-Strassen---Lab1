#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int suma(double m1, double m2, int n);
void mostrar (double** m, int n);
void mult(double **m1, double **m2, double **m3, int n);
void strassen(double **m1, double **m2, double **m3, int n);

main (int argc, char *argv[])
{

	srand(time(NULL));
	if (argc != 2)
	{
		printf("Ingrese solo n \n");
		end(0);
	}
	int n, i, j, a;
	n = atoi(argv[1]);

	double **m1, **m2, **m3;

	m1 = calloc(n, sizeof(double*));
	m2 = calloc(n, sizeof(double*));
	m3 = calloc(n, sizeof(double*));

	for (i = 0; i < n; i = i + 1)
	{
		m3[i] = calloc(n, sizeof(double*));
		m1[i] = calloc(n, sizeof(double*));
		m2[i] = calloc(n, sizeof(double*)); 
	}

 	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			int r = rand() % 100;
			m1[i][j] = r;
		}
	}
 	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			int r = rand() % 100;
			m2[i][j] = r;
		}
	}	

	printf("Ingres opción: 1 -> multiplicación clásica. 2 -> strassen\n");
	scanf("%d", &a);

	switch(a)
	{
		case 1: 
			mult(m1,m2,m3,n);
			break;

		case 2:
			strassen(m1,m2,m3,n);
			break;
	}


 	printf("Matriz 1 \n");
 	mostrar (m1, n);
 	printf("\n");
 	printf("Matriz 2 \n");
 	mostrar (m2, n);
 	printf("\n\n\n");
 	printf("Matriz resultado \n");
 	mostrar (m3,n);
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

void strassen(double **m1, double ** m2, double **m3, int n)
{
	printf("prueba \n");
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