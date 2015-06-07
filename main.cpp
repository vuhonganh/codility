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
//frog jump to river //100%
int solution_L2_2(int X, vector<int> &A)
{
  vector<bool> exist(X, false);//note the idx = position - 1
  int count = X;
  for(int i = 0; i < (int) A.size(); ++i)
    {
      if(A[i] > X || A[i] < 1 || exist[A[i]-1]) continue;
      else
	{
	  exist[A[i]-1] = true;
	  count--;
	  if(count == 0) return i;
	}
    }
  return -1;
}

//counter setting: N=nb of counter// got 77% only
vector<int> solution_L2_3(int N, vector<int> &A)
{
  vector<int> counter(N, 0);
  int curMax = 0;
  bool curMaxChange = false;
  for(int i = 0; i < (int) A.size(); ++i)
    {
      if(curMaxChange && A[i] == N+1)
	{
	  //counter.assign(N, curMax);//because of this part so it will be extremly slow if all operations is set max counter
	  fill(counter.begin(), counter.end(), curMax);//this is no different from above -> need to keep a flag to avoid doing unnesscary updates
	  curMaxChange = false;//still not 100% when there are a lot of max counter operation --> need a curMin to update -> see remake 2
	}
      else
	{
	  if(A[i] > 0 && A[i] < N+1)
	    {
	      counter[A[i]-1]++;
	      curMax = max(curMax, counter[A[i]-1]);
	      curMaxChange = true;
	    }
	}
    }
  return counter;
}

//REMAKE max counter: 100%
vector<int> solution_L2_3_rmk(int N, vector<int> &A)
{
  vector<int> counter(N, 0);
  int curMax = 0;
  int curMin = 0;//keep a curMin
 
  for(int i = 0; i < (int) A.size(); ++i)
    {
      if(A[i] == N+1)
	{
	  //need to update all these array to curMax, however, we can do that later by keeping a curMin = curMax
	  curMin = curMax;
	}
      else
	{
	  if(A[i] > 0 && A[i] < N+1)
	    {
	      if(counter[A[i]-1] < curMin) //haven't updated this cell b4
		{
		  counter[A[i]-1] = curMin;
		}
	      counter[A[i]-1]++;
	      curMax = max(curMax, counter[A[i]-1]);
	    }
	}
    }
  
  for(int i = 0; i < N; ++i)
    {
      counter[i] = max(curMin, counter[i]);
    }  
  return counter;
  
}

//find min positive number that does not appear: 100%
int solution_L2_4(vector<int> &A)
{
  int N = (int) A.size();
  vector<bool> appeared(N, false);
  for(int i = 0; i < N; ++i)
    {
      if(A[i] > 0 && A[i] < N+1)
	{
	  appeared[A[i]-1] = true;
	}
    }
  for(int i = 0; i < N; ++i)
    {
      if(!appeared[i])
	return (i+1);
    }
  return N+1;
}
//NOTE: use unsigned int every time possible if the value is not negative
//passing car : 100% 
int solution_L3_1(vector<int> &A)
{
  unsigned int countZero = 0;
  unsigned int countPasses = 0;
  //each time meet 1, count the number of zero met before
  for(int i = 0; i < (int) A.size(); ++i)
    {
      if(A[i])
	{
	  countPasses += countZero;
	}
      else
	{
	  countZero++;
	}
    }
  return (countPasses > 1000000000)? -1 : countPasses;
}

//number of integer in [A,B] which is divisible by K: 100%
//NOTE: attention that they require O(1) in space and time
int solution_L3_2(int A, int B, int K)
{
  int first = (A%K == 0) ? A : ((A/K) + 1)*K;
  if(B < first) return 0;
  else return (B-first)/K + 1;
}

//find min average slice of an array
//NOTE: prove that min average slice can be formed by 2 or 3 elements
//after that coding is not so difficult
//-> lesson learnt: always check if the big problem can be solved by computing only a small part 
int solution_L3_3(int A[], int N)
{
  //calculate all 2-elements slice and 3-element slice compare the minimum
  
  int minVal = 2000000000;
  int idx = 0;
  for(int i = 0; i < N-1; ++i)
    {
      int cur = (A[i] + A[i+1])*3;
      if(cur < minVal)
	{
	  minVal = cur;
	  idx = i;
	}
    }

 for(int i = 0; i < N-2; ++i)
    {
      int cur = (A[i] + A[i+1] + A[i+2])*2;
      if(cur < minVal)
	{
	  minVal = cur;
	  idx = i;
	}
    }
 return idx;
}

//find minimal impact of DNA sub sequences: 100%
//MAIN IDEA: calcul prefix sum of OCCURENCES
vector<int> solution_L3_4(string &S, vector<int> &P, vector<int> &Q)
{
  vector< vector<int> > occurs;
  int N = S.length();
  vector<int> a = {0, 0, 0, 0};
  occurs.assign(N+1, a);//a little trick to deal with inclusive index 
  char gen[4] = {'A', 'C', 'G', 'T'};
  for(int i = 0; i < N; ++i)
    {
      for(int j = 0; j < 4; ++j)
	{
	  occurs[i+1][j] = (gen[j] == S[i])? 1 : 0;
	  occurs[i+1][j] += occurs[i][j];
	}
     
    }
  int M = P.size();
  vector<int> res(M, 0);
  
  for(int i = 0; i < M; ++i)
    {
      int s = P[i]; int e = Q[i];
      for(int j = 0; j < 4; ++j)
	{
	  if(occurs[e+1][j] > occurs[s][j])
	    {
	      res[i] = j+1;
	      break;
	    } 
	}
    }
  return res;
}

int main()
{
  test_L1_3();
  return 0;
}
