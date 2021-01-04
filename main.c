#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n=512;
int block_size=16;
double startTime, stopTime;



void naive_matrixProd(int M1[][n],int M2[][n],int M3[][n])
{  
    int i,j,k;
   
   for(i=0; i<n; i++)  /* iterate over all rows */
    for(j=0; j<n; j++) /* iterate over all columns */ 
    { M3[i][j]=0;
      for(k=0; k<n; k++) /* compute dot product */
        M3[i][j] = M3[i][j]+M1[i][k]*M2[k][j];
    }
}


void improved_matrixProd(int M1[][n],int M2[][n],int M3[][n])
{  
    
    int i, j, k,i1,j1,k1;
    for (i = 0; i < n; i+=block_size)
        for (j = 0; j < n; j+=block_size)
            for (k = 0; k < n; k+=block_size)
                /* B x B mini matrix multiplications */
                 for (i1 = i; i1 < i+block_size; i1++) 
                    for (j1 = j; j1 < j+block_size; j1++)
                        for (k1 = k; k1 < k+block_size; k1++)
                           M3[i1][j1]+= M1[i1][k1]*M2[k1][j1];
                           
}



void rand_init(int M[][n])
{
    srand(time(NULL));
    int i,j;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            M[i][j]=(int)rand()%256;
        
}
void fill_zero(int M[][n]){
    int i,j;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            M[i][j]=0;
}

int main()
{  
   int M1[n][n];
   int M2[n][n];
   int M3[n][n];
   int M4[n][n];
   rand_init(M1);
   rand_init(M2);
   
   startTime = clock();
   naive_matrixProd(M1,M2,M3);
   stopTime = clock();
   printf("%d * %d Naive Matrix Multiplication Takes  %f secs\n",
	  n,n, (stopTime-startTime)/CLOCKS_PER_SEC);
    
   startTime = clock();
   fill_zero(M4);
   improved_matrixProd(M1,M2,M4);
   stopTime = clock();
   printf("%d * %d Improved Matrix Multiplication Takes  %f secs\n",
	  n,n, (stopTime-startTime)/CLOCKS_PER_SEC);

   return 0;
}
