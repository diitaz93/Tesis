#ifndef FUNCIONES
#define FUNCIONES

#define STEPS 99 //Number of timesteps (minus one due to init) for temporal evolution

/************************* FUNCTION PROTOTYPES ************************************/
void initial(double x[], double y[], double angle[], int N, double L);
void screenshot(double x[], double y[], double angle[], int N);
void update(double x[], double y[], double angle[], int N, double r, double eta, double L, double v);
void var_an(double x[], double y[], double angle[], int N, double r, double eta, double L, double v, double phi);
double v_a(int N, double angle[]);

#endif
