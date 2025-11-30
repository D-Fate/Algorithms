// Лабораторная работа 3:
// разработать алгоритм, написать и выполнить программу,
// реализующую
//      1) генерацию матрицы случайных целых чисел размерами
//         5 x 5 с сохранением ее в двумерном массиве и
//         выводом на экран,
//      2) сортировку строк матрицы методом пузырька по
//         убыванию сумм элементов, при выводе результирующей
//         матрицы суммы вывести шестым столбцом.
#include <iostream>
#include <cstdlib>
#include <ctime>


const int N = 5;


int** createMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    matrix[0] = new int[rows * cols];
    for (int i = 0; i < rows; i++) {
        matrix[i] = matrix[0] + i * cols;
    }
    return matrix;
}


void destruct(int** matrix) {
    delete[] matrix[0];
    delete[] matrix;
}


int** generateRandomMatrix(int size, int max) {
    int** matrix = createMatrix(size, size);
    std::srand(std::time(nullptr));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = std::rand() % (max + 1);
        }
    }
    return matrix;
}


int sum(int* array, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += array[i];
    }
    return result;
}


void print(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << '\t';
        }
        std::cout << std::endl;
    }
}


int main() {
    // создаем случайную матрицу N * N
    int** matrix = generateRandomMatrix(N, 100);
    // выводим случайную матрицу на экран
    std::cout << "Orginal matrix:" << std::endl;
    print(matrix, N, N);
    // считаем сумму каждой строки
    int rowSums[N];
    for (int i = 0; i < N; i++) {
        rowSums[i] = sum(matrix[i], N);
    }
    // создаем и заполняем массив индексов строк
    int rowIndexes[N];
    for (int i = 0; i < N; i++) {
        rowIndexes[i] = i;
    }
    // сортируем пузырьком суммы и индексы по убыванию сумм
    bool isChanged;
    for (int i = 0; i < N - 1; i++) {
        isChanged = false;
        for (int j = 0; j < N - i - 1; j++) {
            if (rowSums[j] > rowSums[j + 1]) {
                std::swap(rowSums[j], rowSums[j + 1]);
                std::swap(rowIndexes[j], rowIndexes[j + 1]);
                isChanged = true;
            }
        }
        if (!isChanged) {
            break;
        }
    }
    // создаем результирующую матрицу
    int** resultMatrix = createMatrix(N, N + 1);
    // заполняем результирующую матрицу
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            resultMatrix[i][j] = matrix[rowIndexes[i]][j];
        }
        resultMatrix[i][N] = rowSums[i];
    }
    // выводим результирующую матрицу
    std::cout << "Result matrix:" << std::endl;
    print(resultMatrix, N, N + 1);
    // освобождаем память
    destruct(resultMatrix);
    destruct(matrix);
    return 0;
}
