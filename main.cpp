#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#define TRACE(x) cout << #x << " = " << x << endl;
//first exo is very easy so i dont write here

//find the missing element in a permutation: 100%
int solution_L1_2(int A[], int N)
{
  int res = N+1;

  for(int i = 0; i < N; ++i)
    {
      res += (i+1); 
      res -= A[i];  //NOTE: if do not do like this, it will be exceed the range of int or until unsinged long for N= 100000 (at that case, the number maximum is 10 billion   
    }
  return res;  
}

//find the minimal difference of the first part of the array and the second part, separated by an index P: 0..(P-1) vs P..(N-1)
//NOTE: P has to be from 1 to N-1
int solution_L1_3(int A[], int N)
{
 
  long sum = 0;
  for(int i = 0; i < N; ++i)
    sum += A[i];
  long res = 2000000000;
  long firstPart = 0;
  long buffer = 0;
  for(int i = 0; i < N-1; ++i)//IMPORTANT to loop until N-1 only
    {
      firstPart += A[i];
      //TRACE(i);
      buffer = ( (sum - 2*firstPart) < 0)? (2*firstPart - sum) : (sum - 2*firstPart);
      //TRACE(buffer);
      if(buffer < res)
	{
	  res = buffer;
	}
      //TRACE(res);
    }
  return res;
}

void test_L1_3()
{
  int A[2] = {1000, -1000};
  int res = solution_L1_3(A, 2);
  printf("res = %d\n", res);  
}

//check if an array is a permutation or not
int solution_L2_1(int A[], int N)
{
  long check = 0;
  bool * visited = NULL;
  visited = static_cast <bool *> (malloc(N*sizeof(bool))) ;
  if(visited == NULL)
    exit(0);
  
  memset(visited, false, N);
  
  for(int i = 0; i < N; ++i)
    {
      if(A[i] > N || A[i] < 1) return 0;      
      if(visited[A[i]-1]) { free(visited); return 0;}
      check += (i+1);
      check -= A[i];    
      visited[A[i]-1] = true;
    }
  free(visited);
  if(check == 0) return 1;
  return 0;
}
int solution_L2_1_cpp(vector <int> &A)
{
  int N = (int) A.size();

  vector<bool> visited;
  visited.assign(N, false);
  long check = 0;

  for(int i = 0; i < N; ++i)
    {
      if(A[i] > N || A[i] < 1) return 0;

      if(visited[A[i]-1]) return 0;
      check += A[i];
      check -= (i+1);
      visited[A[i]-1] = true;
    }
  return (check == 0)? 1 : 0;
}

int main()
{
  test_L1_3();
  return 0;
}
