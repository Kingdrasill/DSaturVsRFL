#include "function.hpp"

/** @brief Compara os algoritmos DSatur e RLF para grafos aleatórios.
 * 
 *  @details 
 *   Este método é usado para comparar os algoritmos DSatur e RLF para grafos aleatórios. Para isto
 *   acontecer, primeiro é se criado um arquivo em que os grafos gerados e as soluções dos algoritmos
 *   seram guardados. Depois disto é se perguntado o números de grafos que devem ser gerados, depois o número
 *   de vértices e por último o número de arestas para os grafos a serem gerados. Com tudo setado os grafos
 *   são gerados, sendo que toda vez que um é gerado ele é colocado no arquivo, resolvido pelos dois
 *   algoritmos sendo que o tempo e solução de cada um é colocado no arquivo. Depois de todos os grafos
 *   forem gerados e resolvidos, no final do arquivo é se colocado o tempo médio de cada algoritmo.
 */
void compareAlgorithmsForGraphs() {
    fstream file;
    string nome = "temposGrafos.txt";
    tempos tDSatur, tRLF;
    solution S;

    file.open(nome, std::ios::out);
    if(file.is_open()) {
        int num, count=0, V, A;
        cout << "Numero de grafos a serem gerados: ";
        cin >> num;
        cout << "Numero de vertices dos grafos: ";
        cin >> V;
        cout << "Numero de arestas dos grafos: ";
        cin >> A;

        while(count < num) {
            graph g = graphRand(V, A);
            int cores[g.numVertices];
            for(int i=0; i<g.numVertices; i++) {
                cores[i] = g.adjMatrix[i][i].color;
                for(int j=0; j<g.numVertices; j++) {
                    file << g.adjMatrix[i][j].edge << ", ";
                }
                file << endl;
            }
            
            timedColoringDSatur(&g, &tDSatur);
            file << "\nTempo em microsegundos do algoritmo DSatur: " << tDSatur.tempo[count].count() << "\nSolucao do DSatur:" << endl;
            S = tDSatur.solucao[count];
            for(int i=0; i<(int)S.cores.size(); i++) {
                file << S.cores[i] << ": ";
                for(int j=0; j<(int)S.sets[i].size(); j++) {
                    file << S.sets[i][j] << " ";
                }
                file << endl;
            }

            for(int i=0; i<g.numVertices; i++) {
                g.adjMatrix[i][i].color = cores[i];
            }
            timedColoringRLF(&g, &tRLF);
            file << "\nTempo em microsegundos do algoritmo RLF: " << tRLF.tempo[count].count() << "\nSolucao do RLF:" << endl;
            S = tRLF.solucao[count];
            for(int i=0; i<(int)S.cores.size(); i++) {
                file << S.cores[i] << ": ";
                for(int j=0; j<(int)S.sets[i].size(); j++) {
                    file << S.sets[i][j] << " ";
                }
                file << endl;
            }
            file << endl;

            count++;
        }
        
        file << "Tempo medio em microsegundos do algoritmo DSatur: ";
        double media=0;
        for(int i=0; i<(int)tDSatur.tempo.size(); i++) {
            media += tDSatur.tempo[i].count();
        }
        media = media / num;
        file << media << endl;

        file << "Tempo medio em microsegundos do algoritmo RLF: ";
        media=0;
        for(int i=0; i<(int)tRLF.tempo.size(); i++) {
            media += tRLF.tempo[i].count();
        }
        media = media / num;
        file << media << endl;
    } else {
        cout << "Nao foi possivel abrir o arquivo " << nome << "!" << endl;
    }
    file.close();
}

/** @brief Compara os algoritmos DSatur e RLF para sudokus 2x2 ou 3x3 aleatórios.
 * 
 *  @details 
 *   Este método é usado para comparar os algoritmos DSatur e RLF para sudokus 2x2 ou 3x3 aleatórios. 
 *   Para isto acontecer, primeiro é se criacado um arquivo em que os sudokus gerados e as soluções dos
 *   algoritmos seram guardados. Depois disto é se perguntado o tamanho do sudoku a ser gerado, depois o
 *   números de  devem ser gerados, depois o número de sudokus a serem gerados e por último o número de
 *   células já devem possuir cores. Com tudo setado os sudokus são gerados, sendo que toda vez que um é
 *   gerado ele é colocado no arquivo, resolvido pelos dois algoritmos sendo que o tempo e solução de cada
 *   um é colocado no arquivo. Depois de todos os sudokus e resolvidos, no final do arquivo é se colocado
 *   o tempo médio de cada algoritmo e porcentagem de sudokus que cada algoritmo conseguiu resolver corretamente.
 */
void compareAlgorithmsForSudokus() {
    fstream file;
    string nome = "temposSudokus.txt";
    tempos tDSatur, tRLF;
    solution S;
    int size, num, cores, count=0;

    file.open(nome, std::ios::out);
    if(file.is_open()) {
        cout << "Tamanho dos sudokus a serem gerados(2-2x2 oy 3-3x3): ";
        cin >> size;
        cout << "Numero de sudokos " << size << "x" << size <<" a serem gerados: ";
        cin >> num;
        cout << "Numero de celulas do sudoku coloridas(0-" << (int)pow(size, 2) << "): ";
        cin >> cores;

        if(cores >= 0 || cores <= (int)pow(size, 2)) {
            while(count < num) {
                graph g;
                initializeSudoku(&g, size);
                sudokuRand(&g, cores);
                int cores[g.numVertices];
                for(int i=0; i<g.numVertices; i++) {
                    cores[i] = g.adjMatrix[i][i].color;
                    for(int j=0; j<g.numVertices; j++) {
                        if(count == 0) file << g.adjMatrix[i][j].edge << ", ";
                    }
                    if(count == 0) file << endl;
                }
                if(checkIfSudokuSovable(g)) {
                    int line=pow(g.numVertices, 1.0/2), l=0;
                    for(int i=0; i<g.numVertices; i++) {
                        file << g.adjMatrix[i][i].color << " ";
                        l++;
                        if(l == line) {
                            l = 0;
                            file << "\n";
                        }
                    }
                    
                    timedColoringDSatur(&g, &tDSatur);
                    file << "\nTempo em microsegundos do algoritmo DSatur: " << tDSatur.tempo[count].count() << "\nSolucao do DSatur:" << endl;
                    S = tDSatur.solucao[count];
                    for(int i=0; i<(int)S.cores.size(); i++) {
                        file << S.cores[i] << ": ";
                        for(int j=0; j<(int)S.sets[i].size(); j++) {
                            file << S.sets[i][j] << " ";
                        }
                        file << endl;
                    }

                    for(int i=0; i<g.numVertices; i++) {
                        g.adjMatrix[i][i].color = cores[i];
                    }
                    timedColoringRLF(&g, &tRLF);
                    file << "\nTempo em microsegundos do algoritmo RLF: " << tRLF.tempo[count].count() << "\nSolucao do RLF:" << endl;
                    S = tRLF.solucao[count];
                    for(int i=0; i<(int)S.cores.size(); i++) {
                        file << S.cores[i] << ": ";
                        for(int j=0; j<(int)S.sets[i].size(); j++) {
                            file << S.sets[i][j] << " ";
                        }
                        file << endl;
                    }
                    file << endl;

                    count++;
                }
            }

            double media=0;
            file << "Tempo medio em microsegundos do algoritmo DSatur: ";
            for(int i=0; i<(int)tDSatur.tempo.size(); i++) {
                media += tDSatur.tempo[i].count();
            }
            media = media / num;
            file << media << endl;

            media=0;
            file << "Tempo medio em microsegundos do algoritmo RLF: ";
            for(int i=0; i<(int)tRLF.tempo.size(); i++) {
                media += tRLF.tempo[i].count();
            }
            media = media / num;
            file << media << endl;

            double corretos = 0;
            file << "\nPorcentagem de sudokus resolvidos corretamente pelo DSatur: ";
            for(int i=0; i<(int)tDSatur.solucao.size(); i++) {
                if((int)tDSatur.solucao[i].cores.size() <= (int)pow(size, 2))
                    corretos++;
            }
            corretos = corretos / num * 100;
            file << corretos << "%" << endl;

            corretos = 0;
            file << "Porcentagem de sudokus resolvidos corretamente pelo RLF: ";
            for(int i=0; i<(int)tRLF.solucao.size(); i++) {
                if((int)tRLF.solucao[i].cores.size() <= (int)pow(size, 2))
                    corretos++;
            }
            corretos = corretos / num * 100;
            file << corretos << "%" << endl;
        }
    } else {
        cout << "Nao foi possivel abrir o arquivo " << nome << "!" << endl;
    }
    file.close();
}