#include "graph.hpp"

typedef struct solution solution;
typedef struct tempos tempos;

struct solution {
    vector<vector<int>> sets;
    vector<int> cores;
};

struct tempos {
    vector<chrono::microseconds> tempo;
    vector<solution> solucao;
};

void colorirVertexDSatur(graph* g, int vertice);
void findNextVertexToPaint(graph* g);
void DStaur(graph* g);

void timedColoringDSatur(graph *g, tempos *dsatur);