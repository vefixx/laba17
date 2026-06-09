//
// Created by verew on 24.05.2026.
//

#include "zadania.h"
#include "string"
#include "iostream"
#include "fstream"
#include "helpers.h"
#include "stack"
#include "cctype"
#include "cmath"
#include "algorithm"

using namespace std;

int GetPriority(char op) {
    switch (op) {
        case '^':
            return 4;
        case '%':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

bool IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

void InfixToPostfix(const string &infix, string &postfix) {
    stack<char> st;
    postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' ') {
            continue;
        }

        if (isdigit(c) || c == 'x') {
            postfix += c;
            postfix += ' ';
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            if (!st.empty()) {
                st.pop();
            }
        }
        else if (IsOperator(c)) {
            while (!st.empty() && st.top() != '(' &&
                   GetPriority(c) <= GetPriority(st.top())) {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        postfix += ' ';
        st.pop();
    }
}

int ParseNumber(const string &str, int &pos) {
    int num = 0;
    while (pos < str.length() && isdigit(str[pos])) {
        num = num * 10 + (str[pos] - '0');
        pos++;
    }
    return num;
}

PNode *BuildTreeFromPostfix(const string &postfix) {
    stack<PNode *> st;
    int i = 0;

    while (i < postfix.length()) {
        if (postfix[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(postfix[i]) || postfix[i] == 'x') {
            if (postfix[i] == 'x') {
                PNode *node = new PNode(-100);
                st.push(node);
                i++;
            } else {
                int num = ParseNumber(postfix, i);
                PNode *node = new PNode(num);
                st.push(node);
            }
        }
        else if (IsOperator(postfix[i])) {
            if (st.size() < 2) {
                return nullptr;
            }

            PNode *right = st.top();
            st.pop();
            PNode *left = st.top();
            st.pop();

            PNode *operator_node = new PNode(0);
            switch (postfix[i]) {
                case '+': operator_node->data = -1;
                    break;
                case '-': operator_node->data = -2;
                    break;
                case '*': operator_node->data = -3;
                    break;
                case '/': operator_node->data = -4;
                    break;
                case '%': operator_node->data = -5;
                    break;
                case '^': operator_node->data = -6;
                    break;
            }

            operator_node->left = left;
            operator_node->right = right;
            st.push(operator_node);
            i++;
        } else {
            i++;
        }
    }

    if (st.empty()) {
        return nullptr;
    }

    return st.top();
}

int EvaluateTree(PNode *node, int xValue) {
    if (node == nullptr) {
        return 0;
    }

    if (node->left == nullptr && node->right == nullptr) {
        if (node->data == -100) {
            return xValue;
        }
        return node->data;
    }

    int leftVal = EvaluateTree(node->left, xValue);
    int rightVal = EvaluateTree(node->right, xValue);

    switch (node->data) {
        case -1:
            return leftVal + rightVal;
        case -2:
            return leftVal - rightVal;
        case -3:
            return leftVal * rightVal;
        case -4:
            return rightVal != 0 ? leftVal / rightVal : 0;
        case -5:
            return rightVal != 0 ? leftVal % rightVal : 0;
        case -6:
        {
            int result = 1;
            for (int i = 0; i < rightVal; i++) {
                result *= leftVal;
            }
            return result;
        }
        default:
            return 0;
    }
}

bool IsVariableX(PNode *node) {
    return node != nullptr && node->data == -100 &&
           node->left == nullptr && node->right == nullptr;
}

PNode *TransformTree(PNode *node) {
    if (node == nullptr) {
        return nullptr;
    }

    node->left = TransformTree(node->left);
    node->right = TransformTree(node->right);

    if (node->data == -6) {
        if (IsVariableX(node->left)) {
            PNode *exponent = node->right;

            PNode *multNode = new PNode(-3);
            multNode->left = exponent;
            multNode->right = new PNode(-100);

            delete node->left;
            delete node;

            return multNode;
        }
    }

    return node;
}

void PrintTreeToFile(PNode *node, ofstream &file, int depth) {
    if (node == nullptr) {
        return;
    }

    PrintTreeToFile(node->right, file, depth + 1);

    file << string(depth * 4, ' ');

    if (node->data == -100) {
        file << "x" << endl;
    } else if (node->data == -1) {
        file << "+" << endl;
    } else if (node->data == -2) {
        file << "-" << endl;
    } else if (node->data == -3) {
        file << "*" << endl;
    } else if (node->data == -4) {
        file << "/" << endl;
    } else if (node->data == -5) {
        file << "%" << endl;
    } else if (node->data == -6) {
        file << "^" << endl;
    } else {
        file << node->data << endl;
    }

    PrintTreeToFile(node->left, file, depth + 1);
}

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

    string filename1, filename2;

    cout << "Введите имя входного файла: ";
    getline(cin, filename1);

    ifstream file_in(filename1);
    if (!file_in.is_open()) {
        cout << "Не удалось открыть файл " << filename1 << endl;
        return;
    }

    string expression;
    getline(file_in, expression);
    file_in.close();

    if (expression.empty()) {
        cout << "Файл пуст" << endl;
        return;
    }

    int x;
    cout << "Введите значение переменной x: ";
    cin >> x;
    cin.ignore();

    string postfix;
    InfixToPostfix(expression, postfix);

    PNode *root = BuildTreeFromPostfix(postfix);
    if (root == nullptr) {
        cout << "Ошибка построения дерева" << endl;
        return;
    }

    cout << "Построенное дерево:" << endl;
    PrintTree(root, 0);

    int result = EvaluateTree(root, x);

    cout << "Введите имя выходного файла: ";
    getline(cin, filename2);

    ofstream file_out(filename2);
    if (!file_out.is_open()) {
        cout << "Не удалось создать файл " << filename2 << endl;
        return;
    }

    file_out << "Результат вычисления: " << result << endl;
    file_out << endl;

    root = TransformTree(root);

    file_out << "Преобразованное дерево:" << endl;
    PrintTreeToFile(root, file_out, 0);

    file_out.close();

    cout << "Результат вычисления: " << result << endl;
    cout << "Преобразованное дерево записано в файл " << filename2 << endl;

    cout << endl << "Преобразованное дерево:" << endl;
    PrintTree(root, 0);
}