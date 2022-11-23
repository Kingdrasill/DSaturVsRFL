#include "rlf.hpp"

void randomGraph();
void readGraphFile();
void readSudokuFile();
void testAlgorithms();

int main(){
    int option;
    cout << "1 - Resolver Sudoku do arquivo\n" 
            << "2 - Resolver grafo do arquivo\n" 
            << "3 - Resolver grafo aleatorio\n"
            << "4 - Testar os algoritmos varias vezes\n"
            << "5 - Sair\n\n"
            << "Como deseja utilizar o programa: ";
    cin >> option;
    switch(option) {
        case 1:
            readSudokuFile();
            break;
        case 2:
            readGraphFile();
            break;
        case 3:
            randomGraph();
            break;
        case 4:
            testAlgorithms();
            break;
        case 5:
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
    }
    return 0;
}

void randomGraph() {
    int V, A;
    cout << "Numero de vertices: ";
    cin >> V;
    cout << "Numero de arestas: ";
    cin >> A;
    graph g = graphRand(V, A);
    printGraph(g);
    colorirGraph(&g);
}

void readGraphFile() {
    fstream file;
    string nome = "graph.txt", linha, num1, num2;
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
            colorirGraph(&g);
        } else {
            cout << "O arquivo nao esta formatado da forma correta!" << endl;
        }
    } else {
        cout << "Nao foi possivel abrir o arquivo " << nome << endl;
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

void testAlgorithms() {
    int option, V, A, num;
    cout << "1 - Testar com grafos aleatorios\n"
            << "2 - Testar com sudokus aleatorios\n"
            << "\nEscolha uma opcao: ";
    cin >> option;
    switch (option) {
        case 1:
            cout << "\nQuantidade de vertices por grafo: ";
            cin >> V;
            cout << "Quantidade de arestas por grafo: ";
            cin >> A;
            cout << "Quantos grafos devem ser gerados: ";
            cin >> num;
            for(int i=0; i<num; i++) {
                cout << endl;
                graph g = graphRand(V,A);
                printGraph(g);
                colorirGraph(&g);
                cout << endl;
            }
            break;
        case 2:
            cout << "\nTamanho do sudoku(2-2x2 ou 3-3x3): ";
            cin >> V;
            if(V == 2 || V == 3) {
                cout << "Quantos vertices devem ser coloridos(Entre 1-" << pow(V, 2) << "): ";
                cin >> A;
                if(A > 0 && A < pow(V, 2)+1) {
                    cout << "Quantos sudoku devem ser gerados: ";
                    cin >> num;
                    int count = 1;
                    while(count <= num) {
                        cout << endl;
                        graph g;
                        createSudokuGraph(&g, V);
                        sudokuRand(&g, A);
                        printSudoku(g);
                        colorirSudoku(&g);
                        count++;
                    }
                }
            }
            break;
        default:
            cout << "Opcao Invalida!" << endl;
            break;
    }        
}