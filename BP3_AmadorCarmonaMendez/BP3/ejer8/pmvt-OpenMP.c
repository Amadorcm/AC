#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main (int argc, char * argv[]){
	if(argc < 2){
		fprintf(stderr,"faltan las filas de la matriz.\n");
		exit(-1);
	}
	unsigned int TAM, i, j;
	unsigned int **matriz, *vector1, *vector2;
	double tiempo, t1,t2;
	//-------------------------------------------------------------

	TAM = atoi(argv[1]);
	vector1 = (unsigned int*) malloc(TAM*sizeof(unsigned int));
	vector2 = (unsigned int*) malloc(TAM*sizeof(unsigned int));
	//-------------------------------------------------------------
	if ((vector1==NULL) || (vector2==NULL) ){
		printf("Error en la reserva de espacio\n");
		exit(-2);
	}
	//--------------------------------------------------------------
	matriz = (unsigned int**) malloc(TAM*sizeof(unsigned int*));
	if ( (matriz==NULL)){
	printf("Error en la reserva de espacio\n");
		exit(-3);
	}
	//--------------------------------------------------------------
	for(i=0; i<TAM; i++){
		matriz[i]=(unsigned int*)malloc(TAM*sizeof(unsigned int));
	}
	if ( (matriz[i]==NULL)){
		printf("Error en la reserva de espacio \n");
		exit(-3);
	}


	//---------------------------------------------------------------
	#pragma omp parallel for private(j)
		for(i=0; i<TAM; i++){
			for(j=0; j<i; j++){
				matriz[i][j]=0;
			}
			for(j=i; j<TAM; j++){
				matriz[i][j]=rand()%100;
			}
		}
	for(i=0; i<TAM; i++){
		vector1[i]=rand()%100;
		vector2[i]=0;
	}
	t1 = omp_get_wtime();
	#pragma omp parallel for private(j) schedule(runtime)
		for(i=0; i<TAM; i++){
			for(j=i; j<TAM; j++){
				vector2[i]+=matriz[i][j]*vector1[j];
			}
		}
	//-----------------------------------------------------------------
	t2=omp_get_wtime();
	tiempo=t2-t1;
	//------------------------------------------------------------------
	//printf("t1 %f, t2 %f",t1,t2);
	printf("Tiempo(seg.): %11.9f\t / Tamaño Vectores: %u",tiempo,TAM);
	printf("Matriz: \n");
		for(i=0; i<TAM; i++){
			for(j=0; j<TAM; j++)
				if(j >= i)
					printf("%d ", matriz[i][j]);
				else
					printf("0 ");
			printf("\n");
		}
		printf("Vector: \n");
		for(i=0; i<TAM; i++)
			printf("%d ", vector1[i]);
		printf("\n");
		printf("Resultado: \n");
		for(i=0; i<TAM; i++)
			printf("%d ", vector2[i]);
		printf("\n");


	//------------------------------------------------------------------
	free(vector1);
	free(vector2);
	for(i=0; i<TAM; i++){
		free(matriz[i]);
	}
	free(matriz);
}