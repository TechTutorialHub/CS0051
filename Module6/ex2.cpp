//pragma acc kernels
//automatically detect parallelizable region and offload them to GPU

#include <iostream>
#include <openacc.h>
using namespace std;

const int N = 5;

int main(){
    int A[N] = {1,2,3,4,5};
    int B[N] = {5,4,3,2,1};
    int C[N];
    
    #pragma acc kernels
    for (int i = 0; i<N; i++){
        
        C[i] = A[i]+B[i];
        cout << "Iteration " <<i<< " : " << A[i] << " + " << B[i] " = " <<C[i]<<endl;
        
    }

    return 0;
}
