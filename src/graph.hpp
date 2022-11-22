#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct graph graph;
typedef struct cell cell;

typedef struct position position;

typedef struct solution solution;

struct graph {
    cell** adjMatrix;
    int numVertices;
};

struct cell {
    bool edge;
    int color;
    int degree;
    int vertex;
};

struct  position {
    int vertex;
    int currentPosition;
    int numberNeighborAdjacent;
    int numberNeighborNotS;
};

struct solution {
    vector<vector<int>> S;
    vector<int> cores;
};

void initializeGraph(graph* g, int num);
void addEdge(graph* g,int i,int j);
void addVertexColor(graph* g, int vertex, int color);
void removeEdge(graph* g,int i,int j);
void removeVertex(graph* g, int x);
void printGraph(graph g);

void createSudokuGraph(graph* g, int n);
void calculateVertexDegree(graph *g);
bool checkIfSudokuSovable(graph g);
void printSudoku(graph g);

void removeSFromGraph(graph *g, vector<position> S);
void removeDuplicates(vector<int> *vec);
bool vertexIsInS(vector<position> S, int vertex);
vector<position> smallestColorInGraph(graph g);
int smallestColorPossible(vector<int> cores);
 
vector<position> onlyMinimumNotS(vector<position> temp);
vector<position> onlyMaximalsAdjacent(vector<position> temp);
void calculateNeighborAdjacenctSAndNotS(graph g, vector<position> S, vector<position>* temp, vector<int> adj);
position findVertexWithMaxDegree(graph g);
void findIndependentSet(graph g, vector<position> *S);
void createVectorOfAdjacentsAndNot(graph g, vector<position> S, vector<position>* adj, vector<int>* notAdj, int color);

solution recursiveLargestFirst(graph copy);
void colorirSudoku(graph *g);
solution colorirGraph(graph *g);