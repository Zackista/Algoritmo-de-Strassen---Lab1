#include <time.h>
#include <stdlib.h>
#include <stdio.h>

main (int argc, char *argv[])
{
	srand(time(NULL));
	if (argc != 2)
	{
		printf("Ingrese solo n \n");
		end(0);
	}
	int n, i, j;
	n = atoi(argv[1]);

	double m1[n][n], m2[n][n], suma[n][n], mult[n][n];

	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			double r = rand() % 100;
			m1[i][j] = r;
		}
	}

	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			double r = rand() % 100;
			m2[i][j] = r;
		}
	}

	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			printf("%lf\n",m1[i][j] );
		}
	}
	printf("\n \n \n");
	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			printf("%lf\n",m2[i][j] );
		}
	}

	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			suma[i][j] = m1[i][j] - m2[i][j];
		}
	}
	printf("\n \n");
	for (i = 0; i < n; i = i + 1)
	{
		for (j = 0; j < n; j = j + 1)
		{
			printf("%lf\n",suma[i][j] );
		}
	}

			// for (i = 0; i < n; i = i + 1)
			// {
			// 	for (j = 0; j < n; j = j + 1)
			// 	{
			// 		mult[i][j] =  m1[]
			// 	}
			// }

}