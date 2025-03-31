#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "parseTree.hpp"  

// Tokenizing function
std::vector<std::string> tokenize(const std::string &new_line) {
    std::vector<std::string> new_tokens;
    size_t new_i = 0;
    while (new_i < new_line.size()) {
        if (std::isspace(new_line[new_i])) {
            new_i++;
            continue;
        }
        else if (std::isalpha(new_line[new_i])) {
            std::string idStr;
            while (new_i < new_line.size() && std::isalpha(new_line[new_i])) {
                idStr.push_back(new_line[new_i]);
                new_i++;
            }
            new_tokens.push_back("id");
        } else if (new_line[new_i] == '+' || new_line[new_i] == '-' ||
                 new_line[new_i] == '*' || new_line[new_i] == '/' ||
                 new_line[new_i] == '(' || new_line[new_i] == ')') {
            new_tokens.push_back(std::string(1, new_line[new_i]));
            new_i++;
        }
        else {
            new_i++;
        }
    }
    new_tokens.push_back("$");
    return new_tokens;
}
// Table as stated in instructions
std::map<std::pair<int, std::string>, std::string> buildParsingTable() {
    std::map<std::pair<int, std::string>, std::string> new_table;
    // State 0
    new_table[{0, "id"}] = "S5";
    new_table[{0, "("}]  = "S4";
    new_table[{0, "E"}]  = "1";
    new_table[{0, "T"}]  = "2";
    new_table[{0, "F"}]  = "3";
    // State 1
    new_table[{1, "+"}] = "S6";
    new_table[{1, "-"}] = "S7";
    new_table[{1, "$"}] = "Acc";
    // State 2
    new_table[{2, "+"}] = "R3";
    new_table[{2, "-"}] = "R3";
    new_table[{2, "*"}] = "S8";
    new_table[{2, "/"}] = "S9";
    new_table[{2, ")"}] = "R3";
    new_table[{2, "$"}] = "R3";
    // State 3
    new_table[{3, "+"}] = "R6";
    new_table[{3, "-"}] = "R6";
    new_table[{3, "*"}] = "R6";
    new_table[{3, "/"}] = "R6";
    new_table[{3, ")"}] = "R6";
    new_table[{3, "$"}] = "R6";
    // State 4
    new_table[{4, "id"}] = "S5";
    new_table[{4, "("}]  = "S4";
    new_table[{4, "E"}]  = "10";
    new_table[{4, "T"}]  = "2";
    new_table[{4, "F"}]  = "3";
    // State 5
    new_table[{5, "+"}] = "R8";
    new_table[{5, "-"}] = "R8";
    new_table[{5, "*"}] = "R8";
    new_table[{5, "/"}] = "R8";
    new_table[{5, ")"}] = "R8";
    new_table[{5, "$"}] = "R8";
    // State 6
    new_table[{6, "id"}] = "S5";
    new_table[{6, "("}]  = "S4";
    new_table[{6, "T"}]  = "11";
    new_table[{6, "F"}]  = "3";
    // State 7
    new_table[{7, "id"}] = "S5";
    new_table[{7, "("}]  = "S4";
    new_table[{7, "T"}]  = "12";
    new_table[{7, "F"}]  = "3";
    // State 8
    new_table[{8, "id"}] = "S5";
    new_table[{8, "("}]  = "S4";
    new_table[{8, "F"}]  = "13";
    // State 9
    new_table[{9, "id"}] = "S5";
    new_table[{9, "("}]  = "S4";
    new_table[{9, "F"}]  = "14";
    // State 10
    new_table[{10, "+"}] = "S6";
    new_table[{10, "-"}] = "S7";
    new_table[{10, ")"}] = "S15";
    // State 11
    new_table[{11, "+"}] = "R1";
    new_table[{11, "-"}] = "R1";
    new_table[{11, "*"}] = "S8";
    new_table[{11, "/"}] = "S9";
    new_table[{11, ")"}] = "R1";
    new_table[{11, "$"}] = "R1";
    // State 12
    new_table[{12, "+"}] = "R2";
    new_table[{12, "-"}] = "R2";
    new_table[{12, "*"}] = "S8";
    new_table[{12, "/"}] = "S9";
    new_table[{12, ")"}] = "R2";
    new_table[{12, "$"}] = "R2";
    // State 13
    new_table[{13, "+"}] = "R4";
    new_table[{13, "-"}] = "R4";
    new_table[{13, "*"}] = "R4";
    new_table[{13, "/"}] = "R4";
    new_table[{13, ")"}] = "R4";
    new_table[{13, "$"}] = "R4";
    // State 14
    new_table[{14, "+"}] = "R5";
    new_table[{14, "-"}] = "R5";
    new_table[{14, "*"}] = "R5";
    new_table[{14, "/"}] = "R5";
    new_table[{14, ")"}] = "R5";
    new_table[{14, "$"}] = "R5";
    // State 15
    new_table[{15, "+"}] = "R7";
    new_table[{15, "-"}] = "R7";
    new_table[{15, "*"}] = "R7";
    new_table[{15, "/"}] = "R7";
    new_table[{15, ")"}] = "R7";
    new_table[{15, "$"}] = "R7";

    return new_table;
}

// productions list
struct Production {
    std::string new_lhs;
    std::vector<std::string> new_rhs;
};

std::vector<Production> buildProductions() {
    std::vector<Production> new_productions;
    // E -> E + T
    // E -> E - T
    // E -> T
    // T -> t * F
    // T -> T / F
    // T -> F
    // T -> (E)
    // F -> id
    new_productions.push_back({"E", {"E", "+", "T"}});  
    new_productions.push_back({"E", {"E", "-", "T"}}); 
    new_productions.push_back({"E", {"T"}});              
    new_productions.push_back({"T", {"T", "*", "F"}});    
    new_productions.push_back({"T", {"T", "/", "F"}});    
    new_productions.push_back({"T", {"F"}});              
    new_productions.push_back({"F", {"(", "E", ")"}});    
    new_productions.push_back({"F", {"id"}});             
    return new_productions;
}

TreeNode* parseLine(const std::string &new_line,
                    const std::map<std::pair<int, std::string>, std::string> &new_parsingTable,
                    const std::vector<Production> &new_productions,
                    bool &new_success) {
    std::vector<std::string> new_tokens = tokenize(new_line);

    std::stack<int> new_stateStack;
    std::stack<TreeNode*> new_nodeStack;

    // state 0
    new_stateStack.push(0);
    size_t new_index = 0;
    new_success = true;

    while (true) {
        int new_currentState = new_stateStack.top();
        std::string new_currentToken = (new_index < new_tokens.size()) ? new_tokens[new_index] : "$";

        auto new_it = new_parsingTable.find({new_currentState, new_currentToken});
        if (new_it == new_parsingTable.end()) {
            new_success = false;
            return nullptr;
        }
        std::string new_action = new_it->second;

        if (new_action == "Acc") {
            if (!new_nodeStack.empty())
                return new_nodeStack.top();
            else {
                new_success = false;
                return nullptr;
            }
        }
        else if (!new_action.empty() && new_action[0] == 'S') {
            // Shift: get the next state
            int new_nextState = std::stoi(new_action.substr(1));
            TreeNode* new_terminalNode = new TreeNode(new_currentToken);
            new_nodeStack.push(new_terminalNode);
            new_stateStack.push(new_nextState);
            ++new_index;
        }
        else if (!new_action.empty() && new_action[0] == 'R') {
            // Reduce action
            int new_prodIndex = std::stoi(new_action.substr(1)) - 1;
            if (new_prodIndex < 0 || new_prodIndex >= (int)new_productions.size()) {
                new_success = false;
                return nullptr;
            }
            Production new_prod = new_productions[new_prodIndex];
            int new_rhsSize = (int)new_prod.new_rhs.size();

            // Pop node
            std::vector<TreeNode*> new_childrenNodes;
            for (int new_i = 0; new_i < new_rhsSize; ++new_i) {
                new_stateStack.pop();
                new_childrenNodes.push_back(new_nodeStack.top());
                new_nodeStack.pop();
            }
            // left-to-right order
            std::reverse(new_childrenNodes.begin(), new_childrenNodes.end());

            // Create a new TreeNode 
            TreeNode* new_lhsNode = new TreeNode(new_prod.new_lhs);
            // Attach children using add_child()
            for (TreeNode* child : new_childrenNodes) {
                new_lhsNode->add_child(child);
            }
            //  lookup for the LHS
            int new_topState = new_stateStack.top();
            auto new_gotoIt = new_parsingTable.find({new_topState, new_prod.new_lhs});
            if (new_gotoIt == new_parsingTable.end()) {
                new_success = false;
                return nullptr;
            }
            int new_gotoState = std::stoi(new_gotoIt->second);
            new_stateStack.push(new_gotoState);
            new_nodeStack.push(new_lhsNode);
        }
        else {
            new_success = false;
            return nullptr;
        }
    }
    new_success = false;
    return nullptr;
}

int main() {
    std::map<std::pair<int, std::string>, std::string> new_parsingTable = buildParsingTable();
    std::vector<Production> new_productions = buildProductions();

    std::string new_firstFileName;
    std::cout << "Enter file name: ";
    std::cin >> new_firstFileName;
    std::ifstream new_firstFile(new_firstFileName);
    if (!new_firstFile.is_open()) {
        std::cerr << "Error opening file: " << new_firstFileName << std::endl;
        return 1;
    }

    std::vector<std::string> new_firstFileOutputs;
    {
        std::string new_line;
        while (std::getline(new_firstFile, new_line)) {
            bool new_success;
            TreeNode* new_root = parseLine(new_line, new_parsingTable, new_productions, new_success);
            std::ostringstream new_outputStream;
            new_outputStream << "Input: " << new_line << "\n";
            if (new_success && new_root) {
                new_outputStream << "Parse Tree:\n";
                //  print  tree using printTree
                new_root->printTree();
            } else {
                new_outputStream << "Error: Invalid sentence.\n";
            }
            new_outputStream << "----------------------------------\n";
            new_firstFileOutputs.push_back(new_outputStream.str());

            // Free parse tree memory
            delete new_root;
        }
    }
    new_firstFile.close();

    std::string new_secondFileName;
    std::cout << "Second file name: ";
    std::cin >> new_secondFileName;
    std::ifstream new_secondFile(new_secondFileName);
    if (!new_secondFile.is_open()) {
        std::cerr << "Error opening file: " << new_secondFileName << std::endl;
        return 1;
    }

    std::vector<std::string> new_secondFileOutputs;
    {
        std::string new_line;
        while (std::getline(new_secondFile, new_line)) {
            bool new_success;
            TreeNode* new_root = parseLine(new_line, new_parsingTable, new_productions, new_success);
            std::ostringstream new_outputStream;
            new_outputStream << "Input: " << new_line << "\n";
            if (new_success && new_root) {
                new_outputStream << "Parse Tree:\n";
                new_root->printTree();
            } else {
                new_outputStream << "Error: Invalid sentence.\n";
            }
            new_outputStream << "----------------------------------\n";
            new_secondFileOutputs.push_back(new_outputStream.str());

            delete new_root;
        }
    }
    new_secondFile.close();

    /*std::cout << "\n\nTest case 1:\n";
    for (auto &new_res : new_firstFileOutputs)
        std::cout << new_res;

    std::cout << "\nTest case 2:\n";
    for (auto &new_res : new_secondFileOutputs)
        std::cout << new_res;
*/
    return 0;
}
