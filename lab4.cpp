// Ћабораторна€ работа 4:
// разработать алгоритм, написать и выполнить программу,
// реализующую
//      1) генерацию массива длины 243, наполненного
//         случайными кириллическими строками, и выводом его на экран,
//      2) сортировку Ўелла по возрастанию,
//         где h[k + 1] = 3 * h[k] + 1
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


const int N = 243;
const int STRING_LENGTH = 4;


std::string generateRandomString(int length) {
    static const char alphabet[] =
        "јЅ¬√ƒ≈®∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя"
        "абвгдеЄжзийклмнопрстуфхцчшщъыьэю€";
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; i++) {
        result += alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    return result;
}


void shellSort(std::string array[], int size) {
    int gap = 1;
    while (gap < (size - 1) / 3) {
        gap = 3 * gap + 1;
    }
    while (gap) {
        int j;
        for (int i = gap; i < size; i += 1) {
            std::string temp = array[i];
            for (j = i; j >= gap and array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp; 
        }
        gap = (gap - 1) / 3;
    }
}


void print(std::string array[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << std::endl;
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::srand(std::time(nullptr));

    std::string array[N];
    for (int i = 0; i < N; i++) {
        array[i] = generateRandomString(STRING_LENGTH);
    }
    std::cout << "Original array:" << std::endl;
    print(array, N);
    std::cout << std::endl;

    shellSort(array, N);
    std::cout << "Sorted array:" << std::endl;
    print(array, N);

    return 0;
}
