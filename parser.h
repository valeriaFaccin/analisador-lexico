#ifndef PARSER_H
#define PARSER_H

#include "tabela_slr.h"
#include "symbol_table.h"
#include <vector>
#include <string>
#include <stack>
#include <memory>

enum class TokenType {
    // Keywords
    DECLARE,
    BEGIN,
    END,
    IF,
    FOR,
    CALL,
    INT,
    
    // Variables and Numbers
    VAR,
    NUM,
    
    // Operators
    ASSIGN,     // =
    EQ,         // ==
    NE,         // !=
    LT,         // <
    GT,         // >
    PLUS,       // +
    MINUS,      // -
    MULT,       // *
    DIV,        // /
    
    // Punctuation
    SEMICOLON,  // ;
    LPAREN,     // (
    RPAREN,     // )
    COMMA,      // ,
    
    // Special
    END_OF_FILE,
    ERROR
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    std::string value;
    
    Token(TokenType t, const std::string& l, int ln) 
        : type(t), lexeme(l), line(ln) {}
};

struct ParseNode {
    std::string symbol;
    std::string value;
    std::vector<std::shared_ptr<ParseNode>> children;
    
    ParseNode(const std::string& s) : symbol(s) {}
};

class Parser {
private:
    std::vector<Token> tokens;
    std::stack<int> stateStack;
    std::stack<std::shared_ptr<ParseNode>> symbolStack;
    std::shared_ptr<SymbolTable> symbolTable;
    int currentTokenIndex;
    int currentLine;
    
    // Error handling
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // Semantic actions
    void semanticAction(int production);
    void handleVariableDeclaration(const std::string& varName, int line);
    void handleFunctionDeclaration(const std::string& funcName, 
                                 const std::vector<std::string>& params, int line);
    void handleVariableAssignment(const std::string& varName, int line);
    void handleFunctionCall(const std::string& funcName, int line);
    
    // Error reporting
    void reportError(const std::string& message, int line);
    void reportWarning(const std::string& message, int line);
    
    // Token conversion
    TokenType convertStateToToken(int state);
    std::string getTokenName(TokenType type);
    
public:
    Parser(std::shared_ptr<SymbolTable> st) 
        : symbolTable(st), currentTokenIndex(0), currentLine(1) {}
    
    // Main parsing functions
    bool parse(const std::vector<Token>& inputTokens);
    bool parseTokenStream(const std::string& tokenStream);
    
    // Error handling
    bool hasErrors() const { return !errors.empty(); }
    bool hasWarnings() const { return !warnings.empty(); }
    void printErrors() const;
    void printWarnings() const;
    
    // Symbol table access
    std::shared_ptr<SymbolTable> getSymbolTable() const { return symbolTable; }
    
    // Parse tree access
    std::shared_ptr<ParseNode> getParseTree() const;
    
    // Utility functions
    void reset();
    void printParseTree(const std::shared_ptr<ParseNode>& node, int depth = 0) const;
};

#endif // PARSER_H 