#pragma once
#ifndef WORD_GAME_H 
#define WORD_GAME_H 
#include <iostream> // Для ввода-вывода.
#include <string> // Для работы со строками.
#include <vector> // Для использования векторов.
#include <cctype> // Для работы с символами.
#include <ctime> // Для работы с временем.
#include <cstdlib> // Для использования rand().
#include <fstream> // Для работы с файлами.
#include <algorithm> // Для алгоритмов, таких как сортировка.
using namespace std; // Для написания кода без std::

// Цвета для форматирования текста в консоли.
const string RESET = "\033[0m"; // Сброс цвета.
const string GREEN = "\033[32m"; // Зеленый цвет.
const string ORANGE = "\033[33m"; // Оранжевый цвет.

// Объявление функций, которые будут использоваться в программе.
void displayTable(const vector<string>& guesses, const string& secretWord); // Функция для отображения таблицы с догадками.
void loadDictionary(const string& filename, vector<string>& dictionary); // Функция для загрузки словаря из файла.
bool isValidWord(const string& word, const vector<string>& dictionary); // Функция для проверки, является ли слово словарным.
void capsLock(string& word); // Функция для преобразования строки в заглавные буквы.
bool isSingleWord(const string& word); // Функция для проверки, состоит ли строка из одного слова.
bool isValidChoice(const string& choice); // Функция для проверки правильности выбора режима игры.
string getSecretWord(int choice, const vector<string>& dictionary); // Функция для получения загаданного слова в зависимости от выбора.
void playGame(const string& secretWord, const vector<string>& dictionary); // Функция для запуска игры с заданным загаданным словом и словарем.

#endif
