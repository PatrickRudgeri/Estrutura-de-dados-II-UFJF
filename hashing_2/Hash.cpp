#include <cmath>
#include <iostream>
#include "Hash.h"

using namespace std;

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
    No *no, *temp;

    h = aplicarFuncHash(key);
    no = new No(key, data);

    cout << "inserindo: (" << key << "," << data << ")";
    cout << " => (" << h << "," << no->data << ")\n";

    if (tabela[h] == nullptr) {
        tabela[h] = no;
        return tabela[h];
    }
    temp = tabela[h];
    while (temp->prox != nullptr) {
        temp = temp->prox;
    }
    colisoes++;
    temp->prox = no;
    return temp;
}

/*      Pesquisa se data com chave key está na tabela.
 * Se estiver, retorna ponteiro para data, caso contrário retorne NULL.
 * */
No *Hash::lookup(int key, int data) {
    int h;
    No *temp;
    h = aplicarFuncHash(key);
    if (tabela[h] != nullptr) {
        temp = tabela[h];
        while (temp != nullptr) {
            if (temp->data == data)
                return temp;
            temp = temp->prox;
        }
    }
    return nullptr;
}

/*
 * Remove a tabela hash da memória
 * */
void Hash::destroy() {
    for (int i = 0; i < m; i++) {
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
    return k % m;
}

/*
 * função hash : Multiplicação
 * */
int Hash::funcMultiplicacao(int k) {
    return floor(m * (k * a - floor(k * a)));
}

/*
 * função hash : MinhaHash
 * */
int Hash::funcMinhaHash(int k) {
    return (11 * (int) pow(k, 2)) % m;
}

int Hash::aplicarFuncHash(int key) {
    int h;
    switch (funcHash) {
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
    cout << "\n\nImprimindo tabela hash:\n";
    for (int i = 0; i < m; i++) {
        No *atual = tabela[i];

        cout << "[" << i << "] ";
        if (atual == nullptr)
            cout << "NULL";

        while (atual != nullptr) {
            cout << "(" << atual->key << ", " << atual->data << ") -> ";
            atual = atual->prox;
        }
        cout << "\n";
    }
}

int Hash::getColisoes() {
    return colisoes;
}


