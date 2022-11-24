#include "dsatur.hpp"

typedef struct position position;

struct  position {
    int vertex;
    int currentPosition;
    int numberNeighborAdjacent;
    int numberNeighborNotS;
};

void removeSetFromGraph(graph *g, vector<position> S);

bool vertexIsInS(vector<position> S, int vertex);

vector<position> smallestColorInGraph(graph g);
int smallestColorPossible(vector<int> cores);
 
vector<position> onlyMinimumNotS(vector<position> temp);
vector<position> onlyMaximalsAdjacent(vector<position> temp);

void calculateNeighborAdjacenctSAndNotS(graph g, vector<position> S, vector<position>* temp, vector<int> adj);
position findVertexWithMaxDegree(graph g);

void createVectorOfAdjacentsAndNot(graph g, vector<position> S, vector<position>* adj, vector<int>* notAdj, int color);

void findIndependentSet(graph g, vector<position> *S);
solution recursiveLargestFirst(graph copy);

void timedColoringRLF(graph *g, tempos *rlf);