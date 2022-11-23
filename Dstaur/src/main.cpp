#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct graph graph;
typedef struct cell cell;


struct graph
{
    cell** adjMatrix;
    int numVertices;
};

struct cell
{
    bool edge;
    int color;
    int degreeSatur;
    int degree;
};

void initialize(graph* g, int num){
    g->numVertices = num;
    g->adjMatrix = new cell*[num];
    for (int i = 0; i < num; i++){
        g->adjMatrix[i] = new cell[num];
        for(int j = 0; j < num; j++){
            g->adjMatrix[i][j].edge = false;
            g->adjMatrix[i][j].color = 0;
            g->adjMatrix[i][j].degreeSatur = 0;
            g->adjMatrix[i][j].degree = 0;
        }
    } 

}

void addEdge(graph* g,int i,int j){
    g->adjMatrix[i][j].edge = true;
    g->adjMatrix[j][i].edge = true;
    g->adjMatrix[i][i].degree +=1;
    g->adjMatrix[j][j].degree +=1;
}

void removeEdge(graph* g,int i,int j){
    g->adjMatrix[i][j].edge = false;
    g->adjMatrix[j][i].edge = false;
    g->adjMatrix[i][i].degree -=1;
    g->adjMatrix[j][j].degree -=1;
}

void toString(graph g){
    for (int i = 0; i < g.numVertices; i++){
        cout << i << " : " ;
        for(int j = 0; j < g.numVertices; j++){
            cout << g.adjMatrix[i][j].edge << " " ;
        }
        cout << endl;
    } 

}


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

    int menorCor;
    if(!corVizinhos.empty()){
        for(int i = 0; i<(int)corVizinhos.size(); i++){
            if(i == 0){
                menorCor = corVizinhos[i]+1;
            }
            else{
                if(menorCor < corVizinhos[i]){
                    break;
                }
                else{
                    menorCor = corVizinhos[i]+1;
                }
            }
        }
    }
    else{
        menorCor = 1;
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

int main(){
    graph g;
    initialize(&g, 7);
    addEdge(&g,0, 1);
    addEdge(&g,0, 6);
    addEdge(&g,0 ,5);
    addEdge(&g,1, 2);
    addEdge(&g,1, 6);
    addEdge(&g,2, 3);
    addEdge(&g,2, 6);
    addEdge(&g,3 ,4);
    addEdge(&g,3, 6);
    addEdge(&g,4, 5);
    addEdge(&g,4, 6);
    addEdge(&g,5, 6);

    DStaur(&g);
    for(int i =0; i< g.numVertices;i++){
        cout << i << ": " << g.adjMatrix[i][i].color << endl;
    }

    return 0;
}