#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using namespace std;

//build a parsing table, we should translate the table found in the instructions into here

//Format the output to print a syntax tree

//Tokenizing functions vector
std::vector<std::string> tokenize(const std::string &new_line) 
{
    std::vector<std::string> new_tokens;

    //Tokenizing functions by looking at +,-,*, id, etc.

    for(size_t new_i = 0; new_i < new_line.size(); ++new_i) 
    {
        char new_char = new_line[new_i];
        if (std::isspace(new_char)) 
        {
            continue;
        } 
        else if (
            new_char == '+' || new_char == '-' || new_char == '*' || new_char == '/' ||
            new_char == '(' || new_char == ')') 
            {
                new_tokens.push_back(std::string(1, new_char));
            } 
            else if (std::isalpha(new_char)) 
            {
                new_tokens.push_back("id");
            } 
            else 
            {
                continue;
            }
        new_tokens.push_back("$");
        return new_tokens;
    }
}

//Function of shift reducing / parsing line by line

int main() {
    std::string new_firstFileName;
    std::cout << "Enter file name: ";
    std:cin >> new_firstFileName;

    std::ifstream new_firstFileName;(new_firstFileName);
    if (!new_firstFileName.is_open()) {
        std::cerr << "Error: Cannot open file! Try again." << std::endl;
        return 1;
    }

    //read second file
    return 0;
}