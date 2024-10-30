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
				printf("\nthread %d suma a[%d] suma=%d \n", omp_get_thread_num(), i, suma);
				printf("omp_get_num_threads() = %d \n", omp_get_num_threads());
			}

			printf("\nDentro de la región parallel:\nomp_get_num_threads() = %d \nomp_get_num_procs() = %d \n omp_in_parallel() = %d \n", omp_get_num_threads(), omp_get_num_procs(), omp_in_parallel());
			
		printf("\nFuera de la región parallel: \nomp_get_num_threads()= %d \n omp_get_num_procs() = %d \n omp_in_parallel() = %d \n", omp_get_num_threads(), omp_get_num_procs(), omp_in_parallel());
}