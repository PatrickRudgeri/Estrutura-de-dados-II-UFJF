#include <iostream>
#include "ArvoreAVL.h"

using namespace std;

int main() {
    ArvoreAVL arv(true);

    cout << "Criando AVL..." << endl;
//    arv.insere(15);
//    arv.insere(20);
//    arv.insere(7);
//    arv.insere(11);
//    arv.insere(18);
//    arv.insere(24);
//    arv.insere(6);
//    arv.insere(8);
//    arv.insere(10);
//    arv.insere(5);
//    arv.insere(12);
//    arv.insere(17);
//    arv.insere(19);

    arv.insere(30);
    arv.insere(40);
    arv.insere(50);
//    arv.insere(55);
//    arv.insere(35);
//    arv.insere(33);
    cout << endl << "---" << endl;
    arv.imprime();
    cout << endl;


    cout << "Busca o valor 35: " << (arv.busca(35) ? "Sim" : "Não") << endl;
    cout << "Busca o valor  5: " << (arv.busca(5) ? "Sim" : "Não") << endl;
    cout << endl;
    cout << "Altura da árvore: " << arv.getAlturaArv() << endl;

//    cout << "Removendo os valores 24, 6, 7, 12, 18, 5." << endl;
//    arv.remove(24);
//    arv.remove(6);
//    arv.remove(7);
//    arv.remove(12);
//    arv.remove(18);
//    arv.remove(5);
//    cout << endl;
//
//    cout << "Arvore AVL final:" << endl;
//    arv.imprime();

    return 0;
}