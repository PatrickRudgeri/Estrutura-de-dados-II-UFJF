#ifndef ATIV_PRATICAS_ED2_HASH_H
#define ATIV_PRATICAS_ED2_HASH_H

struct No{
    No(int key, int data){
        this->key = key;
        this->data = data;
        prox = nullptr;
    }
    int key;
    int data;
    No *prox;
};

enum hashType{divisao, multiplicacao, minhaHash};

class Hash {
public:
    Hash();

    virtual ~Hash();

    void create(int m, hashType hashFunc);

    No *insert(int key, int data);

    No *lookup(int key, int data);

    void destroy();

    int funcDivisao(int k);

    int funcMultiplicacao(int k);

    int funcMinhaHash(int k);

    void imprimirTabela();

    int getColisoes();

private:
    int m;
    float a;
    hashType funcHash;
    int colisoes;
    No **tabela;

    int aplicarFuncHash(int key);
};


#endif //ATIV_PRATICAS_ED2_HASH_H
