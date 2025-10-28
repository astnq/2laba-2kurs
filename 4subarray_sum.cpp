#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class SubarraySumFinder {
public:
    vector<vector<int>> findSubarraysWithSum(const vector<int>& nums, int target) {
        vector<vector<int>> result;
        unordered_map<int, vector<int>> prefixSumMap;
        prefixSumMap[0] = {-1};
        
        int currentSum = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            currentSum += nums[i];
            
            int neededSum = currentSum - target;
            if (prefixSumMap.find(neededSum) != prefixSumMap.end()) {
                for (int startIndex : prefixSumMap[neededSum]) {
                    vector<int> subarray;
                    for (int j = startIndex + 1; j <= i; j++) {
                        subarray.push_back(nums[j]);
                    }
                    result.push_back(subarray);
                }
            }
            
            prefixSumMap[currentSum].push_back(i);
        }
        
        return result;
    }
    
    void printSubarrays(const vector<int>& nums, int target) {
        cout << "Массив: [";
        for (size_t i = 0; i < nums.size(); i++) {
            cout << nums[i];
            if (i < nums.size() - 1) cout << ", ";
        }
        cout << "], цель: " << target << endl;
        
        vector<vector<int>> subarrays = findSubarraysWithSum(nums, target);
        
        if (subarrays.empty()) {
            cout << "Подмассивы с суммой " << target << " не найдены." << endl;
        } else {
            cout << "Найдено " << subarrays.size() << " подмассивов:" << endl;
            for (size_t i = 0; i < subarrays.size(); i++) {
                cout << i + 1 << ". [";
                for (size_t j = 0; j < subarrays[i].size(); j++) {
                    cout << subarrays[i][j];
                    if (j < subarrays[i].size() - 1) cout << ", ";
                }
                cout << "]" << endl;
            }
        }
        cout << endl;
    }
};

int main() {
    SubarraySumFinder finder;
    int choice;
    
    do {
        cout << "=== ПОИСК ПОДМАССИВОВ ===" << endl;
        cout << "1. Ввести массив" << endl;
        cout << "2. Выход" << endl;
        cout << "Выберите опцию: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                int n;
                cout << "Введите количество элементов массива: ";
                cin >> n;
                
                // Очищаем буфер после ввода n
                cin.ignore(10000, '\n');
                
                cout << "Введите " << n << " целых чисел через пробел: ";
                string input;
                getline(cin, input);
                
                // Разбираем всю строку
                stringstream ss(input);
                vector<int> userArray;
                int num;
                int count = 0;
                
                while (ss >> num) {
                    userArray.push_back(num);
                    count++;
                }
                
                // Проверяем количество введенных элементов
                if (count != n) {
                    cout << "Ошибка: введено " << count << " элементов вместо " << n << "!" << endl;
                    break;
                }
                
                cout << endl;
                finder.printSubarrays(userArray, 5);
                break;
            }
            
            case 2:
                cout << "Выход из программы..." << endl;
                break;
                
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
        }
        
        if (choice != 2) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 2);
    
    return 0;
}