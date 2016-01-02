#include <vector>
#include <algorithm>

using namespace std;

/*
  Max Non overlapping Segments
  Located on a line are N segments, numbered from 0 to N − 1, whose positions are given in zero-indexed arrays A and B. For each I (0 ≤ I < N) the position of segment I is from A[I] to B[I] (inclusive). The segments are sorted by their ends, which means that B[K] ≤ B[K + 1] for K such that 0 ≤ K < N − 1.
  Two segments I and J, such that I ≠ J, are overlapping if they share at least one common point. In other words, A[I] ≤ A[J] ≤ B[I] or A[J] ≤ A[I] ≤ B[J].
  We say that the set of segments is non-overlapping if it contains no two overlapping segments. The goal is to find the size of a non-overlapping set containing the maximal number of segments.  
*/

int getMaxAt(int idx, vector<int> &A, vector<int> &B, vector<int> &memo)
{
  if (idx == 0) return 1; //itself
  if (idx < 0) return 0;
  int &ans = memo[idx];
  if (ans != -1) return ans;
  //at idx >= 1: take this one or either not take this one
  //if take this one: search for the idx that not overlap this one
  vector<int>::iterator low = lower_bound(B.begin(), B.begin() + idx - 1, A[idx]);
  int takeThisOne = 0;
  if (*low <= A[idx])
    {
      if (*low == A[idx]) low--;
      int idxFirstGet = low - B.begin();
      takeThisOne = 1 + getMaxAt(idxFirstGet, A, B, memo);
    }
  ans = max(takeThisOne, getMaxAt(idx - 1, A, B, memo));
  return ans;
}

int sol_maxNonOverlappingSegs(vector<int> &A, vector<int> &B)
{
  if (A.size() < 2) return A.size();
  vector<int> memo(A.size(), -1);
  int maxVal = 0;
  for (size_t i = 0; i < A.size(); ++i)
    {
      maxVal = max(getMaxAt(i, A, B, memo), maxVal);
    }
  return maxVal;
}
