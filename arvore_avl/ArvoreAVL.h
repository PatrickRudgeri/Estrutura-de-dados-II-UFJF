#ifndef ATIV_PRATICAS_ED2_ARVOREAVL_H
#define ATIV_PRATICAS_ED2_ARVOREAVL_H


#include "NoAVL.h"

class ArvoreAVL {
private:
    NoAVL *raiz;
    bool balanceamento;
    bool incAltura;

    bool auxBusca(NoAVL *p, int val);

    NoAVL *auxInsere(NoAVL *p, int val);

    NoAVL *auxRemove(NoAVL *p, int val);

    NoAVL *menorSubArvDireita(NoAVL *p);

    NoAVL *removeFolha(NoAVL *p);

    NoAVL *remove1Filho(NoAVL *p);

    void imprimePorNivel(NoAVL *p, int nivel);

    NoAVL *libera(NoAVL *p);

public:
    ArvoreAVL() = default;

    explicit ArvoreAVL(bool balanceamento = false);

    ~ArvoreAVL();

    bool vazia(); // verifica se a árvore está vazia
    bool busca(int val);

    void insere(int val);

    void remove(int val);

    void imprime();

    void setBalanceamento(bool b);

    int getAlturaArv();
};


#endif //ATIV_PRATICAS_ED2_ARVOREAVL_H
