#include "graph.hpp"

/** @brief Inicilizia um grafo com n vértices sem nenhuma aresta.
 * 
 *  @pre Já possuir um 'graph' declarado e o usuário ter informado o 'num'
 * 
 *  @param g Um ponteiro de um 'graph'
 *  @param num Um inteiro que diz a quantidade de vértices
 * 
 *  @return Void
 *  
 *  @details
 *   Iniciliza um grafo usando o inteiro 'num' passado para o método
 *   para dizer qual a quantidade de vértices o grafo tem. O método
 *   seta 'numVertices' para ser igual a 'num', 'numColoridos' para
 *   ser 0 e cria a matriz de adjacência em 'adjMatrix', e dentro de
 *   'adjMatrix' seta os dados de todos os 'cell' como 0.
 */
void initializeGraph(graph* g, int num){
    g->numVertices = num;
    g->numColoridos = 0;
    g->adjMatrix = new cell*[num];
    for (int i = 0; i < num; i++){
        g->adjMatrix[i] = new cell[num];
        for(int j = 0; j < num; j++){
            g->adjMatrix[i][j].edge = false;
            g->adjMatrix[i][j].color = 0;
            g->adjMatrix[i][j].degreeSatur = 0;
            g->adjMatrix[i][j].degree = 0;
        }
        g->adjMatrix[i][i].vertex = i;
    } 

}

/** @brief Inicializa o grafo de um sudoku nxn.
 * 
 *  @pre Já possuir um 'graph' declarado e o usuário ter informado o 'n'
 *  
 *  @param g Um ponteiro de um 'graph'
 *  @param n Um inteiro que diz o tipo de sudoku
 * 
 *  @return Void
 * 
 *  @details
 *   Inicializa o grafo para um sudoku 'n'x'n' logo ele primeiro calcula
 *   a quantidade de blocos em 'cells', a quantidade de vértices em 'size'.
 *   Depois ele usa o método 'initizalizeGraph' para inicilizar o grafo com
 *   'size' vértices, após isto ele cria uma matriz auxiliar para descobrir
 *   quais os vértices fazem parte do bloco de um vértice qualquer do grafo.
 *   Com isto feito, o método pega todos vértices do grafo e monta as arestas
 *   de cada um, sendo elas com os vértices na mesma linha, coluna e no mesmo
 *   bloco, e por último ele chama o método 'calculateVertexDegree' para calcular
 *   o grau de todos os vértices do grafo.
*/
void initializeSudoku(graph *g, int n) {
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

/** @brief Checa se um grafo sudoku é posssivel de resolver.
 * 
 *  @pre O 'graph' passado para o método já ter sido inicializado 
 * 
 *  @param g Um 'graph' que é um sudoku
 * 
 *  @return true se o sudoku for possível de resolver
 *  @return false se o sudoku não for possível de resolver
 * 
 *  @details
 *   Checa se um grafo sudoku é posssivel de resolver, para fazer isto
 *   o método verifica se algum vértice com cor é vizinho de um vértice
 *   que tem uma cor igual a dele e verifica quantas cores diferentes o
 *   grafo possui se for maior que a quantidade necessária, se uma duas
 *   condições acontecerem o método retorna false.
 */
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

/** @brief Adiciona uma cor a um vértice que possível.
 *  
 *  @pre Já possuir um 'graph' declarado e o usuário ter informado um vértice dentro do grafo
 * 
 *  @param g Um ponteiro de um 'graph' já declarado
 *  @param vertex Um inteiro que diz qual vértice deve ser pintado
 *  @param color Um inetiro que informa qual é a cor 
 * 
 *  @return Void
*/
void addVertexColor(graph* g, int vertex, int color) {
    if(vertex < g->numVertices) {
        g->adjMatrix[vertex][vertex].color = color;
    }
}

/** @brief Calcula o grau de todos os vértices de um grafo.
 *  
 *  @pre Já possuir um 'graph' declarado
 * 
 *  @param g Um ponteiro de um 'graph' já declarado
 * 
 *  @return Void
 * 
 *  @details
 *   Calcula o grau de todos os vértices de um grafo, o método
 *   pega um vértice do grafo e olha quantos vizinhos o vértice
 *   possui salvando o valor em 'degree', isto é feito para todos os vértices.
*/
void calculateVertexDegree(graph *g) {
    int grau;
    for(int i = 0;  i < g->numVertices; i++) {
        grau = 0;
        for(int j = 0;  j < g->numVertices; j++) {
            if(i != j) {
                if(g->adjMatrix[i][j].edge)
                    grau++;
            }
        }
        g->adjMatrix[i][i].degree = grau;
    }
}

/** @brief Adiciona uma aresta em um grafo e ao aumenta o grau dos vértices passados.
 *  
 *  @pre Já possuir um 'graph' declarado e o usuário ter informado dois vértices diferentes do grafo
 * 
 *  @param g Um ponteiro de um 'graph' já declarado
 *  @param i Um inteiro que diz uma das extremidades da aresta
 *  @param j Um inetiro que diz outra extremidade da aresta
 * 
 *  @return Void
*/
void addEdge(graph* g,int i,int j){
    if(!g->adjMatrix[i][j].edge) {
        g->adjMatrix[i][j].edge = true;
        g->adjMatrix[j][i].edge = true;
        g->adjMatrix[i][i].degree += 1;
        g->adjMatrix[j][j].degree += 1;
    }
}

/** @brief Remove uma aresta de um grafo e ao diminui o grau dos vértices passados.
 *  
 *  @pre Já possuir um 'graph' declarado e o usuário ter informado dois vértices diferentes do grafo
 * 
 *  @param g Um ponteiro de um 'graph' já declarado
 *  @param i Um inteiro que diz uma das extremidades da aresta
 *  @param j Um inetiro que diz outra extremidade da aresta
 * 
 *  @return Void
*/
void removeEdge(graph* g,int i,int j){
    g->adjMatrix[i][j].edge = false;
    g->adjMatrix[j][i].edge = false;
    g->adjMatrix[i][i].degree -=1;
    g->adjMatrix[j][j].degree -=1;
}

/** @brief Remove um vértice de um grafo.
 *  
 *  @pre Já possuir um 'graph' declarado e o usuário ter informado um vértice
 * 
 *  @param g Um ponteiro de um 'graph' já declarado
 *  @param x Um inteiro que diz qual o vértice a ser removido
 * 
 *  @return Void
 * 
 *  @details
 *   O método remove remove um vértce de um grafo para fazer isto
 *   ele move todas as colunas depois da coluna do vértice a ser removido
 *   da 'adjMatrix' uma coluna para trás e move todas as linhas depois da
 *   linha do vértice a ser removido da 'adjMatrix' uma linha para trás e
 *   por último diminui 'numVertices' do grafo em 1.
*/
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

/** @brief Remove os números repetidos de um vector usando sets.
 *  
 *  @pre Já possuir um 'vector<int>' declarado
 * 
 *  @param vec Um ponteiro de um 'vector<int>' já declarado
 * 
 *  @return Void
*/
void removeDuplicates(vector<int> *vec) {
    set<int> s;
    unsigned size = vec->size();
    for( unsigned i = 0; i < size; ++i ) s.insert( vec->at(i) );
    vec->assign( s.begin(), s.end() );
}

/** @brief Gera um sudoku aleatório com n vértices coloridos.
 *  
 *  @pre Já possuir um 'graph' declarado e o usuário ter informado quantos vértices devem já ser coloridos
 * 
 *  @param g Um ponteiro de um 'graph' já declarado
 *  @param numColors Um inteiro que diz qunatos vértices devem ser coloridos
 * 
 *  @return Void
 * 
 *  @details
 *   Gera um sudoku aleatório com n vértices coloridos, ele colore um vértice
 *   com a menor cor possível e os próximos vértices possíveis vão receber uma
 *   cor maior que a do último vértice colorido.
*/
void sudokuRand(graph *g, int numColors) {
    int cor = 1, buffer;
    while(cor <= numColors) {
        buffer = cor;
        do {
            int vertex = randV(*g);
            if(g->adjMatrix[vertex][vertex].color == 0) {
                addVertexColor(g, vertex, cor);
                cor++;
            }
        } while(buffer == cor);
    }
}

/** @brief Gera um grafo aleatório com n vértices e m arestas.
 *  
 *  @pre O usuário ter informado a quantidade de vértices e arestas
 * 
 *  @param V Um inteiro qua informa a quantidade de vértices
 *  @param A Um inteiro que diz a quantidade de arestas
 * 
 *  @return Retorna um 'graph' aleatório
*/
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

/** @brief Retorna um vértice aleatório de um grafo 
 * 
 *  @pre Já ter um 'graph' declarado
 * 
 *  @param g Um 'graph' para pegar um vértice aleatório
 * 
 *  @return Retorna um vértice alletório do grafo passado ao método
*/
int randV(graph g) {
    double r = rand() / (RAND_MAX + 1.0);
    return r * g.numVertices;
}