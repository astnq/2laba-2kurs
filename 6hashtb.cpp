#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string key;
    cout << "Ввод: ";
    cin >> key;
    
    int chunkSize = 3;
    vector<string> chunks;
    vector<int> chunkValues;
    int n = key.length();
    
    // Разбиваем на части по 3 цифры
    for (int i = 0; i < n; i += chunkSize) {
        string chunk = key.substr(i, chunkSize);
        chunks.push_back(chunk);
        chunkValues.push_back(stoi(chunk));
    }
    
    // Выводим процесс сложения
    cout << "Вывод: ";
    for (size_t i = 0; i < chunks.size(); i++) {
        cout << chunks[i];
        if (i < chunks.size() - 1) cout << "+";
    }
    
    cout << " = ";
    
    int sum = 0;
    for (size_t i = 0; i < chunkValues.size(); i++) {
        sum += chunkValues[i];
    }
    
    cout << sum << endl;
    
    return 0;
}