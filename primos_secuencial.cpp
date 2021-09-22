#include <iostream>
#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

int isPrimeNumber(int);

int main(int argc, char **argv)
{
  
    int n=2000000
 , num_primos=0; 
    struct timeval inicio, fin;
  
  
   gettimeofday(&inicio, NULL);
  
    
   ios_base::sync_with_stdio(false);
   for (int i = 2; i < n; ++i)
        {
                /* code */
                int ind = 1;
                for (int j = 2; j < i; ++j)
                {
                        /* code */
                        if(i%j==0){
                                ind=0;
                                break;
                        }
                }

                //if(ind==0) cout << "[" << id << "]" << i << endl;
                if (ind == 1)
                {
                        ++num_primos;
                }
                //cout << "[" << rank << "]" << "tiene: " << num_primos << " primos" << endl;
        }
    
    gettimeofday(&fin, NULL);
  
   
    double tiempo;
  
    tiempo = (fin.tv_sec - inicio.tv_sec) * 1e6;
    tiempo = (tiempo + (fin.tv_usec - 
                              inicio.tv_usec)) * 1e-6;
  
 
   
   cout << "total de primos en el rango de [0," << n << "], es: " << num_primos << endl; 
   cout << "El tiempo de ejecución fue de: " << fixed << setprecision(5) << tiempo << " segundos..." << endl; 
   return 0;
}
