#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#define TAM 10000
double m1[TAM][TAM],m2[TAM][TAM],m3[TAM][TAM];
//funciones que voy a utilizar
void secuencial(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N);
void modificadoA(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N);
void modificadoB(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N);
void paralelo(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N);
void borrarMatriz(double m3[][TAM],int N);

int main( int argc, char * argv[]){

//comprobamos argumentos 
	if(argc<2){
		printf("Falta el tamaño de las matrices");
		exit(-1);
	}
//almacenar el tamaño de la matriz
	unsigned int N=atoi(argv[1]);
	if(N>TAM){
		N=TAM;
	}
//creacion de las variables que miden el tiempo
	struct timespec ctgsec1,ctgsec2,ctga1,ctga2,ctgb1,ctgb2,ctgpar1,ctgpar2;
	double nctgsec,nctga,nctgb,nctgpar;
//Rellenamos las matrices
	for(int i=0;i<N;i++){
		for(int j=0; j<N; j++){
			m1[i][j]=drand48();
			m2[i][j]=drand48();
		}
	}
//programa secuencial
	borrarMatriz(m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgsec1);
	secuencial(m1,m2,m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgsec2);
	nctgsec=(double)(ctgsec2.tv_sec-ctgsec1.tv_sec)+(double)((ctgsec2.tv_nsec-ctgsec1.tv_nsec)/(1.e+9));
	printf("\nTiempo secuencial: %11.9f | Tamaño: %d | m3[0][0]=%f | m3[%d][%d]=%f ",nctgsec,N,m3[0][0],N-1,N-1,m3[N-1][N-1]);
//programa modificadoA
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
	printf("\nTiempo modificadoB: %11.9f | Tamaño: %d | m3[0][0]=%f | m3[%d][%d]=%f",nctgb,N,m3[0][0],N-1,N-1,m3[N-1][N-1]);
//programa paralelo
	borrarMatriz(m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgpar1);
	modificadoB(m1,m2,m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgpar2);
	nctgpar=(double)(ctgpar2.tv_sec-ctgpar1.tv_sec)+(double)((ctgpar2.tv_nsec-ctgpar1.tv_nsec)/(1.e+9));
	printf("\nTiempo paralelo: %11.9f | Tamaño: %d | m3[0][0]=%f | m3[%d][%d]=%f",nctgpar,N,m3[0][0],N-1,N-1,m3[N-1][N-1]);

}







void secuencial(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N){
	for(int i=0; i<N; i++){
		for(int j=0;j<N; j++){
			for(int k=0;k<N; k++){
				m3[i][j]+=m1[i][k]*m2[k][j];
			}
		}
	}
}
void modificadoA(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N){
	double t0,t1,t2,t3,t4,t5,t6,t7,t8,t9;
	for(int i=0; i<N; i++){
		for(int j=0;j<N; j++){
			t0=0;t1=0;t2=0;t3=0;t4=0;t5=0;t6=0;t7=0;t8=0;t9=0;
			for(int k=0;k<N; k+=10){
				t0+=m1[i][k]*m2[k][j];
				t1+=m1[i][k+1]*m2[k+1][j];
				t2+=m1[i][k+2]*m2[k+2][j];
				t3+=m1[i][k+3]*m2[k+3][j];
				t4+=m1[i][k+4]*m2[k+4][j];
				t5+=m1[i][k+5]*m2[k+5][j];
				t6+=m1[i][k+6]*m2[k+6][j];
				t7+=m1[i][k+7]*m2[k+7][j];
				t8+=m1[i][k+8]*m2[k+8][j];
				t9+=m1[i][k+9]*m2[k+9][j];
			}
			m3[i][j]=t0+t1+t2+t3+t4+t5+t6+t7+t8+t9;
		}
	}
}
void modificadoB(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N){
	for(int i=0; i<N; i++){
		for(int k=0;k<N; k++){
			for(int j=0;j<N; j++){
				m3[i][j]+=m1[i][k]*m2[k][j];
			}
		}
	}
}
void paralelo(double m1[][TAM],double m2[][TAM],double m3[][TAM], int N){
	//#pragma omp parallel for	
	for(int i=0; i<N; i++){
		#pragma omp parallel for
		for(int k=0;k<N; k++){
			for(int j=0;j<N; j++){
				m3[i][j]+=m1[i][k]*m2[k][j];
			}
		}
	}
}
void borrarMatriz(double m3[][TAM],int N){
	for(int i=0; i<N; i++){
		for(int j=0;j<N; j++){
			m3[i][j]=0;
		}
	}
}
