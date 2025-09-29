#include <iostream>
#include <string>
#include <filesystem>
#include "command_interface.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");

    // ��������� ������� ����������
    cout << "������� ����������: " << filesystem::current_path() << endl;

    initGlobalStructures();

    cout << "=== ��������� ������ �� ����������� ������ ===" << endl;
    cout << "������� HELP ��� ������ ������" << endl;

    // ������ ��������� �������� ��� ������
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





    
