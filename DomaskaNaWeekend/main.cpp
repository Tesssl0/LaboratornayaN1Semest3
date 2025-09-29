#include <iostream>
#include <string>
#include <filesystem>
#include "command_interface.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");

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





    
