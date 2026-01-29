#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    const int N = 1000;
    const int displayAmount = 1000; // Define cuantas filas veras en el display

    int A[N], B[N], C[N];
    int threadList[N];
    omp_set_num_threads(4); // this was cool to find out! Esto fija cuantos threads utilizara OpenMP


    // Inicializar números aleatorios
    srand((unsigned)time(nullptr));

    // Llenar arreglos A y B
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000; // %1000 fija el limite superior de aleatoriedad
        B[i] = rand() % 1000;
    }

    // Suma paralela con OpenMP
#pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        int tid = omp_get_thread_num();
        threadList[i] = tid;
        C[i] = A[i] + B[i];
    }

    // Mostrar algunos valores para comprobar
    cout << "Index\tA\tB\tC(A+B)\tThread" << endl;
    for (int i = 0; i < displayAmount; i++) {
        cout << i << "\t"
            << A[i] << "\t"
            << B[i] << "\t"
            << C[i] << "\t"
            << threadList[i] << endl;
    }

    return 0;
}
