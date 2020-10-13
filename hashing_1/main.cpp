// **************************************************************
//  ATIVIDADE 2
// **************************************************************

#include <iostream>
#include <cstdlib>
#include "Hash.h"

using namespace std;

int main(){
    Hash hashTable;
    const int M = 10;
    int key;
//    int seed = time(nullptr);
    int seed = 42;
    srand(seed);

    cout << "seed = " << seed << endl;
    hashTable.create(M, hashType::divisao);
    for (int i=0; i < 10; i++){
        key = rand()%(M*10)+1;
        hashTable.insert(key, i);
    }
    cout << "Colisões: " << hashTable.getColisoes();

    cout << "\n\n*Encontrou {key: 22, data:6}? ";
    if (hashTable.lookup(22, 6) != nullptr)
        cout << "Sim\n";
    else
        cout << "Não\n";

    hashTable.imprimirTabela();
    return 0;
}
















