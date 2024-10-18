// Лабораторная работа 5:
// разработать алгоритм, написать и выполнить программу поиска, 
// вставки и удаления в бинарных деревьях, реализующую
//      1) ввод с клавиатуры в массив символьной последовательности
//         I, Q, D, N, T, K, P, R, U, J, L, M, O, B, G, A, C, E, H, F,
//      2) создание из этой последовательности бинарного дерева и
//         вывод его на экран,
//      3) вставку в бинарное дерево вершин S, Z, K и
//         вывод нового дерева на экран,
//      4) удаление из бинарного дерева вершины F и вывод нового дерева на экран.
// Примечание: 1) деревья реализовать в виде динамических списков;
//             2) при печати использовать симметричный обход дерева.
#include <iostream>
#include <vector>


struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char value) : value(value), left(nullptr), right(nullptr) {}
};


class BinarySearchTree {
    public:
        void print();
        bool search(char);
        void insert(char);
        void remove(char);

        BinarySearchTree() : root_(nullptr) {}
        ~BinarySearchTree() { deleteTree(root_); }
    private:
        void print(TreeNode*);
        bool search(TreeNode*, char);
        void insert(TreeNode*&, char);

        TreeNode* findMin(TreeNode*);
        TreeNode* remove(TreeNode*, char);

        void deleteTree(TreeNode*);

        TreeNode* root_;
};


char getChar() {
    char result = getchar();
    int ch;
    while ((ch = getchar()) != '\n' and ch != EOF);
    return result;
}


int main() {
    BinarySearchTree bst;
    std::cout << "Is input manual? ('y' or 'n')\n>> ";
    if (getChar() == 'y') {
        std::cout << "Enter character\n>> ";
        char input = getChar();
        while (input != '.' and input != '\n' and input != EOF) {
            std::cout << std::endl;
            bst.insert(input);
            std::cout << "Enter character\n>> ";
            input = getChar();
        }
    } else {
        std::vector<char> target = {
            'I', 'Q', 'D', 'N', 'T', 'K', 'P', 'R', 'U', 'J',
            'L', 'M', 'O', 'B', 'G', 'A', 'C', 'E', 'H', 'F'
        };
        for (char t : target) {
            bst.insert(t);
        }
    }
    std::cout << std::endl;
    std::cout << "Original tree:" << std::endl;
    bst.print();
    std::cout << std::endl;

    std::vector<char> elementsToInsert = {'S', 'Z', 'K'};
    for (char e : elementsToInsert) {
        bst.insert(e);
    }
    std::cout << "Tree with inserted elements:" << std::endl;
    bst.print();
    std::cout << std::endl;

    bst.remove('F');
    std::cout << "Tree with deleted elements:" << std::endl;
    bst.print();
    std::cout << std::endl;

    return 0;
}


void BinarySearchTree::print() {
    print(root_);
    std::cout << std::endl;
}

void BinarySearchTree::print(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    print(node->left);
    std::cout << node->value << ' ';
    print(node->right);
}


bool BinarySearchTree::search(char value) {
    return search(root_, value);
}

bool BinarySearchTree::search(TreeNode* node, char value) {
    if (node == nullptr) {
        return false;
    }
    if (node->value == value) {
        return true;
    }
    if (value < node->value) {
        return search(node->left, value);
    }
    return search(node->right, value);
}


void BinarySearchTree::insert(char value) {
    insert(root_, value);
}

void BinarySearchTree::insert(TreeNode*& node, char value) {
    if (node == nullptr) {
        node = new TreeNode(value);
    } else if (value < node->value) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}


void BinarySearchTree::remove(char value) {
    root_ = remove(root_, value);
}

TreeNode* BinarySearchTree::findMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* BinarySearchTree::remove(TreeNode* node, char value) {
    if (node == nullptr) {
        return node;
    }
    if (value < node->value) {
        node->left = remove(node->left, value);
    } else if (value > node->value) {
        node->right = remove(node->right, value);
    } else {
        // Узел найден
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        // Узел с двумя дочерними элементами
        TreeNode* temp = findMin(node->right);
        node->value = temp->value;
        node->right = remove(node->right, temp->value);
    }
    return node;
}


void BinarySearchTree::deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
