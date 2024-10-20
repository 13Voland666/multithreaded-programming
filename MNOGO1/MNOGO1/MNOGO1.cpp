#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <chrono>
#include <locale>

using namespace std;

// Функция для однопоточного выполнения
void single_threaded_version(const string& file_path) {
    // Начало замера времени
    auto start_time = chrono::high_resolution_clock::now();

    // Чтение данных из файла
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << file_path << endl;
        return;
    }

    vector<string> words;
    string line;

    while (getline(file, line)) {
        words.push_back(line);
    }
    file.close();

    // Проверяем, есть ли слова в файле
    if (words.empty()) {
        cout << "Файл пуст." << endl;
        return;
    }

    // Находим самое длинное слово
    string longest_word;
    for (const auto& word : words) {
        if (word.length() > longest_word.length()) {
            longest_word = word;
        }
    }

    // Подсчет количества слов
    size_t word_count = words.size();

    // Подсчет частоты символов в самом длинном слове
    unordered_map<char, int> letter_frequency;
    for (char letter : longest_word) {
        letter_frequency[letter]++;
    }

    // Конец замера времени
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> execution_time = end_time - start_time;

    // Вывод результатов
    cout << "\nСамое длинное слово: " << longest_word << endl;
    cout << "Количество слов: " << word_count << endl;
    cout << "Частота букв в самом длинном слове:" << endl;
    for (const auto& pair : letter_frequency) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Подсчет и вывод времени выполнения
    cout << "\nВремя выполнения программы (однопоточно): " << execution_time.count() << " секунд" << endl;
}

// Функция для нахождения самого длинного слова
void find_longest_word(const vector<string>& words, string& longest_word) {
    for (const auto& word : words) {
        if (word.length() > longest_word.length()) {
            longest_word = word;
        }
    }
}

// Функция для подсчета частоты символов в самом длинном слове
void count_letter_frequency(const string& longest_word, unordered_map<char, int>& letter_frequency) {
    for (char letter : longest_word) {
        letter_frequency[letter]++;
    }
}

// Функция для многопоточного выполнения
void multi_threaded_version(const string& file_path) {
    // Начало замера времени
    auto start_time = chrono::high_resolution_clock::now();

    // Чтение данных из файла
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << file_path << endl;
        return;
    }

    vector<string> words;
    string line;

    while (getline(file, line)) {
        words.push_back(line);
    }
    file.close();

    // Проверяем, есть ли слова в файле
    if (words.empty()) {
        cout << "Файл пуст." << endl;
        return;
    }

    // Подсчет количества слов
    size_t word_count = words.size();
    string longest_word;
    unordered_map<char, int> letter_frequency;

    // Создание потоков для выполнения разных задач
    thread thread1(find_longest_word, ref(words), ref(longest_word));
    thread1.join();  // Ждем завершения потока

    thread thread2(count_letter_frequency, ref(longest_word), ref(letter_frequency));
    thread2.join();  // Ждем завершения второго потока

    // Конец замера времени
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> execution_time = end_time - start_time;

    // Вывод результатов
    cout << "\nСамое длинное слово: " << longest_word << endl;
    cout << "Количество слов: " << word_count << endl;
    cout << "Частота букв в самом длинном слове:" << endl;
    for (const auto& pair : letter_frequency) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Подсчет и вывод времени выполнения
    cout << "\nВремя выполнения программы (многопоточно): " << execution_time.count() << " секунд" << endl;
}

int main() {
    // Установка локали для корректного отображения символов
    setlocale(LC_ALL, "Russian");

    string file_path = "X:\\Politex\\mnogopotok\\1 laba\\data.txt";
    cout << "Однопоточная версия:" << endl;
    single_threaded_version(file_path);

    cout << "\nМногопоточная версия:" << endl;
    multi_threaded_version(file_path);

    return 0;
}
