//factorial of numbers
//#pragma acc parallel
//#pragma acc loop 
#include <iostream>
#include <openacc.h>
using namespace std;

const int N = 5;

int main() {
    int factorial[N];
    
    #pragma acc parallel
    {
        #pragma acc loop
        for (int i = 0; i<N;i++){
                factorial[i]=1;
                for (int j = 1; j<=i+1; j++) {
                    factorial[i] *= j;
                }
            cout << "factorial of "<<i+1<< " = " << factorial[i] << endl;
        }
    }
    return 0;
}
