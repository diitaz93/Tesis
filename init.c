#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
/*Entra por parametro el numero de particulas.
  Se usa un cuadrado de lado 1.0 y velocidad de 1.0*/
{
  //Numero de particulas
  int N;
  N=atoi(argv[1]);
  /*Tamanio del cuadrado
  double L;
  L=atoi(argv[2]);
  */
  /*Velocidad maxima
  double V;
  V=atoi(argv[3]);
  */
  // Se incializan las variables espaciales y la direccion de la velocidad
  double x,y;
  double T;
  
  int i;//Contador
  srand(time(0));//Se planta la funcion rand con el tiempo
  printf("x\t y\t T\n");//Se imprime el encabezado (opcional)
  //Se inicializan las coordenadas de N particulas aleatoriamente
  for(i=0;i<N;i++)
    {
      x=(double)rand()/(double)RAND_MAX;
      y=(double)rand()/(double)RAND_MAX;
      T=(double)rand()*2*M_PI/(double)RAND_MAX;
      printf("%.4f\t %.4f\t %.4f\n",x,y,T);//imprime la coordenada con 4 decimales
    }
  return 1;
}
