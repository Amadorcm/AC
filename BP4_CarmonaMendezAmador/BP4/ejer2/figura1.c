#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#define TAM 10000
#define TAM1 5000
int R[TAM];
struct
{
	int a;
	int b;
}	s[TAM1];
//funciones que voy a utilizar
void original(int R[]);
void modificadoA(int R[]);
void modificadoB(int R[]);

int main( int argc, char * argv[]){

//comprobamos argumentos 
	/*if(argc<2){
		printf("");
		exit(-1);
	}
//almacenar el tamaño de la matriz
	unsigned int N=atoi(argv[1]);
	if(N>TAM){
		N=TAM;
	}*/
//creacion de las variables que miden el tiempo
	struct timespec ctgsec1,ctgsec2,ctga1,ctga2,ctgb1,ctgb2,ctgpar1,ctgpar2;
	double nctgsec,nctga,nctgb,nctgpar;
/*//Rellenamos las matrices
	for(int i=0;i<N;i++){
		for(int j=0; j<N; j++){
			m1[i][j]=drand48();
			m2[i][j]=drand48();
		}
	}*/
//programa original
	
	clock_gettime(CLOCK_REALTIME,&ctgsec1);
	original(R);
	clock_gettime(CLOCK_REALTIME,&ctgsec2);
	nctgsec=(double)(ctgsec2.tv_sec-ctgsec1.tv_sec)+(double)((ctgsec2.tv_nsec-ctgsec1.tv_nsec)/(1.e+9));
	printf("\nTiempo modificadoB: %11.9f | Tamaño: %d | R[0]=%d | R[%d]=%d",nctgb,TAM,R[0],TAM-1,R[TAM-1]);
//programa modificadoA
	
	clock_gettime(CLOCK_REALTIME,&ctga1);
	modificadoA(R);
	clock_gettime(CLOCK_REALTIME,&ctga2);
	nctga=(double)(ctga2.tv_sec-ctga1.tv_sec)+(double)((ctga2.tv_nsec-ctga1.tv_nsec)/(1.e+9));
	printf("\nTiempo modificadoB: %11.9f | Tamaño: %d | R[0]=%d | R[%d]=%d",nctgb,TAM,R[0],TAM-1,R[TAM-1]);

//programa modificadoB
	
	clock_gettime(CLOCK_REALTIME,&ctgb1);
	modificadoB(R);
	clock_gettime(CLOCK_REALTIME,&ctgb2);
	nctgb=(double)(ctgb2.tv_sec-ctgb1.tv_sec)+(double)((ctgb2.tv_nsec-ctgb1.tv_nsec)/(1.e+9));
	printf("\nTiempo modificadoB: %11.9f | Tamaño: %d | R[0]=%d | R[%d]=%d",nctgb,TAM,R[0],TAM-1,R[TAM-1]);
/*//programa paralelo
	
	clock_gettime(CLOCK_REALTIME,&ctgpar1);
	modificadoB(m1,m2,m3,N);
	clock_gettime(CLOCK_REALTIME,&ctgpar2);
	nctgpar=(double)(ctgpar2.tv_sec-ctgpar1.tv_sec)+(double)((ctgpar2.tv_nsec-ctgpar1.tv_nsec)/(1.e+9));
	printf("\nTiempo paralelo: %11.9f | Tamaño: %d | m3[0][0]=%f | m3[%d][%d]=%f",nctgpar,N,m3[0][0],N-1,N-1,m3[N-1][N-1]);*/

}

void original(int R[]){
	int X1, X2;
	for(int i=0; i<TAM; i++){
		X1=0;
		X2=0;
		for(int j=0;j<TAM1; j++){
			X1+=2*s.a[i]+j;
		}
		for(int j=0;j<TAM1; j++){
			X2+=3*s.b[i]+j;
		}
		if(X1<X2){
			R[i]=X1;
		}else{
			R[i]=X2;
		}
	}
}
void modificadoB(int R[]){
	int X1, X2;
	for(int ii=0; ii<TAM; ii++){
		X1=0;
		X2=0;
		for(int ii=0;ii<TAM1; ii+=10){
			X1+=2*s.a[i]+ii;
			X2+=3*s.b[i]+ii;
			X1+=2*s.a[i+1]+ii;
			X2+=3*s.b[i+1]+ii;
			X1+=2*s.a[i+2]+ii;
			X2+=3*s.b[i+2]+ii;
			X1+=2*s.a[i+3]+ii;
			X2+=3*s.b[i+3]+ii;
			X1+=2*s.a[i+4]+ii;
			X2+=3*s.b[i+4]+ii;
			X1+=2*s.a[i+5]+ii;
			X2+=3*s.b[i+5]+ii;
			X1+=2*s.a[i+6]+ii;
			X2+=3*s.b[i+6]+ii;
			X1+=2*s.a[i+7]+ii;
			X2+=3*s.b[i+7]+ii;
			X1+=2*s.a[i+8]+ii;
			X2+=3*s.b[i+8]+ii;
			X1+=2*s.a[i+9]+ii;
			X2+=3*s.b[i+9]+ii;
		}
		if(X1<X2){
			R[i]=X1;
		}else{
			R[i]=X2;
		}
	}
}
void modificadoA(int R[]){
	int X1, X2;
	for(int ii=0; ii<TAM; ii++){
		X1=0;
		X2=0;
		for(int i=0;i<TAM1; i++){
			X1+=2*s.a[i]+ii;
		}
		for(int i=0;i<TAM1; i++){
			X2+=3*s.b[i]+ii;
		}
		R[i]=(X1<X2) ? X1:X2;
	}
}