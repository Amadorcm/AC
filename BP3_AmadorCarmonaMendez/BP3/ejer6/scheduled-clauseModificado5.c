#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
#endif
int main(int argc, char ** argv){
	int i, n = 200, chunk, a[n], suma = 0, mod;
	omp_sched_t tipo;
	if(argc < 3){
		fprintf(stderr,"\nFalta iteraciones o chunk \n");
		exit(-1);
	}
	n = atoi(argv[1]);
	if(n>200) 
		n=200;
	chunk = atoi(argv[2]);
	int dyn = omp_get_dynamic(), nthreads = omp_get_max_threads(), limit = omp_get_thread_limit();
	
	omp_get_schedule(&tipo, &mod); 
 
	for(i=0; i<n; i++) a[i]=i;
		#pragma omp parallel for firstprivate(suma) lastprivate(suma) schedule(dynamic, chunk)
		for(i=0;i<n;i++){
			suma = suma + a[i];
			printf("thread %d suma a[%d] suma=%d \n", omp_get_thread_num(), i, suma);
		}
		#pragma omp single
			omp_get_schedule(&tipo, &mod);
			printf("\nValores actuales: dynamic: %d, nthreads: %d, tipo: %d,mod: %d]\n", omp_get_dynamic(), omp_get_max_threads(), tipo, mod);
			omp_set_dynamic(9);
			omp_set_num_threads(2);
			omp_set_schedule(omp_sched_guided, chunk + 3);
			omp_get_schedule(&tipo, &mod);
			printf("\nValores modicados: dynamic: %d, nthreads: %d, tipo: %d, mod: %d]\n", omp_get_dynamic(), omp_get_max_threads(), tipo, mod);
		printf("Fuera de 'parallel for' suma=%d\n", suma);
}