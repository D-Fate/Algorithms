// Лабораторная работа 7:
// 1) разработайте алгоритм и напишите подпрограмму определения
//    позиции в массиве с помощью хэш-функции по алгоритму умножения
// 2) разработайте алгоритм и напишите подпрограмму, реализующую
//    разрешение коллизий по алгоритму квадратичных проб
// 3) разработайте алгоритм, напишите и выполните программу с
//    ранее разработанными подпрограммами, реализующую
//         1) генерацию 256 ключей (чисел из диапозона [1, 1000)),
//         2) создание хэш-таблицы из 4096-ти элементов с
//            использованием разработанных подпрограмм и
//            вывод ее на экран (пропуская пустые элементы),
//         3) запрос с клавиатуры искомого ключа, поиск его в
//            хэш-таблице и вывод на экран значения ключа и
//            номера его позиции в хэш-таблице.
#include <iostream>


const int N = 256;


template <typename T>
struct Pair {
    int key;
    T value;

    Pair(int key, T value) : key(key), value(value) {}
};


template <typename T>
class HashTable {
    public:
        void add(Pair<T>);
        void remove(int);
        T search(int);
        void print();

        HashTable();
        ~HashTable();
    private:
        int hash(int);
        // collisionResolve();
        void resize();

        int size_;
        int count_;

        Pair<T>* buckets_;
        bool* isOccupied_;

        static const int FILL_FACTOR_ = 75;
};


template <typename T>
HashTable<T>::HashTable() : size_(4096), count_(0) {
    buckets_ = new Pair<T>[size_];
    isOccupied_ = new bool[size_];
    for (int i = 0; i < size_; i++) {
        isOccupied_ = false;
    }
}

template <typename T>
HashTable<T>::~HashTable() {
    delete[] buckets_;
    delete[] isOccupied_;
}

template <typename T>
int HashTable<T>::hash(int key) {
    return 
}