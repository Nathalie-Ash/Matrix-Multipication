#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>

    int**  matrix1;
    int**  matrix2;
    int**  answer;
    int row,col,n,m,k;

int **create_matrix(int ** matrix, int row, int col){
    matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; ++i) {
        matrix[i] = (int *)malloc(col * sizeof(int));
    }
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int row, int col){

     int i,j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

int **matrix_size(int row,int col){

      int **answer = (int **)malloc(row * sizeof(int *));
    
    for (int i = 0; i < row; ++i) {
        answer[i] = (int *)malloc(col * sizeof(int));
    }
    return answer;
}

void * runner(void *arg){
    int i,j;
    
    int sum;
    int tid = *(int *)(arg);

    for(int i = 0;i<k;i++){
        sum = 0;
        for(int j=0;j<n;j++){
           
                answer[tid][i]+=matrix1[tid][j]*matrix2[j][i];
            }
       }
       pthread_exit(NULL);
    }

   
int main(int argc, char *argv[]){
  // int m,n,k;
     
    m = atoi(argv[1]); // number of rows
    n = atoi(argv[2]); // number of columns of matrix 1
    k = atoi(argv[3]); // number of columns of matrix 2
    int i, j;

    if (argc != 4){
        printf("Error in number of input");
        return -1;
    }

    printf("Matrix 1:\n");
    matrix1= create_matrimatrix1,m,n);
    //printMatrix(matrix1,m,n);
   // printf("\n");

    //printf("Matrix 2:\n");
    matrix2=create_matrix(matrix2,n,k);
    //printMatrix(matrix2,n,k);
    //printf("\n");

    //printf("Answer: \n");
    answer = matrix_size(m,k);
     for( i = 0; i<m;i++){
        for (j = 0;j<k;j++){
            answer[i][j] = 0;
     }
    }
          clock_t start_time = clock();  
    for(int i = 0;i<m;i++){
      for(int j = 0;j<k;j++){
        for(int z = 0;z<n;z++){
          answer[i][j] += matrix1[i][z]*matrix2[z][j];
        }
      }
    }
    //printMatrix(answer,m,k);
     clock_t end_time = clock();
    double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nElapsed time: %f seconds\n", elapsed_time);
    return 0;


}