#include "dsatur.hpp"

void colorirVertexDSatur(graph* g, int vertice){
    vector<int> corVizinhos;
    for(int i = 0; i<g->numVertices; i++){
        if(vertice != i && g->adjMatrix[vertice][i].edge){
            if(g->adjMatrix[i][i].color > 0){
                corVizinhos.push_back(g->adjMatrix[i][i].color);
            }
            g->adjMatrix[i][i].degreeSatur++;
        }
    }
    sort(corVizinhos.begin(),corVizinhos.end());

    int menorCor=1;
    if(!corVizinhos.empty()){
        for(int i = 0; i<(int)corVizinhos.size(); i++){
            if(menorCor == corVizinhos[i]){
                menorCor = corVizinhos[i]+1;
            }
        }
    }
    g->adjMatrix[vertice][vertice].color = menorCor;
    g->numColoridos++;
}

void findNextVertexToPaint(graph* g){
    vector<int> Maiores;
    int verticeEscolhido,MaxDSatur=-1;
    for(int i=0; i< g->numVertices; i++){
        if(g->adjMatrix[i][i].color == 0) {
            if(MaxDSatur < g->adjMatrix[i][i].degreeSatur){
                MaxDSatur = g->adjMatrix[i][i].degreeSatur;
                Maiores.clear();
                Maiores.push_back(i);
            }
            else if(MaxDSatur == g->adjMatrix[i][i].degreeSatur){
                Maiores.push_back(i);
            }
        }
    }
    if(Maiores.size() == 1){
        verticeEscolhido = Maiores[0];
    }
    else{
        for(int i=0; i< (int)Maiores.size(); i++){
        if(i == 0){
            verticeEscolhido = Maiores[i];
            MaxDSatur = g->adjMatrix[Maiores[i]][Maiores[i]].degree;        
        }
        else{
            if(MaxDSatur < g->adjMatrix[Maiores[i]][Maiores[i]].degree){
                MaxDSatur = g->adjMatrix[i][i].degree;
                verticeEscolhido = Maiores[i];
            }
        }
    }
    }
    colorirVertexDSatur(g, verticeEscolhido);
}

void DStaur(graph* g){
    while (g->numColoridos != g->numVertices){
        findNextVertexToPaint(g);
    } 
}

void timedColoringDSatur(graph *g, tempos *dsatur) {
    std::chrono::_V2::high_resolution_clock::time_point start, end;

    start = chrono::high_resolution_clock::now();
    DStaur(g);
    end = chrono::high_resolution_clock::now();

    std::chrono::microseconds time = chrono::duration_cast<chrono::microseconds>(end - start);
    dsatur->tempo.push_back(time);

    vector<int> empty;
    empty.clear();
    solution S;
    bool add;
    int cor;
    for(int i=0; i<g->numVertices; i++) {
        add = true;
        cor = g->adjMatrix[i][i].color;
        for(int j=0; j<(int)S.cores.size(); j++) {
            if(cor == S.cores[j])
                add = false;
        }
        if(add)
            S.cores.push_back(cor);
    }
    sort(S.cores.begin(), S.cores.end());
    for(int j=0; j<(int)S.cores.size(); j++) {
        S.sets.push_back(empty);
        for(int i=0; i<g->numVertices; i++) {
            if(g->adjMatrix[i][i].color == S.cores[j])
                S.sets[j].push_back(g->adjMatrix[i][i].vertex);
        }
    }

    dsatur->solucao.push_back(S);
}