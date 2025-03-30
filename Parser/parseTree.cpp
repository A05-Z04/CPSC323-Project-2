#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class for containing the parse tree
class TreeNode
{
    public:
        std::string item; // item held by the node
        std::vector<TreeNode*> children; // vector for containg the child(ren) of a node

        //Constructor
        TreeNode(const std::string& new_var) : item(new_var) {} 

        void add_child(TreeNode* child)
        {
            children.push_back(child);
        }

        //print function for the parse tree
        void printTree(int level = 0)
        {
            for(int i = 0; i < level; ++i)
            {
                std::cout << " "; //indent for level
            }
            std::cout << item << std::endl;

            //print each child node with another indent
            for(TreeNode* child : children)
            {
                child->printTree(level + 1);
            }
        }

        //destructor
        ~TreeNode()
        {
            for(TreeNode* child : children)
            {
                delete child;
            }
        }

};

