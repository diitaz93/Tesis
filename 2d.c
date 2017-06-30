#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(0));
  int r=rand();
  printf("Randmax=%d, random=%d", RAND_MAX, r);
  return 1;
}
