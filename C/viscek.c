#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//Other function headers
#include "funciones.h"

double viscek(int N, double L, double r, double eta)
{
  // Variables & Arrays
  double x[N]; // x coordinate
  double y[N]; // y coordinate
  double angle[N]; // Angle
  double v = 0.03;

  // Initialization
  initial(x, y, angle, N, L);
  //screenshot(x, y, angle, N);

  // Temporal evolution
  int i;
  for (i=0; i<=STEPS-1; i++)
    {
      new_coord(x, y, angle, N, v, L);
      new_angle(x, y, angle, N, r, eta, L);
      //screenshot(x, y, angle, N);
      
    }
  
  // Return order parameter
  double va = v_a(N, angle);
  return va;

}

