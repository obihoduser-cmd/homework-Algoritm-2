
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

template <typename T>
class Cache {
private:
    vector<pair<int, T>> data;

public:
    // Добавление или изменение значения
    void put(int key, T value) {
        for (auto& item : data) {
            if (item.first == key) {
                item.second = value;
                return;
            }
        }

        data.push_back({key, value});
    }

    // Получение значения
    bool get(int key, T& result) const {
        for (const auto& item : data) {
            if (item.first == key) {
                result = item.second;
                return true;
            }
        }

        return false;
    }

    // Проверка наличия ключа
    bool contains(int key) const {
        for (const auto& item : data) {
            if (item.first == key) {
                return true;
            }
        }

        return false;
    }

    // Очистка кэша
    void clear() {
        data.clear();
    }

    // Вывод всех элементов
    void print() const {
        for (const auto& item : data) {
            cout << "Ключ: " << item.first
                 << ", значение: " << item.second << endl;
        }
    }
};

// Измерение времени выполнения
template <typename Func>
long long measureTime(Func func) {
    auto start = high_resolution_clock::now();

    func();

    auto end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "ru");

    Cache<int> cache;

    // Добавление элементов
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    cout << "Содержимое кэша:" << endl;
    cache.print();

    // Получение значения
    int result;

    if (cache.get(2, result)) {
        cout << "\nЗначение по ключу 2: "
             << result << endl;
    } else {
        cout << "Ключ не найден" << endl;
    }

    // Проверка наличия ключа
    cout << "\nЕсть ключ 3? "
         << (cache.contains(3) ? "Да" : "Нет") << endl;

    // Измерение времени выполнения операций
    const int N = 5000;

    long long putTime = measureTime([&]() {
        for (int i = 0; i < N; i++) {
            cache.put(i + 100, i);
        }
    });

    long long getTime = measureTime([&]() {
        for (int i = 0; i < N; i++) {
            cache.get(i + 100, result);
        }
    });

    long long containsTime = measureTime([&]() {
        for (int i = 0; i < N; i++) {
            cache.contains(i + 100);
        }
    });

    long long clearTime = measureTime([&]() {
        cache.clear();
    });

    cout << "\nВремя выполнения операций (" << N
         << " вызовов):" << endl;

    cout << "put: " << putTime << " мкс" << endl;
    cout << "get: " << getTime << " мкс" << endl;
    cout << "contains: " << containsTime << " мкс" << endl;
    cout << "clear: " << clearTime << " мкс" << endl;

    return 0;
}
