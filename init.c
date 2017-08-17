#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define STEPS 19 //Number of timesteps (minus one due to init) for temporal evolution

/************************* FUNCTION PROTOTYPES ************************************/
void initial(double x[], double y[], double angle[], int N, double L);
void screenshot(double x[], double y[], double angle[], int N);
void new_angle(double x[], double y[], double angle[], int N, double r, double eta);
void new_coord(double x[], double y[], double angle[], int N, double v, double L);

/******************************** MAIN ********************************************/
int main(int argc, char **argv)
/* User must type number of particles N, length of square L, noise (eta), and radius of interaction */
{
  // Variables
  int N = atoi(argv[1]);// Number of particles
  double x[N]; // x coordinate
  double y[N]; // y coordinate
  double angle[N]; // Angle
  double L = atof(argv[2]);// Side of square
  double v = 0.03; // Norm of velocity
  double r = atof(argv[4])*L; // First neighbourg radius as a fraction of L
  double eta = atof(argv[3]); //Noise coefficient

  // Initialization
  initial(x, y, angle, N, L);
  screenshot(x, y, angle, N);

  // Temporal evolution
  int i;
  for (i=0; i<=STEPS-1; i++)
    {
      new_coord(x, y, angle, N, v, L);
      new_angle(x, y, angle, N, r, eta);
      screenshot(x, y, angle, N);
      
    }

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
void new_angle(double x[], double y[], double angle[], int N, double r, double eta)
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
	      sum_sin += sin(copy[j]);
	      sum_cos += cos(copy[j]);
	    }// end if
	}// end comparison
      
      at = atan( sum_sin/sum_cos );//new angle calculation
      // values between 0 and 2pi, fix arctan error (EFICIENCY ALERT!!)
      (sum_cos < 0) ? (angle[i] = at + M_PI) : (angle[i] = at);
      angle[i] += (double)rand()*eta/(double)RAND_MAX - 0.5*eta; //Noise added
      (angle[i] < 0) ? (angle[i] += 2*M_PI) : (angle[i] = angle[i]);
    }// end update
}// end new_angle

// UPDATES POSITIONS
void new_coord(double x[], double y[], double angle[], int N, double v, double L)
{
  int i; // index
  double xt, yt; // Temporal variables
  for(i=0;i<=N-1;i++)
    {
      // New coordinate is old coordinate plus velocity times time
      xt = x[i] + v*cos(angle[i]);
      yt = y[i] + v*sin(angle[i]);
      
      // Periodic boundary conditions
      x[i] = fabs( xt - L*floor( xt/L ) );
      y[i] = fabs( yt - L*floor( yt/L ) );
      
    } // end update
} // end new_coord

