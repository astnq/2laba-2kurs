#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

// Структура узла дерева
struct NodeT {
    int data;
    NodeT* left;
    NodeT* right;
    
    NodeT(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Класс очереди для обхода
class Queue {
private:
    NodeT** data;
    int front, rear, size, capacity;
    
public:
    Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
        data = new NodeT*[capacity];
    }
    
    ~Queue() {
        delete[] data;
    }
    
    void push(NodeT* value) {
        if (size == capacity) return;
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
    }
    
    NodeT* pop() {
        if (size == 0) return nullptr;
        NodeT* value = data[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }
    
    bool isEmpty() {
        return size == 0;
    }
};

// Класс дерева с обходом змейкой
class BinaryTree {
private:
    NodeT* root;
    
    NodeT* _insert(NodeT* node, int value) {
        if (node == nullptr) return new NodeT(value);
        if (value < node->data) {
            node->left = _insert(node->left, value);
        } else {
            node->right = _insert(node->right, value);
        }
        return node;
    }
    
    // Функция для вертикального вывода дерева
    void _printVertical(NodeT* node, int space = 0) {
        const int COUNT = 5; // Расстояние между уровнями
        
        if (node == nullptr) return;
        
        // Увеличиваем расстояние между уровнями
        space += COUNT;
        
        // Сначала правый потомок
        _printVertical(node->right, space);
        
        // Печатаем текущий узел после пробелов
        cout << endl;
        for (int i = COUNT; i < space; i++) {
            cout << " ";
        }
        cout << node->data << endl;
        
        // Левый потомок
        _printVertical(node->left, space);
    }
    
public:
    BinaryTree() : root(nullptr) {}
    
    void insert(int value) {
        root = _insert(root, value);
    }
    
    // Обход змейкой с использованием очереди
    void snakeTraversal() {
        if (root == nullptr) {
            cout << "Дерево пустое!" << endl;
            return;
        }
        
        Queue q(100);
        vector<vector<int>> levels;
        vector<int> currentLevel;
        
        q.push(root);
        q.push(nullptr); // маркер конца уровня
        
        while (!q.isEmpty()) {
            NodeT* node = q.pop();
            
            if (node == nullptr) {
                if (!currentLevel.empty()) {
                    levels.push_back(currentLevel);
                    currentLevel.clear();
                }
                if (!q.isEmpty()) {
                    q.push(nullptr);
                }
                continue;
            }
            
            currentLevel.push_back(node->data);
            
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        
        cout << "Обход змейкой: ";
        for (size_t i = 0; i < levels.size(); i++) {
            if (i % 2 == 1) {
                reverse(levels[i].begin(), levels[i].end());
            }
            
            for (size_t j = 0; j < levels[i].size(); j++) {
                cout << levels[i][j];
                if (!(i == levels.size() - 1 && j == levels[i].size() - 1)) {
                    cout << " - ";
                }
            }
        }
        cout << endl;
    }
    
    // Вертикальный вывод дерева
    void printTreeVertical() {
        if (root == nullptr) {
            cout << "Дерево пустое!" << endl;
            return;
        }
        cout << "Вертикальное представление дерева:" << endl;
        cout << "(правое поддерево сверху, левое снизу)" << endl;
        _printVertical(root);
        cout << endl;
    }
};

// Меню для тестирования
int main() {
    BinaryTree tree;
    int choice;
    
    do {
        cout << "\n=== ОБХОД ДЕРЕВА ЗМЕЙКОЙ ===" << endl;
        cout << "1. Ввести дерево" << endl;
        cout << "2. Обход змейкой" << endl;
        cout << "3. Вывод дерева (вертикальный)" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите опцию: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                tree = BinaryTree();
                int n;
                cout << "Введите количество элементов: ";
                cin >> n;
                cout << "Введите " << n << " чисел: ";
                for (int i = 0; i < n; i++) {
                    int val;
                    cin >> val;
                    tree.insert(val);
                }
                cout << "Дерево создано!" << endl;
                break;
            }
                
            case 2:
                tree.snakeTraversal();
                break;
                
            case 3:
                tree.printTreeVertical();
                break;
                
            case 4:
                cout << "Выход..." << endl;
                break;
                
            default:
                cout << "Неверный выбор!" << endl;
        }
        
        if (choice != 4) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 4);
    
    return 0;
}