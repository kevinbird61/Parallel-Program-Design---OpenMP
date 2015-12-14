#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A_SIZE 100000

int *Random_generate_array(int size);
int int_cmp(const void *a , const void *b);

int main(int argc ,char *argv[]){
    int *array, i ,thread_count;
    long size = A_SIZE;
    thread_count = atoi(argv[1]);
    clock_t start , end;
    start = clock();
    array = Random_generate_array(A_SIZE);
    qsort(array , size , sizeof(int) , int_cmp);
    
    for(i = 0; i < A_SIZE ; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    end = clock();
    
    printf("The qsort time is %lf \n" , (end -start) / (double)(CLOCKS_PER_SEC));
    
    return 0;
}

int int_cmp(const void *a , const void *b){
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    return *ia - *ib;
}

int *Random_generate_array(int size){
	int i ;
	int *array = malloc( size * sizeof(int)); 
	srand(time(NULL));
	for(i = 0 ; i < size ; i++){
		array[i] = (rand()%A_SIZE) + 1;
	}
	return array;
}

