// Лабораторная работа 1:
// 1) создать связный двунаправленный список символов
// 2) ввести данные с клавиатуры
// 3) в конец последовательности добавить все ее символы в обратном порядке
//    пример: 1 2 3 -> 1 2 3 2 1
// 4) вывести результат на экран
#include <iostream>


struct Node {
    char value;
    Node* prev;
    Node* next;

    Node(char value) : value(value), prev(nullptr), next(nullptr) {}
};

class List {
    public:
        void push(char);
        void print();

        Node* getTail();

        List();
        ~List();
    private:
        Node* head_;
        Node* tail_;
};

void List::push(char value) {
    Node* node = new Node(value);
    if (head_ == nullptr) {
        head_ = node;
    }
    node->prev = tail_;
    if (tail_ != nullptr) {
        tail_->next = node;
    }
    tail_ = node;
}

void List::print() {
    Node* current = head_;
    Node* next;
    while (current != nullptr) {
        next = current->next;
        std::cout << current->value << ' ';
        current = next;
    }
    std::cout << std::endl;
}

Node* List::getTail() { return tail_; }

List::List() : head_(nullptr), tail_(nullptr) {}

List::~List() {
    Node* current = head_;
    Node* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}


char getChar() {
    char result = getchar();
    int ch;
    while ((ch = getchar()) != '\n' and ch != EOF);
    return result;
}


int main() {
    // создание списка
    List list = List();
    // инициализация списка
    std::cout << "Enter first character\n>> ";
    char input = getChar();
    while (input != '\n' and input != EOF and input != '.') {
        list.push(input);
        std::cout << std::endl << "Enter next character\n>> ";
        input = getChar();
    }
    // вывод списка
    std::cout << "Original list: ";
    list.print();
    // выполнение задания
    Node* current = list.getTail();
    while (current->prev != nullptr) {
        current = current->prev;
        list.push(current->value);
    }
    // повторный вывод списка
    std::cout << "Result: ";
    list.print();
    
    return 0;
}
