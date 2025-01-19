#include "word_game.h" // Подключаем заголовочный файл с определениями функций и типов для игры со словами.
#include <cstdlib> // Подключаем библиотеку для rand() и srand().

void displayTable(const vector<string>& guesses, const string& secretWord) { // Функция для отображения таблицы догадок.
    cout << endl << "Таблица догадок: " << endl; 
    int maxGuesses = min(static_cast<int>(guesses.size()), 5); // Определяем максимальное количество догадок для отображения.
    for (int i = 0; i < maxGuesses; ++i) { // Проходим по каждой догадке.
        string guess = guesses[i]; // Сохраняем текущую догадку.
        for (int j = 0; j < 5; ++j) { // Проходим по каждой букве в догадке.
            if (guess[j] == secretWord[j]) { // Если буква на месте:
                cout << GREEN << "[" << guess[j] << "] " << RESET; // Выводим букву зеленым цветом.
            } 
            else if (secretWord.find(guess[j]) != string::npos) { // Если буква есть в слове, но не на месте:
                cout << ORANGE << "[" << guess[j] << "] " << RESET; // Выводим букву оранжевым цветом.
            } 
            else { // Если буква отсутствует в слове:
                cout << "[" << guess[j] << "] "; // Выводим букву без цветового оформления.
            } 
        } 
        cout << endl; // Переходим на новую строку после отображения догадки.
    } 
} 

void loadDictionary(const string& filename, vector<string>& dictionary) { // Функция для загрузки словаря из файла.
    ifstream file(filename); // Открываем файл для чтения.
    string word; // Переменная для хранения текущего слова.
    while (file >> word) { // Читаем слова из файла по одному.
        if (word.length() == 5) { // Проверяем, что слово состоит из 5 букв.
            dictionary.push_back(word); // Добавляем слово в словарь.
        } 
    } 
} 

bool isValidWord(const string& word, const vector<string>& dictionary) { // Функция для проверки существования слова в словаре.
    return std::find(dictionary.begin(), dictionary.end(), word) != dictionary.end(); // Возвращаем true, если слово есть в словаре.
} 

void capsLock(string& word) { // Функция для преобразования слова в CapsLock.
    for (char& c : word) { // Проходим по каждому символу в слове.
        c = toupper(c); // Преобразуем символ в верхний регистр.
    } 
} 

bool isValidChoice(const string& choice) { // Функция для проверки правильности выбора режима игры.
    string alphabet = "1234567890"; // Строка с допустимыми символами.
    for (char c : choice) { // Проходим по каждому символу в выборе.
        if (alphabet.find(c) == string::npos) { // Если символ не найден в строке допустимых символов:
            return false; // Возвращаем false.
        } 
    } 
    return true; // Если все символы допустимы, возвращаем true.
} 

bool isSingleWord(const string& word) { // Функция для проверки, состоит ли строка из одного слова.
    return word.find(' ') == string::npos; // Возвращаем true, если пробелов нет.
} 

string getSecretWord(int choice, const vector<string>& dictionary) { // Функция для получения загаданного слова.
    string secretWord; // Переменная для хранения загаданного слова.
    if (choice == 1) { // Если выбран режим игры с компьютером:
        srand(static_cast<unsigned int>(time(0))); // Инициализируем генератор случайных чисел.
        secretWord = dictionary[rand() % dictionary.size()]; // Выбираем случайное слово из словаря.
        cout << "Компьютер загадал слово! Угадай его" << endl; // Сообщаем пользователю о загаданном слове.
    } 
    if (choice == 2) { // Если выбран режим игры вдвоем:
        cout << "Ваше загаданное слово: "; // Просим игрока загадать слово.
        cin >> secretWord; // Получаем слово от игрока.
        capsLock(secretWord); // Преобразуем его в CapsLock.
        // Проверяем, что слово валидно, состоит из 5 букв и не содержит пробелов.
        while (secretWord.length() != 5 || !isValidWord(secretWord, dictionary) || !isSingleWord(secretWord)) { 
            cout << "Ошибка! Пожалуйста, введите допустимое 5-буквенное слово без пробелов из словаря." << endl; // Сообщаем об ошибке.
            cin >> secretWord; // Запрашиваем ввод снова.
            capsLock(secretWord); // Преобразуем его в верхний регистр.
        } 
        system("cls"); // Очищаем консоль.
    } 
    return secretWord; // Возвращаем загаданное слово.
} 

void playGame(const string& secretWord, const vector<string>& dictionary) { // Функция для запуска игры.
    vector<string> guesses; // Вектор для хранения догадок.
    bool found = false; // Переменная для отслеживания, угадано ли слово.
    int attempts = 5; // Количество попыток для угадывания слова.
    cout << "У вас есть 5 попыток, чтобы угадать слово!" << endl; // Сообщаем игроку о количестве попыток.

    while (attempts > 0 && !found) { // Цикл продолжается, пока есть попытки и слово не угадано.
        string guess; // Переменная для хранения догадки.
        cout << "Введите вашу догадку: "; // Просим догадку у игрока.
        cin >> guess; // Получаем догадку.

        while (guess.length() != 5) { // Проверяем, что догадка состоит из 5 букв.
            cout << "Введите 5 букв" << endl; // Сообщаем об ошибке.
            cin >> guess; // Запрашиваем ввод снова.
        } 

        capsLock(guess); // Преобразуем догадку в CapsLock.

        if (!isValidWord(guess, dictionary)) { // Проверяем, что догадка существует в словаре.
            cout << "Слово не найдено в словаре. Попробуйте другое слово." << endl; // Сообщаем об ошибке.
            continue; // Продолжаем цикл, запрашивая новую догадку.
        } 

        guesses.push_back(guess); // Добавляем догадку в вектор.
        if (guess == secretWord) { // Если догадка равна загаданному слову:
            found = true; // Устанавливаем флаг о том, что слово угадано.
            cout << "Поздравляем! Вы угадали правильное слово!" << endl; 
        } 
        else { // Если догадка неверна:
            attempts--; // Уменьшаем количество оставшихся попыток.
            cout << "Неправильно! Осталось попыток: " << attempts << endl; // Сообщаем количество оставшихся попыток.
        } 

        displayTable(guesses, secretWord); // Обновляем и отображаем таблицу догадок.
    } 

    if (!found) { // Если слово не угадано после всех попыток:
        cout << "Вы исчерпали все попытки. Загаданное слово было: " << secretWord << endl; // Сообщаем загаданное слово.
    } 
}
