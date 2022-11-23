#include "graph.hpp"

void initializeGraph(graph* g, int num) {
    g->numVertices = num;
    g->adjMatrix = new cell*[num];
    for (int i = 0; i < num; i++){
        g->adjMatrix[i] = new cell[num];
        for(int j = 0; j < num; j++){
            g->adjMatrix[i][j].edge = false;
            g->adjMatrix[i][j].color = 0;
            g->adjMatrix[i][j].degree = 0;
        }
        g->adjMatrix[i][i].vertex = i;
    }
}

void addEdge(graph* g,int i,int j) {
    if(!g->adjMatrix[i][j].edge) {
        g->adjMatrix[i][j].edge = true;
        g->adjMatrix[j][i].edge = true;
        g->adjMatrix[i][i].degree += 1;
        g->adjMatrix[j][j].degree += 1;
    }
}

void addVertexColor(graph* g, int vertex, int color) {
    if(vertex < g->numVertices) {
        g->adjMatrix[vertex][vertex].color = color;
    }
}

void removeEdge(graph* g,int i,int j) {
    g->adjMatrix[i][j].edge = false;
    g->adjMatrix[j][i].edge = false;
    g->adjMatrix[i][i].degree -=1;
    g->adjMatrix[j][j].degree -=1;
}

void removeVertex(graph *g, int x) {
    if(x > g->numVertices) {
        cout << "\nVertice nao existe!" << endl;
    } else {
        int  col=x, row=x;
        
        for(int i=0; i<g->numVertices; i++) {
            col = x;
            while(col < g->numVertices-1) {
                g->adjMatrix[i][col] = g->adjMatrix[i][col+1];
                col++;
            }
        }

        while(row < g->numVertices-1) {
            g->adjMatrix[row] = g->adjMatrix[row+1];
            row++;
        }

        g->numVertices--;
    }
}

void printGraph(graph g) {
    for (int i = 0; i < g.numVertices; i++){
        for(int j = 0; j < g.numVertices; j++){
            cout << g.adjMatrix[i][j].edge << " ";
        }
        cout << endl;
    } 
    cout << endl;
}

void createSudokuGraph(graph *g, int n) {
    int m = 0, x = 0, y = 0;
    int cells = pow(n,2);
    int size = pow(n,4);
    initializeGraph(g, size);

    int aux[cells][cells];
    for(int i = 0; i < cells; i++) {
        m = i % n == 0 ? i : m;
        for(int j = 0; j < cells; j++) {
            aux[i][j] = (j / n) + m;
        }
    }

    for(int k = 0; k < size; k++) {
        int c = 0;
        for(int i = 0; i < cells; i++) {
            for(int j = 0; j < cells; j++) {
                g->adjMatrix[k][c].edge = (x == i && y == j) ? false : (x == i || y == j || aux[i][j] == aux[x][y]) ? true : false;
                c++;
            }
        }

        y++;
        if(y > (cells-1)) {
            y = 0;
            x++;
        }
    }

    calculateVertexDegree(g);
}

void calculateVertexDegree(graph *g) {
    for(int i = 0;  i < g->numVertices; i++) {
        for(int j = 0;  j < g->numVertices; j++) {
            if(i != j) {
                if(g->adjMatrix[i][j].edge)
                    g->adjMatrix[i][i].degree++;
            }
        }
    }
}

bool checkIfSudokuSovable(graph g) {
    vector<int> vertexs, cores;
    bool possible=true;

    for(int i=0; i<g.numVertices; i++) {
        if(g.adjMatrix[i][i].color != 0) {
            vertexs.push_back(i);
            cores.push_back(g.adjMatrix[i][i].color);
        }
    }
    for(int i=0; i<(int)vertexs.size(); i++) {
        for(int j=0; j<(int)vertexs.size(); j++) {
            if(i != j) {
                if(g.adjMatrix[vertexs[i]][vertexs[j]].edge) {
                    if(cores[i] == cores[j])
                        possible = false;
                }
            }
        }
    }
    removeDuplicates(&cores);
    if(cores.size() > pow(g.numVertices, 1.0/2))
        possible = false;

    return possible;
}

void printSudoku(graph g) {
    int cells=pow(g.numVertices, 1.0/4), line=pow(g.numVertices, 1.0/2), block=cells*line;
    int c=0, l=0, b=0;
    for(int i=0; i<g.numVertices; i++) {
        cout << g.adjMatrix[i][i].color << " ";
        c++;
        l++;
        b++;
        if(c == cells) {
            c = 0;
            cout << "\t";
        }
        if(l == line) {
            l = 0;
            cout << "\n";
        }
        if(b == block) {
            b = 0;
            cout << "\n";
        }
    }
}

void removeDuplicates(vector<int> *vec) {
    set<int> s;
    unsigned size = vec->size();
    for( unsigned i = 0; i < size; ++i ) s.insert( vec->at(i) );
    vec->assign( s.begin(), s.end() );
}

void sudokuRand(graph *g, int numColors) {
    int colorido = 1;
    while(colorido <= numColors) {
        int vertex = randV(*g);
        if(g->adjMatrix[vertex][vertex].color == 0) {
            g->adjMatrix[vertex][vertex].color = colorido;
            colorido++;
        }
    }
}

graph graphRand(int V, int A) {
    int numA=0;
    graph g;
    initializeGraph(&g, V);
    while(numA < A) {
        int v = randV(g);
        int w = randV(g);
        if(v != w && !g.adjMatrix[v][w].edge) {
            numA++;
            addEdge(&g, v, w);
        }
    }
    return g;
}

int randV(graph g) {
    double r = rand() / (RAND_MAX + 1.0);
    return r * g.numVertices;
}