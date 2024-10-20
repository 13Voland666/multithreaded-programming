import time
import threading

# Функция для однопоточного выполнения
def single_threaded_version(file_path):
    # Начало замера времени
    start_time = time.time()

    # Чтение данных из файла с явной кодировкой cp1251
    with open(file_path, 'r', encoding='cp1251') as file:
        words = [line.strip() for line in file]

    # Находим самое длинное слово
    longest_word = ""
    for word in words:
        if len(word) > len(longest_word):
            longest_word = word

    # Подсчет количества слов
    word_count = len(words)

    # Подсчет частоты символов в самом длинном слове
    letter_frequency = {}
    for letter in longest_word:
        if letter in letter_frequency:
            letter_frequency[letter] += 1
        else:
            letter_frequency[letter] = 1

    # Конец замера времени
    end_time = time.time()

    # Вывод результатов
    print(f"Самое длинное слово: {longest_word}")
    print(f"Количество слов: {word_count}")
    print("Частота букв в самом длинном слове:")
    for letter, freq in letter_frequency.items():
        print(f"{letter}: {freq}")

    # Подсчет и вывод времени выполнения
    execution_time = end_time - start_time
    print(f"\nВремя выполнения программы (однопоточно): {execution_time:.6f} секунд")


# Функция для многопоточного выполнения
def multi_threaded_version(file_path):
    # Функция для нахождения самого длинного слова
    def find_longest_word(words, result):
        longest_word = ""
        for word in words:
            if len(word) > len(longest_word):
                longest_word = word
        result["longest_word"] = longest_word

    # Функция для подсчета частоты символов в самом длинном слове
    def count_letter_frequency(longest_word, result):
        letter_frequency = {}
        for letter in longest_word:
            if letter in letter_frequency:
                letter_frequency[letter] += 1
            else:
                letter_frequency[letter] = 1
        result["letter_frequency"] = letter_frequency

    # Начало замера времени
    start_time = time.time()

    # Чтение данных из файла с явной кодировкой cp1251
    with open(file_path, 'r', encoding='cp1251') as file:
        words = [line.strip() for line in file]

    # Подсчет количества слов
    word_count = len(words)

    # Словарь для хранения результатов из потоков
    result = {}

    # Создание потоков для выполнения разных задач
    thread1 = threading.Thread(target=find_longest_word, args=(words, result))
    thread1.start()

    # Ждем завершения потока, так как второй поток зависит от результата первого
    thread1.join()

    # Запускаем поток для подсчета частоты символов после того, как у нас есть самое длинное слово
    thread2 = threading.Thread(target=count_letter_frequency, args=(result["longest_word"], result))
    thread2.start()

    # Ждем завершения второго потока
    thread2.join()

    # Конец замера времени
    end_time = time.time()

    # Вывод результатов
    print(f"Самое длинное слово: {result['longest_word']}")
    print(f"Количество слов: {word_count}")
    print("Частота букв в самом длинном слове:")
    for letter, freq in result['letter_frequency'].items():
        print(f"{letter}: {freq}")

    # Подсчет и вывод времени выполнения
    execution_time = end_time - start_time
    print(f"\nВремя выполнения программы (многопоточно): {execution_time:.6f} секунд")


# Вызов функций
file_path = 'data.txt'
print("Однопоточная версия:")
single_threaded_version(file_path)

print("\nМногопоточная версия:")
multi_threaded_version(file_path)
