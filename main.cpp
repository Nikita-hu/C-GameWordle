#include "word_game.h" // Подключаем заголовочный файл, содержащий определения функций и типов для игры со словами.
int main() {
    setlocale(LC_ALL, "Russian"); // Устанавливаем локализацию для поддержки русского языка.
    string number; // Объявляем строковую переменную для хранения выбора режима игры.
    vector<string> dictionary; // Объявляем вектор строк для хранения словаря.
    loadDictionary("dictionary.txt", dictionary); // Загружаем слова из файла "dictionary.txt" в вектор dictionary.
    // Выводим меню выбора режима игры.
    cout << "Выберите режим:\n1. Игра с компьютером\n2. Игра вдвоем\n";
    cin >> number;  // Считываем ввод пользователя как строку.
    // Проверяем ввод на корректность: должно быть 1 или 2.
    while (!isValidChoice(number) || (number != "1" && number != "2")) {
        cout << "Ошибка! Пожалуйста, введите 1 или 2." << endl; // Выводим сообщение об ошибке.
        cin >> number; // Запрашиваем ввод снова.
    }
    // Преобразуем строку с выбором в целое число.
    int choice = stoi(number);
    string secretWord = getSecretWord(choice, dictionary); // Получаем загаданное слово в зависимости от выбора режима игры.
    playGame(secretWord, dictionary); // Запускаем игру с полученным загаданным словом и словарем.
    return 0;
}
