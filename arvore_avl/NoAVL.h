#ifndef ATIV_PRATICAS_ED2_NOAVL_H
#define ATIV_PRATICAS_ED2_NOAVL_H


class NoAVL {
private:
    NoAVL *esq;
    int info;
    NoAVL *dir;
    int fator;
    int altura;
public:
    NoAVL() {
        fator = 0;
        altura = 0;
        info = -1;
        esq = nullptr;
        dir = nullptr;
    };

    NoAVL(int val, NoAVL *esq, NoAVL *dir) {
        fator = 0;
        altura = 0;
        info = val;
        this->esq = esq;
        this->dir = dir;
    };

    ~NoAVL() = default;

    void setEsq(NoAVL *p) { esq = p; }

    void setInfo(int val) { info = val; }

    void setDir(NoAVL *p) { dir = p; }

    void setFator(int f) { fator = f; }

    void setAltura(int h) { altura = h; }

    NoAVL *getEsq() { return esq; }

    int getInfo() { return info; }

    NoAVL *getDir() { return dir; }

    int getFator() { return fator; }

    int getAltura() { return altura; }
};


#endif //ATIV_PRATICAS_ED2_NOAVL_H
