#include "dsatur.hpp"

void Colorir(graph* g, int vertice){
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
}

void proxVerticeColorir(graph* g){
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
    Colorir(g, verticeEscolhido);
}

void DStaur(graph* g){
    bool continuar= true;
    int cont= 0;
    while (continuar){
        cont =0;
        for(int i =0; i < g->numVertices; i++){
            if(g->adjMatrix[i][i].color == 0){
                cont += 1;
            }
        }
        if(cont > 0){
            proxVerticeColorir(g);
        }
        else{
            continuar = false;
        }
    }
       
}