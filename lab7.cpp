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
#include <cstdlib>
#include <ctime>


const int N = 256;
const int TABLE_SIZE = 4096;


template <typename T>
struct Pair {
    int key;
    T value;

    Pair() : key(0), value(T()) {}
    Pair(int key, T value) : key(key), value(value) {}
};


template <typename T>
class HashTable {
    public:
        void add(Pair<T>);
        void remove(int);
        Pair<T> search(int);
        void print();

        HashTable();
        ~HashTable();
    private:
        int hash(int);
        int collision_resolve(int, int);

        void resize();

        int size_;
        int count_;

        Pair<T>* buckets_;
        bool* is_occupied_;

        static const int FILL_FACTOR_ = 75;
};


int main() {
    std::srand(std::time(nullptr));

    HashTable<int> table;
    // генерация 256 ключей из диапазона [1, 1000)
    std::cout << "Generating 256 keys..." << std::endl;
    for (int i = 0; i < N; i++) {
        int key = std::rand() % 999 + 1;
        table.add(Pair<int>(key, key * 10));
    }
    
    // вывод хэш-таблицы (пропуская пустые элементы)
    std::cout << "Hash table contents:" << std::endl;
    table.print();
    std::cout << std::endl;
    
    // поиск ключа
    std::cout << "Enter key to search\n>> ";
    int target;
    std::cin >> target;
    
    Pair<int> result = table.search(target);
    if (result.key != -1) {
        std::cout << "Found key " << result.key 
                  << " with value " << result.value 
                  << " at position in table" << std::endl;
    } else {
        std::cout << "Key " << target << " not found" << std::endl;
    }
    
    return 0;
}


template <typename T>
void HashTable<T>::add(Pair<T> pair) {
    if (count_ * 100 / size_ >= FILL_FACTOR_) {
        resize();
    }

    int attempt = 0;
    int index = hash(pair.key);
    
    while (is_occupied_[index] && attempt < size_) {
        if (buckets_[index].key == pair.key) {
            buckets_[index].value = pair.value;
            return;
        }
        attempt++;
        index = collision_resolve(hash(pair.key), attempt);
    }

    if (attempt < size_) {
        buckets_[index] = pair;
        is_occupied_[index] = true;
        count_++;
    }
}

template <typename T>
void HashTable<T>::remove(int key) {
    int attempt = 0;
    int index = hash(key);
    
    while (is_occupied_[index] && attempt < size_) {
        if (buckets_[index].key == key) {
            is_occupied_[index] = false;
            count_--;
            return;
        }
        attempt++;
        index = collision_resolve(hash(key), attempt);
    }
}

template <typename T>
Pair<T> HashTable<T>::search(int key) {
    int attempt = 0;
    int index = hash(key);
    
    while (is_occupied_[index] && attempt < size_) {
        if (buckets_[index].key == key) {
            return buckets_[index];
        }
        attempt++;
        index = collision_resolve(hash(key), attempt);
    }
    
    return Pair<T>(-1, T());
}

template <typename T>
void HashTable<T>::print() {
    for (int i = 0; i < size_; i++) {
        if (is_occupied_[i]) {
            std::cout << "Index " << i << ": key=" << buckets_[i].key 
                      << ", value=" << buckets_[i].value << std::endl;
        }
    }
}


template <typename T>
HashTable<T>::HashTable() : size_(TABLE_SIZE), count_(0) {
    buckets_ = new Pair<T>[size_];
    is_occupied_ = new bool[size_];
    for (int i = 0; i < size_; i++) {
        is_occupied_[i] = false;
    }
}

template <typename T>
HashTable<T>::~HashTable() {
    delete[] buckets_;
    delete[] is_occupied_;
}


template <typename T>
int HashTable<T>::hash(int key) {
    const double A = 0.6180339887;
    double product = key * A;
    double fractional = product - static_cast<int>(product);
    return static_cast<int>(size_ * fractional);
}

template <typename T>
int HashTable<T>::collision_resolve(int hash, int attempt) {
    return (hash + attempt * attempt) % size_;
}

template <typename T>
void HashTable<T>::resize() {
    int old_size = size_;
    size_ *= 2;
    
    Pair<T>* old_buckets = buckets_;
    bool* old_occupied = is_occupied_;
    
    buckets_ = new Pair<T>[size_];
    is_occupied_ = new bool[size_];
    
    for (int i = 0; i < size_; i++) {
        is_occupied_[i] = false;
    }
    
    count_ = 0;
    for (int i = 0; i < old_size; i++) {
        if (old_occupied[i]) {
            add(old_buckets[i]);
        }
    }
    
    delete[] old_buckets;
    delete[] old_occupied;
}