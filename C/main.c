#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// Include headers
#include "funciones.h"
#include "viscek.h"

#define SIZE 25
// Note: Mute viscek.c before running this simulation

int main()
{
  /*------------- Initialization of variables -------------------------*/
  // Number of particles for the simulations
  double M[SIZE] = {40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 500, 600, 700, 800, 900, 1000,
		1100, 1200, 1300, 1400, 1500, 1600, 2000, 3000, 4000};
  // Size of cell
  double L = 20;
  // Density array
  double rho[SIZE];
  int i, j;
  for (i=0;i<SIZE;i++)
    {
      rho[i] = M[i]/pow(L,2);
    }
  //Noise
  double eta = 3;
  // Order parameter
  double va[SIZE];
  // Number of runs
  int N = 100;
  
  /*----------------------- Computation of data -----------------------*/
  double vt; // Temporal variable
  //printf("Nos fuimos!\n");
  for (i=0;i<SIZE;i++)
    {
      vt = 0;
      for (j=0;j<N;j++)
	{ 
	  vt += viscek(M[i],L,1,eta);
	}
      va[i] = vt/N;
      //printf("%d\%%\n",i*4);
    }
  
  /*------------------------- Print data ---------------------------*/
  for (i=0;i<SIZE;i++)
    {
      printf("%.4f\t%.4f\n", rho[i], va[i]);
    }
  
  /*----- Return ------*/
  return 0;
}
