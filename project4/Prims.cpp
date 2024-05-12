#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

#define V 5

void printMST(vector<int> parent, vector<vector<double>> graph, ofstream &outputFile)
{
    outputFile << "Edge\tWeight\n";
    for (int i = 1; i < V; i++)
    {
        outputFile << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
    }
}

int minKey(vector<double> key, vector<bool> mstSet)
{
    double min = numeric_limits<double>::max();
    int min_index;

    for (int v = 0; v < V; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void primMST(vector<vector<double>> graph, ofstream &outputFile)
{
    vector<int> parent(V);
    vector<double> key(V);
    vector<bool> mstSet(V, false);

    for (int i = 0; i < V; i++)
    {
        key[i] = numeric_limits<double>::max();
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, outputFile);
}

int main()
{
    vector<vector<double>> graph(V, vector<double>(V, 0.0));

    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cout << "Failed to open input file.\n";
        return 1;
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            inputFile >> graph[i][j];
        }
    }

    ofstream outputFile("primsout.txt");
    if (!outputFile.is_open())
    {
        cout << "Failed to open output file.\n";
        return 1;
    }

    primMST(graph, outputFile);

    outputFile.close();
    inputFile.close();

    return 0;
}
