#include "graph.hpp"

typedef struct solution solution;
typedef struct tempos tempos;

/** @struct solution
 *  @brief Está estutura é usada para salvar os conjuntos de vértices e as cores que os métodos 'DSatur' e 'recursiveLargestFirst' geram ao resolver um grafo
 *  @var solution::sets
 *  Membro 'sets' é um vector que guarda os conjuntos de vértices que tem a mesma cor
 *  @var solution::cores
 *  Membro 'cores' é um vector que armazena as cores do membro 'sets', a cor de um conjunto vai estar na mesma posição do conjunto em 'sets' só que em cores
 */

struct solution {
    vector<vector<int>> sets;
    vector<int> cores;
};

/** @struct tempos
 *  @brief Está estrutura é utilizada para guardar os tempos que o método 'DSatur' ou 'recursiveLargestFirst' demora para colorir vários grafo, assim como os 'solution' dos grafos 
 *  @var tempos::tempo
 *  Membro 'tempo' é um vector que guarda os tempos que um dos algoritmos demoram para colorir os grafos dados a eles
 *  @var tempos::solucao
 *  Membro 'solucao' é um vector que armazena os 'solution' que um dos algoritmos geram para os grafos dados a eles
*/

struct tempos {
    vector<chrono::microseconds> tempo;
    vector<solution> solucao;
};

void colorirVertexDSatur(graph* g, int vertice);
void findNextVertexToPaint(graph* g);
void DStaur(graph* g);

void timedColoringDSatur(graph *g, tempos *dsatur);