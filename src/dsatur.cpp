#include "dsatur.hpp"

/** @brief Escolhe a menor cor possível para um vértice para coloração DSatur.
 * 
 *  @pre Já possuir um 'graph' inicializado e ter um vértice que deaseja ser colorido
 * 
 *  @param g Um ponteiro de 'graph'
 *  @param vertice Um inteiro representado qual o vértice a ser colorido
 * 
 *  @return Void
 * 
 *  @details
 *   O método 'colorirVertexDSatur' é utilizado pelo algoritmo DSatur para saber qual
 *   a cor que um vértice dado deve receber. Isto é feito primeiro colocando as cores dos vizinhos
 *   do vértice a ser colorido que já possuem cor num vector, ao mesmo tempo aumentando
 *   o 'degreeSatur' de todos os vizinhos em 1 pois eles tem um vértice a mais com cor, após isto
 *   o vector é ordenado de forma crescente. Então, é usado uma variável auxiliar 'menorCor', que
 *   é iniciada com a menor cor possível 1, para saber qual a menor cor possível para o vértice,
 *   para saber a cor do vértice é primeiro verificado se o vector das cores do vizinhos está vazio
 *   se ele estiver o vértice recebe a cor 1, senão é feito um teste com todas as cores do vector
 *   verificando se 'menorCor' é igual uma das cores se for 'menorCor' aumenta em 1 logo no final se
 *   terá a menor cor possível diferentes das do vizinhos já com cores para o vértice, e no final aumenta
 *   o número de vértices coloridos no grafo 'numColoridos'. 
*/
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

/** @brief Escolhe qual o próximo vértice a ser colorido para coloração DSatur.
 * 
 *  @pre Já possuir um 'graph' inicializado
 * 
 *  @param g Um ponteiro de 'graph'
 * 
 *  @return Void
 * 
 *  @details
 *   O método 'findNextVertexToPaint' é utilizado pelo algoritmo DSatur para saber qual
 *   o próximo vértice deve ser colorido usando o método 'colorirVertexDSatur'. Isto é feito
 *   primeiro colocando os vértices com maior 'degreeSatur' em um vector, se este vector só tiver
 *   um vértice este já é enviado para colorir, senão é escolhido o vértice que tiver o maior
 *   número de vizinhos, ou seja, que tiver o maior 'degree', e o vértice escolhido é envidado 
 *   para ser colorido. 
*/
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

/** @brief Fica chamando 'findNextVertexToPaint' até que o número de vértices coloridos seja igual ao número de vértices do grafo.
 * 
 *  @pre Já possuir um 'graph' inicializado
 * 
 *  @param g Um ponteiro de 'graph'
 * 
 *  @return Void
*/
void DStaur(graph* g){
    while (g->numColoridos != g->numVertices){
        findNextVertexToPaint(g);
    } 
}

/** @brief Salva o tempo que o algoritmo DSatur demora em microsegundos e qual foi a solução do algoritmo para um grafo.
 * 
 *  @pre Já possuir um 'graph' inicializado e já possuir um 'tempos' inicializado
 * 
 *  @param g Um ponteiro de 'graph'
 *  @param dsatur Um ponteiro de 'tempos'
 * 
 *  @return Void
 * 
 *  @details
 *   O método 'timedColoringDSatur' é utilizado para calcular o tempo que o algoritmo DSatur demora para colorir um grafo
 *   em microsegundos que demois é aramzenado em 'dsatur'. E como o algoritmo não cria um solution ao rodar 'DSatur' um
 *   é criado para o grafo que também é armazenado em 'dsatur', para fazer isto ele primeiro descobre quantas cores diferentes
 *   se tem no grafo colorido e depois salvas para cada cor quais os vértices que possuem está cor.
*/
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