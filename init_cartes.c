#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
/*Entran por parametro el numero de particulas, el tamanio del cuadrado y la velocidad maxima*/
{
  //Numero de particulas
  int N;
  N=atoi(argv[1]);
  //Tamanio del cuadrado
  double L;
  L=atoi(argv[2]);
  //Velocidad maxima
  double V;
  V=atoi(argv[3]);
  // Se incializan las variables espaciales y las velocidades
  double x,y;
  double vx,vy;
  
  int i;//Contador
  srand(time(0));//Se planta la funcion rand con el tiempo
  printf("x\t y\t vx\t vy\n");//Se imprime el encabezado (opcional)
  //Se inicializan las coordenadas de N particulas aleatoriamente
  for(i=0;i<N;i++)
    {
      x=(double)rand()*L/(double)RAND_MAX;
      y=(double)rand()*L/(double)RAND_MAX;
      vx=(double)rand()*V/(double)RAND_MAX;
      vy=sqrt(pow(V,2)-pow(vx,2));
      printf("%.4f\t %.4f\t %.4f\t %.4f\n",x,y,vx,vy);//imprime la coordenada con 4 decimales
    }
  return 1;
}
