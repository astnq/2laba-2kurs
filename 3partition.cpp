#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

void findMinDifferencePartition(const vector<int>& nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    int n = nums.size();
    
    vector<bool> dp(totalSum + 1, false);
    dp[0] = true;
    vector<int> parent(totalSum + 1, -1);
    
    for (int num : nums) {
        for (int j = totalSum; j >= num; j--) {
            if (dp[j - num] && !dp[j]) {
                dp[j] = true;
                parent[j] = num;
            }
        }
    }
    
    int target = totalSum / 2;
    int bestSum = 0;
    for (int j = target; j >= 0; j--) {
        if (dp[j]) {
            bestSum = j;
            break;
        }
    }
    
    vector<int> subset1;
    int currentSum = bestSum;
    while (currentSum > 0) {
        int num = parent[currentSum];
        subset1.push_back(num);
        currentSum -= num;
    }
    
    vector<int> subset2;
    vector<bool> used(n, false);
    
    for (int num : subset1) {
        auto it = find(nums.begin(), nums.end(), num);
        if (it != nums.end()) {
            int index = distance(nums.begin(), it);
            used[index] = true;
            while ((it = find(it + 1, nums.end(), num)) != nums.end()) {
                index = distance(nums.begin(), it);
                used[index] = true;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            subset2.push_back(nums[i]);
        }
    }
    
    cout << "Подмножество 1: {";
    for (size_t i = 0; i < subset1.size(); i++) {
        cout << subset1[i];
        if (i < subset1.size() - 1) cout << ", ";
    }
    cout << "}, сумма = " << accumulate(subset1.begin(), subset1.end(), 0) << endl;
    
    cout << "Подмножество 2: {";
    for (size_t i = 0; i < subset2.size(); i++) {
        cout << subset2[i];
        if (i < subset2.size() - 1) cout << ", ";
    }
    cout << "}, сумма = " << accumulate(subset2.begin(), subset2.end(), 0) << endl;
    
    int diff = abs(accumulate(subset1.begin(), subset1.end(), 0) - 
                   accumulate(subset2.begin(), subset2.end(), 0));
    cout << "Разница сумм: " << diff << endl << endl;
}

int main() {
    int choice;
    
    do {
        cout << "=== МЕНЮ РАЗБИЕНИЯ МНОЖЕСТВА ===" << endl;
        cout << "1. Тестовые примеры" << endl;
        cout << "2. Ввести своё множество" << endl;
        cout << "3. Выход" << endl;
        cout << "Выберите опцию: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                vector<vector<int>> testCases = {
                    {5, 8, 1, 14, 7},
                    {1, 2, 3, 4, 5},
                    {10, 20, 30, 40},
                    {1, 3, 5, 7, 9},
                    {2, 4, 6, 8, 10}
                };
                
                for (size_t i = 0; i < testCases.size(); i++) {
                    cout << "--- Пример " << i + 1 << " ---" << endl;
                    findMinDifferencePartition(testCases[i]);
                }
                break;
            }
            
            case 2: {
                int n;
                cout << "Введите количество элементов: ";
                cin >> n;
                
                if (n <= 0) {
                    cout << "Ошибка: количество элементов должно быть положительным!" << endl;
                    break;
                }
                
                vector<int> userNums(n);
                cout << "Введите " << n << " натуральных чисел: ";
                for (int i = 0; i < n; i++) {
                    cin >> userNums[i];
                    if (userNums[i] <= 0) {
                        cout << "Ошибка: числа должны быть натуральными!" << endl;
                        return 1;
                    }
                }
                
                cout << endl;
                findMinDifferencePartition(userNums);
                break;
            }
            
            case 3:
                cout << "Выход из программы..." << endl;
                break;
                
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
        
        if (choice != 3) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 3);
    
    return 0;
}