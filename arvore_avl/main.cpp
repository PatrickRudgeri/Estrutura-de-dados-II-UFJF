#include <iostream>
#include <random>
#include <chrono>
#include "ArvoreAVL.h"

using namespace std;
using namespace std::chrono;

// MACROS
#define TIME_POINT high_resolution_clock::time_point
#define NOW high_resolution_clock::now
#define DURATION_CAST duration_cast<duration<double>>

struct Args {
    ArvoreAVL *arv;
    int N, M, *vetInfos, *vetIndex;
};

void gerarNumAleatorios(int *&vet, int N, int maxRange) {
    vet = new int[N];
    random_device randomDevice;
    unsigned seed = randomDevice();

    default_random_engine randomEngine(seed);
    uniform_int_distribution<int> unifDist(0, maxRange);

    for (int i = 0; i < N; i++) {
        vet[i] = unifDist(randomEngine);
    }
}

void testeBuscasNaArvore(Args *pArgs) {
    int idx;
    for (int i = 0; i < pArgs->M; i++) {
        idx = pArgs->vetIndex[i];
        pArgs->arv->busca(pArgs->vetInfos[idx]);
    }
}

void testesArvores(Args *pArgs) {
    string arvTipo;

    arvTipo = pArgs->arv->isAvl() ? "AVL" : "ABB";

    cout << "Criando " + arvTipo + "..." << endl;

    for (int i = 0; i < pArgs->N; i++) {
        pArgs->arv->inserir(pArgs->vetInfos[i]);
    }

    cout << "Executando buscas na " + arvTipo + "..." << endl;

    TIME_POINT inicio = NOW();
    testeBuscasNaArvore(pArgs);

    cout << "Tempo de execucação:" << DURATION_CAST(NOW() - inicio).count() << " s" << endl;
    cout << "Altura : " << pArgs->arv->getAlturaArv() << endl;
    cout << "Comparações de chaves (buscas): " << pArgs->arv->getContComp() << endl;

}

int main() {
    Args args{};
    cout << "Digite o valor de M (buscas) e o valor de N (qt de nós): "; //no formato: M N
    cin >> args.M >> args.N;

    gerarNumAleatorios(args.vetInfos, args.N, args.N * 10);
    gerarNumAleatorios(args.vetIndex, args.M, args.N - 1); //indices aleatórios para buscas

    //---- Dados aleatórios ----/
    //---- testes ABB
    cout << "*** Dados aleatórios ***\n\n";
    cout << "ABB:" << endl;
    args.arv = new ArvoreAVL();
    testesArvores(&args);
    delete args.arv;

    //---- testes AVL
    cout << "\nAVL:" << endl;
    args.arv = new ArvoreAVL(true);
    testesArvores(&args);
    delete args.arv;

    cout << "***********************\n\n";

    //---- Dados ordenados ----/
    for (int i = 0; i < args.N; i++) {
        args.vetInfos[i] = i;
    }
    //---- testes ABB
    cout << "*** Dados Ordenados ***\n\n";
    cout << "ABB:" << endl;
    args.arv = new ArvoreAVL();
    testesArvores(&args);
    delete args.arv;

    //---- testes AVL
    cout << "\nAVL:" << endl;
    args.arv = new ArvoreAVL(true);
    testesArvores(&args);
    delete args.arv;

    delete[] args.vetInfos;
    delete[] args.vetIndex;

    return 0;
}