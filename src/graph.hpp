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


struct graph
{
    cell** adjMatrix;
    int numVertices;
};

struct cell {
    bool edge;
    int color;
    int degree;
    int degreeSatur;
    int vertex;
};

void initializeGraph(graph* g, int num);
void initializeSudoku(graph* g, int n);

bool checkIfSudokuSovable(graph g);
void addVertexColor(graph* g, int vertex, int color);
void calculateVertexDegree(graph *g);

void addEdge(graph* g,int i,int j);
void removeEdge(graph* g,int i,int j);
void removeVertex(graph* g, int x);

void printGraph(graph g);
void printSudoku(graph g);

void removeDuplicates(vector<int> *vec);
void sudokuRand(graph *g, int numColors);
graph graphRand(int v, int a);
int randV(graph g);