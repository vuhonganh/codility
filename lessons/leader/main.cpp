#include <map>
#include <vector>
using namespace std;
/*
  A zero-indexed array A consisting of N integers is given. The dominator of array A is the value that occurs in more than half of the elements of A.
  Given a zero-indexed array A consisting of N integers, returns index of any element of array A in which the dominator of A occurs. The function should return −1 if array A does not have a dominator.
  Complexity:
  expected worst-case time complexity is O(N);
  expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).
 */

int solution_dominator(vector<int> &A)
{
  // write your code in C++11
  map<int, int> m;
  int lengthArr = (int) A.size();
  int halfLen = (lengthArr / 2);

  for (int i = 0; i < lengthArr; ++i)
    {
      m[A[i]]++;
      if (m[A[i]] > halfLen) return i;
    }
  return -1;
}

int main()
{
  return 0;
}
