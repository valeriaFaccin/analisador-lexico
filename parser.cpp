#include "parser.h"
#include <iostream>
#include <sstream>
#include <algorithm>

TokenType Parser::convertStateToToken(int state) {
  
    switch (state) {
        case 1: return TokenType::VAR;      // Variable
        case 2: return TokenType::NUM;      // Number
        case 8: return TokenType::LT;       // <
        case 9: return TokenType::GT;       // >
        case 10: return TokenType::PLUS;    // +
        case 11: return TokenType::MINUS;   // -
        case 12: return TokenType::MULT;    // *
        case 13: return TokenType::DIV;     // /
        case 14: return TokenType::SEMICOLON; // ;
        case 15: return TokenType::ASSIGN;  // =
        case 16: return TokenType::NE;      // !=
        case 17: return TokenType::LPAREN;  // (
        case 18: return TokenType::RPAREN;  // )
        case 19: return TokenType::COMMA;   // ,
        case 24: return TokenType::IF;      // if
        case 25: return TokenType::INT;     // int
        case 26: return TokenType::EQ;      // ==
        case 28: return TokenType::END;     // end
        case 29: return TokenType::CALL;    // call
        case 30: return TokenType::DECLARE; // declare
        case 31: return TokenType::FOR;     // for
        case 32: return TokenType::BEGIN;   // begin
        default: return TokenType::ERROR;
    }
}

std::string Parser::getTokenName(TokenType type) {
    switch (type) {
        case TokenType::DECLARE: return "DECLARE";
        case TokenType::BEGIN: return "BEGIN";
        case TokenType::END: return "END";
        case TokenType::IF: return "IF";
        case TokenType::FOR: return "FOR";
        case TokenType::CALL: return "CALL";
        case TokenType::INT: return "INT";
        case TokenType::VAR: return "VAR";
        case TokenType::NUM: return "NUM";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::EQ: return "EQ";
        case TokenType::NE: return "NE";
        case TokenType::LT: return "LT";
        case TokenType::GT: return "GT";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULT: return "MULT";
        case TokenType::DIV: return "DIV";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::COMMA: return "COMMA";
        case TokenType::END_OF_FILE: return "EOF";
        case TokenType::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void Parser::reportError(const std::string& message, int line) {
    std::string errorMsg = "Error at line " + std::to_string(line) + ": " + message;
    errors.push_back(errorMsg);
}

void Parser::reportWarning(const std::string& message, int line) {
    std::string warningMsg = "Warning at line " + std::to_string(line) + ": " + message;
    warnings.push_back(warningMsg);
}

void Parser::printErrors() const {
    if (errors.empty()) {
        std::cout << "No errors found." << std::endl;
        return;
    }
    
    std::cout << "\n=== PARSING ERRORS ===" << std::endl;
    for (const auto& error : errors) {
        std::cout << error << std::endl;
    }
    std::cout << "=====================" << std::endl;
}

void Parser::printWarnings() const {
    if (warnings.empty()) {
        std::cout << "No warnings found." << std::endl;
        return;
    }
    
    std::cout << "\n=== PARSING WARNINGS ===" << std::endl;
    for (const auto& warning : warnings) {
        std::cout << warning << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

void Parser::semanticAction(int production) {
    switch (production) {
        case 1: // S' -> S
            break;
            
        case 2: // S -> DECLARATION
            break;
            
        case 3: // S -> C
            break;
            
        case 4: // DECLARATION -> declare VAR ( PARAMS ) BODY
            
            if (symbolStack.size() >= 6) {
                auto bodyNode = symbolStack.top(); symbolStack.pop();
                auto rparenNode = symbolStack.top(); symbolStack.pop();
                auto paramsNode = symbolStack.top(); symbolStack.pop();
                auto lparenNode = symbolStack.top(); symbolStack.pop();
                auto varNode = symbolStack.top(); symbolStack.pop();
                auto declareNode = symbolStack.top(); symbolStack.pop();
                
                   
                std::string funcName = varNode->value;
                std::vector<std::string> params;
                
                // Parse parameters (simplified)
                if (paramsNode->symbol == "VARLIST") {
                    // Extract parameters from VARLIST
                    // This is a simplified implementation
                }
                
                handleFunctionDeclaration(funcName, params, currentLine);
            }
            break;
            
        case 5: // C -> begin CMD end
            // Handle command block
            if (symbolStack.size() >= 3) {
                auto endNode = symbolStack.top(); symbolStack.pop();
                auto cmdNode = symbolStack.top(); symbolStack.pop();
                auto beginNode = symbolStack.top(); symbolStack.pop();
                
                // Enter new scope for command block
                symbolTable->enterScope();
            }
            break;
            
        case 6: // CMD -> VAR = EXPR ; CMD
            // Handle variable assignment
            if (symbolStack.size() >= 5) {
                auto cmdNode = symbolStack.top(); symbolStack.pop();
                auto semicolonNode = symbolStack.top(); symbolStack.pop();
                auto exprNode = symbolStack.top(); symbolStack.pop();
                auto assignNode = symbolStack.top(); symbolStack.pop();
                auto varNode = symbolStack.top(); symbolStack.pop();
                
                std::string varName = varNode->value;
                handleVariableAssignment(varName, currentLine);
            }
            break;
            
        case 7: // CMD -> if COND CMD
            // Handle if statement
            break;
            
        case 8: // CMD -> for COND CMD
            // Handle for loop
            break;
            
        case 9: // CMD -> call VAR ; CMD
            // Handle function call
            if (symbolStack.size() >= 5) {
                auto cmdNode = symbolStack.top(); symbolStack.pop();
                auto semicolonNode = symbolStack.top(); symbolStack.pop();
                auto varNode = symbolStack.top(); symbolStack.pop();
                auto callNode = symbolStack.top(); symbolStack.pop();
                
                std::string funcName = varNode->value;
                handleFunctionCall(funcName, currentLine);
            }
            break;
            
        case 10: // CMD -> ;
            // Handle empty command
            break;
            
        case 11: // VAR -> (a+e+i+o+u)+(a+e+i+o+u+0+1)*
            // Variable name recognized
            break;
            
        case 12: // NUM -> (0+1)+
            // Number recognized
            break;
            
        default:
            // Handle other productions
            break;
    }
}

void Parser::handleVariableDeclaration(const std::string& varName, int line) {
    if (!symbolTable->insertSymbol(varName, SymbolType::VARIABLE, DataType::INT, line)) {
        reportError("Variable '" + varName + "' already declared in current scope", line);
    }
}

void Parser::handleFunctionDeclaration(const std::string& funcName, 
                                     const std::vector<std::string>& params, int line) {
    if (!symbolTable->insertFunction(funcName, DataType::VOID, params, line)) {
        reportError("Function '" + funcName + "' already declared", line);
    }
}

void Parser::handleVariableAssignment(const std::string& varName, int line) {
    auto symbol = symbolTable->lookupSymbol(varName);
    if (!symbol) {
        reportError("Variable '" + varName + "' not declared", line);
    } else if (symbol->type != SymbolType::VARIABLE) {
        reportError("'" + varName + "' is not a variable", line);
    }
}

void Parser::handleFunctionCall(const std::string& funcName, int line) {
    auto symbol = symbolTable->lookupSymbol(funcName);
    if (!symbol) {
        reportError("Function '" + funcName + "' not declared", line);
    } else if (symbol->type != SymbolType::FUNCTION) {
        reportError("'" + funcName + "' is not a function", line);
    }
}

bool Parser::parse(const std::vector<Token>& inputTokens) {
    tokens = inputTokens;
    reset();
    
    // Initialize stacks
    stateStack.push(0);
    
    while (currentTokenIndex < tokens.size()) {
        int currentState = stateStack.top();
        Token currentToken = tokens[currentTokenIndex];
        
        // Get goto transition
        int nextState = getSLRTable()->getGoto(currentState, getTokenName(currentToken.type));
        
        if (nextState != -1) {
            // Shift action
            stateStack.push(nextState);
            
            // Create parse node for token
            auto node = std::make_shared<ParseNode>(getTokenName(currentToken.type));
            node->value = currentToken.lexeme;
            symbolStack.push(node);
            
            currentTokenIndex++;
            currentLine = currentToken.line;
        } else {
            // Check for reduce action
            bool reduced = false;
            auto state = getSLRTable()->getState(currentState);
            
            if (state) {
                // Check if any production can be reduced
                // This is a simplified implementation
                // In a full implementation, you would check the follow sets
                
                // For now, we'll implement a basic reduce mechanism
                if (currentState == 1) { // Accept state
                    return true;
                }
            }
            
            if (!reduced) {
                // Error - no valid action
                std::string expected = "Unexpected token '" + currentToken.lexeme + "'";
                reportError(expected, currentToken.line);
                return false;
            }
        }
    }
    
    return true;
}

bool Parser::parseTokenStream(const std::string& tokenStream) {
    // Convert token stream string to tokens
    std::vector<Token> tokens;
    std::istringstream iss(tokenStream);
    std::string token;
    int line = 1;
    
    while (iss >> token) {
        try {
            int state = std::stoi(token);
            TokenType type = convertStateToToken(state);
            tokens.emplace_back(type, token, line);
        } catch (const std::exception& e) {
            reportError("Invalid token: " + token, line);
            return false;
        }
    }
    
    return parse(tokens);
}

std::shared_ptr<ParseNode> Parser::getParseTree() const {
    if (symbolStack.empty()) {
        return nullptr;
    }
    return symbolStack.top();
}

void Parser::reset() {
    while (!stateStack.empty()) stateStack.pop();
    while (!symbolStack.empty()) symbolStack.pop();
    currentTokenIndex = 0;
    currentLine = 1;
    errors.clear();
    warnings.clear();
}

void Parser::printParseTree(const std::shared_ptr<ParseNode>& node, int depth) const {
    if (!node) return;
    
    std::string indent(depth * 2, ' ');
    std::cout << indent << node->symbol;
    if (!node->value.empty()) {
        std::cout << " (" << node->value << ")";
    }
    std::cout << std::endl;
    
    for (const auto& child : node->children) {
        printParseTree(child, depth + 1);
    }
} 