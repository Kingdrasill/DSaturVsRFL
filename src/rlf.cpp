#include "rlf.hpp"

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

bool vertexIsInS(vector<position> S, int vertex) {
    for(int i=0; i<(int)S.size(); i++)
        if(S[i].currentPosition == vertex)
            return true;
    return false;
}

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