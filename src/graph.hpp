#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

typedef struct graph graph;
typedef struct cell cell;

/** @struct graph
 *  @brief Está estrutura armazena o grafo, os dados dos vértices são armazendos nas posições em que a coluna e a linha são iguas 
 *  @var graph::adjMatrix 
 *  Membro 'adjMatrix' é uma matriz de 'cell' que contêm a matriz de adjacência do grafo, além dos dados dos vértices do grafo
 *  @var graph::numVertices
 *  Membro 'numVertices' é um inteiro que guarda o número de vértices do grafo
 *  @var graph::numColoridos
 *  Membro 'numColoridos' é um inteiro que armazena o número de vértices coloridos do grafo, usado no método 'DSatur'
 */

struct graph {
    cell** adjMatrix;
    int numVertices;
    int numColoridos;
};

/** @struct cell
 *  @brief Está estrutura armazena os dados dos vértices ou de uma aresta
 *  @var cell::edge 
 *  Membro 'edge' é um booleano que armazena se um vértice está conectado com outro em 'adjMatrix'
 *  @var cell::color
 *  Membro 'color' é um inteiro que guarda o a cor de um vétice
 *  @var cell::degree
 *  Membro 'degree' é um inteiro que armazena o grau do vértice
 *  @var cell::degreeSatur
 *  Membro 'degreeSatur' é um inteiro qu salva o grau de saturação de um vértice, usado no método 'DSatur'
 *  @var cell::vertex
 *  Membro 'vertex' é um inteiro que guarda o identificador do vértice
 */

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

void removeDuplicates(vector<int> *vec);
void sudokuRand(graph *g, int numColors);
graph graphRand(int v, int a);
int randV(graph g);