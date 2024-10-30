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
			printf("\nthread %d dynamic %d \n", omp_get_thread_num(), dyn);
			printf("thread %d  nthreads %d \n", omp_get_thread_num(), nthreads);
			printf("thread %d  limit %d \n", omp_get_thread_num(), limit);
			printf("thread %d  mod %d \n", omp_get_thread_num(), mod);
			if(tipo == omp_sched_static)
				printf("Es estático \n");
			if(tipo == omp_sched_dynamic)
				printf("Es dinámico \n");
			if(tipo == omp_sched_guided)
				printf("Es guided \n");
	
		printf("\nFuera de 'parallel for'\n suma %d\n dynamic %d\n nthreads %d\n limit %d\n mod %d\n",suma,dyn, nthreads, limit, mod);
		if(tipo == omp_sched_static) 
			printf("Es estático \n");
		if(tipo == omp_sched_dynamic) 
			printf("Es dinámico \n");
		if(tipo == omp_sched_guided) 
			printf("Es guided \n");
}
