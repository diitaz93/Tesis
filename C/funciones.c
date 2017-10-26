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

//UPDATES THE POSITION AND ANGLE OF VELOCITY
void update(double x[], double y[], double angle[], int N, double r, double eta, double L, double v)
{
  int i, j;// indexes
  int cont; // counter
  double xt, yt, x_v, y_v; // Temporal position variables
  double sum_sin, sum_cos; // Sum of sines and cosines
  double at; // Temporal variable
  double dist; // Euclidean distance

  // Makes copy of array to make availiable the past angles
  double copy[N];
  for (i=0;i<=N-1;i++)
    {
      copy[i] = angle[i];
    }

  // Update
  for(i=0;i<=N-1;i++)
    {
        /************ Position Update ******************/
        // New coordinate is old coordinate plus velocity times time
        xt = x[i] + v*cos(copy[i]);
        yt = y[i] + v*sin(copy[i]);

        // Periodic boundary conditions
        x[i] = fabs( xt - L*floor( xt/L ) );
        y[i] = fabs( yt - L*floor( yt/L ) );
        /*************** Angle Update *****************/
        sum_sin = 0;//sum of sines of neighbourgs
        sum_cos = 0;//sum of cosines of neighbourgs
        cont = 0; // initializa counter in zero
        for(j=0;j<=N-1;j++)// Comparison
            {
              // X distance between particles j and i (j=0)
              x_v = fabs(x[j]-x[i]);
              // Y distance between particles j and i (j=0)
              y_v = fabs(y[j]-y[i]);
              // Find the lowest distance conseidering PBC
              x_v = fmin(x_v,L-xt);
              y_v = fmin(y_v,L-yt);

              // Compares euclidean distance
              dist = sqrt( pow(x_v, 2) + pow(y_v, 2));
              if ( dist < r )
                {
                  // If neighbourg, sum sines and cosines of angle
                  sum_sin += sin(copy[j]);
                  sum_cos += cos(copy[j]);
                  cont ++;
                }// end if
            }// end comparison
	/************* Arctan problem and noise ******************/
	// If there are no neighbourgs
	if (cont==0)
	  {
	    at = copy[i] + (double)rand()*eta/(double)RAND_MAX - 0.5*eta;
	  }
	else
	  {
	    at = atan2(sum_sin,sum_cos) + (double)rand()*eta/(double)RAND_MAX - 0.5*eta;
	  }
	// Only positive angles
	if (at < 0)
	  {
	    at += 2*M_PI;
	  }
	// Boundary Connditions
	angle[i] = fabs(at - 2*M_PI*floor(at/2*M_PI));

    }// end arctan
}// end update


//UPDATES THE POSITION AND ANGLE OF VELOCITY WITH ANGLE RESTRICTION
void var_an(double x[], double y[], double angle[], int N, double r, double eta, double L, double v, double phi)
{
  int i, j;// indexes
  int cont; // counter
  double xt, yt, x_v, y_v; // Temporal position variables
  double sum_sin, sum_cos; // Sum of sines and cosines
  double at, Th; // Temporal variable
  double dist;// Euclidean distance
  double in, out; // Inner and outer angles

  // Makes copy of array to make availiable the past angles
  double copy[N];
  for (i=0;i<=N-1;i++)
    {
      copy[i] = angle[i];
    }

  // Update
  for(i=0;i<=N-1;i++)
    {
        /************ Position Update ******************/
        // New coordinate is old coordinate plus velocity times time
        xt = x[i] + v*cos(copy[i]);
        yt = y[i] + v*sin(copy[i]);

        // Periodic boundary conditions
        x[i] = fabs( xt - L*floor( xt/L ) );
        y[i] = fabs( yt - L*floor( yt/L ) );
        /*************** Angle Update *****************/
        sum_sin = 0;//sum of sines of neighbourgs
        sum_cos = 0;//sum of cosines of neighbourgs
        cont = 0; // initializa counter in zero
        for(j=0;j<=N-1;j++)// Comparison
            {
              // X distance between particles j and i (j=0)
              x_v = x[j]-x[i];
              // If periodic distance is shorter
              if (L-fabs(x_v) < fabs(x_v))
              {
                if (x_v > 0)
                {
                    x_v = -(L-x_v);
                }
                else
                {
                    x_v = L - fabs(x_v);
                }
              }
              // Y distance between particles j and i (j=0)
              y_v = y[j]-y[i];
               // If periodic distance is shorter
              if (L-fabs(y_v) < fabs(y_v))
              {
                if (y_v > 0)
                {
                    y_v = -(L-y_v);
                }
                else
                {
                    y_v = L - fabs(y_v);
                }
              }
              // Euclidean distance
              dist = sqrt (pow(x_v,2) + pow(y_v,2));
              if (dist < r) // Radial neighbourgs
              {
                Th = atan2(y_v,x_v); // Determines angles of radial neighbourgs
                // Correct minus sign
                if (Th < 0)
                {
                    Th += 2*M_PI;
                }
                // Internal angle between velocity of i and position of j
                in = fabs(copy[j]-Th);
                // External angle between velocity of i and position of j
                out = -in+2*M_PI;
                // If any is in range, is angular neighbourg
                if (in < phi || out < phi)
                {
                    // If neighbourg, sum sines and cosines of angle
                    sum_sin += sin(copy[j]);
                    sum_cos += cos(copy[j]);
                    cont ++;
                }//end angular neighbourgs
              }//end radial neighbourgs
            }// end comparison
	/************* Arctan problem and noise ******************/
	// If there are no neighbourgs
	if (cont==0)
	  {
	    at = copy[i] + (double)rand()*eta/(double)RAND_MAX - 0.5*eta;
	  }
	else
	  {
	    at = atan2(sum_sin,sum_cos) + (double)rand()*eta/(double)RAND_MAX - 0.5*eta;
	  }
	// Only positive angles
	if (at < 0)
	  {
	    at += 2*M_PI;
	  }
	// Boundary Connditions
	angle[i] = fabs(at - 2*M_PI*floor(at/2*M_PI));

    }// end arctan
}// end update


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
