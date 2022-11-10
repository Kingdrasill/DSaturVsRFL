#include <iostream>

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
    string color;
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
            g->adjMatrix[i][j].color = "";
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


void colorir(graph, vertice){
	loop(vizinhos ){
		verificarCorVizinhos(){
			salvarVetorCorVizinhos()
		}
		Vizinho +1 degreeSatur;
	}
	menorCordiferentedosViz();
}

void proxVerticeColorir(graph){
	loop(vertices){
		escolherMaiorDSatur;
		empateDSatur = escolherMaiorDegree;
		empateDegree = qualquerUmEmpate;
	}
	Colorir(graph, verticeEscolhido);
	
}

void DSatur(graph){
	loop(){
		proxVerticeColorir(graph);
		verificarVerticeNull = if continuar loop. else sair loop
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
   

    toString(g);

    return 0;
}