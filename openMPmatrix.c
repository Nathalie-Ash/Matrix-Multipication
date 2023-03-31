#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "omp.h"

int m,numthreads,chunk;
int **mat1,**mat2,**final;

int main(int argc, char** argv)
{     struct timeval tstart, tend;
  double exectime;
  int i,x,z;
    m =  atoi(argv[1]);
    numthreads = atoi(argv[2]);
    
    int * val1 = (int*) malloc( m * m * sizeof(int) );
	mat1 = (int**) malloc( m * sizeof(int*) );
	int * val2 = (int*) malloc( m * m * sizeof(int) );
    mat2 = (int**) malloc( m * sizeof(int*) );
	int * val3 = (int*) malloc( m * m * sizeof(int) );
    final = (int**) malloc( m * sizeof(int*) );
	
  for (int i = 0; i < m; ++i) {
    mat1[ i ] = &val1[ i * m ];
  }
  for (int i = 0; i < m; ++i) {
    mat2[ i ] = &val2[ i * m ];
  }
  for (int i = 0; i < m; ++i) {
    final[ i ] = &val3[ i * m ];
  }
    if (argc!=3){
        printf("err");
        return 1;
    }
    for (int i =0;i<m;i++){
        for (int j =0;j<m;j++){
            final[i][j]=0;
        }
    }
    for (int i =0;i<m;i++){
        for (int j =0;j<m;j++){
              mat1[i][j]= rand()%10+1;
         
        }
    }
 
    for (int i =0;i<m;i++){
        for (int j =0;j<m;j++){
                 mat2[i][j]= rand()%10+1;
        }
    }
	
    omp_set_num_threads(numthreads);
    chunk = m/numthreads;
    gettimeofday( &tstart, NULL );

#pragma omp parallel for shared(mat1, mat2, final, chunk) \
  private(i,z,x) schedule(static, chunk)
    for(int x = 0; x<m;x++){
        for(int z = 0; z<m;z++){
            for (int i =0;i<m;i++){
                final[x][z]+=mat1[x][i]*mat2[i][z];
            }
        }
    }
    gettimeofday( &tend, NULL );
    // for (int i =0;i<m;i++){
    //     for (int j =0;j<m;j++){
    //            printf("%d ",final[i][j]);
    //     }   
    //     printf("\n");
    // }

  exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
  exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   

  printf( "Execution time:%.3lf sec\n", exectime/1000.0);
        return 0;
}