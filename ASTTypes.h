#pragma once

#include <string>
#include <vector>
#include <variant>

struct SemanticActions {
    std::string name;
    std::vector<std::string> cods;
};

struct Lex
{
    std::string digVal;
};

using Node = std::variant<SemanticActions, Lex>;