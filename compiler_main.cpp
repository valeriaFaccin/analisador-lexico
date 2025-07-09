#include "transicoes.h"
#include "tabela_slr.h"
#include "symbol_table.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <memory>

using namespace std;


struct TokenInfo {
    int state;
    string lexeme;
    int line;
    
    TokenInfo(int s, const string& l, int ln) : state(s), lexeme(l), line(ln) {}
};

class Compiler {
private:
    shared_ptr<SymbolTable> symbolTable;
    shared_ptr<Parser> parser;
    
    
    set<int> finalStates = {1, 2, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 24, 25, 26, 28, 29, 30, 31, 32};
    
public:
    Compiler() {
        symbolTable = make_shared<SymbolTable>();
        parser = make_shared<Parser>(symbolTable);
    }
    
    
    vector<TokenInfo> lexicalAnalysis(const string& input) {
        vector<TokenInfo> tokens;
        int state = 0;
        string currentLexeme = "";
        int line = 1;
        
        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];
            
            
            if (c == '\n') {
                line++;
                continue;
            }
            
            
            if (c == ' ' || c == '\t') {
                if (!currentLexeme.empty() && finalStates.find(state) != finalStates.end()) {
                    tokens.emplace_back(state, currentLexeme, line);
                    currentLexeme = "";
                    state = 0;
                }
                continue;
            }
            
            
            int nextState = -1;
            if (transicoes[state].find(c) != transicoes[state].end()) {
                nextState = transicoes[state][c];
            }
            
            if (nextState != -1) {
                state = nextState;
                currentLexeme += c;
            } else {
                
                if (!currentLexeme.empty() && finalStates.find(state) != finalStates.end()) {
                    tokens.emplace_back(state, currentLexeme, line);
                    currentLexeme = "";
                    state = 0;
                    i--; // Retry current character
                } else {
                    cout << "Error: Invalid character '" << c << "' at line " << line << endl;
                    return tokens;
                }
            }
        }
        
        
        if (!currentLexeme.empty() && finalStates.find(state) != finalStates.end()) {
            tokens.emplace_back(state, currentLexeme, line);
        }
        
        return tokens;
    }
    
    
    vector<Token> convertTokens(const vector<TokenInfo>& lexTokens) {
        vector<Token> parserTokens;
        
        for (const auto& lexToken : lexTokens) {
            TokenType type = parser->convertStateToToken(lexToken.state);
            Token token(type, lexToken.lexeme, lexToken.line);
            parserTokens.push_back(token);
        }
        
        return parserTokens;
    }
    
    
    bool compile(const string& input) {
        cout << "=== COMPILER PIPELINE ===" << endl;
        cout << "Input: " << input << endl;
        
        
        cout << "\n--- LEXICAL ANALYSIS ---" << endl;
        auto lexTokens = lexicalAnalysis(input);
        
        cout << "Tokens found:" << endl;
        for (const auto& token : lexTokens) {
            cout << "  State " << token.state << ": '" << token.lexeme << "' at line " << token.line << endl;
        }
        
        if (lexTokens.empty()) {
            cout << "No valid tokens found!" << endl;
            return false;
        }
        

        cout << "\n--- TOKEN CONVERSION ---" << endl;
        auto parserTokens = convertTokens(lexTokens);
        
        cout << "Converted tokens:" << endl;
        for (const auto& token : parserTokens) {
            cout << "  " << parser->getTokenName(token.type) << ": '" << token.lexeme << "' at line " << token.line << endl;
        }
        
        
        cout << "\n--- SYNTAX ANALYSIS ---" << endl;
        bool parseSuccess = parser->parse(parserTokens);
        
        if (parseSuccess) {
            cout << "✓ Parsing successful!" << endl;
        } else {
            cout << "✗ Parsing failed!" << endl;
        }
        
        
        if (parser->hasErrors()) {
            parser->printErrors();
        }
        
        if (parser->hasWarnings()) {
            parser->printWarnings();
        }
        
        
        cout << "\n--- SYMBOL TABLE ---" << endl;
        symbolTable->printSymbolTable();
        
        
        cout << "\n--- PARSE TREE ---" << endl;
        auto parseTree = parser->getParseTree();
        if (parseTree) {
            parser->printParseTree(parseTree);
        } else {
            cout << "No parse tree generated." << endl;
        }
        
        cout << "\n=== COMPILATION " << (parseSuccess ? "SUCCESSFUL" : "FAILED") << " ===" << endl;
        
        return parseSuccess;
    }
    
    
    void runTests() {
        cout << "Running compiler tests..." << endl;
        
        
        cout << "\n\nTEST 1: Variable Assignment" << endl;
        compile("abc = 101;");
        
        
        cout << "\n\nTEST 2: Function Declaration" << endl;
        compile("declare func(a, b) int x; begin x = 1; end");
        
        
        cout << "\n\nTEST 3: If Statement" << endl;
        compile("if a < b begin x = 1; end");
        
        
        cout << "\n\nTEST 4: For Loop" << endl;
        compile("for a > b begin call func; end");
        
        
        cout << "\n\nTEST 5: Invalid Input" << endl;
        compile("xyz = 123;"); // Invalid variable name
    }
};

int main() {
    Compiler compiler;
    
    compiler.runTests();
    
    
    cout << "\n\n=== INTERACTIVE MODE ===" << endl;
    cout << "Enter your program (type 'quit' to exit):" << endl;
    
    string input;
    while (true) {
        cout << "\n> ";
        getline(cin, input);
        
        if (input == "quit" || input == "exit") {
            break;
        }
        
        if (!input.empty()) {
            compiler.compile(input);
        }
    }
    
    cout << "Goodbye!" << endl;
    return 0;
} 