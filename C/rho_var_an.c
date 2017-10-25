/*------------------------------------------------------------------------------
                                    RHO
This program generate data to plot rho vs. va fro the viscek model.
------------------------------------------------------------------------------ */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// Include headers
#include "funciones.h"
#include "viscek.h"

#define SIZE 25 //Numbero of points in the plot
// Note: Mute viscek.c before running this simulation

int main()
{
  /*------------- Initialization of variables -------------------------*/
  // Indices
  int i, j;
  // Restriction angle
  double phi = M_PI/2;
  // Number of particles for the simulations
  double M[SIZE] = {40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 500, 600, 700, 800, 900, 1000,
		1100, 1200, 1300, 1400, 1500, 1600, 2000, 3000, 4000};
  // Size of cell
  double L = 20;
  // Density array
  double rho[SIZE];
  // Initialize rho as N divided by area (L²)
  for (i=0;i<SIZE;i++)
    {
      rho[i] = M[i]/pow(L,2);
    }
  //Noise
  double eta = 2.75;
  // Order parameter
  double va[SIZE];
  // Standard deviation
  double err[SIZE];
  // Number of runs
  int N[SIZE] = {5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 2500, 2500, 2500,
		 2500, 2500, 2000, 2000, 2000, 2000, 2000, 500, 500, 500, 500, 500};
  
  /*----------------------- Computation of data -----------------------*/
  double vt; // Temporal velocity
  double et; // Temporal stdev
  double V; // Temporal variable
  // Loop over points
  for (i=0;i<SIZE;i++)
    {
      vt = 0;
      et = 0;
      // Average
      for (j=0;j<N[i];j++)
	{
	  V = viscek_var_an(M[i],L,1,eta,phi);
	  vt += V;
	  et += pow(V,2);
	}
      va[i] = vt/N[i]; // Average velocity
      err[i] = sqrt( et/N[i] - pow(va[i],2) ); //Stdev
      printf("%.4f\t%.4f\t%.4f\n", rho[i], va[i], err[i]); // Print data
      fflush(stdout); // Clear buffer
      //printf("%d\%%\n",i*4);
    }
  
  /*----- Return ------*/
  printf("\a"); //Bell
  return 0;
}
