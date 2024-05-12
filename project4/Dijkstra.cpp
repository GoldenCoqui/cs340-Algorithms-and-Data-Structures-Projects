#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

#define V 5

int NO_PARENT = -1;

void printPath(int currentVertex, vector<int> parents, ofstream &outputFile)
{
    if (currentVertex == NO_PARENT)
    {
        return;
    }
    printPath(parents[currentVertex], parents, outputFile);
    outputFile << currentVertex << " ";
}

void printSolution(int startVertex, vector<int> distances, vector<int> parents, ofstream &outputFile)
{
    int nVertices = distances.size();

    for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++)
    {
        if (vertexIndex != startVertex)
        {
            outputFile << startVertex << " " << vertexIndex << " ";
            printPath(vertexIndex, parents, outputFile);
            outputFile << fixed << setprecision(1) << " " << distances[vertexIndex] << endl;
        }
    }
}

void dijkstra(vector<vector<double>> adjacencyMatrix, int startVertex, ofstream &outputFile)
{
    int nVertices = adjacencyMatrix[0].size();
    vector<int> shortestDistances(nVertices);
    vector<bool> added(nVertices);
    vector<int> parents(nVertices);

    for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++)
    {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }

    shortestDistances[startVertex] = 0;
    parents[startVertex] = NO_PARENT;

    for (int i = 1; i < nVertices; i++)
    {
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;

        for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++)
        {
            if (!added[vertexIndex] && shortestDistances[vertexIndex] < shortestDistance)
            {
                nearestVertex = vertexIndex;
                shortestDistance = shortestDistances[vertexIndex];
            }
        }

        added[nearestVertex] = true;

        for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++)
        {
            int edgeDistance = adjacencyMatrix[nearestVertex][vertexIndex];

            if (edgeDistance > 0 && (shortestDistance + edgeDistance) < shortestDistances[vertexIndex])
            {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }

    printSolution(startVertex, shortestDistances, parents, outputFile);
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

    ofstream outputFile("dijkstraout.txt");
    if (!outputFile.is_open())
    {
        cout << "Failed to open output file.\n";
        return 1;
    }

    dijkstra(graph, 0, outputFile);

    outputFile.close();
    inputFile.close();

    return 0;
}
