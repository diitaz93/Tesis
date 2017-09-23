#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
void new_angle(double x[], double y[], double angle[], int N, double r, double eta, double L)
{
  int i, j;// indexes
  double sum_sin, sum_cos;
  double at; // Temporal variable
  double dist_eu, dist_per;

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
	  dist_eu = sqrt( pow( (x[i]-x[j]), 2) + pow( (y[i]-y[j]), 2));
	  dist_per = sqrt ( pow( (L-fabs(x[i]-x[j])) ,2) + pow( (L-fabs(y[i]-y[j])) ,2));
			  
	  if ( dist_eu < r || dist_per < r )
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

// CALCULATES ORDER PARAMETER
double v_a(int N, double angle[])
{
  double vx = 0;
  double vy = 0;
  int i;
  for(i=0;i<N-1;i++)
    {
      vx += cos(angle[i]);
      vy += sin(angle[i]);
    }

  double va = sqrt( pow(vx,2) + pow(vy,2) )/N;
  return va;

}
