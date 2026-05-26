//
// Created by verew on 24.05.2026.
//

#include "zadania.h"
#include "string"
#include "iostream"
#include "fstream"
#include "helpers.h"
#include "stack"

int Calc(PNode *node) {
    if (node == nullptr) return 0;

    if (node->left == nullptr && node->right == nullptr) {
        return node->data;
    }

    int left_data = Calc(node->left);
    int right_data = Calc(node->right);

    switch (node->data) {
        case -1:
            return left_data + right_data;
        case -2:
            return left_data - right_data;
        case -3:
            return left_data * right_data;
        case -4:
            return right_data != 0 ? left_data / right_data : 0;
        default:
            return 0;
    }
}

PNode *RemoveAdds(PNode *root) {
    if (root == nullptr) {
        return nullptr;
    }

    root->left = RemoveAdds(root->left);
    root->right = RemoveAdds(root->right);

    if (root->data == -1) {
        if (root->left != nullptr && root->right != nullptr) {
            int result = Calc(root->left) + Calc(root->right);

            delete root->left;
            delete root->right;

            root->data = result;
            root->left = nullptr;
            root->right = nullptr;
        }
    }

    return root;
}

void Zadanie1() {
    using namespace std;

    string filename;
    cout << "Введите имя файла: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }

    string expr;
    getline(file, expr);
    file.close();

    if (expr.empty()) {
        cout << "Файл пуст" << endl;
        return;
    }

    stack<PNode *> st;
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (c >= '0' && c <= '9') {
            PNode *node = new PNode(c - '0');
            st.push(node);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (st.size() < 2) {
                cout << "Некорректное выражение" << endl;
                while (!st.empty()) {
                    delete st.top();
                    st.pop();
                }
                return;
            }

            PNode *right = st.top();
            st.pop();
            PNode *left = st.top();
            st.pop();

            PNode *operator_node = new PNode(0);
            if (c == '+')
                operator_node->data = -1;
            else if (c == '-')
                operator_node->data = -2;
            else if (c == '*')
                operator_node->data = -3;
            else if (c == '/')
                operator_node->data = -4;

            operator_node->left = left;
            operator_node->right = right;

            st.push(operator_node);
        }
    }

    if (st.size() != 1) {
        cout << "Некорректное выражение" << endl;
        while (!st.empty()) {
            delete st.top();
            st.pop();
        }
        return;
    }

    PNode *root = st.top();
    st.pop();

    cout << "Дерево:" << endl;
    PrintTree(root, 0);

    root = RemoveAdds(root);

    cout << "Дерево после удаления операции сложения:" << endl;
    PrintTree(root, 0);

    cout << root << endl;
}

void Zadanie2() {
    using namespace std;


}
