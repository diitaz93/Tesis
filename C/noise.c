/*--------------------------------------------------------------------------
                              NOISE
This program generates data to make plot of noise vs. va for various values
of N.
------------------------------------------------------------------------- */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// Include headers
#include "funciones.h"
#include "viscek.h"

#define NS 5 // Number of plots (Ns)
#define ETAS 50 //Number of points in ach plot
// Note: Mute viscek.c before running this simulation

int main()
{
  /*------------- Initialization of variables -------------------------*/
  // Indices
  int i,j,k;
  // Number of particles for the simulations
  double M[NS] = {40, 100, 400, 4000, 10000};
  // Size of cell
  double L[NS] = {3.1, 5, 10, 31.6, 50};
  // Noise
  double eta[ETAS];
  // Number of runs
  double N[ETAS];
  // Initialize eta from 0 to ETAS and N
  for(i=1;i<ETAS+1;i++)
    {
      eta[i-1] = (double)(5*i)/ETAS;
      N[i-1] = 2000*eta[i-1];
    }
  // Complete initialization for N
  for (i=0;i<10;i++)
    {
      N[i] = 1000;
    }
  // Order parameter
  double va[NS][ETAS];
  // Standard Deviation
  double err[NS][ETAS];
  /*----------------------- Computation of data -----------------------*/
  double vt; // Temporal velocity
  double et; // Temporal stdev
  double V; // Temporal variable
  // Iteration over N values
  for (i=0;i<1;i++)
    {
      // Iteration over noise values
      for (j=0;j<ETAS;j++)
	{
	  vt = 0;
	  et = 0;
	  // Average
	  for (k=0;k<N[j];k++)
	    {
	      V = viscek(M[i],L[i],1,eta[j]);
	      vt += V;
	      et += pow(V,2);
	    }
	  va[i][j] = vt/N[j];
	  err[i][j] = sqrt( et/N[j] - pow(va[i][j],2) );
	  printf("%.4f\t%.4f\t%.4f\n",eta[j],va[i][j],err[i][j]); // Print data
	  fflush( stdout ); // Clear buffer
	  //printf("%d%%\n",j);
	}
    }
  
  /*----- Return ------*/
  printf("\a"); // Bell
  return 0;
}
