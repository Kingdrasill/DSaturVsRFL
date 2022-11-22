#include "graph.hpp"

void readGraphFile();
void readSudokuFile();

int main(){
    readGraphFile();
    return 0;
}

void readGraphFile() {
    fstream file;
    string nome = "graph.txt", linha, num1, num2;
    solution cores;
    graph g;

    file.open(nome);
    if(file.is_open()) {
        if(getline(file, num1, '\n')) {
            int n = stoi(num1);
            initializeGraph(&g, n);
            while(getline(file, linha, '\n')) {
                stringstream vertexs(linha);
                getline(vertexs, num1, ',');
                getline(vertexs, num2, ',');
                if(num1 != num2) {
                    addEdge(&g, stoi(num1), stoi(num2));
                } else 
                    cout << "Lacos nao sao permitidos!" << endl;
            }
            printGraph(g);
            cores = colorirGraph(&g);
        } else {
            cout << "O arquivo nao esta formatado da forma correta!" << endl;
        }
    } else {
        cout << "Nao foi possivel abrir o arquivo " << nome << endl;
    }
    file.close();
    file.open(nome);
    if(file.is_open()) {
        if(getline(file, num1, '\n')) {
            int n = stoi(num1);
            initializeGraph(&g, n);
            while(getline(file, linha, '\n')) {
                stringstream vertexs(linha);
                getline(vertexs, num1, ',');
                getline(vertexs, num2, ',');
                if(num1 != num2) {
                    addEdge(&g, stoi(num1), stoi(num2));
                } else 
                    cout << "Lacos nao sao permitidos!" << endl;
            }
            for(int i=0; i<(int)cores.cores.size(); i++) {
                for(int j=0; j<(int)cores.S[i].size(); j++) {
                    addVertexColor(&g, cores.S[i][j], cores.cores[i]);
                }
            }
        }
    }
    file.close();
}

void readSudokuFile() {
    fstream file;
    string nome = "sudoku.txt", linha, num;

    file.open(nome);
    if(file.is_open()) {
        getline(file, num, '\n');
        int n = stoi(num);
        if(n == 2 || n == 3) {
            graph g;
            createSudokuGraph(&g, n);
            int i=0, c=0, cor=0;
            while(i<n*n) {
                getline(file, linha, '\n');
                stringstream nums(linha);
                while(getline(nums, num, ',')) {
                    cor = stoi(num);
                    if(cor != 0) {
                        addVertexColor(&g, c, cor);
                    }
                    c++;
                }
                i++;
            }
            cout << "Sudoku a ser completado: \n" << endl;
            printSudoku(g);
            colorirSudoku(&g);
        }
    } else {
        cout << "Nao foi possivel abrir o arquivo " << nome << endl;
    }
    file.close();
}