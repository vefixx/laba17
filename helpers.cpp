//
// Created by verew on 24.05.2026.
//

#include "helpers.h"
#include "fstream"
#include "iostream"


void PrintTree(const PNode* tree, int h) {
    using namespace std;

    if (!tree)
        return;

    PrintTree(tree->right, h + 1);

    cout << string(h * 4, ' ') << tree->data << endl;

    PrintTree(tree->left, h + 1);
}

void AddToTree(PNode*& tree, int data) {
    if (!tree) {
        tree = new PNode(data);
        return;
    }
    if (data < tree->data)
        AddToTree(tree->left, data);
    else
        AddToTree(tree->right, data);
}

PNode * LoadBSTreeFromFile(std::string file_name) {
    using namespace std;

    fstream file(file_name);
    if (!file.is_open()) {
        cout << "Файл " << file_name << " не найден" << endl;
        return nullptr;
    }

    int n;
    if (!(file >> n))
        return nullptr;

    PNode* tree = nullptr;

    for (int i = 0; i < n; i++) {
        int el;
        file >> el;
        AddToTree(tree, el);
    }

    return tree;
}

PNode * GenerateBSTree(int n, int a, int b) {
    using namespace std;

    if (a > b) {
        swap(a,b);
    }

    PNode* tree = nullptr;

    for (int i = 0; i < n; i++) {
        int value = rand() % (b - a + 1) - a;
        AddToTree(tree, value);
    }

    return tree;
}

PNode * CreateBSTreeFromVector(const std::vector<int> &v) {
    using namespace std;

    PNode* tree = nullptr;

    for (int el : v) {
        AddToTree(tree, el);
    }

    return tree;
}

#include "helpers.h"