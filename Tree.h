#pragma once

#include "TreeNode.h"

class Tree {
    TreeNode *root;

public:
    explicit Tree(TreeNode *root) : root(root) {}

    void optimize();

    void evaluate();
};
