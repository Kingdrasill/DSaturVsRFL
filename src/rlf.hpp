#include "dsatur.hpp"

typedef struct position position;

/** @struct position 
 *  @brief Está é uma estrutura usada para guardar um vertex, a posição atual de um vertex na matriz de adjacência, o número de vizinhos adjacente aos vértices de um conjunto independente S e o número de vizinhos que não fazem parte de um conjunto indepente S 
 *  @var position::vertex
 *  Membro 'vertex' é um inteiro que guarda um vertex do grafo
 *  @var position::currentPosition
 *  Membro 'currentPosition' é um inteiro que salva a posição atual do 'vertex' na matriz de adjacência
 *  @var position::numberNeighborAdjacent
 *  Membro 'numberNeighborAdjacent é um inteiro que armazena o número de vizinhos adjacente aos vértices de um conjunto independente S
 *  @var position::numberNeighborNotS
 *  Membro 'numberNeighborNotS' é um inteiro que salva o número de vizinhos que não fazem parte de um conjunto indepente S
*/

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