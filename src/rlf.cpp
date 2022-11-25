#include "rlf.hpp"

/** @brief Remove um conjunto de vértices S de um grafo g.
 * 
 *  @pre Já possuir um 'graph' inicializado e o conjunto S já ter sido preenchido
 * 
 *  @param g Um ponteiro de 'graph'
 *  @param S Um vector de 'position'
 * 
 *  @return Void
 *  
 *  @details
 *   O método 'removeSetFromGraph' é utilizado quando se quer remover um conjunto de vértices
 *   de um grafo. Para isto ser feito primeiro é se diminui o 'degree' de todos os vizinhos 
 *   dos vértices no conjunto S e depois o método acha a posição atual dos vértices no grafo
 *   e os remove utilizando o método 'removeVertex'.
*/
void removeSetFromGraph(graph *g, vector<position> S) {
    for(int i=0; i<(int)S.size(); i++) {
        for(int j=0; j<g->numVertices; j++) {
            if(j != S[i].currentPosition && g->adjMatrix[S[i].currentPosition][j].edge)
                g->adjMatrix[j][j].degree--;
        }
    }
    for(int i=0; i<(int)S.size(); i++) {
        for(int j=0; j<g->numVertices; j++) {
            if(S[i].vertex == g->adjMatrix[j][j].vertex) {
                removeVertex(g, j);
            }
        }
    }
}

/** @brief Checa se um vértice faz parte de um conjunto de vértices S.
 * 
 *  @pre Já possuir um vector de 'positon' S inicializado e ter sido passado o vértice a ser verificado
 * 
 *  @param S Um vector de 'position'
 *  @param vertex Um inteiro com qual vértice vai ser verificado
 * 
 *  @return true se o vértice estiver no conjunto S
 *  @return false se o vértice não estiver no conjunto S
*/
bool vertexIsInS(vector<position> S, int vertex) {
    for(int i=0; i<(int)S.size(); i++)
        if(S[i].currentPosition == vertex)
            return true;
    return false;
}

/** @brief Pega um conjunto de vértices de um grafo que possuam a menor cor do mesmo.
 * 
 *  @pre Já possuir um 'graph' inicializado
 * 
 *  @param g Um 'graph'
 * 
 *  @return Um vector<position> com todos os vértices que possuam a menor cor do grafo passado
*/
vector<position> smallestColorInGraph(graph g) {
    vector<position> s;
    position p;
    p.numberNeighborAdjacent = 0;
    p.numberNeighborNotS = 0;
    int min = 0;
    
    for (int i=0; i<g.numVertices; i++) {
        if(g.adjMatrix[i][i].color > 0) {
            if(min == 0) {
                if(g.adjMatrix[i][i].color != 0) {
                    min = g.adjMatrix[i][i].color;
                    s.clear();
                    p.vertex = g.adjMatrix[i][i].vertex;
                    p.currentPosition = i;
                    s.push_back(p);
                }
            } else {
                if(g.adjMatrix[i][i].color < min) {
                    min = g.adjMatrix[i][i].color;
                    s.clear();
                    p.vertex = g.adjMatrix[i][i].vertex;
                    p.currentPosition = i;
                    s.push_back(p);
                } else if(g.adjMatrix[i][i].color == min) {
                    p.vertex = g.adjMatrix[i][i].vertex;
                    p.currentPosition = i;
                    s.push_back(p);
                }
            }
        }
    }
    return s;
}

/** @brief Pega um vector de inteiros 'cores' e pega qual o menor valoar dele e retorna ele mais 1.
 * 
 *  @pre Já possuir um vector de interios inicializado
 * 
 *  @param cores Um vector de inteiros
 * 
 *  @return Um inteiro com a menor cor do vector cores mais 1
*/
int smallestColorPossible(vector<int> cores) {
    sort(cores.begin(), cores.end());
    int smallest;
    for(int i=0; i<(int)cores.size(); i++) {
        if(i == 0)
            smallest = cores[i]+1;
        else {
            if(smallest == cores[i])
                smallest = cores[i]+1;
        }
    }
    return smallest;
}

/** @brief Pega um conjunto de vértices de um grafo e retorna o(s) vértice(s) com o menor número de vizinhos do conjunto.
 * 
 *  @pre Já possuir um vector de 'position' inicializado
 * 
 *  @param temp Um vector de 'position'
 * 
 *  @return Um vector<position> com todos os vértices com o menor número de vizinhos do conjunto.
 * 
 *  @details
 *   O método 'onlyMinimumNotS' é utilizado para descobrir o vértice ou os vértices que possuem o menor número de 
 *   vizinhos que não estam no conjunto de vértices indepentes S. Para fazer isto é passado ao método um conjunto
 *   de vértices que não vizinhos aos vértices de S e retorna o(s) vértices(s) que tiverem o menor número de vinhizos
 *   que não fazem parte de S, que está dentro de 'numberNeighborNotS' dos membros do vector de 'position' passado.
*/
vector<position> onlyMinimumNotS(vector<position> temp) {
    vector<position> minimum;

    for(int i=0; i<(int)temp.size(); i++) {
        if(i==0) {
            minimum.push_back(temp[i]);
        } else {
            if(minimum.front().numberNeighborNotS > temp[i].numberNeighborNotS) {
                minimum.clear();
                minimum.push_back(temp[i]);
            } else if (minimum.front().numberNeighborAdjacent == temp[i].numberNeighborAdjacent) {
                minimum.push_back(temp[i]);
            }
        }
    }

    return minimum;
}

/** @brief Pega um conjunto de vértices de um grafo e retorna o(s) vértice(s) com o maior número de vizinhos adjacentes a um conjunto de vértices independentes S.
 * 
 *  @pre Já possuir um vector de 'position' inicializado
 * 
 *  @param temp Um vector de 'position'
 * 
 *  @return Um vector<position> com todos os vértices com o maior número de vizinhos adjacentes a um conjunto de vértices independentes S
 * 
 *  @details
 *   O método 'onlyMaximalsAdjacent' é utilizado para descobrir o vértice ou os vértices que possuem o maior número de 
 *   vizinhos que são adjacentes aos vértices de um conjunto de vértices indepentes S. Para fazer isto é passado ao método um conjunto
 *   de vértices que não vizinhos aos vértices de S e que já foi calculado o número de vizinhos adjacentes aos de S, e retorna o(s) vértices(s)
 *   que tiverem o maior número de vinhizos o número de vizinhos adjacentes aos de S, que está dentro de 'numberNeighborAdjacent' dos membros do
 *   vector de 'position' passado.
*/
vector<position> onlyMaximalsAdjacent(vector<position> temp) {
    vector<position> maximals;

    for(int i=0; i<(int)temp.size(); i++) {
        if(i==0) {
            maximals.push_back(temp[i]);
        } else {
            if(maximals.front().numberNeighborAdjacent < temp[i].numberNeighborAdjacent) {
                maximals.clear();
                maximals.push_back(temp[i]);
            } else if (maximals.front().numberNeighborAdjacent == temp[i].numberNeighborAdjacent) {
                maximals.push_back(temp[i]);
            }
        }
    }

    return maximals;
}

/** @brief Calcula o número de vizinhos adjacentes aos de S e o número de vizinhos que não estão em S de um conjunto de vértices.
 * 
 *  @pre Já possuir um 'graph' inicializado, ter dois vector de 'position' inicializados e um vector de interios inicializado
 * 
 *  @param g Um 'graph'
 *  @param S Um vector de 'position'
 *  @param temp Um ponteiro de vector de 'position'
 *  @param adj Um vector de inteiros
 * 
 *  @return Void
 * 
 *  @details
 *   O método 'calculateNeighborAdjacentSAndNotS' é utilizado para Calcula o número de vizinhos adjacentes aos de S e o número de vizinhos que
 *   não estão em S de um conjunto de vértices 'temp'. Para fazer isto é passado ao método  um conjunto de vértices independentes S, um conjunto
 *   de vértices que não vizinhos aos vértices de S 'temp' e um conjunto de vértices adjacentes aos de S 'adj', com estes conjuntos ele calcula
 *   para cada vértice em 'temp' o numero de vizinhos com os vértices em adj, que é guardado em 'numberNeighborAdjacent', e calcula o numero de vizinhos
 *   que não estão em S, que é guardado em 'numberNeighborNotS'.
*/
void calculateNeighborAdjacenctSAndNotS(graph g, vector<position> S, vector<position>* temp, vector<int> adj) {
    for(int i=0; i<(int)temp->size(); i++) {
        for(int j=0; j<(int)adj.size(); j++) {
            if(temp->at(i).currentPosition != adj[j]) {
                if(g.adjMatrix[temp->at(i).currentPosition][adj[j]].edge) {
                    temp->at(i).numberNeighborAdjacent++;
                }
            }
        }
        for(int j=0; j<g.numVertices; j++) {
            if(temp->at(i).currentPosition != j) {
                if(!vertexIsInS(S, j)) {
                    if(g.adjMatrix[temp->at(i).currentPosition][j].edge) {
                        temp->at(i).numberNeighborNotS++;
                    }
                }
            }
        }
    }
}

/** @brief Retorna o vértice de maior 'degree' de um grafo.
 * 
 *  @pre Já possuir um 'graph' inicializado
 * 
 *  @param g Um 'graph'
 * 
 *  @return Um 'position' com o vértice do grafo com o maior 'degree'
*/
position findVertexWithMaxDegree(graph g) {
    int max = -1;
    position vertex;

    for(int i=0; i<g.numVertices; i++) {
        if(max < g.adjMatrix[i][i].degree && g.adjMatrix[i][i].color == 0) {
            max = g.adjMatrix[i][i].degree;
            vertex.currentPosition = i;
            vertex.vertex = g.adjMatrix[i][i].vertex;
        }
    }

    return vertex;
}

/** @brief Inicializa dois conjuntos de vértices com base no conjunto de vértices independentes S.
 * 
 *  @pre Já possuir um 'graph' inicializado, ter dois vector de 'position' inicializados, um vector de interios inicializado e uma cor ter sido passada
 * 
 *  @param g Um 'graph'
 *  @param S Um vector de 'position'
 *  @param notAdj Um ponteiro de vector de 'position'
 *  @param adj Um ponteiro vector de inteiros
 *  @param color Um inteiro que possui uma cor
 * 
 *  @return Void
 * 
 *  @details
 *   O método 'createVectorOfAdjacentsAndNot' é utilizado para inicializar dois conjuntos de vértices com base no conjunto de vértices
 *   independentes S, em que um vai ser um conjunto de vértices que não são adjacentes a nenhum vértice em S 'notAdj' e um que vai ser um conjunto
 *   de vértices que são adjacentes os vértices em S 'adj. Para fazer isto, todos os vértices do grafos são verificados se eles são adjancentes a um
 *   vértice do S, se for adjacente o vértice é salvo em 'adj', ou se eles não forem adjacentes a nenhum vértice de S, se o vértice não for adjacente
 *   ele é salvo em 'notAdj'. A cor passada é utilizada se algum vértice em S já tiver uma cor, caso seja passada os vértices em 'notAdj' tem que ter
 *   cor igual a 0 ou igual a cor passada.
*/
void createVectorOfAdjacentsAndNot(graph g, vector<position> S, vector<position>* notAdj, vector<int>* adj, int color) {
    int add;
    position p;
    p.numberNeighborAdjacent = 0;
    p.numberNeighborNotS = 0;

    for(int i=0; i<g.numVertices; i++) {
        add = 0;
        for(int j=0; j<(int)S.size(); j++) {
            if(i == S[j].currentPosition) {
                break;
            } else {
                if(g.adjMatrix[i][S[j].currentPosition].edge)
                    adj->push_back(i);
                else
                    add++;
            }
        }
        if(add == (int)S.size() && (g.adjMatrix[i][i].color == 0 || g.adjMatrix[i][i].color == color)) {
            p.currentPosition = i;
            p.vertex = g.adjMatrix[i][i].vertex;
            notAdj->push_back(p);
        }
    }
}

/** @brief Cria um conjunto de vértices independentes S.
 * 
 *  @pre Já possuir um 'graph' inicializado e um vector de 'position' inicializado
 *  
 *  @param g Um 'graph'
 *  @param S Um ponteiro de vector de 'position'
 * 
 *  @return Void
 * 
 *  @details
 *   O método 'findIndepentSet' é utilizado para criar um conjunto de vértices independentes S de um grafo. Para fazer isto,
 *   primeiro é se verificado se existe algum vértice que já possui cor no grafo, se tiver é colocado me S os vértices que possuem
 *   a menor cor do grafo e senão tiver é colocado o vértice que tiver o maior 'degree' em S. Depois é se colocado vértices em S
 *   que não sejam adjacentes até que não tem mais vértices que não sejam adjacentes em S, para fazer este processo primeiro é
 *   chamado o método 'createVectorOfAdjacentsAndNotS', passando a cor se tiver ou 0 senão tiver, e depois remove os vértices
 *   duplicados no conjunto de vértices adjacentes. Se o conjunto de vértices não adjacentes estiver vazio não se tenta colocar 
 *   mais vértices em S, senão chama-se o métodp 'calculateNeighborAdjacentSAndNotS', depois é chamado o método 'onlyMaximalsAdjacents'
 *   que depois dele se é verifcado se houve mais de um vértice com o maior número de vizinhos adjacentes aos de S, se so tiver um
 *   vértice ele é adicionado em S senão é chamado o método 'onlyMinimumNotS' que é adicionado o primeiro vértice retornado do
 *   método ao conjunto S.  
*/
void findIndependentSet(graph g, vector<position> *S) {
    vector<position> coloridos, temp;
    vector<int> adjacent;
    bool cont;

    coloridos = smallestColorInGraph(g);
    if(coloridos.empty()) {
        S->push_back(findVertexWithMaxDegree(g));  
        do  {
            createVectorOfAdjacentsAndNot(g, *S, &temp, &adjacent, 0);
            removeDuplicates(&adjacent);
            if(!temp.empty()) {
                cont = true;
                calculateNeighborAdjacenctSAndNotS(g, *S, &temp, adjacent);
                adjacent.clear();
                temp = onlyMaximalsAdjacent(temp);

                if(temp.size() > 1) {
                    temp = onlyMinimumNotS(temp);
                    S->push_back(temp[0]);
                } else {
                    S->push_back(temp[0]);
                }
            } else {
                cont = false;
            }
            temp.clear();
        } while (cont);
    } else {
        for(int i=0; i<(int)coloridos.size(); i++) {
            S->push_back(coloridos[i]);
        }
        do  {
            createVectorOfAdjacentsAndNot(g, *S, &temp, &adjacent, g.adjMatrix[S->front().currentPosition][S->front().currentPosition].color);
            removeDuplicates(&adjacent);
            if(!temp.empty()) {
                cont = true;
                calculateNeighborAdjacenctSAndNotS(g, *S, &temp, adjacent);
                adjacent.clear();
                temp = onlyMaximalsAdjacent(temp);

                if(temp.size() > 1) {
                    temp = onlyMinimumNotS(temp);
                    S->push_back(temp[0]);
                } else {
                    S->push_back(temp[0]);
                }
            } else {
                cont = false;
            }
            temp.clear();
        } while (cont);
    }
}

/** @brief Faz a coloração de vértices de um grafo por meio do algoritmo RLF.
 * 
 *  @pre Já possuir um 'graph' inicializado e um vector de 'position' inicializado
 *  
 *  @param copy Um 'graph'
 * 
 *  @return Um solution para o grafo passado
 * 
 *  @details
 *   O método 'recursiveLargestFirst' é utilizado para fazer a coloração de vértices de um grafo por meio do algoritmo RLF. Para isto
 *   acontecer o método 'findIndependentSet' é chamado e os vértices que este método cria no conjunto de vértices independentes S são
 *   removidos do grafo, e depois o conjunto de vértices independentes S é guardado em um solution com uma cor para o conjunto, este
 *   processo é feito até que o número de vértices do grafo seja 0. No final o sloution com todos os conjuntos S e suas cores é retornado.
*/
solution recursiveLargestFirst(graph copy) {
    solution cores;
    vector<position> S;
    vector<int> conjunto;
    int cor;

    while(copy.numVertices > 0) {
        S.clear();
        findIndependentSet(copy, &S);
        cor = 0;
        for(int i=0; i<(int)S.size(); i++) {
            conjunto.push_back(S[i].vertex);
            if(copy.adjMatrix[S[i].currentPosition][S[i].currentPosition].color > 0) {
                cor = copy.adjMatrix[S[i].currentPosition][S[i].currentPosition].color;
            }
        }
        cores.cores.push_back(cor);
        cores.sets.push_back(conjunto);
        removeSetFromGraph(&copy, S);
        S.clear();
        conjunto.clear();
    }

    return cores;
}

/** @brief Salva o tempo que o algoritmo RLF demora em microsegundos e qual foi a solução do algoritmo para um grafo.
 * 
 *  @pre Já possuir um 'graph' inicializado e já possuir um 'tempos' inicializado
 * 
 *  @param g Um ponteiro de 'graph'
 *  @param rlf Um ponteiro de 'tempos'
 * 
 *  @return Void
 * 
 *  @details
 *   O método 'timedColoringRLF' é utilizado para calcular o tempo que o algoritmo RLF demora para colorir um grafo
 *   em microsegundos que demois é aramzenado em 'rlf'. E como o algoritmo já cria um solution ao rodar 'recursiveLargestFirst' 
 *   diferentemente do DSatur ele apenas arruma as cores da solution e armazena a solution em 'rlf'.
*/
void timedColoringRLF(graph *g, tempos *rlf) {
    std::chrono::_V2::high_resolution_clock::time_point start, end;

    start = chrono::high_resolution_clock::now();
    solution S = recursiveLargestFirst(*g);
    end = chrono::high_resolution_clock::now();

    std::chrono::microseconds time = chrono::duration_cast<chrono::microseconds>(end - start);
    rlf->tempo.push_back(time);
    for(int i=0; i<(int)S.sets.size(); i++) {
        S.cores[i] = i+1;
    }
    rlf->solucao.push_back(S);
}