#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "funciones.h"
#include "viscek.h"

int main()
{
  double va = viscek(200,5,1,0.1);
  printf("%.4f",va);
  return 0;
}
