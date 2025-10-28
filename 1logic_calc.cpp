#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
using namespace std;

// Твой стек
class Stack {
private:
    string* data;
    int head;
    int capacity;  

public:
    Stack(size_t size) : capacity(size), head(-1) { 
        data = new string[capacity];
    }

    Stack() : capacity(30), head(-1) { 
        data = new string[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(string value) { 
        if (head == capacity - 1) { 
            throw overflow_error("Stack is full");
        }
        data[++head] = value;
    }

    string pop() { 
        if (head == -1) { 
            throw underflow_error("Stack is empty");
        }
        return data[head--];
    }

    string peek() { 
        if (head == -1) { 
            throw underflow_error("Stack is empty");
        } 
        return data[head];
    }

    bool isEmpty() {  
        return head == -1;
    }

    size_t size() { 
        return head + 1;
    }
};

// Калькулятор логических выражений
class LogicCalculator {
private:
    Stack values;
    Stack operators;
    
    int getPriority(char op) {
        if (op == '!') return 3;
        if (op == '&') return 2;
        if (op == '|' || op == '^') return 1;
        return 0;
    }
    
    void executeOperator(char op) {
        if (op == '!') {
            int a = stoi(values.pop());
            values.push(to_string(!a));
        } else {
            int b = stoi(values.pop());
            int a = stoi(values.pop());
            
            switch(op) {
                case '&': values.push(to_string(a && b)); break;
                case '|': values.push(to_string(a || b)); break;
                case '^': values.push(to_string(a != b)); break;
            }
        }
    }
    
public:
    int evaluate(const string& expression) {
        while (!values.isEmpty()) values.pop();
        while (!operators.isEmpty()) operators.pop();
        
        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];
            
            if (c == ' ') continue;
            
            if (isdigit(c)) {
                values.push(string(1, c));
            }
            else if (c == '(') {
                operators.push(string(1, c));
            }
            else if (c == ')') {
                while (!operators.isEmpty() && operators.peek() != "(") {
                    executeOperator(operators.pop()[0]);
                }
                if (!operators.isEmpty()) {
                    operators.pop();
                }
            }
            else if (c == '!' || c == '&' || c == '|' || c == '^') {
                if (c == '!' && (i == 0 || expression[i-1] == '(' || 
                                getPriority(expression[i-1]) > 0)) {
                    operators.push(string(1, c));
                    continue;
                }
                
                while (!operators.isEmpty() && 
                       getPriority(operators.peek()[0]) >= getPriority(c)) {
                    executeOperator(operators.pop()[0]);
                }
                operators.push(string(1, c));
            }
        }
        
        while (!operators.isEmpty()) {
            executeOperator(operators.pop()[0]);
        }
        
        if (values.isEmpty()) {
            throw runtime_error("Invalid expression");
        }
        
        return stoi(values.pop());
    }
};

// Тестирование
int main() {
    LogicCalculator calc;
    
    // Тестовые выражения
    string expressions[] = {
        "1&0",      // 0
        "1|0",      // 1  
        "!1",       // 0
        "1^0",      // 1
        "(1|0)&1",  // 1
        "1&0|1",    // 1
        "!0&1",     // 1
        "1^1^1",    // 1
        "(1|0)&(0|1)" // 1
    };
    
    cout << "Тестирование логического калькулятора:\n";
    for (const string& expr : expressions) {
        try {
            int result = calc.evaluate(expr);
            cout << expr << " = " << result << endl;
        } catch (const exception& e) {
            cout << expr << " -> Ошибка: " << e.what() << endl;
        }
    }
    
    // Интерактивный режим
    cout << "\nИнтерактивный режим (для выхода введите 'exit'):\n";
    string input;
    while (true) {
        cout << "Введите выражение: ";
        getline(cin, input);
        
        if (input == "exit") break;
        
        try {
            int result = calc.evaluate(input);
            cout << "Результат: " << result << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    
    return 0;
}