//Tarea de Rodrigo Calles
#include "mpi.h"
#include<iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;

#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n)(BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)

int main(int argc, char **argv ){
  MPI_Init( &argc , &argv);
  int id, i,j, np, n, ind, gap, inicio, fin, num_elems_rango, num_primos_local = 0;
  double t1,t2, promedio_tiempos; 

  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  n               = atoi(argv[1]);
  inicio          = BLOCK_LOW(id,np,n)+1; // para que empiece en 1
  if(id==0) inicio++;

  fin             = BLOCK_HIGH(id,np,n)+1;
  num_elems_rango = BLOCK_SIZE(id,np,n);

  MPI_Barrier(MPI_COMM_WORLD); 
  t1 = MPI_Wtime(); 

  for( i= inicio; i <= fin; i++ ){
    ind = 1;
    for( j = 2; j < i; j++ ){
      if( i%j == 0 ){
          ind = 0;
          break;
      }
    }
    if( ind == 1 ) num_primos_local++;
  }

  MPI_Send( &num_primos_local, 1, MPI_FLOAT, 0, 9, MPI_COMM_WORLD );

  if( id == 0 ){
      int num_primos = num_primos_local;
        for( i = 1 ; i < np ; i++ ){
            MPI_Recv( &num_primos_local, 1, MPI_FLOAT, i, 9, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            num_primos += num_primos_local;
        }

        //sleep(3);

        //printf("\nEl número de primos totales en el rango [1,%d] es %d\n ",n,num_primos);
        cout << "El número de primos totales en el rango [1," << n << "] " << "es " << num_primos << endl;  
  }

  MPI_Barrier(MPI_COMM_WORLD); 
  t2 = MPI_Wtime();

  if (id == 0) cout << "y tomó un total de: " << fixed <<  setprecision(10) << t2-t1 << " segundos" << endl;

  MPI_Finalize();
}
