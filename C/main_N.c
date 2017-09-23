#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// Include headers
#include "funciones.h"
#include "viscek.h"

#define NS 5
#define ETAS 100
// Note: Mute viscek.c before running this simulation

int main()
{
  //printf("\nhola");
  //fflush( stdout );
  /*------------- Initialization of variables -------------------------*/
  // Number of particles for the simulations
  double M[NS] = {40, 100, 400, 4000, 10000};
  // Size of cell
  double L[NS] = {3.1, 5, 10, 31.6, 50};
  //Noise
  int i,j,k;
  double eta[ETAS];
  for(i=0;i<ETAS;i++)
    {
      eta[i] = (double)(5*i)/ETAS;
    }
  // Order parameter
  double va[NS][ETAS];
  // Number of runs
  int N = 5000;
  
  /*----------------------- Computation of data -----------------------*/
  double vt;
  // Iteration over N values
  for (i=0;i<1;i++)
    {
      // Iteration over noise values
      for (j=0;j<ETAS;j++)
	{
	  vt=0;
	  // Average
	  for (k=0;k<N;k++)
	    {
	      vt += viscek(M[i],L[i],1,eta[j]);
	    }
	  va[i][j] = vt/N;
	  printf("%.4f\t%.4f\n",eta[j],va[i][j]);
	  fflush( stdout );
	  //printf("%d%%\n",j);
	}
    }
  
  /*------------------------- Print data ---------------------------*/
  // Prints each row of va followerd by eta each time
  /*for(i=0;i<1;i++)
    {
      for(j=0;j<ETAS;j++)
	{
	  printf("%.4f\t",va[i][j]);
	}
      printf("\n");
      for(k=0;k<ETAS;k++)
	{
	  printf("%.4f\t",eta[k]);
	}
     }*/
  
  /*----- Return ------*/
  printf("\a"); // Bell
  return 0;
}
