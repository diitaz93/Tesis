#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/************************* FUNCTION PROTOTYPES ************************************/
void initial(double x[], double y[], double angle[], int N, double L);
void screenshot(double x[], double y[], double angle[], int N);
void new_angle(double x[], double y[], double angle[], int N, double r);
void new_coord(double x[], double y[], double angle[], int N, double delta_t, double v, double L);

/******************************** MAIN ********************************************/
int main(int argc, char **argv)
/* User must type number of particles N */
{
  // Variables
  int N = atoi(argv[1]);// Number of particles
  double x[N]; // x coordinate
  double y[N]; // y coordinate
  double angle[N]; // Angle
  double L = 1.0;// Side of square
  double v = 0.03; // Norm of velocity
  double r = 1.0; // First neighbourg radius
  double delta_t = 1.0; // Timestep

  // Initialization
  initial(x, y, angle, N, L);
  screenshot(x, y, angle, N);

  // Temporal evolution
  new_coord(x, y, angle, N, delta_t, v, L);
  new_angle(x, y, angle, N, r);
  screenshot(x, y, angle, N);

  // Return
  return 0;
}

/******************** FUNCTIONS *****************************************/

// INITIALIZES ARRAYS RANDOMLY
void initial(double x[], double y[], double angle[], int N, double L)
{
  srand(time(0));// rand is seeded with time
  int i;
  for(i=0;i<=N-1;i++)
    {
      x[i] = (double)rand()*L / (double)RAND_MAX;
      y[i] = (double)rand()*L / (double)RAND_MAX;
      angle[i] = (double)rand()*2*M_PI / (double)RAND_MAX;
    }
}

// PRINTS IN ROWS THE 3 ARRAYS (EFFICIENCY ALERT!!)
void screenshot(double x[], double y[], double angle[], int N)
{
  int i;
  //x
  for(i=0;i<=N-1;i++)
    {
      printf("%.4f\t",x[i]);
    }
  printf("\n");
  //y
  for(i=0;i<=N-1;i++)
    {
      printf("%.4f\t",y[i]);
    }
  printf("\n");
  //angle
  for(i=0;i<=N-1;i++)
    {
      printf("%.4f\t",angle[i]);
    }
  printf("\n");
}

//UPDATES THE ANGLE OF VELOCITY
void new_angle(double x[], double y[], double angle[], int N, double r)
{
  int i, j;// indexes
  double sum_sin, sum_cos;
  double at; // Temporal variable
  
  // Makes copy of array
  double copy[N];
  for (i=0;i<=N-1;i++)
    {
      copy[i] = angle[i];
    }
  
  // Update	 
  for(i=0;i<=N-1;i++)
    {
      sum_sin = 0;//sum of sines of neighbourgs
      sum_cos = 0;//sum of cosines of neighbourgs
      
      for(j=0;j<=N-1;j++)// Comparison
	{
	  // Compares euclidean distance
	  if ( sqrt( pow( (x[i]-x[j]), 2) + pow( (y[i]-y[j]), 2) ) < r )
	    {
	      // If neighbourg, sum sines and cosines of angle
	      sum_sin+=sin(copy[j]);
	      sum_cos+=cos(copy[j]);
	    }// end if
	}// end comparison
      
      at=atan( sum_sin/sum_cos );//new angle calculation
      // values between 0 and 2pi
      angle[i] = at;//fabs( at - 2 * M_PI * floor( at/2*M_PI ) );
    }// end update
}// end new_angle

// UPDATES POSITIONS
void new_coord(double x[], double y[], double angle[], int N, double delta_t, double v, double L)
{
  int i; // index
  double xt, yt; // Temporal variables
  for(i=0;i<=N-1;i++)
    {
      // New coordinate is old coordinate plus velocity times time
      xt = x[i] + v*cos(angle[i])*delta_t;
      yt = y[i] + v*sin(angle[i])*delta_t;
      
      // Periodic boundary conditions
      x[i] = fabs( xt - L*floor( xt/L ) );
      y[i] = fabs( yt - L*floor( yt/L ) );
      
    } // end update
} // end new_coord

