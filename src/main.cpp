#include "function.hpp"

int main(){
    int option;
    cout << "1 - Comparar os algoritmos para Grafos aleatorios\n"
            << "2 - Comparar os algoritmos para Sudokus aleatorios\n"
            << "3 - Sair\n\n"
            << "Como deseja utilizar o programa: ";
    cin >> option;
    switch(option) {
        case 1:
            compareAlgorithmsForGraphs();
            break;
        case 2:
            compareAlgorithmsForSudokus();
            break;
        case 3:
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
    }
    return 0;
}