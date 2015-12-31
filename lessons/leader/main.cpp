#include <map>
#include <vector>
using namespace std;
/* Problem Dominator
  A zero-indexed array A consisting of N integers is given. The dominator of array A is the value that occurs in more than half of the elements of A.
  Given a zero-indexed array A consisting of N integers, returns index of any element of array A in which the dominator of A occurs. The function should return −1 if array A does not have a dominator.
  Complexity:
  expected worst-case time complexity is O(N);
  expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).
 */
//using map gives 100% score but in fact the time complexity is O(NlogN) (each search requires O(logN) time complexity)
//the optimal solution is the Moore Algorithm discussed below
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

//Moore's observation: if the array contains a dominator, the fact that remove the dominator value and a different value in the array will not change the dominator
//so we will first find the candidate which can be the dominator and do an iteration to check if this is a real dominator or just a frequent value
//the task to find the candidate by "removing" pair of different value is not trivial, see the technique below
int linear_sol_dominator(vector<int> &A)
{
  int candidateIdx = 0;
  int count = 1;
  for (size_t i = 1; i < A.size(); ++i)
    {
      if (A[candidateIdx] == A[i])
	{
	  count++;
	}
      else //find a different value
	{
	  count--;
	}
      if (count == 0)
	{
	  candidateIdx = i; //NOTE: this could work only if the condition of dominator is MORE THAN HALF (if it could be equal HALF, then this is not correct)
	  count = 1; //VERY IMPORTANT THIS LINE : restart this process from this value
	}
    }
  int cnt = 0;
  int moreThenHalf = ((int) (A.size() / 2)) + 1;
  for (size_t i = 0; i < A.size(); ++i)
    {
      if (A[candidateIdx] == A[i])
	cnt++;
    }
  if (cnt >= moreThenHalf) return candidateIdx;
  else return -1; 
}

void testDominator()
{
  vector<int> A {3, 4, 3, 2, 3, -1, 3, 3};
  
}

/*
  Problem : Equi-Leader 
  
  A non-empty zero-indexed array A consisting of N integers is given.
  The leader of this array is the value that occurs in more than half of the elements of A.
  An equi leader is an index S such that 0 ≤ S < N − 1 and two sequences A[0], A[1], ..., A[S] and A[S + 1], A[S + 2], ..., A[N − 1] have leaders of the same value
  Given a non-empty zero-indexed array A consisting of N integers, returns the number of equi leaders.
*/
//Observation: if two sequences have the same leader, than it must be the leader of the whole array (sum the occurence of this value will prove that trivially)
//So we need to compute the leader and then start counting 
int solution_Equi_Leader(vector<int> &A)
{
  int candidateIdx = 0;
  int count = 1;
  for (size_t i = 1; i < A.size(); ++i)
    {
      if (A[candidateIdx] == A[i])
	{
	  count++;
	}
      else //find a different value
	{
	  count--;
	}
      if (count == 0)
	{
	  candidateIdx = i; //NOTE: this could work only if the condition of dominator is MORE THAN HALF (if it could be equal HALF, then this is not correct)
	  count = 1; //VERY IMPORTANT THIS LINE : restart this process from this value
	}
    }
  int nbOccur = 0;
  int moreThenHalf = ((int) (A.size() / 2)) + 1;
  for (size_t i = 0; i < A.size(); ++i)
    {
      if (A[candidateIdx] == A[i])
	nbOccur++;
    }
  int leaderVal = 0;
  if (nbOccur >= moreThenHalf) leaderVal = A[candidateIdx];
  else return 0; //no leader meaning no equi-leader 
  
  //start counting number of equi-leader
  int S;
  int len_0_S, len_Sp1_end;
  int lenArr = (int) A.size();
  int cntToS = 0;
  int cntEquiLead = 0;
  for (S = 0; S < lenArr - 1; ++S)
    {
      len_0_S = S + 1;
      len_Sp1_end = lenArr - len_0_S;
      if (leaderVal == A[S])
	{
	  cntToS++;
	}
      if ( (cntToS > len_0_S / 2) && ((nbOccur - cntToS) > len_Sp1_end / 2) )
	{
	  cntEquiLead++;
	}
    }
  return cntEquiLead;
}


int main()
{
  return 0;
}
