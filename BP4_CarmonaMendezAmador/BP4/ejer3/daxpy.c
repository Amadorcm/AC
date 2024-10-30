#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#define TAM 100000
double x[TAM],y[TAM];
//funciones que voy a utilizar
void daxpy(double x[], double y[], const double a, unsigned int N);


int main( int argc, char * argv[]){

//comprobamos argumentos 
	if(argc<2){
		printf("Falta el tamaño del vector");
		exit(-1);
	}
//almacenar el tamaño de la matriz
	unsigned int N=atoi(argv[1]);
	if(N>TAM){
		N=TAM;
	}
//creacion de las variables que miden el tiempo
	struct timespec ctgsec1,ctgsec2,ctga1,ctga2,ctgb1,ctgb2;
	double nctgsec,nctga,nctgb;
//asignamos valores
	const double a = 1.5;
    for (int i = 0; i < TAM; i++) {
        x[i] = (rand() % 15) * 2;
        y[i] = (rand() % 23) * 3;
    }
//programa secuencial
	//borrarMatriz(m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgsec1);
	daxpy(x,y,a,N);
	clock_gettime(CLOCK_REALTIME,&ctgsec2);
	nctgsec=(double)(ctgsec2.tv_sec-ctgsec1.tv_sec)+(double)((ctgsec2.tv_nsec-ctgsec1.tv_nsec)/(1.e+9));
	printf("\nTiempo secuencial: %11.9f | Tamaño: %d | y[%d] = %f\t | y[%d] = %f\n", nctgsec, 0, y[0], N-1, y[N-1]);
/*//programa modificadoA
	borrarMatriz(m3,N);
	clock_gettime(CLOCK_REALTIME,&ctga1);
	modificadoA(m1,m2,m3,N);
	clock_gettime(CLOCK_REALTIME,&ctga2);
	nctga=(double)(ctga2.tv_sec-ctga1.tv_sec)+(double)((ctga2.tv_nsec-ctga1.tv_nsec)/(1.e+9));
	printf("\nTiempo modificadoA: %11.9f | Tamaño: %d | m3[0][0]=%f | m3[%d][%d]=%f",nctga,N,m3[0][0],N-1,N-1,m3[N-1][N-1]);

//programa modificadoB
	borrarMatriz(m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgb1);
	modificadoB(m1,m2,m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgb2);
	nctgb=(double)(ctgb2.tv_sec-ctgb1.tv_sec)+(double)((ctgb2.tv_nsec-ctgb1.tv_nsec)/(1.e+9));
	printf("\nTiempo modificadoB: %11.9f | Tamaño: %d | m3[0][0]=%f | m3[%d][%d]=%f",nctgb,N,m3[0][0],N-1,N-1,m3[N-1][N-1]);**/

}




void daxpy (double x[], double y[], const double a, unsigned int N) {
    for (unsigned int i = 0; i < N; i++)
        y[i] = a*x[i] + y[i];
}
