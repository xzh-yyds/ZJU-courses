#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef int value_t;

int main(){
    int M = 4;
    int L = 5;
    int N = 4;
    
    // value_t *A = (value_t*)malloc(sizeof(value_t) * M * L);
    // value_t *B = (value_t*)malloc(sizeof(value_t) * L * N);
    // value_t *C = (value_t*)malloc(sizeof(value_t) * M * N);

    value_t A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    value_t B[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    value_t *C = (value_t*)malloc(sizeof(value_t) * M * N);

    int i=0, j=0, k=0;
    #pragma omp parallel for
    for (i=0; i<M; i++ ) {
        printf("%d ", i);
        for (j=0; j<M; j++ ) {
            value_t sum = 0;
            for (k=0; k<L; k++ ) {
                sum += A[i*L+k] * B[k*N+j];
            }
            C[i*N+j] = sum;
        }
    }
    printf("\n");

    for(i=0; i<M; i++){
        for(j=0; j<N; j++){
            printf(j ? " %4d" : "%4d", C[i*M+j]);
        }
        printf("\n");
    }

    return 0;
}