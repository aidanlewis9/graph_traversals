// traversals.cpp
// Aidan Lewis

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct node {
  bool path; // does this path exist
  bool visited; // has the path been checked yet
};

bool checkPath(int, int, int, vector<vector<node>> &);

int main()
{
  int n = 1;
  int edges;
  while (cin >> edges) // before the user has inputted ctrl+D
  {
    vector<node> vec(edges*2, {false, false}); // max vertices = edges + 1, initialize each node
    vector<vector<node>> matrix(edges*2, vec); // vector of vectors (2D)
    for (int i = 0; i < edges; i++) // for each inputted edge
    {
      char e1, e2;
      cin >> e1 >> e2; // input edge
      int edge1 = e1 - 'A'; // convert to int
      int edge2 = e2 - 'A';
      matrix[edge1][edge2].path = true; // path exists
    }
    int paths;
    cin >> paths; // number of paths
    for (int j = 0; j < paths; j++) // for each inputted path
    {
      char p1, p2;
      cin >> p1 >> p2; // input path
      int start = p1 - 'A'; // convert to int
      int end = p2 - 'A';
      if (checkPath(start, end, edges, matrix)) // is there a path?
      {
	cout << "In Graph " << n << " there is a path from " << p1 << " to " << p2 << endl;
      }
      else // no path
      {
	cout << "In Graph " << n << " there is no path from " << p1 << " to " << p2 << endl;
      }
    }
    n++;
    cout << endl;
  }
}

bool checkPath(int start, int end, int edges, vector<vector<node>> &matrix)
{
  if (matrix[start][end].path == true) // if path exists
  {
    return true;
  }
  else
  {
    for (int i = 0; i < edges; i++) // for each possible path from start node
    {
      if (matrix[start][i].path && !matrix[start][i].visited) // if path exists and not visited yet
      {
	matrix[start][i].visited = true; // node has been visited
	bool found = checkPath(i, end, edges, matrix); // recursive call
	matrix[start][i].visited = false;
	return found;
      }
    }
  }
  return false; // path was not found
}
