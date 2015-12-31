#include <vector>
#include <stack>

using namespace std;

/* STONE WALL: greedy + stack
You are going to build a stone wall. The wall should be straight and N meters long, and its thickness should be constant; however, it should have different heights in different places. The height of the wall is specified by a zero-indexed array H of N positive integers. H[I] is the height of the wall from I to I+1 meters to the right of its left end. In particular, H[0] is the height of the wall's left end and H[N−1] is the height of the wall's right end.

The wall should be built of cuboid stone blocks (that is, all sides of such blocks are rectangular). Your task is to compute the minimum number of blocks needed to build the wall.
*/
int solution_StoneWall(vector<int> &H)
{
  //observation: we need to use a new stone if the height changes: if the height increase we need adding new stone but we have to stop using a stone only when the height decrease. It means that the stone can be as long as until we meet new wall shorter than it
  //-> that why we use a stack here:
  //meet new height that is taller: add it
  //meet new height that is shorter: pop the one at top until the height of top is smaller (or empty means height = 0), add new wall
  stack<int> st;
  int cnt = 0;
  for (size_t i = 0; i < H.size(); ++i)
    {
      if (st.empty())
	{
	  st.push(H[i]);
	  cnt ++;
	}
      else
	{
	  if (st.top() < H[i])
	    {
	      st.push(H[i]);
	      cnt++;
	    }
	  else 
	    {
	      while (!st.empty() && st.top() > H[i])
		{
		  st.pop();
		}
	      if (st.empty() || st.top() < H[i]) 
		{
		  st.push(H[i]);
		  cnt++;
		}
	    }
	}
    }
  return cnt;
}
int main()
{

  return 0;
}
