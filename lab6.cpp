// Ћабораторна€ работа 6:
// –азработать алгоритм, написать и выполнить программу, 
// осуществл€ющую поразр€дную сортировку элементов динамического списка ј, 
// состо€щего из 50 элементов. Ёлементами €вл€ютс€ даты текущего столети€,
// представленные в виде одной строки, в которой день и год
// записаны цифрами (день - двум€, год - четырьм€), а мес€ц - словом. 
// Ёлементы можно вводить с клавиатуры, читать из файла или
// генерировать случайным образом по желанию разработчика.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


const int N = 50;
const int MIN_DATE_VALUES[] = {1, 1, 2001};
const int MAX_DATE_VALUES[] = {31, 12, 2100};


struct Date {
    int day;
    int month;
    int year;
    int key[3];

    void print(char);

    Date(int dd, int mm, int yyyy) : day(dd), month(mm), year(yyyy) {
        key[0] = day;
        key[1] = month;
        key[2] = year;
    }
};

void Date::print(char endl = '\n') {
    static const std::string months[] {
        "€нвар€", "феврал€", "марта", "апрел€",
        "ма€", "июн€", "июл€", "августа",
        "сент€бр€", "окт€бр€", "но€бр€", "декабр€"
    };
    if (day < 10) {
        std::cout << '0';
    }
    std::cout << day << ' '
              << months[month - 1] << ' '
              << year << endl;
}


int getDays(int month) {
    // количество дней в мес€це без учета високосности
    return 28 + ((0x3bbeecc >> (month * 2)) & 3);
}

bool isCorrect(int dd, int mm, int yyyy) {
    if (yyyy < MIN_DATE_VALUES[2] or yyyy > MAX_DATE_VALUES[2]) {
        return false;
    }
    if (mm < 1 or mm > 12) {
        return false;
    }
    int days = getDays(mm) +
        // поправка на високосность
        (int) (yyyy % 400 == 0 or (yyyy % 100 != 0 and yyyy % 4 == 0));
    if (dd < 1 or dd > days) {
        return false;
    }
    return true;
}

Date random() {
    int day, month, year;
    day = month = year = -1;
    while (!isCorrect(day, month, year)) {
        day = std::rand() % MAX_DATE_VALUES[0] + 1;
        month = std::rand() % MAX_DATE_VALUES[1] + 1;
        year = std::rand() % MAX_DATE_VALUES[2] + 1;
    }
    return Date(day, month, year);
}


struct Node {
    Date date;
    Node* prev;
    Node* next;

    Node(Date d) : date(d), prev(nullptr), next(nullptr) {}
};

class List {
    public:
        void push(Date);
        void concat(List&);
        Date popFirst();

        void print();
        void radixSort();

        List();
        ~List();
    private:
        Node* head_;
        Node* tail_;
};

void List::push(Date date) {
    Node* node = new Node(date);
    if (head_ == nullptr) {
        head_ = node;
    }
    node->prev = tail_;
    if (tail_ != nullptr) {
        tail_->next = node;
    }
    tail_ = node;
}

void List::concat(List& other) {
    if (!other.head_) return;
    if (!head_) {
        head_ = other.head_;
        tail_ = other.tail_;
    } else {
        tail_->next = other.head_;
        other.head_->prev = tail_;
        tail_ = other.tail_;
    }
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

Date List::popFirst() {
    if (head_ == nullptr) {
        throw std::out_of_range("pop from empty list");
    }
    Node* node = head_;
    head_ = head_->next;
    if (head_ != nullptr) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }
    Date date = node->date;
    delete node;
    return date;
}

void List::print() {
    Node* current = head_;
    Node* next;
    while (current != nullptr) {
        next = current->next;
        current->date.print();
        current = next;
    }
}

void List::radixSort() {
    for (int i = 0; i < 3; i++) {
        auto length = MAX_DATE_VALUES[i] - MIN_DATE_VALUES[i] + 1;
        List digits[length];
        while (tail_ != nullptr) {
            Date d = this->popFirst();
            digits[(d.key[i] - 1) % length].push(d);
        }
        for (int j = 0; j < length; j++) {
            this->concat(digits[j]);
        }
    }
}

List::List() : head_(nullptr), tail_(nullptr) {}

List::~List() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::srand(std::time(nullptr));
    
    List dates = List();
    for (int i = 0; i < N; i++) {
        dates.push(random());
    }
    std::cout << "Original list:" << std::endl;
    dates.print();
    std::cout << std::endl;

    dates.radixSort();
    std::cout << "Sorted list:" << std::endl;
    dates.print();

    return 0;
}
