#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <sstream>

using namespace std;

class LFUCache {
private:
    int capacity;
    int minFreq;
    
    // Узел для хранения значения и частоты
    struct Node {
        int value;
        int frequency;
        list<int>::iterator it; // итератор на позицию в списке частот
    };
    
    // key -> {value, frequency, iterator}
    unordered_map<int, Node> cache;
    
    // frequency -> list of keys (в порядке от последнего к первому использованию)
    unordered_map<int, list<int>> freqMap;
    
    void updateFrequency(int key) {
        Node& node = cache[key];
        int oldFreq = node.frequency;
        
        // Удаляем ключ из старого списка частот
        freqMap[oldFreq].erase(node.it);
        
        // Если список стал пустым и это была минимальная частота, обновляем minFreq
        if (freqMap[oldFreq].empty()) {
            freqMap.erase(oldFreq);
            if (oldFreq == minFreq) {
                minFreq++;
            }
        }
        
        // Увеличиваем частоту и добавляем в новый список
        node.frequency++;
        int newFreq = node.frequency;
        freqMap[newFreq].push_front(key);
        node.it = freqMap[newFreq].begin();
    }
    
public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        
        // Обновляем частоту использования
        updateFrequency(key);
        return cache[key].value;
    }
    
    void set(int key, int value) {
        if (capacity <= 0) return;
        
        // Если ключ уже существует
        if (cache.find(key) != cache.end()) {
            cache[key].value = value;
            updateFrequency(key);
            return;
        }
        
        // Если кэш полный, удаляем наименее используемый элемент
        if (cache.size() >= capacity) {
            // Находим ключ для удаления (последний в списке с minFreq)
            int keyToRemove = freqMap[minFreq].back();
            freqMap[minFreq].pop_back();
            
            // Если список стал пустым, удаляем его
            if (freqMap[minFreq].empty()) {
                freqMap.erase(minFreq);
            }
            
            cache.erase(keyToRemove);
        }
        
        // Добавляем новый элемент с частотой 1
        minFreq = 1;
        freqMap[1].push_front(key);
        cache[key] = {value, 1, freqMap[1].begin()};
    }
};

int main() {
    int cap, Q;
    cout << "Введите емкость кэша: ";
    cin >> cap;
    cout << "Введите количество запросов: ";
    cin >> Q;
    cin.ignore(); // очищаем буфер
    
    LFUCache cache(cap);
    
    cout << "Введите запросы (SET x y или GET x):" << endl;
    for (int i = 0; i < Q; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string command;
        ss >> command;
        
        if (command == "SET") {
            int x, y;
            ss >> x >> y;
            cache.set(x, y);
        } else if (command == "GET") {
            int x;
            ss >> x;
            int result = cache.get(x);
            cout << result << " ";
        }
    }
    cout << endl;
    
    return 0;
}