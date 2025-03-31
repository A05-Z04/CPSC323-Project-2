#include "parseTree.hpp"
#include <iostream>
using namespace std;

// Constructor implementation
TreeNode::TreeNode(const std::string& new_var) : item(new_var) {}

// add_child implementation
void TreeNode::add_child(TreeNode* child) {
    children.push_back(child);
}

// printTree implementation
void TreeNode::printTree(int level) {
    for (int i = 0; i < level; ++i) {
        std::cout << " "; // indent for level
    }
    std::cout << item << std::endl;
    for (TreeNode* child : children) {
        child->printTree(level + 1);
    }
}

// Destructor implementation
TreeNode::~TreeNode() {
    for (TreeNode* child : children) {
        delete child;
    }
}
