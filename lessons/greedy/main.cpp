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

/* GREEDY PROOF: ( from codesays.com )
  Let’s scan from left to right, according to the end points. Since the input has already been sorted with the end points, linear scan works. Firstly, we define the cluster as: let the first item of that segment be segment[i], the cluster is all the segments from segment[i] to segment[j] (both inclusive, and i <= j), such that:
for all x (i < x <= j), segment[i].begin <= segment[x].begin <= segment[i].end

Any two segments in one cluster are overlapping.
1. Because the segments are sorted as the end point, (that is, for all x (i < x <= j), segment[x].end >= segment[i].end), and the definition of cluster, all the other segments are overlapping with the first one.
2. Any two no-first segments are overlapping. Because both their begin points are <= segment[i].end, and both end points are >= segment[i].end.
End of proof. As a result, in one cluster, we can pick up AT MOST one segment.

In any two consecutive clusters, we can choose two segments MAXIMUMLY. Let cluster[i] be the i(th) cluster, and cluster[i].segment[j] be the j(th) segment in the i(th) cluster.
1. We CAN choose two. As the definition of cluster, we have:
cluster[i].segment[first].end < cluster[i+1].segment[first].begin
And with the definition of segment, we have:
cluster[i].segment[first].begin <= cluster[i].segment[first].end < cluster[i+1].segment[first].begin <= cluster[i+1].segment[first].end
Therefore, they (cluster[i].segment[first] and cluster[i+1].segment[first]) are not overlapping.
2. We can choose two AT MOST. If we can choose three or more non-overlapping segments in these two consecutive clusters, according to pigeonhole principle, at least two non-overlapping segments are in one cluster. But according to our previous discussion, it is impossible.

Similarly, we can proof that: with N clusters, we can pick up N non-overlapping segments at most. Therefore, the orginal question becomes: find the number of clusters in the segments.
*/
int sol_maxNonOverlappingSegs_GREEDY(vector<int> &A, vector<int> &B) //100% 
{
  if (A.size() < 2) return A.size();
  int cnt = 1;
  int curPoint = B[0];
  size_t idx = 1;
  while (idx < A.size())
    {
      while (idx < A.size() && A[idx] <= curPoint) idx++;
      if (idx < A.size())
	{
	  cnt++;
	  curPoint = B[idx];
	}
    }
  return cnt;
}
