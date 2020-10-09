#include <bits/stdc++.h>
using namespace std;
#define pb push_back
int n, m, adding = 7; //Initializing the size of the bitmap
vector<bool> visited(n*m+adding, false); //Initializing the vector of the visited nodes
vector<int> p(n*m); //Initializing the vector for making the pairs (adj. list pos. <-> vertice)
vector<pair<int, int>> pDist(n*m+adding); //Initializing the vector of distances for each vertice to the closest '1' (adj. num <-> vertice)

/*Check if the current node is '1' in p vector*/
bool isOneInP(int num) {
	return (p[num] == 1);
}

/*Function to do BFS*/
void BFS(vector<int> adj[], int start) {
	queue<int> q; //Initializing the queue for BFS doing
	visited[start] = true; //Marking the starting node as visited
	q.push(start); //Pushing the starting node to the queue
	pDist.pb(make_pair(start, 0)); //Pushing the starting node ('1') to pDist and making its distance as 0
	cout << "BFS:\n";

	while (!q.empty()) {
		int curNumNode = q.front(); //Getting the num of the current node from the queue
		q.pop(); //Deleting the num of the current node from the queue

		if (p[curNumNode] == 1) {
			for (auto it : adj[curNumNode]) {
				if (!visited[it]) {
					visited[it] = true;
					q.push(it);

					if (p[it] == 1)
						pDist.pb(make_pair(it, 0));
					else if (p[it] == 0)
						pDist.pb(make_pair(it, 1));
				}
				else {
					if (p[it] == 1 && pDist[it].second != 0)
						pDist[it].second = 0;
					else if (p[it] == 0 && pDist[it].second != 1)
						pDist[it].second = 1;
				}
			}
		}

		else if (p[curNumNode] == 0) {
			for (auto it : adj[curNumNode]) {
				if (!visited[it]) {
					visited[it] = true;
					q.push(it);

					if (p[it] == 1)
						pDist.pb(make_pair(it, 0));
					else if (p[it] == 0)
						pDist.pb(make_pair(it, pDist[curNumNode].second + 1));
				}
				else {
					if (p[it] == 0 && pDist[it].second - pDist[curNumNode].second > 1)
						pDist[it].second = pDist[curNumNode].second + 1;
					else if (p[it] == 1 && pDist[it].second != 0)
						pDist[it].second = 0;
				}
			}
		}

	}
}

/*Function to find the first occurance of the '1* in vector of pairs*/
int findFirstOne() {
	for (int i = 0; i < n*m; ++i)
		if (p[i] == 1)
			return i;
	return 0;
}

/*Check if the current position of the string if not out of bound*/
bool isSafe(int x, int y, int maxY, int maxX) {
	return (x >= 0 && x < maxX && y >= 0 && y <= maxY);
}

/*Function to add neighbours to each vertice of the bitmap*/
void addNeighbours(vector<int> adj[], string s, int n, int m, int numRow) {
	for (int i = 0; i < m; ++i) { 		//For each character in the inputted string
		int curAdjPos = i + (m*numRow); //Current position of the adjacency list
		p.pb(s[i]-'0'); //Adding the current vertice to the vector for making a pair (curAdjPos <-> vertice)

		if (isSafe(i, numRow, n, m))				//Checking and adding current cell to the current adj list
			adj[curAdjPos].pb(curAdjPos);
		if (isSafe(i-1, numRow, n, m))				//Checking and adding left cell to the current adj list
			adj[curAdjPos].pb(curAdjPos-1);
		if (isSafe(i+1, numRow, n, m))				//Checking and adding right cell to the current adj list
			adj[curAdjPos].pb(curAdjPos+1);

		if (curAdjPos >= m) { //If it's a 2nd row or more, add the current node as a neighbour to the upper node and 
			adj[curAdjPos-m].pb(curAdjPos); //the upper node to the current node
			adj[curAdjPos].pb(curAdjPos-m); 
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	cin >> n >> m; cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Inputting the size of the bitmap
	vector<int> adj[n*m+10]; //Initializing the adjacency list of each node

	for (int i = 0; i < n; ++i) {
		string s; getline(cin, s); //Inputting the line of the bitmap
		addNeighbours(adj, s, n, m, i); //Adding neighbours to each vertice of the bitmap
	}
	int firstOnePos = findFirstOne(); //Finding the first occurance of '1' in vector of pairs
	BFS(adj, firstOnePos); //Start doing BFS
	
	sort(pDist.begin(), pDist.end());
	for (auto it : pDist)
		cout << it.first << " " << it.second << "\n";

	cout << "\n";
	for (auto it : p)
		cout << it << "\n";

	cout << "\n";

	return 0;
}

/*
3 4
0001
0011
0110


3 2 1 0
2 1 0 0
1 0 0 1
*/