//parallel array squaring
// 1 2 3 4 5
// 1 4 9 16 25

#include <iostream>
#include <openacc.h>

using namespace std;
const int N = 5;

int main(){
    int arr[N] = {1,2,3,4,5};
    int squareArr[N];
    
    #pragma acc parallel loop //parallel using the GPU
    for (int i = 0; i<N; i++){
        squareArr[i] = arr[i] * arr[i];
        cout << "Thread processing index "<<i<< " -> "<< squareArr[i]<<endl;
        
    }
    return 0;
}
