#include "iostream"
#include "windows.h"
#include "zadania.h"
#include "cstdlib"
#include "ctime"
#include "validator.h"

int main() {
    using namespace std;

    srand(time({}));

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n = -1;

    while (n != 0) {
        cout << "1) Удаление операций сложения " << endl;
        cout << "2) Вычисление дерева с переменной " << endl;

        n = Validator::GetIntFromConsole("Введите номер задачи: ");

        switch (n) {
            case 1:
                Zadanie1();
                break;
            case 2:
                Zadanie2();
                break;
            case 0:
                cout << "      /\\_/\\   " << endl;
                cout << "     ( o.o )  " << endl;
                cout << "      > ^ <   " << endl;
                break;
            default:
                cout << "Неверный номер задачи" << endl;
                break;
        }
    }
}