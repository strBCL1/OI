#include <bits/stdc++.h>
using namespace std;
#define pb push_back

/*Function to print bitmap*/
void printBitmap(vector<int> pDist, int n, int m) {
    int count = 0;
    for (int i = 0; i < n*m; ++i) {
        if (count != 0 && count % m == 0) cout << "\n";
        cout << pDist[i] << " ";
        count++;
    }
}

/*Function to do BFS on bitmap*/
vector<int> BFS(vector<int> adj[], vector<int> p, vector<int> pDist, vector<bool> visited, int m, int start) {
    queue<int> q; //Initializing the queue for BFS doing
    visited[start] = true; //Marking the starting node as visited
    q.push(start); //Pushing the starting node to the queue
    pDist[start] = 0; //Pushing the starting node ('1') to pDist and making its distance as 0

    while (!q.empty()) {
        int curNumNode = q.front(); //Getting the num of the current node from the queue
        q.pop(); //Deleting the num of the current node from the queue

        //cout << curNumNode << " ";
        if (p[curNumNode] == 1) {
            for (auto it : adj[curNumNode]) {
                if (!visited[it]) {
                    visited[it] = true;
                    q.push(it);

                    if (p[it] == 1)
                        pDist[it] = 0;
                    if (p[it] == 0)
                        pDist[it] = 1;
                }
                    if (p[it] == 1) {
                        pDist[curNumNode] = 0;
                        pDist[it] = 0;
                    }
                    if (p[it] == 0) {
                        pDist[curNumNode] = 0;
                        pDist[it] = 1;
                    } 
                
            }
        }

        if (p[curNumNode] == 0) {
            for (auto it : adj[curNumNode]) {
                if (!visited[it]) {
                    visited[it] = true;
                    q.push(it);

                    if (p[it] == 1)
                        pDist[it] = 0;
                    if (p[it] == 0)
                        pDist[it] = pDist[curNumNode]+1;
                }
                
                    if (p[it] == 1) {
                        pDist[curNumNode] = 1;
                        pDist[it] = 0;
                    }

                    if (p[it] == 0) {
                        if (pDist[it] - pDist[curNumNode] > 1)
                            pDist[it] = pDist[curNumNode] + 1;
                        if (pDist[curNumNode] - pDist[it] > 1)
                            pDist[curNumNode] = pDist[it] + 1;
                    }
                
                    
            }
        }
    }
    return pDist;
}

/*Function to find the first occurance of '1' in bitmap*/
int findFirstZero(vector<int> p, int n, int m) {
    for (int i = 0; i < n*m-1; ++i)
        if (p[i+1] == 1 && p[i] == 0)
            return i+1;
    return 0;
}

/*Checking if the current position of the string if not out of bound*/
bool isSafe(int x, int y, int maxY, int maxX) {
    return (x >= 0 && x < maxX && y >= 0 && y <= maxY);
}


/*Function to add all neighbours to each vertice*/
vector<int> addNeighbours(vector<int> adj[], vector<int> p, string s, int n, int m, int numRow, vector<bool> visited) {
    for (int i = 0; i < m; ++i) { //For each character in the string s
        int curAdjPos = i + (m*numRow); //Current position in the adjacency list
        p[curAdjPos] = s[i]-'0'; //Adding the current vertice to the vector of pairs (curAdjPos <-> vertice)
    
        if (isSafe(i, numRow, n, m))                //Checking and adding current cell to the current adj list
            adj[curAdjPos].pb(curAdjPos);
        if (isSafe(i-1, numRow, n, m))              //Checking and adding left cell to the current adj list
            adj[curAdjPos].pb(curAdjPos-1);
        if (isSafe(i+1, numRow, n, m))              //Checking and adding right cell to the current adj list
            adj[curAdjPos].pb(curAdjPos+1);

        if (curAdjPos >= m) { //If it's a 2nd row or more, add the current node as a neighbour to the upper node and 
            adj[curAdjPos-m].pb(curAdjPos); //the upper node to the current node
            adj[curAdjPos].pb(curAdjPos-m); 
        }
    }
    
    return p;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m; //Initializing the size of the bitmap
    cin >> n >> m; cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Inputting the size of the bitmap
    vector<int> adj[n*m+6]; //initializing the vector of adjacency lists
    vector<bool> visited(n*m, false); //Initializing the vector of visited vertices
    vector<int> p(n*m, 0); //Initializing the vector which will store the bitmap
    vector<int> pDist(n*m, 0); //Initializing the vector which will store the distance for each '0' to the closest '1'

    /*cout << "adj.size(): " << adj[0].size() << "\n";
    cout << "visited.size(): " << visited.size() << "\n";
    cout << "p.size(): " << p.size() << "\n";
    cout << "pDist.size(): " << pDist.size() << "\n";*/

    for (int i = 0; i < n; ++i) { //For n times
        string s; getline(cin, s); //Input the line of the bitmap
        p = addNeighbours(adj, p, s, n, m, i, visited); //Add neighbours to each vertice of the bitmap
    }

    int firstZeroPos = findFirstZero(p, n, m); //Find the first occurance of '1' in bitmap
    pDist = BFS(adj, p, pDist, visited, m, firstZeroPos); //Do BFS on bitmap
    printBitmap(pDist, n, m); //Print the bitmap

    return 0;
}

/*
5 5

11000
00011
00000
00000
00100


3 4

0001
0011
0110
*/
