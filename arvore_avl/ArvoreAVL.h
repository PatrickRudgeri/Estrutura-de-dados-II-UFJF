#ifndef ATIV_PRATICAS_ED2_ARVOREAVL_H
#define ATIV_PRATICAS_ED2_ARVOREAVL_H


#include "NoAVL.h"

class ArvoreAVL {
private:
    NoAVL *raiz;
    bool balanceamento;
    bool incAltura;
    int contComp;

    bool auxBusca(NoAVL *p, int val);

    NoAVL *auxInsere(NoAVL *p, int val);

    NoAVL *auxRemove(NoAVL *p, int val);

    NoAVL *menorSubArvDireita(NoAVL *p);

    NoAVL *removeFolha(NoAVL *p);

    NoAVL *remove1Filho(NoAVL *p);

    void imprimePorNivel(NoAVL *p, int nivel);

    NoAVL *libera(NoAVL *p);

    //AVL methods
    NoAVL *aplicarRotacao(NoAVL *p);
    void updateFactor(NoAVL *p);
    void updateAltura(NoAVL *p);
    void updateNoh(NoAVL *p, NoAVL *r);
    NoAVL *rotacaoSimplesEsq(NoAVL *p);
    NoAVL *rotacaoSimplesDir(NoAVL *p);

    bool incContComp(bool expression=false); //apenas um "wrapper" para incrementar contador

public:
    ArvoreAVL();

    explicit ArvoreAVL(bool balanceamento);

    ~ArvoreAVL();

    bool vazia(); // verifica se a árvore está vazia
    bool busca(int val);

    void inserir(int val);

    void remove(int val);

    void imprime();

    void setBalanceamento(bool b);

    int getAlturaArv();

    int getContComp() const;

    bool isAvl() const;
};


#endif //ATIV_PRATICAS_ED2_ARVOREAVL_H
