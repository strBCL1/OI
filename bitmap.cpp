#include <bits/stdc++.h>
using namespace std;
int n, m; //Initializing the size of the bitmap
queue<int> q; //Initializing the queue for BFS traversal

/*Print the distances for all vertices to the closest '1's*/
void printDistances(vector<int> pDist) {
    for (int i = 0; i < n*m; ++i) {
        if (i != 0 && i % m == 0) cout << "\n";
        cout << pDist[i] << " ";
    }
}

/*Function to do BFS traversal*/
vector<int> BFS(vector<int> adj[], vector<int> p, vector<int> pDist, vector<bool> visited) {
    while (!q.empty()) { //While the queue isn't empty
        int curNumNode = q.front(); //Get the top element
        q.pop();  //Pop the top element

        for (auto it : adj[curNumNode]) { //For each neighbour of the current vertice
            if (!visited[it]) { //If a neighbour hasn't been visited,
                q.push(it); //push it to the queue
                visited[it] = true; //mark it as visited

                if (p[it] == 1) //If a neighbour is '1', set the distance to it as 0
                    pDist[it] = 0;
                else //else if a neighbour is '0', add 1 to the distance to that '0'
                    pDist[it] = pDist[curNumNode] + 1;
            }
        }
    }
    return pDist; //Update the distances vector
}

/*Checking if the current position of the string if not out of bound*/
bool isSafe(int x, int y, int maxY, int maxX) {
    return (x >= 0 && x < maxX && y >= 0 && y <= maxY);
}

/*Function to add all neighbours to each vertice*/
vector<int> addNeighbours(vector<int> adj[], vector<int> pDist, vector<bool> visited, vector<int> p, string s, int numRow) {
    for (int i = 0; i < m; ++i) { //For each vertice of the inputted line in bitmap
        int curAdjPos = i + (m*numRow); //Current position in the adjacency list
        /*[] [] [] [] [] [curAdjPos] [] [] [] [] [] [] [] [] [] []*/
        /*         Neighbours of each vertice of the bitmap       */

        p[curAdjPos] = s[i]-'0'; //Add the current vertice to the bitmap

        if (p[curAdjPos] == 1) { //If the current node is '1'
            visited[curAdjPos] = true; //mark the current node as visited
            q.push(curAdjPos); //push the current node to the queue
            pDist[curAdjPos] = 0; //set the distance to it as 0
        }

        if (isSafe(i, numRow, n, m))         //Checking and adding current cell to the current adj list
            adj[curAdjPos].push_back(curAdjPos);
        if (isSafe(i-1, numRow, n, m))       //Checking and adding left cell to the current adj list
            adj[curAdjPos].push_back(curAdjPos-1);
        if (isSafe(i+1, numRow, n, m))       //Checking and adding right cell to the current adj list
            adj[curAdjPos].push_back(curAdjPos+1);

        if (curAdjPos >= m) { //If it's a 2nd row or more, 
            adj[curAdjPos-m].push_back(curAdjPos); //add the current node as a neighbour to the upper node and 
            adj[curAdjPos].push_back(curAdjPos-m); //add the upper node to the current node
        }
    }
    return p; //Update the bitmap to the current values
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //Get input from file and output into a file;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    cin >> n >> m; cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Inputting the size of the bitmap

    vector<int> adj[n*m+6]; //Initializing the vector of adjacency lists
    vector<bool> visited(n*m+6, false); //Initializing the vector of visited vertices as false(none of them isn't visited now)
    vector<int> p(n*m+6); //Initializing the vector which will store the bitmap
    vector<int> pDist(n*m+6); //Initializing the vector which will store the distance for each '0' to the closest '1' 
    
    for (int i = 0; i < n; ++i) { //For n times
        string s; getline(cin, s); //input the line of the bitmap
        p = addNeighbours(adj, pDist, visited, p, s, i); //add neighbours to each vertice of the bitmap
    }

    pDist = BFS(adj, p, pDist, visited); //Do BFS on bitmap
    printDistances(pDist); //Print the distances for each '0' to the closest '1'
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
