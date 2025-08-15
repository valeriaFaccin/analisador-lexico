#pragma once

#include <stack>
#include "ASTTypes.h"


class AbstractSyntaxTree
{    
public:
    AbstractSyntaxTree();

    void MakeLeaf(Lex& lex);
    void MakeNode(int state);
    void printResult();
    void printEstado();
private:
    int temp;
    std::stack<Node> AST;

    std::string genTemp();

    template<typename... Strings>
    std::string genCode(Strings... strings) {
        std::string result;
        ((result += strings), ...);  // concatenates all arguments
        return result;
    }
};

