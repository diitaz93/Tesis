#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
  int N;
  N=atoi(argv[1]);
  srand(time(0));
  double x;
  double y;
  int i;
  printf("x\t y\n");
  for(i=0;i<N;i++)
    {
      x=(double)rand()/(double)RAND_MAX;
      y=(double)rand()/(double)RAND_MAX;
      printf("%.4f\t %.4f\n",x,y);
    }
  return 1;
}
