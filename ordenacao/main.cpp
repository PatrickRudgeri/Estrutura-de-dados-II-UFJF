// **************************************************************
//  ATIVIDADE 1 
// **************************************************************

#include <iostream>
#include <cstdlib>     // srand, rand
#include <ctime>       // time
#include <chrono>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace std::chrono;

// MACROS
#define TIME_POINT high_resolution_clock::time_point
#define NOW high_resolution_clock::now
#define DURATION_CAST duration_cast<duration<double>>

//funções auxiliares
void imprimeVetor(int *vet, int n) {
    for (int i = 0; i < n; i++) cout << vet[i] << " ";
    cout << endl;
}

unsigned long comp;

bool compararMaior(int a, int b) {
    comp++;
    return a > b;
}

unsigned long trocas;

void atribuir(int *a, int *b) {
    if (*a != *b) { //é necessário essa verificação?
        trocas++;
        *a = *b;
    }
}

void troca(int *a, int *b) {
    trocas++;
    int aux = *a;
    *a = *b;
    *b = aux;
}
//-------------------------------------------------


// Criar uma rotina para gerar um vetor de tamanho N com numeros 
// aleatórios
void geraVetorAleatorio(int *vet, int n, unsigned int seed) {
    int x;
    srand(seed);
    for (int i = 0; i < n; i++) {
        x = rand() % (n * 10) + 1;
        vet[i] = x;
    }
}

// Insere aqui o método de ordenacão classe quadrática
void insertionSort(int *vet_o, int n) {
    int pivo, i, vet[n];
    comp = 0, trocas = 0;
    copy(vet_o, vet_o + n, vet);
    cout << "Insertion sort" << " | ";

    TIME_POINT inicio = NOW();
    for (int j = 1; j < n; j++) {
        pivo = vet[j];
        i = j - 1;
        while (i >= 0 && compararMaior(vet[i], pivo)) {
            atribuir(&vet[i + 1], &vet[i]); // vet[i+1] recebe vet[i]
            i--;
        }
        atribuir(&vet[i + 1], &pivo); // vet[i+1] recebe pivo

    }
    cout << DURATION_CAST(NOW() - inicio).count() << " s | ";

    cout << "comparações: " << comp << " | ";
    cout << "alterações no vetor: " << trocas << endl;
}

// Insere aqui o método Shellsort
void shellsort(int *vet_o, int n) {
    int pivo, i, h, vet[n];
    comp = 0, trocas = 0;
    copy(vet_o, vet_o + n, vet);
    cout << "Shell sort" << " | ";

    TIME_POINT inicio = NOW();
    h = n / 2;
    while (h > 0) {
        //insertion sort
        for (int j = h; j < n; j++) {
            pivo = vet[j];
            i = j;

            while (i >= h && compararMaior(vet[i - h], pivo)) {
                atribuir(&vet[i], &vet[i - h]);
                i -= h;
            }
            atribuir(&vet[i], &pivo);
        }
        h /= 2;
    }
    cout << DURATION_CAST(NOW() - inicio).count() << " s | ";

    cout << "comparações: " << comp << " | ";
    cout << "alterações no vetor: " << trocas << endl;
}


// Insere aqui o método de ordenacão classe NLOGN

int particionamento(int *vet, int low, int high);

void quicksort(int *vet, int low, int high) {
    if (low < high) {
        int pivo_index = particionamento(vet, low, high);
        quicksort(vet, low, pivo_index - 1);
        quicksort(vet, pivo_index + 1, high);
    }

}

void quicksort(int *vet_o, int n) {
    int vet[n];
    trocas = 0, comp = 0;
    copy(vet_o, vet_o + n, vet);
    cout << "QuickSort" << " | ";
    TIME_POINT inicio = NOW();

    quicksort(vet, 0, n - 1);

    cout << DURATION_CAST(NOW() - inicio).count() << " s | ";
    cout << "comparações: " << comp << " | ";
    cout << "alterações no vetor: " << trocas << endl;
}

int particionamento(int *vet, int low, int high) {
    int i_pivo, pivo, i, j;
    i_pivo = high;  // utilizando limite superior como pivô
    pivo = vet[i_pivo];
    i = low - 1;

    for (j = low; j <= high; j++) {
        if (compararMaior(pivo, vet[j])) {
            i++;
            troca(&vet[i], &vet[j]);
        }
    }
    troca(&vet[i + 1], &vet[high]);
    return i + 1;
}


// Dica:
// Crie rotina para comparar e trocar 
//  e coloque um contador internamente para
// obter as métricas de desempenho. 

// Observação:
// Caso queira, pode-se implementar usando OO.
//
int compare(const void *a, const void *b) {
    return (*(int *) a > *(int *) b);
}

void qsort(int *vet_o, int n) {
    int vet[n];
    copy(vet_o, vet_o + n, vet);
    cout << "qsort" << "\t| ";
    TIME_POINT inicio = NOW();

    std::qsort(vet_o, n, sizeof(int), compare);

    cout << DURATION_CAST(NOW() - inicio).count() << " s | ";
}

int main() {
    int *vet, n, x;
    unsigned int seed;

    cin >> x;
    for (int i = 0; i < x; i++) {
        cout << "\n\nn" << i + 1 << ": ";
        cin >> n;
        vet = new int[(int) n];
        seed = time(NULL);
        geraVetorAleatorio(vet, n, seed);

        insertionSort(vet, n);
        shellsort(vet, n);
        quicksort(vet, n);
        qsort(vet, n);

        delete[] vet;
    }
}