// Лабораторная работа 4:
// разработать алгоритм, написать и выполнить программу,
// реализующую
//      1) генерацию массива длины 243, наполненного
//         случайными кириллическими строками, и выводом его на экран,
//      2) сортировку Шелла по возрастанию,
//         где h[k + 1] = 3 * h[k] + 1
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>


const int N = 243;
const int STRING_LENGTH = 4;


std::string generateRandomString(int length) {
    static const std::vector<std::string> alphabet = {
        "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й",
        "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф",
        "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я",
        "а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й",
        "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф",
        "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"
    };
    std::string result;
    for (int i = 0; i < length; i++) {
        int index = rand() % alphabet.size();
        result += alphabet[index];
    }
    return result;
}


void shellSort(std::string array[], int size) {
    int gap = 1;
    while (gap < size / 3) {
        gap = 3 * gap + 1;
    }
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            std::string temp = array[i];
            int j = i;
            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
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
    std::srand(std::time(nullptr));

    std::string array[N];
    for (int i = 0; i < N; i++) {
        array[i] = generateRandomString(STRING_LENGTH);
    }
    
    std::cout << "Исходный массив:" << std::endl;
    print(array, N);
    std::cout << std::endl;

    shellSort(array, N);
    std::cout << "Отсортированный массив:" << std::endl;
    print(array, N);

    return 0;
}
