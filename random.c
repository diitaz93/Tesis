#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(0));
  int r=rand();
  double d=(double)r/(double)RAND_MAX;
  printf("Randmax=%d, random=%d, fraction=%.3f\n", RAND_MAX, r, d);
  return 1;
}
