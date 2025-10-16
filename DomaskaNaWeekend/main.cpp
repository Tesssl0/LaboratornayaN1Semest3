#include <iostream>
#include <string>
#include <locale>
#include <windows.h>

#include <sstream>
#include "command_interface.h"

using namespace std;

struct CommandLineArgs {
    string filename;
    string query;
};

CommandLineArgs parseArgs(int argc, char* argv[]) {
    CommandLineArgs args;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            args.filename = argv[++i];
        }
        else if (arg == "--query" && i + 1 < argc) {
            args.query = argv[++i];
        }
    }
    return args;
}

// Глобальный флаг для тихого режима
bool silentMode = true;

// Функция для проверки, изменяет ли команда данные
bool isReadOnlyCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    // Список команд только для чтения
    const char* readOnlyCommands[] = {
        "SGET", "QGET", "MGET", "FGET", "LGET", "TGET",
        "PRINT", "HELP", "CHECK_TREE"
    };

    const int numCommands = sizeof(readOnlyCommands) / sizeof(readOnlyCommands[0]);

    for (int i = 0; i < numCommands; i++) {
        if (cmd == readOnlyCommands[i]) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Ru");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    initGlobalStructures();

    // Режим командной строки
    if (argc > 1) {
        CommandLineArgs args = parseArgs(argc, argv);

        if (!args.filename.empty() && !args.query.empty()) {
            // Включаем тихий режим для командной строки
            silentMode = true;

            // ЗАГРУЖАЕМ ДАННЫЕ ПЕРЕД ВЫПОЛНЕНИЕМ КОМАНДЫ
            LOAD_ALL_FROM(args.filename);

            // Проверяем, не является ли команда EXIT или QUIT
            string commandUpper = args.query;
            for (char& c : commandUpper) {
                c = toupper(c);
            }

            size_t firstNonSpace = commandUpper.find_first_not_of(" \t");
            if (firstNonSpace != string::npos) {
                commandUpper = commandUpper.substr(firstNonSpace);
            }

            if (commandUpper.substr(0, 4) == "EXIT" || commandUpper.substr(0, 4) == "QUIT") {
                cout << "Команда EXIT/QUIT не поддерживается в режиме командной строки" << endl;
                return 0;
            }

            // Выполняем запрос
            processCommand(args.query);

            // Сохраняем изменения только если команда изменяла данные (тихо)
            if (!isReadOnlyCommand(args.query)) {
                SAVE_ALL_TO(args.filename);
                if (!silentMode) {
                    cout << "Изменения сохранены в файл " << args.filename << endl;
                }
            }
            else {
                if (!silentMode) {
                    cout << "Данные не изменены, сохранение не требуется" << endl;
                }
            }
            return 0;
        }
        else {
            cout << "Использование: " << argv[0] << " --file <filename> --query '<command>'" << endl;
            cout << "Пример: " << argv[0] << " --file file.data --query 'SPUSH mystack item'" << endl;
            return 1;
        }
    }

    // Интерактивный режим 
    string command;
    string currentFilename = "";

    while (true) {
        cout << "> ";
        getline(cin, command);
        if (command.empty()) continue;

        // Обработка команды LOAD в интерактивном режиме
        if (command.substr(0, 5) == "LOAD ") {
            string filename = command.substr(5);
            if (!filename.empty()) {
                LOAD_ALL_FROM(filename);
                currentFilename = filename;
            }
            continue;
        }

        // Обработка команды SAVE в интерактивном режиме
        if (command.substr(0, 5) == "SAVE ") {
            string filename = command.substr(5);
            if (!filename.empty()) {
                SAVE_ALL_TO(filename);
                currentFilename = filename;
                cout << "Данные сохранены в файл " << filename << endl;
            }
            continue;
        }

        processCommand(command);

        // Автосохранение в интерактивном режиме, если файл указан
        if (!currentFilename.empty() && !isReadOnlyCommand(command)) {
            SAVE_ALL_TO(currentFilename);
        }
    }
    return 0;
}