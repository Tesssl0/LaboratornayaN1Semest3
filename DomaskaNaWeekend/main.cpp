#include <iostream>
#include <string>
#include <filesystem>
#include <locale>
#include "command_interface.h"

using namespace std;

int main() {
    // Установка локали для корректного отображения кириллицы
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ios_base::sync_with_stdio(false);
    wcin.imbue(locale("ru_RU.UTF-8"));
    wcout.imbue(locale("ru_RU.UTF-8"));

    // Проверяем текущую директорию
    cout << "Текущая директория: " << filesystem::current_path() << endl;

    initGlobalStructures();

    cout << "=== ИНТЕРФЕЙС РАБОТЫ СО СТРУКТУРАМИ ДАННЫХ ===" << endl;
    cout << "Введите HELP для списка команд" << endl;

    // Только начальная загрузка при старте
    LOAD_ALL();

    string command;
    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command.empty()) continue;

        processCommand(command);
    }

    return 0;
}


    
