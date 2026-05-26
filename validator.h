//
// Created by verew on 24.05.2026.
//

#ifndef LABA17_VALIDATOR_H
#define LABA17_VALIDATOR_H

#include "iostream"
#include "limits"
#include "string"

class Validator {
public:
    static int GetIntFromConsole(const std::string& title) {
        using namespace std;

        int n;
        while (true) {
            cout << title;
            cin >> n;
            if (cin.fail()) {
                cout << "Неверный ввод" << endl;
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                continue;
            }

            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            if (cin.gcount() > 1) {
                cout << "Неверный ввод" << endl;
                continue;
            }

            return n;
        }
    }
};

#endif //LABA17_VALIDATOR_H