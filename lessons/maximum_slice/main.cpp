#include <vector>
#include <algorithm>

using namespace std;

/*
  Max profit problem
  A zero-indexed array A consisting of N integers is given. It contains daily prices of a stock share for a period of N consecutive days. If a single share was bought on day P and sold on day Q, where 0 ≤ P ≤ Q < N, then the profit of such transaction is equal to A[Q] − A[P], provided that A[Q] ≥ A[P]. Otherwise, the transaction brings loss of A[P] − A[Q].
  Complexity:
  expected worst-case time complexity is O(N);
  expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).
*/

int solution_max_profit(vector<int> &A) 
{
  if (A.empty()) return 0;
  // write your code in C++11
  int possibleMin = A[0];
  int profit = 0;
  for (size_t i = 1; i < A.size(); ++i)
    {
      if (A[i] > possibleMin)
        {
	  profit = max(profit, A[i] - possibleMin);
        }
      else
        {
	  possibleMin = A[i];    
        }        
    }
  return profit;
}
