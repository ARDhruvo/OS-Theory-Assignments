#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

#define BLACK 1  // All cycles from the node have been explored
#define GRAY 0   // Node is being explored FROM the DFS from a certain source
#define WHITE -1 // Node is unexplored DURING the DFS from a certain source

/* Use for input:
6 9
1 2
2 3
2 5
3 4
3 1
4 5
5 3
5 6
6 2

6 9
1 2
2 3
2 4
3 1
4 3
4 5
5 3
5 6
6 3
 */

int node_no, edge_no;
vector<int> nodes;
stack<int> explored;
vector<stack<int>> allCycles;
int src = 1;

// Extra functions

// Function to insert nodes in the nodes vector
// Ensures easier traversal of all nodes in the graph

void insNode(int node)
{
    if (!nodes.empty())
    {
        for (int u : nodes)
        {
            if (u == node)
            {
                return;
            }
        }
        nodes.push_back(node);
    }
    else
    {
        nodes.push_back(node);
    }
}

// Function to print the adjacency list of the graph

void printGraph(vector<vector<int>> &Graph)
{
    cout << "Adjacency List:" << endl;
    for (int i : nodes) // For each node u in Graph
    {
        cout << i << " -> ";
        for (int j : Graph[i]) // For each node v adjacent to u
        {
            cout << j << " ";
        }
        paragraph;
    }
    paragraph;
}

// Main DFS and cycle detection functions

void DFS(int u, vector<vector<int>> &Graph, vector<int> &color)
{
    explored.push(u); // Push the node in the explored stack
    color[u] = GRAY;  // Mark the node as being explored

    for (int v : Graph[u]) // For each adjacent node v of u
    {
        if (color[v] != BLACK) // If v is not fully explored
        {
            if (v == src) // Cycle found
            {
                stack<int> cycle;
                cycle = explored; // Making a duplicate of the explored stack to prevent modification in the original
                stack<int> cycleSet;
                cycleSet.push(src); // For cycle starting node
                while (!cycle.empty())
                {
                    cycleSet.push(cycle.top());
                    cycle.pop();
                }
                allCycles.push_back(cycleSet);
            }
            else if (color[v] == WHITE) // If v is unexplored
            {
                DFS(v, Graph, color);
            }
        }
    }

    explored.pop();   // Removing the node from the explored stack
    color[u] = WHITE; // Marking the node as unexplored for other DFS paths
}

void allCycleDetection(vector<vector<int>> &Graph, vector<int> &color)
{
    /*
     * The main idea is to run DFS from each node in the graph
     * This ensures all islands are also covered
     * Additionally, the DFS finds cycle only from the selected source node
     * This ensures no duplicate cycles are found
     */

    for (int s : nodes) // For each node s in the graph
    {
        src = s; // Set the source node for which cycles are to be found

        // Clear the explored stack before each DFS run
        while (!explored.empty())
        {
            explored.pop();
        }

        DFS(s, Graph, color);
        color[s] = BLACK; // Mark the source node as fully explored
    }

    // Print all cycles found

    if (allCycles.empty())
    {
        cout << "No deadlock found in the graph." << endl;
    }
    else
    {
        cout << "All cycles found in the graph:" << endl;
        for (stack<int> cycle : allCycles)
        {
            stack<int> temp = cycle;
            cout << temp.top();
            temp.pop();
            while (!temp.empty())
            {
                cout << " -> " << temp.top();
                temp.pop();
            }
            paragraph;
        }
    }
    paragraph;
}

int main()
{
    // Graph Input
    cout << "Enter number of processes and edges in the Wait-For Graph: " << endl;
    cin >> node_no >> edge_no;
    vector<vector<int>> Graph(node_no + 1);
    vector<int> color(node_no + 1, WHITE);
    paragraph;

    cout << "Enter process connections (A B for A -> B): " << endl;
    int nodeA, nodeB;
    for (int i = 1; i <= edge_no; i++)
    {
        cin >> nodeA >> nodeB;

        Graph[nodeA].push_back(nodeB); // Updates the Adjacency List
        // Keeps track of all nodes inserted in the graph
        insNode(nodeA);
        insNode(nodeB);
    }
    paragraph;

    printGraph(Graph);
    paragraph;

    allCycleDetection(Graph, color);

    // Terminal hold
    cout << "Program has been executed" << endl;
    getchar();
    return 0;
}
