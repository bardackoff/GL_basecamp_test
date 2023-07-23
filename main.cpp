#include <iostream>
#include <vector>
#include <thread>
#include "file_search.hpp"

int main() {
    std::string searchPath = "/path/to/search"; // Замініть це значення на потрібний шлях для пошуку
    std::string fileName = "example.txt"; // Замініть на ім'я файлу, яке ви хочете знайти

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<std::string> results(numThreads, ""); // Зберігатиме результати пошуку для кожного потоку

    // Розподіліть пошук між декількома потоками
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(findFile, searchPath, fileName, i, numThreads, std::ref(results[i]));
    }

    // Очікуємо завершення всіх потоків
    for (auto& t : threads) {
        t.join();
    }

    // Шукаємо перший ненульовий результат
    for (const auto& result : results) {
        if (!result.empty()) {
            std::cout << "Знайдено файл за шляхом: " << result << std::endl;
            return 0;
        }
    }

    std::cout << "Файл не знайдено." << std::endl;

    return 0;
}
