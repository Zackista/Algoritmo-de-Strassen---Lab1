 #include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
   int i, j, n=0;
  
//Ingresamos valor de n (para la matriz cuadrada)
 
    printf("Ingrese el valor de n : ");
    scanf("%d", &n);   
    int M[n][n];

//Ingresamos valores a la matriz
 
       for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            printf("Ingrese el valor %d%d: ", i, j);
            scanf("%d", &M[i][j]);
        }
    }
    printf("\n");

//Mostramos la matriz

    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            printf("[");
            printf("%d", M[i][j]);
            printf("]");
        }
    printf("\n");
    }
   
/*
//Mostramos Matriz M
    printf("Matriz de entrada: ");
    i=1;
    while(i<=32){
        printf("%d", M[i]);
    i++;
    }
    printf("\n");

*/
}
