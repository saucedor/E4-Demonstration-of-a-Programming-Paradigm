#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define THREADS 4

using namespace std;

void initMatrix(char **m, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m[i][j] = rand() % 2 == 0 ? 'X' : '.';
}

void printMatrix(char **m, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
    cout << "-------------------------" << endl;
}

char analyzeCell(char **m, int N, int i, int j) {
    int alive = 0;
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
            if ((x != 0 || y != 0) && i + x >= 0 && j + y >= 0 && i + x < N && j + y < N)
                alive += m[i + x][j + y] == 'X';

    if (m[i][j] == 'X') {
        if (alive < 2 || alive > 3) return '.';
        else return 'X';
    } else {
        if (alive == 3) return 'X';
        else return '.';
    }
}

char** allocateMatrix(int N) {
    char **matrix = new char*[N];
    for (int i = 0; i < N; i++)
        matrix[i] = new char[N];
    return matrix;
}

void deallocateMatrix(char **matrix, int N) {
    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;
}

int main() {
    srand(time(NULL));

    int N, GENERATIONS;
    cout << "Size of the Matrix: ";
    cin >> N;
    cout << "Number of Generations: ";
    cin >> GENERATIONS;

    char **current = allocateMatrix(N);
    char **next = allocateMatrix(N);

    initMatrix(current, N);

    cout << "Initial State:\n";
    printMatrix(current, N);

    for (int gen = 0; gen < GENERATIONS; gen++) {
        #pragma omp parallel for num_threads(THREADS) collapse(2)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                next[i][j] = analyzeCell(current, N, i, j);

        #pragma omp parallel for num_threads(THREADS) collapse(2)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                current[i][j] = next[i][j];

        cout << "Gen " << gen + 1 << ":\n";
        printMatrix(current, N);
    }

    deallocateMatrix(current, N);
    deallocateMatrix(next, N);

    return 0;
}
