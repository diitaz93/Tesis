#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
/*Entra por parametro el numero de particulas.
  Se usa un cuadrado de lado 1.0 y velocidad de 1.0*/
{
  //Inicializacion
  int N = atoi(argv[1]);//Numero de particulas
  double x[N];//Coordenada x
  double y[N];// Coordenada y
  double angle[N];// Angulo
  int i;//Contador  
  srand(time(0));//Se planta la funcion rand con el tiempo
  
  printf("x\t y\t Ángulo\n");//Se imprime el encabezado (opcional)
  
  //Se inicializan las coordenadas de N particulas aleatoriamente
  for(i=0;i<N;i++)
    {
      x[i] = (double)rand() / (double)RAND_MAX;
      y[i] = (double)rand() / (double)RAND_MAX;
      angle[i] = (double)rand()*2*M_PI / (double)RAND_MAX;
      printf("%.4f\t %.4f\t %.4f\n",x[i],y[i],angle[i]);
    }
  
  return 0;
}
