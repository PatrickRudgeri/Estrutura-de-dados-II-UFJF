// **************************************************************
//  ATIVIDADE 2
// **************************************************************
// Dados do Aluno
// Nome: Patrick Rudgeri Pilato Lemes
// Matricula: 201865075AC
// E-mail: patrick.rudgeri@estudante.ufjf.br
//***************************************************************


#include <iostream>
#include <cstdlib>
#include "Hash.h"

using namespace std;

int main(){
    Hash hashTable;
    const int M = 10;
    int key;
    srand(time(0));

    hashTable.create(M, hashType::divisao);
    for (int i=0; i < 10; i++){
        key = rand()%(M*10)+1;
        hashTable.insert(key, i);
    }
    cout << "Colisões: " << hashTable.getColisoes();

    hashTable.imprimirTabela();
    return 0;
}
















