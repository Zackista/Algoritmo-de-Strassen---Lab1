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
	FILE *file;
	srand(time(NULL));
	if (argc != 3)
	{
		printf("Ingrese solo tipo de multiplicación, n y n0 \n");
		end(0);
	}
	int opcion, i, j, j1, aux;
	double **m1, **m2, **m3;
	float tiempo = 0;
	clock_t inicio1, fin1; // Se crea variable 'clock_t' para calcular el tiempo de ejecúción del programa.
	inicio1 = clock();	
	n = atoi(argv[1]);
	n0 = atoi(argv[2]);
	aux = n;
	

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

	mult(m1,m2,m3,aux);
 	fin1=clock();
	tiempo = (fin1-inicio1)/(double)CLOCKS_PER_SEC;
	printf("El tiempo de ejecución fue de: %f \n",tiempo); // %f es porque es un flotante!!!
 	file = fopen("expstrassen.txt", "a");
 	fprintf(file, "Multiplicacion clasica N: %d, n0: %d, tiempo: %F  \t ", aux, n0, tiempo);

 	printf("Matriz 1 clasica \n");
 	mostrar (m1, aux);
 	printf("\n");
 	printf("Matriz 2 \n");
 	mostrar (m2, aux);
 	printf("\n\n\n");
 	printf("Matriz resultado \n");
 	mostrar (m3, aux);


	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			m3[i][j] = 0;
		}
	}

 	clock_t inicio2, fin2;
 	inicio2 = clock();
 

 	if (aux % 2 == 0)
 	{
		strassen(m1,m2,m3,n);
		fin2=clock();
		tiempo = (fin2-inicio2)/(double)CLOCKS_PER_SEC;
		printf("El tiempo de ejecución fue de: %f \n",tiempo); // %f es porque es un flotante!!!
		fprintf(file, "Multiplicacion Strassen N: %d, n0: %d, tiempo: %F  \n", aux, n0, tiempo);
 	}

	
 	printf("Matriz 1 strassen \n");
 	mostrar (m1, aux);
 	printf("\n");
 	printf("Matriz 2 \n");
 	mostrar (m2, aux);
 	printf("\n\n\n");
 	printf("Matriz resultado \n");
 	mostrar (m3, aux);



    if(file == NULL)
    {
        printf("Error al abrir archivo");
    }
    // for (i = 0; i < n; i = i + 1)
    // {
    // 	if (i != 0)
    // 	{
    // 		fprintf(file, "\n");
    // 	}
    // 	for (j = 0; j < n; j = j + 1)
    // 	{
    // 		fprintf(file,"%lf \t \t %lf ",m1[i][j]), m2[i][j];
    // 		printf("hola");
    // 	}
    // }


    // fprintf(file,"\t \t ");

  //   for (i = 0; i < aux; i = i + 1)
  //   {

		// fprintf(file, "\n");    	
		// for (j = 0; j < aux; j = j + 1)
		// {
  //   		fprintf(file,"%lf ",m1[i][j]);
  //   		if (j == aux-1)
  //   		{
  //   			fprintf(file, "\t\t");   
  //   			for(j1 = 0; j1 < aux; j1 = j1 + 1)
  //   			{
	 //    			fprintf(file, "%lf ",m2[i][j1] );
	 //    			if (j1 == aux-1 && i == 0)
	 //    			{
		// 				fprintf(file, "\t \t %F ",tiempo);
	 //    			}
	 //    			if (j1 == aux-1 && i == aux-1)
	 //    			{
	 //    				fprintf(file, "\n\n\n"); 
	 //    			}
	 //    		}
  //   		}
		// }
  //   }


    return 0;

    // fprintf(file, "\t \t %F \n", tiempo);
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