#define SAMPLES 1000
#define MATSIZE 4096

#include <time.h>
#include <iostream>

int mat[MATSIZE][MATSIZE];

void transpose()
{
   for ( int i = 0 ; i < MATSIZE ; i++ )
   for ( int j = 0 ; j < MATSIZE ; j++ )
   {
       int aux = mat[i][j];
       mat[i][j] = mat[j][i];
       mat[j][i] = aux;
   }
}

int main()
{
   //initialize matrix
   for ( int i = 0 ; i < MATSIZE ; i++ )
   for ( int j = 0 ; j < MATSIZE ; j++ )
       mat[i][j] = i+j;

   int t = clock();
   for ( int i = 0 ; i < SAMPLES ; i++ )
       transpose();
   int elapsed = clock() - t;

   std::cout << "Average for a matrix of " << MATSIZE << ": " << elapsed / SAMPLES;
}