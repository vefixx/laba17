//
// Created by verew on 24.05.2026.
//

#include "io.h"
#include "helpers.h"
#include "iostream"
#include "validator.h"

PNode *ChooseTreeCreateMethodAndGetRoot() {
    using namespace std;

    cout << "1) Из консоли" << endl;
    cout << "2) Из файла" << endl;
    cout << "3) Рандомно" << endl;

    int choose = Validator::GetIntFromConsole("Введите способ заполнения дерева: ");

    PNode* tree = nullptr;
    switch (choose) {
        case 1: {
            int n = Validator::GetIntFromConsole("Введите количество элементов: ");

            if (n <= 0) {
                cout << "Некорректный ввод" << endl;
                return nullptr;
            }

            vector<int> v(n);
            for (int i = 0; i < n; i++) {
                int val = Validator::GetIntFromConsole("Введите элемент №" + to_string(i + 1) + ": ");;
                v[i] = val;
            }

            tree = CreateBSTreeFromVector(v);
            break;
        }
        case 2: {
            string file_name;
            cout << "Введите название файла (пр. input.txt): ";
            getline(cin, file_name);

            tree = LoadBSTreeFromFile(file_name);
            break;
        }
        case 3: {
            int n = Validator::GetIntFromConsole("Введите количество элементов: ");

            if (n <= 0) {
                cout << "Некорректный ввод" << endl;
                return nullptr;
            }

            int a = Validator::GetIntFromConsole("Введите начало диапазона (a): ");
            int b = Validator::GetIntFromConsole("Введите конец диапазона (b): ");

            tree = GenerateBSTree(n, a, b);
            break;
        }
        default: {
            cout << "Некорректный ввод" << endl;
            return nullptr;
        }
    }

    if (tree) {
        cout << "Дерево:" << endl;
        PrintTree(tree, 0);
    }

    return tree;
}
