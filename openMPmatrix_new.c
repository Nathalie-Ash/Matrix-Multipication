#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>
   
int size, nthreads, chunksize;
    
int **create_matrix(int ** matrix, int size){
    matrix = (int **)malloc(size *size* sizeof(int *));
    for (int i = 0; i < size; ++i) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int size){
    int i,j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}



int main(int argc, char *argv[]){
    int**  matrix1;
    int**  matrix2;
    int**  answer;
   
    struct timeval tstart, tend;
    size = atoi(argv[1]); // number of rows
    nthreads = atoi(argv[2]); // number of columns of matrix 1
    double exectime;
    int i,j,z;
    int sum =0;

    if (argc != 3){
        printf("Error in number of input");
        return -1;
    }


   omp_set_num_threads(nthreads);
   chunksize = size/nthreads;
   
    matrix1= create_matrix(matrix1,size);
    matrix2=create_matrix(matrix2,size);
    answer = create_matrix(answer,size);
   

     for( i = 0; i<size;i++){
        for (j = 0;j<size;j++){
            answer[i][j] = 0;
     }
    }

    // printf("Answer:\n");
    gettimeofday( &tstart, NULL ); 

    #pragma omp parallel for shared(matrix1,matrix2,answer,chunksize) \
    private(i,j,z,sum) schedule(static,chunksize)
   
    for ( i = 0;i<size;i++){
        for( j=0;j<size;j++){
            sum =0;
            for( z = 0;z<size;z++){
                sum += matrix1[i][z]*matrix2[z][j];
            }
            answer[i][j] = sum;
        }
    }
    gettimeofday( &tend, NULL );
    

     //printMatrix(answer,size);
     
     exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
  exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   

  printf( "Execution time:%.3lf sec\n",exectime/1000.0);

    return 0;


}


   