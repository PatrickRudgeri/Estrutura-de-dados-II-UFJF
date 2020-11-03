#include "ArvoreAVL.h"
#include <iostream>

using namespace std;

ArvoreAVL::ArvoreAVL(bool balanceamento) {
    raiz = nullptr;
    this->balanceamento = balanceamento;
    incAltura = false;
}

bool ArvoreAVL::vazia() {
    return raiz == nullptr;
}

void ArvoreAVL::insere(int val) {
    cout << "inserindo " << val << ":" << endl;
    raiz = auxInsere(raiz, val);
}

NoAVL *aplicarRotacao(NoAVL *p);

void updateFactor(NoAVL *p);

void updateAltura(NoAVL *p);

NoAVL *ArvoreAVL::auxInsere(NoAVL *p, int val) {

    NoAVL *filho, *pTemp;
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
        updateAltura(p);
    }
    if (balanceamento) {
        updateFactor(p);

        cout << "\t" << p->getInfo() << " (h=" << p->getAltura() << ")" << " (f=" << p->getFator() << ")"
             << endl; //fixme:debug
//      Se fator for > 1 ou < que -1, então fazer rotação, atualizar altura do nó movido e atualizar fatores
        if (p->getFator() > 1 || p->getFator() < -1) {
//            pTemp = p;
            p = aplicarRotacao(p);
            incAltura = false;
        }
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
void updateNoh(NoAVL *p, NoAVL *r){
    updateAltura(p);//atualizando a altura do nó que foi movido
    updateAltura(r);
    updateFactor(p); //atualizando fator do nó p
    updateFactor(r); //atualizando fator do nó r
}

NoAVL *rotacaoSimplesEsq(NoAVL *p) {
    cout << "\t\t\t*Rotação à esquerda*" << endl;
    NoAVL *r = p->getDir();//
    p->setDir(r->getEsq());
    r->setEsq(p);
    updateNoh(p, r);
    return r;
}

NoAVL *rotacaoSimplesDir(NoAVL *p) {
    cout << "\t\t\t*Rotação à direita*" << endl;
    NoAVL *r = p->getEsq();
    p->setEsq(r->getDir());
    r->setDir(p);
    updateNoh(p, r);
    return r;
}

NoAVL *aplicarRotacao(NoAVL *p) {
    // Implementar aqui as funções de rotação
    NoAVL *q;
    cout << "\t\tAplicando rotação em : p->info=" << p->getInfo() << endl; //fixme: debug
    //rotação à esquerda
    if (p->getFator() == 2) {
        q = p->getDir();
        // se F(q) == -1, então é rotação dupla. Ou uma simples à direita + 1 simples à esquerda
        if (q->getFator() == -1) {
            p->setDir(rotacaoSimplesDir(q));
        }
        // se F(q) != -1, então é apenas uma simples à esquerda
        q = rotacaoSimplesEsq(p);


    } else { //rotação à direita
        q = p->getEsq();
        // se F(q) == 1, então é rotação dupla. Ou uma simples à esquerda + 1 simples à direita
        if (q->getFator() == 1) {
            p->setEsq(rotacaoSimplesEsq(q));
        }
        // se F(q) != 1, então é apenas uma simples à direita
        q = rotacaoSimplesDir(p);
    }
    return q;
}

void updateFactor(NoAVL *p) {
    // lambda function para retornar a altura (int) do nó passado como parâmetro (por referencia)
    auto getAltura = [&](NoAVL *filho) mutable -> int {
        return filho != nullptr ? filho->getAltura() : -1;
    };
    p->setFator(getAltura(p->getDir()) - getAltura(p->getEsq()));
}

void updateAltura(NoAVL *p) {
    NoAVL *esq, *dir;
    int he, hd;
    esq = p->getEsq();
    dir = p->getDir();
    he = (esq == nullptr) ? -1 : esq->getAltura();
    hd = (dir == nullptr) ? -1 : dir->getAltura();
    p->setAltura((he > hd ? he : hd) + 1);
}
