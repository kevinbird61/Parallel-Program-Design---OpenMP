#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define A_SIZE 100000

int *Random_generate_array(int size);

int main(int argc , char* argv[]){
	/* Define the variable */
	int size,i,j,count;
	int thread_count;
	thread_count = strtol(argv[1] , NULL , 10);	
	int *array= Random_generate_array(A_SIZE);
	size = A_SIZE;
	clock_t start , end;
	float result;
	/* Counting Time */
	start = clock();
	/* Counting Sort */
	int *temp = malloc(size*sizeof(int));
	//#pragma omp parallel for num_threads(thread_count) default(none) shared(array,size,temp) private(i,j,count)
	for(i=0;i<size;i++){
		count = 0 ;
		for(j = 0;j < size ; j++)
			if(array[j] < array[i])
				count++;
			else if(array[j] == array[i] && j < i)
				count ++;
		temp[count] = array[i];
	} 
	// End the measurement
	end = clock();
	memcpy(array , temp , size*sizeof(int));
	free(temp);
	/* Print Result */
	for(i=0;i<A_SIZE;i++){
		printf("%d ", array[i] );
	}
	result = ((end-start)/(double)CLOCKS_PER_SEC);
	//printf("\nAnd The Using Parallel Time is %lf\n",((end-start)/(double)CLOCKS_PER_SEC) );
	/* Stop and return */
	array= Random_generate_array(A_SIZE);
	/* Counting Time */
	start = clock();
	/* Counting Sort */
	temp = malloc(size*sizeof(int));
	#pragma omp parallel for num_threads(thread_count) default(none) shared(array,size,temp) private(i,j,count)
	for(i=0;i<size;i++){
		count = 0 ;
		for(j = 0;j < size ; j++)
			if(array[j] < array[i])
				count++;
			else if(array[j] == array[i] && j < i)
				count ++;
		temp[count] = array[i]; 
	} 
	// End the measurement
	end = clock();
	memcpy(array , temp , size*sizeof(int));
	free(temp);
	/* Print Result */
	for(i=0;i<A_SIZE;i++){
		printf("%d ", array[i] );
	}
	printf("\nAnd The UnOpenMP Time is %lf ; Using is %lf time\n", result ,((end-start)/(double)CLOCKS_PER_SEC)  );	
	return 0;	
}

int *Random_generate_array(int size)
{
	int i ;
	int *array = malloc( size * sizeof(int)); 
	srand(time(NULL));
	for(i = 0 ; i < size ; i++){
		array[i] = (rand()%A_SIZE) + 1;
	}
	return array;
}
