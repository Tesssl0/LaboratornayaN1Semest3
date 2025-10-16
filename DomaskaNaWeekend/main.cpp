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

// ���������� ���� ��� ������ ������
bool silentMode = true;

// ������� ��� ��������, �������� �� ������� ������
bool isReadOnlyCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    // ������ ������ ������ ��� ������
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

    // ����� ��������� ������
    if (argc > 1) {
        CommandLineArgs args = parseArgs(argc, argv);

        if (!args.filename.empty() && !args.query.empty()) {
            // �������� ����� ����� ��� ��������� ������
            silentMode = true;

            // ��������� ������ ����� ����������� �������
            LOAD_ALL_FROM(args.filename);

            // ���������, �� �������� �� ������� EXIT ��� QUIT
            string commandUpper = args.query;
            for (char& c : commandUpper) {
                c = toupper(c);
            }

            size_t firstNonSpace = commandUpper.find_first_not_of(" \t");
            if (firstNonSpace != string::npos) {
                commandUpper = commandUpper.substr(firstNonSpace);
            }

            if (commandUpper.substr(0, 4) == "EXIT" || commandUpper.substr(0, 4) == "QUIT") {
                cout << "������� EXIT/QUIT �� �������������� � ������ ��������� ������" << endl;
                return 0;
            }

            // ��������� ������
            processCommand(args.query);

            // ��������� ��������� ������ ���� ������� �������� ������ (����)
            if (!isReadOnlyCommand(args.query)) {
                SAVE_ALL_TO(args.filename);
                if (!silentMode) {
                    cout << "��������� ��������� � ���� " << args.filename << endl;
                }
            }
            else {
                if (!silentMode) {
                    cout << "������ �� ��������, ���������� �� ���������" << endl;
                }
            }
            return 0;
        }
        else {
            cout << "�������������: " << argv[0] << " --file <filename> --query '<command>'" << endl;
            cout << "������: " << argv[0] << " --file file.data --query 'SPUSH mystack item'" << endl;
            return 1;
        }
    }

    // ������������� ����� 
    string command;
    string currentFilename = "";

    while (true) {
        cout << "> ";
        getline(cin, command);
        if (command.empty()) continue;

        // ��������� ������� LOAD � ������������� ������
        if (command.substr(0, 5) == "LOAD ") {
            string filename = command.substr(5);
            if (!filename.empty()) {
                LOAD_ALL_FROM(filename);
                currentFilename = filename;
            }
            continue;
        }

        // ��������� ������� SAVE � ������������� ������
        if (command.substr(0, 5) == "SAVE ") {
            string filename = command.substr(5);
            if (!filename.empty()) {
                SAVE_ALL_TO(filename);
                currentFilename = filename;
                cout << "������ ��������� � ���� " << filename << endl;
            }
            continue;
        }

        processCommand(command);

        // �������������� � ������������� ������, ���� ���� ������
        if (!currentFilename.empty() && !isReadOnlyCommand(command)) {
            SAVE_ALL_TO(currentFilename);
        }
    }
    return 0;
}