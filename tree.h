//
// Created by verew on 24.05.2026.
//

#ifndef LABA17_TREE_H
#define LABA17_TREE_H

class PNode {
public:
    int data;
    PNode* left;
    PNode* right;

    PNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

#endif //LABA17_TREE_H