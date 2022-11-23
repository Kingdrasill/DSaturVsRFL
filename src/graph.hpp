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

void removeDuplicates(vector<int> *vec);

void sudokuRand(graph *g, int numColors);
graph graphRand(int v, int a);
int randV(graph g);