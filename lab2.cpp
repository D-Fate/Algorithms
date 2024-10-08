// Лабораторная работа 2:
// 1) написать подпрограмму линейного поиска в символьном массиве
// 2) массив заполняется поэлементно клавиатурным вводом
// 3) искомый символ также вводится с помощью клавиатуры
#include <iostream>


void clearInputStream() {
    int ch;
    while ((ch = getchar()) != '\n' and ch != EOF);
}


char getChar() {
    char result = getchar();
    clearInputStream();
    return result;
}


int findElement(char array[], char value) {
    int length = sizeof(array) / sizeof(*array); 
    for (int i = 0; i < length; i++) {
        if (array[i] == value)
            return i;
    }
    return -1;
}


int main() {
    int length = -1;
    while (length < 0) {
        std::cout << "Enter array length\n>> ";
        std::cin >> length;
        std::cout << std::endl;
    }
    clearInputStream();

    char* array = new char[length];
    for (int i = 0; i < length; i++) {
        std::cout << "Enter a[" << i << "]\n>> ";
        array[i] = getChar();
    }

    char target;
    std::cout << "Enter target element\n>> ";
    target = getChar();
    std::cout << std::endl;

    std::cout << "Entered array: ";
    for (int i = 0; i < length; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Target element index: "
              << findElement(array, target)
              << std::endl;
    delete[] array;
    return 0;
}
