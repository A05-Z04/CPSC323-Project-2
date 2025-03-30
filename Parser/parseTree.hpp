#ifndef PARSE_TREE_HPP
#define PARSE_TREE_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TreeNode
{
    public:
        std::string item;
        std::vector<TreeNode*> children;

        TreeNode(const std::string& new_var);
        void add_child(TreeNode* child);
        ~TreeNode();
};

#endif 
