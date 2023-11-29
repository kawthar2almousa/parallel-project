#include <omp.h>
#include <iostream>
#include <chrono>
#include <time.h>
#define SIZE 10 
void swap(int *num1, int *num2);
int main (int argc, char *argv[]) {
int A[SIZE] = {3, 5,6, 4, 1, 8, 7, 2, 10, 9};
int N = SIZE;
int i=0, j=0; 
int first;
auto start = std::chrono::high_resolution_clock::now();
 double totaltime = 0.0;
for( i = 0; i < N-1; i++ )
{
first = i % 2; 
 #pragma omp parallel for default(none) 
shared(A,first,N,start,totaltime) private(j)
for( j = first; j < N-1; j += 1 )
{
#pragma omp critical
{
if( A[ j ] > A[ j+1 ] )
{
    swap(&A[j], &A[j+1]);
} }
auto end = std::chrono::high_resolution_clock::now(); 
//nanoSecond
std::chrono::duration<double, std::nano> runningtime = 
end - start;
#pragma omp atomic
totaltime += runningtime.count();
} }
 std::cout << "Execution time: " << totaltime << " ns\n";
for(i=0; i<N; i++)
{
std::cout << " " << A[i];
}
 std::cout << "\n";
return 0;
}
void swap(int *num1, int *num2)
{
int temp = *num1;
*num1 = *num2;
*num2 = temp;
}