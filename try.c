#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
  double eta=0.01;
  srand(time(0));
  double x = (double)rand();
  printf("%.4f\n",x);
  printf("%.4f\n",x + (double)rand()*eta-0.5*eta);
  return 0;
}
