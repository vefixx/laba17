//
// Created by verew on 24.05.2026.
//

#ifndef LABA17_HELPERS_H
#define LABA17_HELPERS_H
#include "tree.h"
#include "vector"
#include "string"

void PrintTree(const PNode* tree, int h);
void AddToTree(PNode*& tree, int data);

PNode* LoadBSTreeFromFile(std::string file_name);
PNode* GenerateBSTree(int n, int a, int b);
PNode* CreateBSTreeFromVector(const std::vector<int>& v);

#endif //LABA17_HELPERS_H