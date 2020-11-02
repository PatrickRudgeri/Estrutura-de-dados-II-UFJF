#include "ArvoreAVL.h"
#include <iostream>

using namespace std;

ArvoreAVL::ArvoreAVL() {
    raiz = nullptr;
    balanceamento = false;
    incAltura = false;
}

bool ArvoreAVL::vazia() {
    return raiz == nullptr;
}

void ArvoreAVL::insere(int val) {
    cout << "inserindo " << val << ":"<< endl;
    raiz = auxInsere(raiz, val);
}

NoAVL *ArvoreAVL::auxInsere(NoAVL *p, int val) {

    NoAVL *filho = nullptr;
    if (p == nullptr) {
        p = new NoAVL(val, nullptr, nullptr);
    } else if (val < p->getInfo()) {
        filho = auxInsere(p->getEsq(), val);
        p->setEsq(filho);
    } else {
        filho = auxInsere(p->getDir(), val);
        p->setDir(filho);
    }
    // Quando o nó atual for uma folha, flag incAltura se torna true
    if (p->getEsq() == nullptr && p->getDir() == nullptr) {
        incAltura = true;
    }
    // se flag é true e o noh atual não foi o noh adicionado
    if (incAltura) {
        if (filho != nullptr)
            p->setAltura(filho->getAltura() + 1);
    }
    //refatorar para método
    p->setFator(
            (p->getDir() != nullptr ? p->getDir()->getAltura() : -1) -
            (p->getEsq() != nullptr ? p->getEsq()->getAltura() : -1)
    );

    cout << "\t" << p->getInfo() << " (h=" << p->getAltura() << ")" << " (f=" << p->getFator() << ")" << endl; //fixme:debug

      if(p->getFator() > 1 || p->getFator() < -1){
          aplicarRotacao(p);
      }

    return p;
}

bool ArvoreAVL::busca(int val) {
    return auxBusca(raiz, val);
}

bool ArvoreAVL::auxBusca(NoAVL *p, int val) {
    if (p == nullptr)
        return false;
    else if (p->getInfo() == val)
        return true;
    else if (val < p->getInfo())
        return auxBusca(p->getEsq(), val);
    else
        return auxBusca(p->getDir(), val);
}

void ArvoreAVL::remove(int val) {
    raiz = auxRemove(raiz, val);
}

NoAVL *ArvoreAVL::auxRemove(NoAVL *p, int val) {
    if (p == nullptr)
        return nullptr;
    else if (val < p->getInfo())
        p->setEsq(auxRemove(p->getEsq(), val));
    else if (val > p->getInfo())
        p->setDir(auxRemove(p->getDir(), val));
    else {
        if (p->getEsq() == nullptr && p->getDir() == nullptr)
            p = removeFolha(p);
        else if ((p->getEsq() == nullptr) || (p->getDir() == nullptr))
            p = remove1Filho(p);
        else {
            NoAVL *aux = menorSubArvDireita(p);
            int tmp = aux->getInfo();
            p->setInfo(tmp);
            aux->setInfo(val);
            p->setDir(auxRemove(p->getDir(), val));
        }
    }
    return p;
}

NoAVL *ArvoreAVL::removeFolha(NoAVL *p) {
    delete p;
    return nullptr;
}

NoAVL *ArvoreAVL::remove1Filho(NoAVL *p) {
    NoAVL *aux;
    if (p->getEsq() == nullptr)
        aux = p->getDir();
    else
        aux = p->getEsq();
    delete p;
    return aux;
}

NoAVL *ArvoreAVL::menorSubArvDireita(NoAVL *p) {
    NoAVL *aux = p->getDir();
    while (aux->getEsq() != nullptr)
        aux = aux->getEsq();
    return aux;
}

void ArvoreAVL::imprime() {
    imprimePorNivel(raiz, 0);
}

void ArvoreAVL::imprimePorNivel(NoAVL *p, int nivel) {
    if (p != nullptr) {
        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getInfo() << " (h=" << p->getAltura() << ")" << " (f=" << p->getFator() << ")" << endl;
        imprimePorNivel(p->getEsq(), nivel + 1);
        imprimePorNivel(p->getDir(), nivel + 1);
    }
}

ArvoreAVL::~ArvoreAVL() {
    raiz = libera(raiz);
}

NoAVL *ArvoreAVL::libera(NoAVL *p) {
    if (p != nullptr) {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = nullptr;
    }
    return p;
}

void ArvoreAVL::setBalanceamento(bool b) {
    balanceamento = b;
}

int ArvoreAVL::getAlturaArv() {
    return (raiz != nullptr) ? raiz->getAltura() : -1;
}

void ArvoreAVL::aplicarRotacao(NoAVL *pAvl) {
    // Implementar aqui as funções de rotação
    cout << "\t\tAplicando rotação em :" << pAvl->getInfo() << endl;
}
