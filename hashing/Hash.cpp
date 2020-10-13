#include <cmath>
#include <iostream>
#include "Hash.h"

Hash::Hash() {
    a = (sqrt(5) - 1) / 2;
}

Hash::~Hash() {
    destroy();
}

/*
 * Cria uma tabela de tamanho m que usa a função hash
 * */
void Hash::create(int m, hashType hashFunc) {
    this->m = m;
    funcHash = hashFunc;
    colisoes = 0;
    tabela = new No *[m];
    for (int i = 0; i < m; i++) {
        tabela[i] = nullptr;
    }
}

/*      Insere data com chave key na tabela.
 * A função deve retornar um ponteiro para o elemento inserido.
 * Se data  já existir, retorna-se um ponteiro para ele.
 * */
No *Hash::insert(int key, int data) {
    int h;
    No *no, *pesquisaNo, *temp;

    h = aplicarFuncHash(key);
    no = new No(h, data);

    std::cout << "insert: (" << key << "," << data << ")";
    std::cout << " => (" << no->key << "," << no->data << ")\n";

    pesquisaNo = lookup(key, data);
    if (pesquisaNo == nullptr) {
        tabela[h] = no;
        return tabela[h];
    }

    temp = pesquisaNo;

    while (temp->prox != nullptr){
        colisoes++; //fixme: está com problema nesse contador
        temp = temp->prox;
    }
    temp->prox = no;
    return temp;

}

/*      Pesquisa se data com chave key está na tabela.
 * Se estiver, retorna ponteiro para data, caso contrário retorne NULL.
 * */
No *Hash::lookup(int key, int data) {
    int h;
    h = aplicarFuncHash(key);
    if (tabela[h] != nullptr) {
        return tabela[h];
    }
    return nullptr;
}

/*
 * Remove a tabela hash da memória
 * */
void Hash::destroy() {
    for (int i = 0; i < this->m; i++) {
        No *atual = tabela[i];
        No *tmp;
        while (atual != nullptr) {
            tmp = atual->prox;
            delete atual;
            atual = tmp;
        }
    }
    delete[] tabela;
}

/*
 * função hash : Divisão
 * */
int Hash::funcDivisao(int k) {
    return k % this->m;
}

/*
 * função hash : Multiplicação
 * */
int Hash::funcMultiplicacao(int k) {
    return floor(this->m * (k * this->a - floor(k * this->a)));
}

/*
 * função hash : MinhaHash
 * */
int Hash::funcMinhaHash(int k) {
    return funcDivisao(k + (int) pow(k, 2));
}

int Hash::aplicarFuncHash(int key) {
    int h;
    switch (this->funcHash) {
        case hashType::divisao:
            h = funcDivisao(key);
            break;
        case hashType::multiplicacao:
            h = funcMultiplicacao(key);
            break;
        case hashType::minhaHash:
            h = funcMinhaHash(key);
            break;
    }
    return h;
}

void Hash::imprimirTabela() {
    std::cout << "\n\nImprimindo tabela hash:\n";
    for (int i = 0; i < this->m; i++) {
        No *atual = tabela[i];

        std::cout << "[" << i << "] ";
        if (atual == nullptr)
            std::cout << "NULL";

        while (atual != nullptr) {
            std::cout << "(" << atual->key << ", " << atual->data << ") -> ";
            atual = atual->prox;
        }
        std::cout << "\n";
    }
}

int Hash::getColisoes(){
    return colisoes;
}


